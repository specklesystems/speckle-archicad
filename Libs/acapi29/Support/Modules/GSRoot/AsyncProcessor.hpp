#pragma once

#ifndef ASYNCPROCESSOR_HPP
#define ASYNCPROCESSOR_HPP


#include "PooledExecutor.hpp"
#include "BlockingQueue.hpp"
#include "Lock.hpp"
#include "Optional.hpp"
#include "Array.hpp"
#include "Owner.hpp"

#ifdef CHECKED_VERSION
#include "Thread.hpp"
#endif

#include <atomic>


template <typename DataType, USize PackSize>
class Packer
{
	GS_DEBUG_ONLY (GS::IntPtr threadId = 0);
public:
	static constexpr USize PackageSize = PackSize;
	using PackageType = GS::Array<DataType>;

public:
	Packer (const std::function<void (PackageType&&)>& output) :
		output (output),
		data (PackSize)
	{
	}

	~Packer ()
	{
		DBASSERT (data.IsEmpty ());
	}

	void Add (const DataType& i)
	{
		GS_DEBUG_ONLY (if (threadId == 0) threadId = GS::Thread::GetCurrentThreadId ());
		DBASSERT (threadId == GS::Thread::GetCurrentThreadId ());

		FlushIfLimitReached ();

		data.Push (i);
	}

	void Add (DataType&& i)
	{
		GS_DEBUG_ONLY (if (threadId == 0) threadId = GS::Thread::GetCurrentThreadId ());
		DBASSERT (threadId == GS::Thread::GetCurrentThreadId ());

		FlushIfLimitReached ();

		data.Push (std::move (i));
	}

	void Finish ()
	{
		Flush ();
	}

private:
	void FlushIfLimitReached ()
	{
		if (data.GetSize () == PackageSize) {
			Flush ();
		}
	}

	void Flush ()
	{
		if (!data.IsEmpty ()) {
			output (std::move (data));
			data.Clear ();
			data.SetCapacity (PackSize);
		}
	}

	const std::function<void (PackageType&&)>	output;
	PackageType									data;
};


enum class CallOutput
{
	InTheSameThread,
	InSeparateThread,
	InMultipleThreads
};


template <typename InputDataType, USize PackageSize = 1, typename OutputDataType = InputDataType, USize OutputPackageSize = PackageSize>
class AsyncProcessor
{
public:
	template <typename ProcessorFnType>
	AsyncProcessor (const ProcessorFnType& processorFn,
					const std::function<void (OutputDataType&&)>& output,
					CallOutput callOutput = CallOutput::InTheSameThread,
					UInt32 threadNum = 1, GS::Executor* executor = nullptr):
		executorInstance (executor == nullptr ? GS::NewOwned<GS::PooledExecutor> (1, (callOutput == CallOutput::InSeparateThread) ? threadNum + 1 : threadNum) : GS::Owner<GS::PooledExecutor> ()),
		impl (new Impl (processorFn, output, callOutput, threadNum, executor != nullptr ? *executor : *executorInstance))
	{
	}

	~AsyncProcessor ()
	{
		delete impl;
	}

	void Add (const InputDataType& i)
	{
		impl->Add (i);
	}

	void Add (InputDataType&& i)
	{
		impl->Add (std::move (i));
	}

	void Finish ()
	{
		impl->Finish ();
	}

private:
	class Impl
	{
		using InputPackageType = typename Packer<InputDataType, PackageSize>::PackageType;
		using OutputPackageType = typename Packer<OutputDataType, PackageSize>::PackageType;
	public:
		template <typename ProcessorFnType>
		Impl (const ProcessorFnType& processorFn,
			  const std::function<void (OutputDataType&&)>& output,
			  CallOutput callOutput,
			  UInt32 threadNum,
			  GS::Executor& executor) :
			output (output),
			callOutput (callOutput),
			threadNum (threadNum),
			packer ([&](auto&& package) {
				ScheduleInputPackage<ProcessorFnType> (std::move (package));
			}),
			executor (executor),
			scheduledInputs (0),
			scheduledOutputs (0),
			runningInputProcessors (0),
			finishedPhase1 (false)
		{
			firstProcessor = CreateProcessor (inputPackages, processorFn);

			synchronized (lockForExecutor) {
				executor.Execute (firstProcessor);

				if (callOutput == CallOutput::InSeparateThread) {
					executor.Execute (CreateOutput ());
				}
			}
		}

		void Add (const InputDataType& i)
		{
			packer.Add (i);
		}

		void Add (InputDataType&& i)
		{
			packer.Add (std::move (i));
		}

		void Finish ()
		{
			packer.Finish ();

			finishedPhase1 = true;
			if (scheduledInputs == 0) {
				inputPackages.Push (InputPackageType ());
			}
			executor.Wait ();
			if (callOutput == CallOutput::InTheSameThread) {
				CreateOutput ()->Run ();
			}
		}

	private:
		template <typename ProcessorFnType>
		GS::Runnable* CreateProcessor (GS::BlockingQueue<InputPackageType>&	inputPackages,
									   const ProcessorFnType&				processorFn)
		{
			++runningInputProcessors;

			if (callOutput == CallOutput::InMultipleThreads) {
				return new DirectOutputProcessor<InputPackageType, ProcessorFnType> (
					inputPackages,
					processorFn,
					output,
					scheduledInputs,
					[&finishedPhase1 = finishedPhase1]() { return finishedPhase1.load (); },
					[&runningInputProcessors = runningInputProcessors]() {--runningInputProcessors; },
					[this]() { StartNewProcessorIfNeeded<ProcessorFnType> (); });
			} else {
				return new QueueOutputProcessor<ProcessorFnType> (
					inputPackages,
					processorFn,
					outputPackages,
					scheduledInputs,
					scheduledOutputs,
					[&finishedPhase1 = finishedPhase1]() { return finishedPhase1.load (); },
					[&runningInputProcessors = runningInputProcessors, &outputPackages = outputPackages]() {
						if (--runningInputProcessors == 0)
							outputPackages.Push (OutputPackageType ());
					}, [this]() { StartNewProcessorIfNeeded<ProcessorFnType> (); });
			}
		}

		GS::RunnableTask CreateOutput ()
		{
			return CreateOutputImpl ([](auto&& data, const std::function<void (OutputDataType&&)>&) { return std::move (data); });
		}

		template <typename ProcessorFnType>
		GS::RunnableTask CreateOutputImpl (const ProcessorFnType& processorFn)
		{
			return new DirectOutputProcessor<OutputPackageType, ProcessorFnType> (
				outputPackages,
				processorFn,
				output,
				scheduledOutputs,
				[&runningInputProcessors = runningInputProcessors]() { return runningInputProcessors == 0; },
				[]() { return; }, []() { return; });
		}

		template <typename ProcessorFnType>
		void StartNewProcessorIfNeeded ()
		{
			if (runningInputProcessors < threadNum && inputPackages.GetSize () > 1) {
				synchronized (lockForExecutor) {
					++runningInputProcessors;
					executor.Execute (static_cast<Processor<ProcessorFnType, InputPackageType>*>(&*firstProcessor)->Clone ());
				}
			}
		}

		template <typename ProcessorFnType>
		void ScheduleInputPackage (InputPackageType&& package)
		{
			scheduledInputs += package.GetSize ();
			inputPackages.Push (std::move (package));
			StartNewProcessorIfNeeded<ProcessorFnType> ();
		}

		template <typename ProcessorFnType, typename PackageType>
		class Processor : public GS::Runnable {
		protected:
			Processor (GS::BlockingQueue<PackageType>&	inputPackages,
					   const ProcessorFnType&			processorFn,
					   std::atomic_uint&				scheduledInputs,
					   const std::function<bool ()>&	isFinished,
					   const std::function<void ()>&	onFinished,
					   const std::function<void ()>&	startNewProcessorIfNeeded) :
				processorFn (processorFn),
				inputPackages (inputPackages),
				scheduledInputs (scheduledInputs),
				isFinished (isFinished),
				onFinished (onFinished),
				startNewProcessorIfNeeded (startNewProcessorIfNeeded)
			{
			}

			Processor (const Processor& other) :
				processorFn (other.processorFn),
				inputPackages (other.inputPackages),
				scheduledInputs (other.scheduledInputs),
				isFinished (other.isFinished),
				onFinished (other.onFinished),
				startNewProcessorIfNeeded (other.startNewProcessorIfNeeded)
			{
			}

		public:
			virtual GS::RunnableTask Clone ()
			{
				return nullptr;
			}

		private:
			virtual void Run () override
			{
				PackageType localPackage;
				for (;;) {
					PackageType package;
					if (localPackage.GetSize () == 0) {
						inputPackages.Pop (&package);
						if (package.IsEmpty ()) {
							Close ();
							return;
						}
					} else {
						package = PackageType (std::move (localPackage));
						localPackage = PackageType ();
					}

					for (UIndex i = 0; i < package.GetSize (); ++i) {
						Return (processorFn (std::move (package[i]),
											 [&localPackage,
											 &inputPackages = inputPackages,
											 &scheduledInputs = scheduledInputs,
											 &startNewProcessorIfNeeded = startNewProcessorIfNeeded](auto&& elem) {
												localPackage.Push (std::move (elem));
												++scheduledInputs;
												if (localPackage.GetSize () > PackageSize) {
													inputPackages.Push (std::move (localPackage));
													startNewProcessorIfNeeded ();
													localPackage = PackageType ();
												}
											 }));
						--scheduledInputs;
						if (isFinished () && scheduledInputs == 0) {
							inputPackages.Push (PackageType ());
						}
					}
				}
			}

			virtual void Return (OutputDataType&& result) = 0;
			virtual void Finish () {}

			void Close ()
			{
				Finish ();
				inputPackages.Push (PackageType ());
				onFinished ();
			}

			void Return (GS::Optional<OutputDataType>&& result)
			{
				if (result.HasValue ()) {
					Return (std::move (result.Get ()));
				}
			}

			void Return (GS::Array<OutputDataType>&& results)
			{
				for (UIndex i = 0; i < results.GetSize (); ++i) {
					Return (std::move (results[i]));
				}
			}

			const ProcessorFnType			processorFn;
			GS::BlockingQueue<PackageType>&	inputPackages;
			std::atomic_uint&				scheduledInputs;
			const std::function<bool ()>	isFinished;
			const std::function<void ()>	onFinished;
			const std::function<void ()>	startNewProcessorIfNeeded;
		};

		template <typename PackageType, typename ProcessorFnType>
		class DirectOutputProcessor : public Processor<ProcessorFnType, PackageType> {
		public:
			DirectOutputProcessor (GS::BlockingQueue<PackageType>&					inputPackages,
								   const ProcessorFnType&							processorFn,
								   const std::function<void (OutputDataType&&)>&	output,
								   std::atomic_uint&								scheduledInputs,
								   const std::function<bool ()>&					isFinished,
								   const std::function<void ()>&					onFinished,
								   const std::function<void ()>&					startNewProcessorIfNeeded) :
				Processor<ProcessorFnType, PackageType> (inputPackages, processorFn, scheduledInputs, isFinished, onFinished, startNewProcessorIfNeeded),
				output (output)
			{
			}

			DirectOutputProcessor (const DirectOutputProcessor& other) :
				Processor<ProcessorFnType, PackageType> (other), output (other.output)
			{
			}

			virtual void Return (OutputDataType&& result) override
			{
				output (std::move (result));
			}

			virtual GS::RunnableTask Clone () override
			{
				return new DirectOutputProcessor (*this);
			}

			const std::function<void (OutputDataType&&)>	output;
		};

		template <typename ProcessorFnType>
		class QueueOutputProcessor : public Processor<ProcessorFnType, InputPackageType> {
		public:
			QueueOutputProcessor (GS::BlockingQueue<InputPackageType>&	inputPackages,
								  const ProcessorFnType&				processorFn,
								  GS::BlockingQueue<OutputPackageType>&	outputPackages,
								  std::atomic_uint&						scheduledInputs,
								  std::atomic_uint&						scheduledOutputs,
								  const std::function<bool ()>&			isFinished,
								  const std::function<void ()>&			onFinished,
								  const std::function<void ()>&			startNewProcessorIfNeeded) :
				Processor<ProcessorFnType, InputPackageType> (inputPackages, processorFn, scheduledInputs, isFinished, onFinished, startNewProcessorIfNeeded),
				outputPackages (outputPackages),
				scheduledOutputs (scheduledOutputs),
				packer ([&](auto&& package) {
				++scheduledOutputs;
				outputPackages.Push (std::move (package));
			})
			{
			}

			QueueOutputProcessor (const QueueOutputProcessor& other) :
				Processor<ProcessorFnType, InputPackageType> (other),
				outputPackages (other.outputPackages),
				scheduledOutputs (other.scheduledOutputs),
				packer ([&](auto&& package) {
					++scheduledOutputs;
					outputPackages.Push (std::move (package));
				})
			{
			}

			virtual GS::RunnableTask Clone () override
			{
				return new QueueOutputProcessor (*this);
			}

			virtual void Return (OutputDataType&& result) override
			{
				packer.Add (std::move (result));
			}

			virtual void Finish () override
			{
				packer.Finish ();
			}

			GS::BlockingQueue<OutputPackageType>&		outputPackages;
			std::atomic_uint&							scheduledOutputs;
			Packer<OutputDataType, OutputPackageSize>	packer;
		};

		const std::function<void (OutputDataType&&)>	output;
		const CallOutput								callOutput;
		const UInt32									threadNum;
		Packer<InputDataType, PackageSize>				packer;
		GS::Executor&									executor;
		GS::Lock										lockForExecutor;
		GS::RunnableTask								firstProcessor;
		GS::BlockingQueue<InputPackageType>				inputPackages;
		GS::BlockingQueue<OutputPackageType>			outputPackages;
		std::atomic_uint								scheduledInputs;
		std::atomic_uint								scheduledOutputs;
		std::atomic_uint								runningInputProcessors;
		std::atomic_bool								finishedPhase1;
	};

	GS::Owner<GS::PooledExecutor>	executorInstance;
	Impl*							impl = 0;
};


#endif
