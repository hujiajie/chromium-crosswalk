// Copyright (C) 2011 Samsung Electronics Corporation. All rights reserved.
// Copyright (C) 2015 Intel Corporation All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLSampler_h
#define WebCLSampler_h

#include "core/webcl/WebCLException.h"
#include "modules/webcl/WebCLConfig.h"
#include "modules/webcl/WebCLObject.h"
#include "modules/webcl/WebCLOpenCL.h"

#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>

namespace blink {

class ExceptionState;
class WebCL;

class WebCLSampler : public WebCLObject, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    ~WebCLSampler() override;
    static PassRefPtr<WebCLSampler> create(cl_sampler, PassRefPtr<WebCLContext>);

    ScriptValue getInfo(ScriptState*, cl_sampler_info, ExceptionState&);
    void release() override;

    cl_sampler getSampler() const { return m_clSampler; }

    template<typename T>
    int getInfo(unsigned name, T& info)
    {
        ASSERT(!isReleased());

        int status = getInfoCustom(name, info);
        if (status != WebCLException::INVALID_VALUE)
            return status;

        return clGetSamplerInfo(m_clSampler, name, sizeof(T), &info, nullptr);
    }

private:
    WebCLSampler(cl_sampler, PassRefPtr<WebCLContext>);
    bool isReleased() const { return !m_clSampler; }

    template<typename T>
    int getInfoCustom(unsigned name, T& info)
    {
        return WebCLException::INVALID_VALUE;
    }

    cl_sampler m_clSampler;
};

} // namespace blink

#endif // WebCLSampler_h
