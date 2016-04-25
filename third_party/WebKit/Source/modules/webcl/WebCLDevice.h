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
#include <wtf/RefPtr.h>
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
    unsigned getQueueProperties();
    unsigned long long getMaxMemAllocSize();
    unsigned getImage2DMaxWidth();
    unsigned getImage2DMaxHeight();
    unsigned getMaxWorkGroup();
    Vector<unsigned> getMaxWorkItem();
    PassRefPtr<WebCLPlatform> getPlatform() const { return m_platform; }
    cl_device_id getDeviceId() { return m_clDeviceId; }

    template<typename T>
    T getInfo(unsigned name, ExceptionState& exceptionState)
    {
        int status;
        T info;

        status = getAsSpecialInfo(info, name);
        if (status == WebCLException::SUCCESS)
            return info;
        if (status != WebCLException::INVALID_VALUE) {
            WebCLException::throwException(status, exceptionState);
            return info;
        }

        status = getAsOrdinaryInfo(info, name);
        if (status != WebCLException::SUCCESS)
            WebCLException::throwException(status, exceptionState);
        return info;
    }

private:
    WebCLDevice(cl_device_id, WebCLPlatform* platform);

    template<typename T>
    int getAsSpecialInfo(T& info, unsigned name)
    {
        return WebCLException::INVALID_VALUE;
    }
    int getAsSpecialInfo(String& info, unsigned name);
    int getAsSpecialInfo(RefPtr<WebCLPlatform>& info, unsigned name);

    template<typename T>
    int getAsOrdinaryInfo(T& info, unsigned name)
    {
        return clGetDeviceInfo(m_clDeviceId, name, sizeof(T), &info, nullptr);
    }
    template<typename T>
    int getAsOrdinaryInfo(Vector<T>& info, unsigned name)
    {
        int status;
        size_t expectedSizeInBytes = sizeof(T);
        size_t actualSizeInBytes;
        size_t maxSizeInBytes = std::numeric_limits<size_t>::max();

        do {
            status = clGetDeviceInfo(m_clDeviceId, name, expectedSizeInBytes, nullptr, &actualSizeInBytes);
            if (status != WebCLException::SUCCESS)
                return status;
            if (actualSizeInBytes < expectedSizeInBytes || expectedSizeInBytes == maxSizeInBytes)
                break;
            if (expectedSizeInBytes <= maxSizeInBytes / 2)
                expectedSizeInBytes *= 2;
            else
                expectedSizeInBytes = maxSizeInBytes;
        } while (true);

        info.resize(actualSizeInBytes / sizeof(T));
        return clGetDeviceInfo(m_clDeviceId, name, actualSizeInBytes, info.data(), nullptr);
    }
    int getAsOrdinaryInfo(String& info, unsigned name);

    WebCLPlatform* m_platform;
    WebCLExtension m_extension;
    cl_device_id m_clDeviceId;
};

} // namespace blink

#endif // WebCLDevice_h
