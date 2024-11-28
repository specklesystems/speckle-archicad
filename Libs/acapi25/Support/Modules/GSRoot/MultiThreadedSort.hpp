// *****************************************************************************
//
// SG compatible
//
// *****************************************************************************

#ifndef MULTITHREADEDSORT_HPP
#define MULTITHREADEDSORT_HPP


// --------------------------------- Includes ----------------------------------

#include "PagedArray.hpp"
#include "Algorithms.hpp"
#include "Runnable.hpp"
#include "Thread.hpp"
#include "BlockingQueue.hpp"
#include "System.hpp"


// -------------------------------- Definitions --------------------------------

namespace GS {

template<typename T, typename BinPred>
void MultiThreadedSort (GS::PagedArray<T>& arrayToSort, BinPred pred, USize threadsToUse = 0);


// -------------------------------- Implementation -----------------------------

template<typename T, typename BinPred>
class ThreadData
{
private:
	class RunnableInterface: public GS::Runnable
	{
	private:
		ThreadData& threadData;

	private:
		virtual void	Run () override
		{
			threadData.DoInThread ();
		}

	private:
		RunnableInterface (const RunnableInterface&);				// disable
		RunnableInterface& operator= (const RunnableInterface&);	// disable

	public:
		RunnableInterface (ThreadData& threadData):
			threadData (threadData)
		{
		}
	};

private:
	GS::Thread*							thread;
	GS::BlockingQueue<ThreadData*>&		queue;
	const GS::PagedArray<T>&			sourceArray;
	const UIndex						firstIndex;
	const UIndex						lastIndex;
	BinPred								pred;

public:
	GS::PagedArray<T>					resultArray;

private:
	ThreadData (const ThreadData&);				// disable
	ThreadData& operator= (const ThreadData&);	// disable

private:
	void	DoInThread ()
	{
		for (UIndex i = firstIndex; i < lastIndex; ++i) {
			resultArray.Push (sourceArray[i]);
		}

		if (resultArray.GetSize () > 1) {
			GS::StableSort (resultArray.Begin (), resultArray.End (), pred);
		}

		queue.Push (this);
	}

public:
	ThreadData (GS::BlockingQueue<ThreadData*>&	queue, const GS::PagedArray<T>& sourceArray, UIndex firstIndex, const UIndex lastIndex, BinPred pred):
		queue (queue),
		sourceArray (sourceArray),
		firstIndex (firstIndex),
		lastIndex (lastIndex),
		resultArray (),
		pred (pred)
	{
		thread = new GS::Thread (new RunnableInterface (*this), "MultiThreadedSortThread");
		thread->Start ();
	}

	~ThreadData ()
	{
		thread->Join ();
		delete thread;
	}
};


template<typename T, typename BinPred>
void MultiThreadedSort (GS::PagedArray<T>& arrayToSort, BinPred pred, USize threadsToUse)
{
	class ArrayMerger
	{
	public:
		static void	Do (const GS::PagedArray<T>& first, const GS::PagedArray<T>& second, BinPred pred, GS::PagedArray<T>& result)
		{
			const USize firstSize = first.GetSize ();
			const USize secondSize = second.GetSize ();

			GS::PagedArray<T> merged;

			UIndex firstIndex = 0;
			UIndex secondIndex = 0;

			while (firstIndex < firstSize && secondIndex < secondSize) {
				if (pred (first[firstIndex], second[secondIndex])) {
					merged.Push (first[firstIndex++]);
				} else {
					merged.Push (second[secondIndex++]);
				}
			}
			while (firstIndex < firstSize) {
				merged.Push (first[firstIndex++]);
			}
			while (secondIndex < secondSize) {
				merged.Push (second[secondIndex++]);
			}

			result = merged;
		}
	};

	if (threadsToUse == 0) {
		if (arrayToSort.GetSize () < 10000) {
			threadsToUse = 1;
		} else {
			threadsToUse = GS::System::GetNumberOfActiveProcessors ();
		}
	}

	const USize arraySize = arrayToSort.GetSize ();

	if (threadsToUse > 1) {
		GS::BlockingQueue<ThreadData<T, BinPred>*> queue;

		{
			const USize threadDataSize = arraySize / threadsToUse;
			UIndex rangeBegin = 0;
			for (UIndex i = 0; i < threadsToUse - 1; ++i) {
				new ThreadData<T, BinPred> (queue, arrayToSort, rangeBegin, rangeBegin + threadDataSize, pred);
				rangeBegin += threadDataSize;
			}
			new ThreadData<T, BinPred> (queue, arrayToSort, rangeBegin, arraySize, pred);
		}

		GS::PagedArray<T> sortedArray;

		for (UIndex i = 0; i < threadsToUse; ++i) {
			ThreadData<T, BinPred>* threadData = queue.Pop ();
			ArrayMerger::Do (sortedArray, threadData->resultArray, pred, sortedArray);
			delete threadData;
		}

		DBASSERT (arrayToSort.GetSize () == sortedArray.GetSize ());

		arrayToSort = sortedArray;
	} else if (arrayToSort.GetSize () > 1) {
		GS::StableSort (arrayToSort.Begin (), arrayToSort.End (), pred);
	}
}

} // namespace GS

#endif
