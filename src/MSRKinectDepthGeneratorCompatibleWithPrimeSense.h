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
#include "MSRKinectDepthGenerator.h"
#include "PrimeSenseProperties.h"

// experimental
class MSRKinectDepthGeneratorCompatibleWithPrimeSense :
	public MSRKinectDepthGenerator
{
private:
	typedef MSRKinectDepthGenerator SuperClass;

private:
	PrimeSenseProperties m_properties;

public:
	XnStatus GetIntProperty(const XnChar* strName, XnUInt64& nValue) const
	{
		if (m_properties.GetIntProperty(strName, nValue) == XN_STATUS_OK) {
			return XN_STATUS_OK;
		} else {
			return SuperClass::GetIntProperty(strName, nValue);
		}
	}

	XnStatus GetRealProperty(const XnChar* strName, XnDouble& dValue) const
	{
		if (m_properties.GetRealProperty(strName, dValue) == XN_STATUS_OK) {
			return XN_STATUS_OK;
		} else {
			return SuperClass::GetRealProperty(strName, dValue);
		}
	}

	XnStatus GetGeneralProperty(const XnChar* strName, XnUInt32 nBufferSize, void* pBuffer) const
	{
		if (m_properties.GetGeneralProperty(strName, nBufferSize, pBuffer) == XN_STATUS_OK) {
			return XN_STATUS_OK;
		} else {
			return SuperClass::GetGeneralProperty(strName, nBufferSize, pBuffer);
		}
	}

	XnDepthPixel GetDeviceMaxDepth() { return 10000; }

	// ModuleExtendedSerializationInterface implementation
	virtual XnStatus NotifyExState(XnNodeNotifications *pNotifications, void *pCookie)
	{
		RegisterNodeNotifications(pNotifications, pCookie);
		try {
			for (Properties::IntPropertyMap::const_iterator i = m_properties.GetIntProperties().begin();
					i != m_properties.GetIntProperties().end(); i++) {
				CHECK_XN_STATUS(OnNodeIntPropChanged(i->first.c_str(), i->second));
			}
			for (Properties::DoublePropertyMap::const_iterator i = m_properties.GetRealProperties().begin();
					i != m_properties.GetRealProperties().end(); i++) {
				CHECK_XN_STATUS(OnNodeRealPropChanged(i->first.c_str(), i->second));
			}
			for (Properties::BinaryPropertyMap::const_iterator i = m_properties.GetGeneralProperties().begin();
					i != m_properties.GetGeneralProperties().end(); i++) {
				CHECK_XN_STATUS(OnNodeGeneralPropChanged(i->first.c_str(), i->second.length, i->second.data));
			}
			return XN_STATUS_OK;
		} catch (XnStatusException& e) {
			return e.nStatus;
		}
	}

};
