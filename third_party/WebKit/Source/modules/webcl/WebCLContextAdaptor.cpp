// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLContextAdaptor.h"

#include "core/dom/DOMArrayBufferView.h"
#include "core/html/HTMLCanvasElement.h"
#include "core/html/HTMLImageElement.h"
#include "core/html/HTMLVideoElement.h"
#include "core/html/ImageData.h"
#include "modules/webcl/WebCLBuffer.h"
#include "modules/webcl/WebCLBufferAdaptor.h"
#include "modules/webcl/WebCLCommandQueue.h"
#include "modules/webcl/WebCLCommandQueueAdaptor.h"
#include "modules/webcl/WebCLContext.h"
#include "modules/webcl/WebCLDevice.h"
#include "modules/webcl/WebCLDeviceAdaptor.h"
#include "modules/webcl/WebCLImage.h"
#include "modules/webcl/WebCLImageAdaptor.h"
#include "modules/webcl/WebCLProgram.h"
#include "modules/webcl/WebCLProgramAdaptor.h"
#include "modules/webcl/WebCLSampler.h"
#include "modules/webcl/WebCLSamplerAdaptor.h"
#include "modules/webcl/WebCLUserEvent.h"
#include "modules/webcl/WebCLUserEventAdaptor.h"
#include "wtf/RefPtr.h"

namespace blink {

WebCLContextAdaptor* WebCLContextAdaptor::create(WebCLContext* impl)
{
    return new WebCLContextAdaptor(impl);
}

WebCLContextAdaptor::WebCLContextAdaptor(WebCLContext* impl)
    : WebCLScriptWrappableAdaptor<WebCLContext>(impl)
{
}

WebCLContextAdaptor::~WebCLContextAdaptor()
{
}

WebCLBufferAdaptor* WebCLContextAdaptor::createBuffer(unsigned memFlags, unsigned sizeInBytes, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLBuffer> buffer = impl->createBuffer(memFlags, sizeInBytes, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return buffer->toWebCLAdaptor<WebCLBuffer>();
}

WebCLBufferAdaptor* WebCLContextAdaptor::createBuffer(unsigned memFlags, unsigned sizeInBytes, DOMArrayBufferView* hostPtr, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLBuffer> buffer = impl->createBuffer(memFlags, sizeInBytes, hostPtr, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return buffer->toWebCLAdaptor<WebCLBuffer>();
}

WebCLCommandQueueAdaptor* WebCLContextAdaptor::createCommandQueue(ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLCommandQueue> commandQueue = impl->createCommandQueue(exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return commandQueue->toWebCLAdaptor();
}

WebCLCommandQueueAdaptor* WebCLContextAdaptor::createCommandQueue(WebCLDeviceAdaptor* deviceAdaptor, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    WebCLDevice* device = deviceAdaptor->toWebCLImpl();
    RefPtr<WebCLCommandQueue> commandQueue = impl->createCommandQueue(device, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return commandQueue->toWebCLAdaptor();
}

WebCLCommandQueueAdaptor* WebCLContextAdaptor::createCommandQueue(WebCLDeviceAdaptor* deviceAdaptor, unsigned properties, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    WebCLDevice* device = deviceAdaptor->toWebCLImpl();
    RefPtr<WebCLCommandQueue> commandQueue = impl->createCommandQueue(device, properties, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return commandQueue->toWebCLAdaptor();
}

WebCLImageAdaptor* WebCLContextAdaptor::createImage(unsigned memFlags, const WebCLImageDescriptor& descriptor, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLImage> image = impl->createImage(memFlags, descriptor, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return image->toWebCLAdaptor<WebCLImage>();
}

WebCLImageAdaptor* WebCLContextAdaptor::createImage(unsigned memFlags, const WebCLImageDescriptor& descriptor, DOMArrayBufferView* hostPtr, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLImage> image = impl->createImage(memFlags, descriptor, hostPtr, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return image->toWebCLAdaptor<WebCLImage>();
}

WebCLProgramAdaptor* WebCLContextAdaptor::createProgram(const String& source, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLProgram> program = impl->createProgram(source, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return program->toWebCLAdaptor();
}

WebCLSamplerAdaptor* WebCLContextAdaptor::createSampler(bool normalizedCoords, unsigned addressingMode, unsigned filterMode, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLSampler> sampler = impl->createSampler(normalizedCoords, addressingMode, filterMode, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return sampler->toWebCLAdaptor();
}

WebCLUserEventAdaptor* WebCLContextAdaptor::createUserEvent(ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLUserEvent> userEvent = impl->createUserEvent(exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return userEvent->toWebCLAdaptor<WebCLUserEvent>();
}

ScriptValue WebCLContextAdaptor::getInfo(ScriptState* scriptState, unsigned name, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    return impl->getInfo(scriptState, name, exceptionState);
}

Nullable<HeapVector<WebCLImageDescriptor>> WebCLContextAdaptor::getSupportedImageFormats(ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    return impl->getSupportedImageFormats(exceptionState);
}

Nullable<HeapVector<WebCLImageDescriptor>> WebCLContextAdaptor::getSupportedImageFormats(unsigned memFlags, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    return impl->getSupportedImageFormats(memFlags, exceptionState);
}

void WebCLContextAdaptor::release()
{
    WebCLContext* impl = toWebCLImpl();
    impl->release();
}

void WebCLContextAdaptor::releaseAll()
{
    WebCLContext* impl = toWebCLImpl();
    impl->releaseAll();
}

WebCLBufferAdaptor* WebCLContextAdaptor::createBuffer(unsigned memFlags, ImageData* srcPixels, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLBuffer> buffer = impl->createBuffer(memFlags, srcPixels, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return buffer->toWebCLAdaptor<WebCLBuffer>();
}

WebCLBufferAdaptor* WebCLContextAdaptor::createBuffer(unsigned memFlags, HTMLCanvasElement* srcCanvas, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLBuffer> buffer = impl->createBuffer(memFlags, srcCanvas, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return buffer->toWebCLAdaptor<WebCLBuffer>();
}

WebCLBufferAdaptor* WebCLContextAdaptor::createBuffer(unsigned memFlags, HTMLImageElement* srcImage, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLBuffer> buffer = impl->createBuffer(memFlags, srcImage, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return buffer->toWebCLAdaptor<WebCLBuffer>();
}

WebCLImageAdaptor* WebCLContextAdaptor::createImage(unsigned memFlags, ImageData* srcPixels, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLImage> image = impl->createImage(memFlags, srcPixels, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return image->toWebCLAdaptor<WebCLImage>();
}

WebCLImageAdaptor* WebCLContextAdaptor::createImage(unsigned memFlags, HTMLCanvasElement* srcCanvas, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLImage> image = impl->createImage(memFlags, srcCanvas, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return image->toWebCLAdaptor<WebCLImage>();
}

WebCLImageAdaptor* WebCLContextAdaptor::createImage(unsigned memFlags, HTMLImageElement* srcImage, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLImage> image = impl->createImage(memFlags, srcImage, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return image->toWebCLAdaptor<WebCLImage>();
}

WebCLImageAdaptor* WebCLContextAdaptor::createImage(unsigned memFlags, HTMLVideoElement* srcVideo, ExceptionState& exceptionState)
{
    WebCLContext* impl = toWebCLImpl();
    RefPtr<WebCLImage> image = impl->createImage(memFlags, srcVideo, exceptionState);
    if (exceptionState.hadException())
        return nullptr;
    return image->toWebCLAdaptor<WebCLImage>();
}

} // namespace blink
