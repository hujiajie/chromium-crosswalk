// Copyright (C) 2011 Samsung Electronics Corporation. All rights reserved.
// Copyright (C) 2015 Intel Corporation All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLDevice_h
#define WebCLDevice_h

#include "core/webcl/WebCLException.h"
#include "modules/webcl/WebCLConfig.h"
#include "modules/webcl/WebCLExtension.h"
#include "modules/webcl/WebCLOpenCL.h"
#include "modules/webcl/WebCLPlatform.h"

#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/PassRefPtr.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace blink {

class ExceptionState;
class WebCL;
class WebCLGetInfo;
class WebCLPlatform;

class WebCLDevice final : public RefCounted<WebCLDevice>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    ~WebCLDevice();
    static PassRefPtr<WebCLDevice> create(cl_device_id);
    static PassRefPtr<WebCLDevice> create(cl_device_id, WebCLPlatform* platform);

    ScriptValue getInfo(ScriptState*, unsigned, ExceptionState&);

    void cacheDeviceExtensions();
    bool enableExtension(const String& name);
    void getEnabledExtensions(HashSet<String>& extensions);
    Vector<String> getSupportedExtensions();
    cl_device_id getDeviceId() { return m_clDeviceId; }

    template<typename T>
    int getInfo(unsigned name, T& info)
    {
        int status = getInfoCustom(name, info);
        if (status != WebCLException::INVALID_VALUE)
            return status;

        return clGetDeviceInfo(m_clDeviceId, name, sizeof(T), &info, nullptr);
    }
    template<typename T>
    int getInfo(unsigned name, Vector<T>& info)
    {
        int status = getInfoCustom(name, info);
        if (status != WebCLException::INVALID_VALUE)
            return status;

        size_t sizeInBytes = 0;
        status = clGetDeviceInfo(m_clDeviceId, name, 0, nullptr, &sizeInBytes);
        if (status == WebCLException::SUCCESS && sizeInBytes >= sizeof(T) && sizeInBytes % sizeof(T) == 0) {
            info.resize(sizeInBytes / sizeof(T));
            return clGetDeviceInfo(m_clDeviceId, name, sizeInBytes, info.data(), nullptr);
        }

        return WebCLException::FAILURE;
    }
    int getInfo(unsigned name, String&);
    PassRefPtr<WebCLPlatform> platform();

private:
    WebCLDevice(cl_device_id, WebCLPlatform* platform);

    template<typename T>
    int getInfoCustom(unsigned name, T& info)
    {
        return WebCLException::INVALID_VALUE;
    }
    int getInfoCustom(unsigned name, cl_device_exec_capabilities&);
    int getInfoCustom(unsigned name, String&);

    WebCLPlatform* m_platform;
    WebCLExtension m_extension;
    cl_device_id m_clDeviceId;
};

} // namespace blink

#endif // WebCLDevice_h
