#pragma once

#include "ProcessWindow.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"


static GSErrCode ProcessWindow_InitProcessWindow(const GS::UniString* title = nullptr, Int32* nPhase = nullptr, API_ProcessControlTypeID* processCntrolType = nullptr)
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_ProcessWindow_InitProcessWindow(title, nPhase, processCntrolType);
#elif defined(AC27)
	err = ACAPI_ProcessWindow_InitProcessWindow(title, nPhase, processCntrolType);
#elif defined(AC26)
	err = ACAPI_Interface(APIIo_InitProcessWindowID, title, nPhase);
#endif

	return err;
}

static GSErrCode ProcessWindow_SetNextProcessPhase(const GS::UniString* subtitle, Int32* maxval, bool* showPercent = nullptr)
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_ProcessWindow_SetNextProcessPhase(subtitle, maxval, showPercent);
#elif defined(AC27)
	err = ACAPI_ProcessWindow_SetNextProcessPhase(subtitle, maxval, showPercent);
#elif defined(AC26)
	err = ACAPI_Interface(APIIo_SetNextProcessPhaseID, subtitle, maxval);
#endif

	return err;
}

static GSErrCode ProcessWindow_SetProcessValue(Int32* newval)
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_ProcessWindow_SetProcessValue(newval);
#elif defined(AC27)
	err = ACAPI_ProcessWindow_SetProcessValue(newval);
#elif defined(AC26)
	err = ACAPI_Interface(APIIo_SetProcessValue, newval);
#endif

	return err;
}

static GSErrCode ProcessWindow_CloseProcessWindow()
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_ProcessWindow_CloseProcessWindow();
#elif defined(AC27)
	err = ACAPI_ProcessWindow_CloseProcessWindow();
#elif defined(AC26)
	err = ACAPI_Interface(APIIo_CloseProcessWindowID, nullptr, nullptr);
#endif

	return err;
}

static bool ProcessWindow_IsProcessCanceled()
{
#if defined(AC28)
	return (ACAPI_ProcessWindow_IsProcessCanceled() == APIERR_CANCEL);
#elif defined(AC27)
	return (ACAPI_ProcessWindow_IsProcessCanceled() == APIERR_CANCEL);
#elif defined(AC26)
	return ACAPI_Interface(APIIo_IsProcessCanceledID, nullptr, nullptr);
#endif
}

void ProcessWindow::Init(const std::string& title, int phaseCount)
{
	Int32 nPhase = phaseCount;
	auto windowTitle = GS::UniString(title.c_str());
	API_ProcessControlTypeID pcType = API_MenuCommandEnabled;
	CHECK_ERROR(ProcessWindow_InitProcessWindow(&windowTitle, &nPhase, &pcType));
	TIWait(1.00);
}

void ProcessWindow::SetNextProcessPhase(const std::string& title, int phaseCount)
{
	Int32 nPhase = phaseCount;
	auto windowTitle = GS::UniString(title.c_str());
	bool showPercent = true;
	CHECK_ERROR(ProcessWindow_SetNextProcessPhase(&windowTitle, &nPhase, &showPercent));
}

void ProcessWindow::SetProcessValue(int value) 
{
	Int32 newval = value;
	CHECK_ERROR(ProcessWindow_SetProcessValue(&newval));
	TIWait(0.005);
}

bool ProcessWindow::IsProcessCanceled() 
{
	return ProcessWindow_IsProcessCanceled();
}

void ProcessWindow::Close() 
{
	CHECK_ERROR(ProcessWindow_CloseProcessWindow());
}
