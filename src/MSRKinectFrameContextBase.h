//@COPYRIGHT@//
//
// Copyright (c) 2012, Tomoto S. Washio
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of the Tomoto S. Washio nor the names of his
//     contributors may be used to endorse or promote products derived from
//     this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TOMOTO S. WASHIO BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//@COPYRIGHT@//

#pragma once
#include "base.h"
#include "MSRKinectRequirement.h"
#include "IMultiThreadFrameContext.h"

class MSRKinectFrameContextBase : public virtual IMultiThreadFrameContext
{
protected:
	HANDLE m_hNextFrameEvent;
	CRITICAL_SECTION m_frameLock;

	BOOL m_bRunning;

	XnUInt32 m_nFrameID;
	XnUInt64 m_lTimestamp;

	MSRKinectRequirement* m_pRequirement;

public:
	INuiSensor* GetSensor() { return m_pRequirement->GetSensor(); }
	MSRKinectRequirement* GetRequirement() { return m_pRequirement; }

	virtual XnUInt32 GetFrameID() { return m_nFrameID; }
	virtual XnUInt64 GetTimestamp() { return m_lTimestamp; }
	virtual BOOL IsRunning() { return m_bRunning; }

protected:
	MSRKinectFrameContextBase(MSRKinectRequirement* pRequirement, HANDLE hNextFrameEvent) :
		m_pRequirement(pRequirement),
		m_hNextFrameEvent(hNextFrameEvent),
		m_bRunning(FALSE),
		m_nFrameID(0), m_lTimestamp(0)
	{
		InitializeCriticalSection(&m_frameLock);
	}

public:
	virtual ~MSRKinectFrameContextBase()
	{
		DeleteCriticalSection(&m_frameLock);
	}

	void LockFrame()
	{
		EnterCriticalSection(&m_frameLock);
	}

	void UnlockFrame()
	{
		LeaveCriticalSection(&m_frameLock);
	}

};
