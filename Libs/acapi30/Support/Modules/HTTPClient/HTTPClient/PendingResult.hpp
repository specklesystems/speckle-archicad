// *****************************************************************************
//
// PendingResult class header
//
// Contact person: EP
//
// *****************************************************************************

#ifndef GS_HTTPCLIENT_PENDING_RESULT_HPP
#define GS_HTTPCLIENT_PENDING_RESULT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

// from GSRoot
#include "AsyncResultPtr.hpp"
#include "Cancelable.hpp"
#include "Waitable.hpp"
#include "Definitions.hpp"
#include "Expected.hpp"

// from HTTPClient
#include "ErrorCode.hpp"
#include "Export.hpp"
#include "Response.hpp"

namespace HTTPClient {

using Result = GS::Expected<Response, ErrorCode>;


class HTTPCLIENT_EXPORTED PendingResult : public GS::Cancelable, public GS::Waitable {
public:
	explicit PendingResult (const GS::AsyncResultPtr& pendingResultPtr, bool fireAndForget = false);
	explicit PendingResult (ErrorCode errCode);
	virtual ~PendingResult ();
    PendingResult (const PendingResult&) = delete;
    PendingResult& operator= (const PendingResult&) = delete;
    PendingResult (PendingResult&&);
    PendingResult& operator= (PendingResult&&);

	bool IsCompleted () const;

	Result AcquireResult ();

// Waitable
	virtual bool Wait (const GS::Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool Wait (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual	void Wait (bool interruptible = true) override;

// Cancelable
	virtual bool IsCanceled () const override;
	virtual void Cancel () override;

private:
	GS::Expected<GS::AsyncResultPtr, ErrorCode> m_result;
	bool m_resultAcquired;
	bool m_fireAndForget;
};

}	// namespace HTTPClient

#endif	// GS_HTTPCLIENT_PENDING_RESULT_HPP