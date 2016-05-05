// Copyright (C) 2011 Samsung Electronics Corporation. All rights reserved.
// Copyright (C) 2015 Intel Corporation All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLProgram_h
#define WebCLProgram_h

#include "core/webcl/WebCLException.h"
#include "modules/webcl/WebCLConfig.h"
#include "modules/webcl/WebCLCallback.h"
#include "modules/webcl/WebCLDevice.h"
#include "modules/webcl/WebCLObject.h"

#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/RefPtr.h>
#include <wtf/Threading.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace blink {

class ExceptionState;
class WebCL;
class WebCLContext;
class WebCLKernel;
class WebCLProgramHolder;

class WebCLProgram : public WebCLObject, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    ~WebCLProgram() override;
    static PassRefPtr<WebCLProgram> create(cl_program, PassRefPtr<WebCLContext>, const String&);

    ScriptValue getInfo(ScriptState*, int, ExceptionState&);
    ScriptValue getBuildInfo(ScriptState* scriptState, WebCLDevice*, int, ExceptionState&);
    PassRefPtr<WebCLKernel> createKernel(const String&, ExceptionState&);
    Vector<RefPtr<WebCLKernel>> createKernelsInProgram(ExceptionState&);
    void build(const Vector<RefPtr<WebCLDevice>>&, const String&, WebCLCallback*, ExceptionState&);
    void build(const String&, WebCLCallback*, ExceptionState&);
    void release() override;

    const String& sourceWithCommentsStripped();

    template<typename T>
    int getInfo(unsigned name, T& info)
    {
        int status = getInfoCustom(name, info);
        if (status != WebCLException::INVALID_VALUE)
            return status;

        return clGetProgramInfo(m_clProgram, name, sizeof(T), &info, nullptr);
    }
    int getInfo(unsigned name, String& info);
    Vector<RefPtr<WebCLDevice>> devices();

    template<typename T>
    int getBuildInfo(WebCLDevice* device, unsigned name, T& info)
    {
        int status = getBuildInfoCustom(device, name, info);
        if (status != WebCLException::INVALID_VALUE)
            return status;

        return clGetProgramBuildInfo(m_clProgram, device->getDeviceId(), name, sizeof(T), &info, nullptr);
    }
    int getBuildInfo(WebCLDevice*, unsigned name, String& info);

private:
    WebCLProgram(cl_program, PassRefPtr<WebCLContext>, const String&);
    bool isReleased() const { return !m_clProgram; }
    bool isExtensionEnabled(RefPtr<blink::WebCLContext>, const String&);
    typedef void (CL_CALLBACK *pfnNotify)(cl_program, void*);
    static void CL_CALLBACK callbackProxy(cl_program, void*);
    static void callbackProxyOnMainThread(PassOwnPtr<WebCLProgramHolder>);
    cl_program getProgram() { return m_clProgram; }

    template<typename T>
    int getInfoCustom(unsigned name, T& info)
    {
        return WebCLException::INVALID_VALUE;
    }

    template<typename T>
    int getBuildInfoCustom(WebCLDevice* device, unsigned name, T& info)
    {
        return WebCLException::INVALID_VALUE;
    }

    Persistent<WebCLCallback> m_buildCallback;
    String m_programSource;
    String m_programSourceWithCommentsStripped;
    bool m_isProgramBuilt;
    cl_program m_clProgram;
};

} // namespace blink

#endif // WebCLProgram_h
