// Copyright (C) 2011 Samsung Electronics Corporation. All rights reserved.
// Copyright (C) 2015 Intel Corporation All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLKernel_h
#define WebCLKernel_h

#include "core/webcl/WebCLException.h"
#include "modules/webcl/WebCLKernelArgInfoProvider.h"
#include "modules/webcl/WebCLProgram.h"

#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/RefPtr.h>
#include <wtf/text/WTFString.h>

namespace blink {

class DOMArrayBufferView;
class ExceptionState;
class WebCL;
class WebCLCommandQueue;
class WebCLDevice;
class WebCLKernelArgInfo;
class WebCLMemoryObject;
class WebCLPlatform;
class WebCLSampler;

class WebCLKernel : public WebCLObject, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    ~WebCLKernel() override;
    static PassRefPtr<WebCLKernel> create(cl_kernel, PassRefPtr<WebCLContext>, PassRefPtr<WebCLProgram>);

    ScriptValue getInfo(ScriptState*, int, ExceptionState&);
    ScriptValue getWorkGroupInfo(ScriptState*, WebCLDevice*, int, ExceptionState&);
    WebCLKernelArgInfo* getArgInfo(unsigned index, ExceptionState&);
    void setArg(unsigned, const ScriptValue&, ExceptionState&);
    void setArg(unsigned, WebCLMemoryObject*, ExceptionState&);
    void setArg(unsigned, WebCLSampler*, ExceptionState&);
    void setArg(unsigned, DOMArrayBufferView*, ExceptionState&);
    void setArg(unsigned, size_t, const void*, ExceptionState&);
    void release() override;

    unsigned associatedArguments();
    const Vector<unsigned>& requiredArguments() { return m_argumentInfoProvider.requiredArguments(); }
    cl_kernel getKernel() const { return m_clKernel; }

    template<typename T>
    int getInfo(unsigned name, T& info)
    {
        int status = getInfoCustom(name, info);
        if (status != WebCLException::INVALID_VALUE)
            return status;

        return clGetKernelInfo(m_clKernel, name, sizeof(T), &info, nullptr);
    }
    int getInfo(unsigned name, String& info);
    PassRefPtr<WebCLProgram> program();

private:
    WebCLKernel(cl_kernel, PassRefPtr<WebCLContext>, PassRefPtr<WebCLProgram>);
    bool isReleased() const { return !m_clKernel; }

    template<typename T>
    int getInfoCustom(unsigned name, T& info)
    {
        return WebCLException::INVALID_VALUE;
    }

    RefPtr<WebCLProgram> m_program;
    WebCLKernelArgInfoProvider m_argumentInfoProvider;
    cl_kernel m_clKernel;
};

} // namespace blink

#endif // WebCLKernel_h
