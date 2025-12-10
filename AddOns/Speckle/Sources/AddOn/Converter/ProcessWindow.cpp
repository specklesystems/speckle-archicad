#pragma once

#include "ProcessWindow.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

ProcessWindow::ProcessWindow()
{
	time = std::chrono::high_resolution_clock::now();
}

void ProcessWindow::Init(const std::string& title, int phaseCount)
{
	Int32 nPhase = phaseCount;
	auto windowTitle = GS::UniString(title.c_str());
	API_ProcessControlTypeID pcType = API_MenuCommandEnabled;
	CHECK_ERROR(ACAPI_ProcessWindow_InitProcessWindow(&windowTitle, &nPhase, &pcType));
	TIWait(0.05);
}

void ProcessWindow::SetNextProcessPhase(const std::string& title, int phaseCount)
{	
	Int32 nPhase = phaseCount;
	auto windowTitle = GS::UniString(title.c_str());
	bool showPercent = true;
	CHECK_ERROR(ACAPI_ProcessWindow_SetNextProcessPhase(&windowTitle, &nPhase, &showPercent));
	TIWait(0.05);
}

void ProcessWindow::SetProcessValue(int value) 
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - time).count();
	if (elapsedTime > 20)
	{
		Int32 newval = value;
		CHECK_ERROR(ACAPI_ProcessWindow_SetProcessValue(&newval));
		//TIWait(0.001);
		time = std::chrono::high_resolution_clock::now();
	}
}

bool ProcessWindow::IsProcessCanceled() 
{
	return ACAPI_ProcessWindow_IsProcessCanceled() == APIERR_CANCEL;
}

void ProcessWindow::Close() 
{
	CHECK_ERROR(ACAPI_ProcessWindow_CloseProcessWindow());
}
