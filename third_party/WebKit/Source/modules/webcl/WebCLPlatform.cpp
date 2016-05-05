// Copyright (C) 2011 Samsung Electronics Corporation. All rights reserved.
// Copyright (C) 2015 Intel Corporation All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "bindings/core/v8/V8Binding.h"
#include "core/webcl/WebCLException.h"
#include "modules/webcl/WebCL.h"
#include "modules/webcl/WebCLOpenCL.h"
#include "modules/webcl/WebCLPlatform.h"

namespace blink {

WebCLPlatform::~WebCLPlatform()
{
}

PassRefPtr<WebCLPlatform> WebCLPlatform::create(cl_platform_id m_clPlatformId)
{
    return adoptRef(new WebCLPlatform(m_clPlatformId));
}

Vector<RefPtr<WebCLDevice>> WebCLPlatform::getDevices(ExceptionState& es)
{
    return getDevices(CL_DEVICE_TYPE_ALL, es);
}

Vector<RefPtr<WebCLDevice>> WebCLPlatform::getDevices(unsigned deviceType, ExceptionState& es)
{
    if (!m_clPlatformId) {
        es.throwWebCLException(WebCLException::INVALID_PLATFORM, WebCLException::invalidPlatformMessage);
        return Vector<RefPtr<WebCLDevice>>();
    }

    if (deviceType && !WebCLInputChecker::isValidDeviceType(deviceType)) {
        es.throwWebCLException(WebCLException::INVALID_DEVICE_TYPE, WebCLException::invalidDeviceTypeMessage);
        return Vector<RefPtr<WebCLDevice>>();
    }

    if (!deviceType)
        deviceType = CL_DEVICE_TYPE_ALL;

    if (m_cachedDeviceType == deviceType && m_devices.size())
        return m_devices;

    cl_int err = CL_SUCCESS;
    cl_uint numDevices = 0;
    switch(deviceType) {
    case CL_DEVICE_TYPE_GPU:
        err = clGetDeviceIDs(m_clPlatformId, CL_DEVICE_TYPE_GPU, 0, nullptr, &numDevices);
        break;
    case CL_DEVICE_TYPE_CPU:
        err = clGetDeviceIDs(m_clPlatformId, CL_DEVICE_TYPE_CPU, 0, nullptr, &numDevices);
        break;
    case CL_DEVICE_TYPE_ACCELERATOR:
        err = clGetDeviceIDs(m_clPlatformId, CL_DEVICE_TYPE_ACCELERATOR, 0, nullptr, &numDevices);
        break;
    case CL_DEVICE_TYPE_DEFAULT:
        err = clGetDeviceIDs(m_clPlatformId, CL_DEVICE_TYPE_DEFAULT, 0, nullptr, &numDevices);
        break;
    case CL_DEVICE_TYPE_ALL:
        err = clGetDeviceIDs(m_clPlatformId, CL_DEVICE_TYPE_ALL, 0, nullptr, &numDevices);
        break;
    default:
        ASSERT_NOT_REACHED();
    }

    if (err != CL_SUCCESS) {
        WebCLException::throwException(err, es);
        return Vector<RefPtr<WebCLDevice>>();
    }

    Vector<cl_device_id> clDevices;
    clDevices.resize(numDevices);

    switch (deviceType) {
    case CL_DEVICE_TYPE_GPU:
        err = clGetDeviceIDs(m_clPlatformId, CL_DEVICE_TYPE_GPU, numDevices, clDevices.data(), nullptr);
        break;
    case CL_DEVICE_TYPE_CPU:
        err = clGetDeviceIDs(m_clPlatformId, CL_DEVICE_TYPE_CPU, numDevices, clDevices.data(), nullptr);
        break;
    case CL_DEVICE_TYPE_ACCELERATOR:
        err = clGetDeviceIDs(m_clPlatformId, CL_DEVICE_TYPE_ACCELERATOR, numDevices, clDevices.data(), nullptr);
        break;
    case CL_DEVICE_TYPE_DEFAULT:
        err = clGetDeviceIDs(m_clPlatformId, CL_DEVICE_TYPE_DEFAULT, numDevices, clDevices.data(), nullptr );
        break;
    case CL_DEVICE_TYPE_ALL:
        err = clGetDeviceIDs(m_clPlatformId, CL_DEVICE_TYPE_ALL, numDevices, clDevices.data(), nullptr);
        break;
    default:
        ASSERT_NOT_REACHED();
    }

    if (err != CL_SUCCESS) {
        WebCLException::throwException(err, es);
        return Vector<RefPtr<WebCLDevice>>();
    }

    m_devices.clear();
    for (auto clDevice : clDevices) {
        RefPtr<WebCLDevice> device = WebCLDevice::create(clDevice, this);
        if (device)
            m_devices.append(device);
    }

    clDevices.clear();
    m_cachedDeviceType = deviceType;
    return m_devices;
}

ScriptValue WebCLPlatform::getInfo(ScriptState* scriptState, int platformInfo, ExceptionState& es)
{
    v8::Isolate* isolate = scriptState->isolate();

    if (!m_clPlatformId) {
        es.throwWebCLException(WebCLException::INVALID_PLATFORM, WebCLException::invalidPlatformMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }

    int status;
    switch (platformInfo) {
    case CL_PLATFORM_PROFILE:
    case CL_PLATFORM_VERSION:
    case CL_PLATFORM_NAME:
    case CL_PLATFORM_VENDOR:
    case CL_PLATFORM_EXTENSIONS:
        {
            String info;
            status = getInfo(platformInfo, info);
            if (status != WebCLException::SUCCESS)
                WebCLException::throwException(status, es);
            return ScriptValue(scriptState, v8String(isolate, info));
        }
    default:
        es.throwWebCLException(WebCLException::INVALID_VALUE, WebCLException::invalidValueMessage);
        return ScriptValue(scriptState, v8::Null(isolate));
    }
}

void WebCLPlatform::cachePlatformExtensions()
{
    String platformString;
    Vector<String> extensions;

    if (!m_clPlatformId)
        return;

    int status = getInfo(CL_PLATFORM_EXTENSIONS, platformString);
    if (status != CL_SUCCESS)
        return;

    platformString.split(' ', extensions);

    for (auto extension : extensions) {
        if (!extension.containsOnlyWhitespace())
            m_extension.addSupportedCLExtension(String(extension));
    }
}

bool WebCLPlatform::enableExtension(const String& name)
{
    return m_extension.enableExtension(name);
}

Vector<String> WebCLPlatform::getSupportedExtensions()
{
    return m_extension.getSupportedExtensions();
}

void WebCLPlatform::getEnabledExtensions(HashSet<String>& extensions)
{
    m_extension.getEnabledExtensions(extensions);
}

int WebCLPlatform::getInfo(unsigned name, String& info)
{
    int status = getInfoCustom(name, info);
    if (status != WebCLException::INVALID_VALUE)
        return status;

    size_t sizeInBytes = 0;
    status = clGetPlatformInfo(m_clPlatformId, name, 0, nullptr, &sizeInBytes);
    if (status == WebCLException::SUCCESS && sizeInBytes >= sizeof(char) && sizeInBytes % sizeof(char) == 0) {
        char* stringBuffer = new char[sizeInBytes / sizeof(char)];
        status = clGetPlatformInfo(m_clPlatformId, name, sizeInBytes, stringBuffer, nullptr);
        if (status == WebCLException::SUCCESS)
            info = stringBuffer;
        delete [] stringBuffer;
        return status;
    }

    return WebCLException::FAILURE;
}

int WebCLPlatform::getInfoCustom(unsigned name, String& info)
{
    switch (name) {
    case CL_PLATFORM_PROFILE:
        info = "WEBCL_PROFILE";
        return WebCLException::SUCCESS;
    case CL_PLATFORM_VERSION:
        info = "WebCL 1.0";
        return WebCLException::SUCCESS;
    default:
        return WebCLException::INVALID_VALUE;
    }
}

WebCLPlatform::WebCLPlatform(cl_platform_id platform)
    : m_cachedDeviceType(0)
    , m_clPlatformId(platform)
{
    cachePlatformExtensions();
}

} // namespace blink
