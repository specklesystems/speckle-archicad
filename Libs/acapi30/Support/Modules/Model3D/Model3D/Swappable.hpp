#if !defined(SWAPPABLE_HPP)
#define SWAPPABLE_HPP

#pragma once

#include "Model3DExport.h"
#include "Lock.hpp"
#include "Condition.hpp"


class TaskState;

class MODEL3D_DLL_EXPORT Swappable {
	friend class SwapQueue;
	friend class ProcessSwapQueue;

	enum TaskStateEnum : UInt32 {
		InMemory,
		Pending,
		Started,
		Swapped,
		Destroyed
	};

	volatile TaskStateEnum state;
	GS::Lock stateLock;
	GS::Condition finishedCond;

protected:
	virtual void Purge		() = 0;
	virtual void ReadPurged () = 0;
	virtual void ReInitImp	() = 0;

	void AboutToDestroy ();

public:
	Swappable ();
	virtual ~Swappable();

	void SwapToDisk ();
	void RestoreFromDisk () const;
	void ReInit ();
};


void MODEL3D_DLL_EXPORT InitSwapQueue ();
void MODEL3D_DLL_EXPORT TerminateSwapQueue ();


#endif