// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLCommandQueueAdaptor.h"

#include "core/dom/DOMArrayBufferView.h"
#include "core/html/HTMLCanvasElement.h"
#include "core/html/HTMLImageElement.h"
#include "core/html/HTMLVideoElement.h"
#include "core/html/ImageData.h"
#include "modules/webcl/WebCLBuffer.h"
#include "modules/webcl/WebCLBufferAdaptor.h"
#include "modules/webcl/WebCLCallback.h"
#include "modules/webcl/WebCLCommandQueue.h"
#include "modules/webcl/WebCLEvent.h"
#include "modules/webcl/WebCLEventAdaptor.h"
#include "modules/webcl/WebCLImage.h"
#include "modules/webcl/WebCLImageAdaptor.h"
#include "modules/webcl/WebCLKernel.h"
#include "modules/webcl/WebCLKernelAdaptor.h"
#include "wtf/RefPtr.h"

namespace blink {

WebCLCommandQueueAdaptor* WebCLCommandQueueAdaptor::create(WebCLCommandQueue* impl)
{
    return new WebCLCommandQueueAdaptor(impl);
}

WebCLCommandQueueAdaptor::WebCLCommandQueueAdaptor(WebCLCommandQueue* impl)
    : WebCLScriptWrappableAdaptor<WebCLCommandQueue>(impl)
{
}

WebCLCommandQueueAdaptor::~WebCLCommandQueueAdaptor()
{
}

void WebCLCommandQueueAdaptor::enqueueCopyBuffer(
    WebCLBufferAdaptor* srcBufferAdaptor,
    WebCLBufferAdaptor* dstBufferAdaptor,
    unsigned srcOffset,
    unsigned dstOffset,
    unsigned numBytes,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* srcBuffer = srcBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    WebCLBuffer* dstBuffer = dstBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueCopyBuffer(srcBuffer, dstBuffer, srcOffset, dstOffset, numBytes, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyBuffer(
    WebCLBufferAdaptor* srcBufferAdaptor,
    WebCLBufferAdaptor* dstBufferAdaptor,
    unsigned srcOffset,
    unsigned dstOffset,
    unsigned numBytes,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* srcBuffer = srcBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    WebCLBuffer* dstBuffer = dstBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueCopyBuffer(srcBuffer, dstBuffer, srcOffset, dstOffset, numBytes, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyBuffer(
    WebCLBufferAdaptor* srcBufferAdaptor,
    WebCLBufferAdaptor* dstBufferAdaptor,
    unsigned srcOffset,
    unsigned dstOffset,
    unsigned numBytes,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* srcBuffer = srcBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    WebCLBuffer* dstBuffer = dstBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueCopyBuffer(srcBuffer, dstBuffer, srcOffset, dstOffset, numBytes, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyBufferRect(
    WebCLBufferAdaptor* srcBufferAdaptor,
    WebCLBufferAdaptor* dstBufferAdaptor,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& region,
    unsigned srcRowPitch,
    unsigned srcSlicePitch,
    unsigned dstRowPitch,
    unsigned dstSlicePitch,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* srcBuffer = srcBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    WebCLBuffer* dstBuffer = dstBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueCopyBufferRect(srcBuffer, dstBuffer, srcOrigin, dstOrigin, region, srcRowPitch, srcSlicePitch,
        dstRowPitch, dstSlicePitch, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyBufferRect(
    WebCLBufferAdaptor* srcBufferAdaptor,
    WebCLBufferAdaptor* dstBufferAdaptor,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& region,
    unsigned srcRowPitch,
    unsigned srcSlicePitch,
    unsigned dstRowPitch,
    unsigned dstSlicePitch,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* srcBuffer = srcBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    WebCLBuffer* dstBuffer = dstBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueCopyBufferRect(srcBuffer, dstBuffer, srcOrigin, dstOrigin, region, srcRowPitch, srcSlicePitch,
        dstRowPitch, dstSlicePitch, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyBufferRect(
    WebCLBufferAdaptor* srcBufferAdaptor,
    WebCLBufferAdaptor* dstBufferAdaptor,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& region,
    unsigned srcRowPitch,
    unsigned srcSlicePitch,
    unsigned dstRowPitch,
    unsigned dstSlicePitch,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* srcBuffer = srcBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    WebCLBuffer* dstBuffer = dstBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueCopyBufferRect(srcBuffer, dstBuffer, srcOrigin, dstOrigin, region, srcRowPitch, srcSlicePitch,
        dstRowPitch, dstSlicePitch, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyImage(
    WebCLImageAdaptor* srcImageAdaptor,
    WebCLImageAdaptor* dstImageAdaptor,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& region,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* srcImage = srcImageAdaptor->toWebCLImpl<WebCLImage>();
    WebCLImage* dstImage = dstImageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueCopyImage(srcImage, dstImage, srcOrigin, dstOrigin, region, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyImage(
    WebCLImageAdaptor* srcImageAdaptor,
    WebCLImageAdaptor* dstImageAdaptor,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& region,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* srcImage = srcImageAdaptor->toWebCLImpl<WebCLImage>();
    WebCLImage* dstImage = dstImageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueCopyImage(srcImage, dstImage, srcOrigin, dstOrigin, region, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyImage(
    WebCLImageAdaptor* srcImageAdaptor,
    WebCLImageAdaptor* dstImageAdaptor,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& region,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* srcImage = srcImageAdaptor->toWebCLImpl<WebCLImage>();
    WebCLImage* dstImage = dstImageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueCopyImage(srcImage, dstImage, srcOrigin, dstOrigin, region, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyImageToBuffer(
    WebCLImageAdaptor* srcImageAdaptor,
    WebCLBufferAdaptor* dstBufferAdaptor,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& srcRegion,
    unsigned dstOffset,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* srcImage = srcImageAdaptor->toWebCLImpl<WebCLImage>();
    WebCLBuffer* dstBuffer = dstBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueCopyImageToBuffer(srcImage, dstBuffer, srcOrigin, srcRegion, dstOffset, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyImageToBuffer(
    WebCLImageAdaptor* srcImageAdaptor,
    WebCLBufferAdaptor* dstBufferAdaptor,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& srcRegion,
    unsigned dstOffset,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* srcImage = srcImageAdaptor->toWebCLImpl<WebCLImage>();
    WebCLBuffer* dstBuffer = dstBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueCopyImageToBuffer(srcImage, dstBuffer, srcOrigin, srcRegion, dstOffset, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyImageToBuffer(
    WebCLImageAdaptor* srcImageAdaptor,
    WebCLBufferAdaptor* dstBufferAdaptor,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& srcRegion,
    unsigned dstOffset,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* srcImage = srcImageAdaptor->toWebCLImpl<WebCLImage>();
    WebCLBuffer* dstBuffer = dstBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueCopyImageToBuffer(srcImage, dstBuffer, srcOrigin, srcRegion, dstOffset, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyBufferToImage(
    WebCLBufferAdaptor* srcBufferAdaptor,
    WebCLImageAdaptor* dstImageAdaptor,
    unsigned srcOffset,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& dstRegion,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* srcBuffer = srcBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    WebCLImage* dstImage = dstImageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueCopyBufferToImage(srcBuffer, dstImage, srcOffset, dstOrigin, dstRegion, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyBufferToImage(
    WebCLBufferAdaptor* srcBufferAdaptor,
    WebCLImageAdaptor* dstImageAdaptor,
    unsigned srcOffset,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& dstRegion,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* srcBuffer = srcBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    WebCLImage* dstImage = dstImageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueCopyBufferToImage(srcBuffer, dstImage, srcOffset, dstOrigin, dstRegion, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueCopyBufferToImage(
    WebCLBufferAdaptor* srcBufferAdaptor,
    WebCLImageAdaptor* dstImageAdaptor,
    unsigned srcOffset,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& dstRegion,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* srcBuffer = srcBufferAdaptor->toWebCLImpl<WebCLBuffer>();
    WebCLImage* dstImage = dstImageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueCopyBufferToImage(srcBuffer, dstImage, srcOffset, dstOrigin, dstRegion, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    unsigned bufferOffset,
    unsigned numBytes,
    DOMArrayBufferView* hostPtr,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueReadBuffer(buffer, blockingRead, bufferOffset, numBytes, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    unsigned bufferOffset,
    unsigned numBytes,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueReadBuffer(buffer, blockingRead, bufferOffset, numBytes, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    unsigned bufferOffset,
    unsigned numBytes,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueReadBuffer(buffer, blockingRead, bufferOffset, numBytes, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& hostOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    unsigned hostRowPitch,
    unsigned hostSlicePitch,
    DOMArrayBufferView* hostPtr,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueReadBufferRect(buffer, blockingRead, bufferOrigin, hostOrigin, region, bufferRowPitch, bufferSlicePitch,
        hostRowPitch, hostSlicePitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& hostOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    unsigned hostRowPitch,
    unsigned hostSlicePitch,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueReadBufferRect(buffer, blockingRead, bufferOrigin, hostOrigin, region, bufferRowPitch, bufferSlicePitch,
        hostRowPitch, hostSlicePitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& hostOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    unsigned hostRowPitch,
    unsigned hostSlicePitch,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueReadBufferRect(buffer, blockingRead, bufferOrigin, hostOrigin, region, bufferRowPitch, bufferSlicePitch,
        hostRowPitch, hostSlicePitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingRead,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    unsigned hostRowPitch,
    DOMArrayBufferView* hostPtr,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueReadImage(image, blockingRead, origin, region, hostRowPitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingRead,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    unsigned hostRowPitch,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueReadImage(image, blockingRead, origin, region, hostRowPitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingRead,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    unsigned hostRowPitch,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueReadImage(image, blockingRead, origin, region, hostRowPitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    unsigned numBytes,
    DOMArrayBufferView* hostPtr,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, numBytes, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    unsigned numBytes,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, numBytes, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    unsigned numBytes,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, numBytes, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& hostOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    unsigned hostRowPitch,
    unsigned hostSlicePitch,
    DOMArrayBufferView* hostPtr,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, hostOrigin, region, bufferRowPitch, bufferSlicePitch,
        hostRowPitch, hostSlicePitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& hostOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    unsigned hostRowPitch,
    unsigned hostSlicePitch,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, hostOrigin, region, bufferRowPitch, bufferSlicePitch,
        hostRowPitch, hostSlicePitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& hostOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    unsigned hostRowPitch,
    unsigned hostSlicePitch,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, hostOrigin, region, bufferRowPitch, bufferSlicePitch,
        hostRowPitch, hostSlicePitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    unsigned hostRowPitch,
    DOMArrayBufferView* hostPtr,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, hostRowPitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    unsigned hostRowPitch,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, hostRowPitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    unsigned hostRowPitch,
    DOMArrayBufferView* hostPtr,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, hostRowPitch, hostPtr, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueNDRangeKernel(
    WebCLKernelAdaptor* kernelAdaptor,
    unsigned workDim,
    const Nullable<Vector<unsigned>>& globalWorkOffset,
    const Vector<unsigned>& globalWorkSize,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLKernel* kernel = kernelAdaptor->toWebCLImpl();
    Vector<double> globalWorkOffsetInDouble;
    if (globalWorkOffset)
        globalWorkOffsetInDouble.appendVector(globalWorkOffset.get());
    Vector<double> globalWorkSizeInDouble;
    globalWorkSizeInDouble.appendVector(globalWorkSize);
    Vector<double> localWorkSizeInDouble;
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueNDRangeKernel(kernel, workDim, globalWorkOffsetInDouble, globalWorkSizeInDouble,
        localWorkSizeInDouble, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueNDRangeKernel(
    WebCLKernelAdaptor* kernelAdaptor,
    unsigned workDim,
    const Nullable<Vector<unsigned>>& globalWorkOffset,
    const Vector<unsigned>& globalWorkSize,
    const Nullable<Vector<unsigned>>& localWorkSize,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLKernel* kernel = kernelAdaptor->toWebCLImpl();
    Vector<double> globalWorkOffsetInDouble;
    if (globalWorkOffset)
        globalWorkOffsetInDouble.appendVector(globalWorkOffset.get());
    Vector<double> globalWorkSizeInDouble;
    globalWorkSizeInDouble.appendVector(globalWorkSize);
    Vector<double> localWorkSizeInDouble;
    if (localWorkSize)
        localWorkSizeInDouble.appendVector(localWorkSize.get());
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueNDRangeKernel(kernel, workDim, globalWorkOffsetInDouble, globalWorkSizeInDouble,
        localWorkSizeInDouble, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueNDRangeKernel(
    WebCLKernelAdaptor* kernelAdaptor,
    unsigned workDim,
    const Nullable<Vector<unsigned>>& globalWorkOffset,
    const Vector<unsigned>& globalWorkSize,
    const Nullable<Vector<unsigned>>& localWorkSize,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLKernel* kernel = kernelAdaptor->toWebCLImpl();
    Vector<double> globalWorkOffsetInDouble;
    if (globalWorkOffset)
        globalWorkOffsetInDouble.appendVector(globalWorkOffset.get());
    Vector<double> globalWorkSizeInDouble;
    globalWorkSizeInDouble.appendVector(globalWorkSize);
    Vector<double> localWorkSizeInDouble;
    if (localWorkSize)
        localWorkSizeInDouble.appendVector(localWorkSize.get());
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueNDRangeKernel(kernel, workDim, globalWorkOffsetInDouble, globalWorkSizeInDouble,
        localWorkSizeInDouble, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueNDRangeKernel(
    WebCLKernelAdaptor* kernelAdaptor,
    unsigned workDim,
    const Nullable<Vector<unsigned>>& globalWorkOffset,
    const Vector<unsigned>& globalWorkSize,
    const Nullable<Vector<unsigned>>& localWorkSize,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLKernel* kernel = kernelAdaptor->toWebCLImpl();
    Vector<double> globalWorkOffsetInDouble;
    if (globalWorkOffset)
        globalWorkOffsetInDouble.appendVector(globalWorkOffset.get());
    Vector<double> globalWorkSizeInDouble;
    globalWorkSizeInDouble.appendVector(globalWorkSize);
    Vector<double> localWorkSizeInDouble;
    if (localWorkSize)
        localWorkSizeInDouble.appendVector(localWorkSize.get());
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueNDRangeKernel(kernel, workDim, globalWorkOffsetInDouble, globalWorkSizeInDouble,
        localWorkSizeInDouble, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueMarker(WebCLEventAdaptor* eventAdaptor, ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLEvent* event = eventAdaptor->toWebCLImpl();
    impl->enqueueMarker(event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueBarrier(ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    impl->enqueueBarrier(exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWaitForEvents(const HeapVector<Member<WebCLEventAdaptor>>& eventWaitAdaptorList, ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    for (auto eventWaitAdaptor : eventWaitAdaptorList)
        eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    impl->enqueueWaitForEvents(eventWaitList, exceptionState);
}

void WebCLCommandQueueAdaptor::finish(WebCLCallback* callback, ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    impl->finish(callback, exceptionState);
}

void WebCLCommandQueueAdaptor::flush(ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    impl->flush(exceptionState);
}

ScriptValue WebCLCommandQueueAdaptor::getInfo(ScriptState* scriptState, unsigned name, ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    return impl->getInfo(scriptState, name, exceptionState);
}

void WebCLCommandQueueAdaptor::release()
{
    WebCLCommandQueue* impl = toWebCLImpl();
    impl->release();
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    ImageData* srcPixels,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, srcPixels, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    ImageData* srcPixels,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, srcPixels, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    ImageData* srcPixels,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, srcPixels, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    HTMLCanvasElement* srcCanvas,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, srcCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    HTMLCanvasElement* srcCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, srcCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    HTMLCanvasElement* srcCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, srcCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    HTMLImageElement* srcImage,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, srcImage, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    HTMLImageElement* srcImage,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, srcImage, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    unsigned bufferOffset,
    HTMLImageElement* srcImage,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteBuffer(buffer, blockingWrite, bufferOffset, srcImage, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    ImageData* srcPixels,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, srcOrigin, region,
        bufferRowPitch, bufferSlicePitch, srcPixels, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    ImageData* srcPixels,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, srcOrigin, region,
        bufferRowPitch, bufferSlicePitch, srcPixels, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    ImageData* srcPixels,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, srcOrigin, region,
        bufferRowPitch, bufferSlicePitch, srcPixels, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    HTMLCanvasElement* srcCanvas,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, srcOrigin, region,
        bufferRowPitch, bufferSlicePitch, srcCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    HTMLCanvasElement* srcCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, srcOrigin, region,
        bufferRowPitch, bufferSlicePitch, srcCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    HTMLCanvasElement* srcCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, srcOrigin, region,
        bufferRowPitch, bufferSlicePitch, srcCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    HTMLImageElement* srcImage,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, srcOrigin, region,
        bufferRowPitch, bufferSlicePitch, srcImage, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    HTMLImageElement* srcImage,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, srcOrigin, region,
        bufferRowPitch, bufferSlicePitch, srcImage, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& srcOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    HTMLImageElement* srcImage,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteBufferRect(buffer, blockingWrite, bufferOrigin, srcOrigin, region,
        bufferRowPitch, bufferSlicePitch, srcImage, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    ImageData* srcPixels,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcPixels, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    ImageData* srcPixels,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcPixels, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    ImageData* srcPixels,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcPixels, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    HTMLCanvasElement* srcCanvas,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    HTMLCanvasElement* srcCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    HTMLCanvasElement* srcCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    HTMLImageElement* srcImage,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcImage, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    HTMLImageElement* srcImage,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcImage, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    HTMLImageElement* srcImage,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcImage, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    unsigned bufferOffset,
    unsigned numBytes,
    HTMLCanvasElement* dstCanvas,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueReadBuffer(buffer, blockingRead, bufferOffset, numBytes, dstCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    unsigned bufferOffset,
    unsigned numBytes,
    HTMLCanvasElement* dstCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueReadBuffer(buffer, blockingRead, bufferOffset, numBytes, dstCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBuffer(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    unsigned bufferOffset,
    unsigned numBytes,
    HTMLCanvasElement* dstCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueReadBuffer(buffer, blockingRead, bufferOffset, numBytes, dstCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    HTMLCanvasElement* dstCanvas,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueReadBufferRect(buffer, blockingRead, bufferOrigin, dstOrigin, region,
        bufferRowPitch, bufferSlicePitch, dstCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    HTMLCanvasElement* dstCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueReadBufferRect(buffer, blockingRead, bufferOrigin, dstOrigin, region,
        bufferRowPitch, bufferSlicePitch, dstCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadBufferRect(
    WebCLBufferAdaptor* bufferAdaptor,
    bool blockingRead,
    const Vector<unsigned>& bufferOrigin,
    const Vector<unsigned>& dstOrigin,
    const Vector<unsigned>& region,
    unsigned bufferRowPitch,
    unsigned bufferSlicePitch,
    HTMLCanvasElement* dstCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLBuffer* buffer = bufferAdaptor->toWebCLImpl<WebCLBuffer>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueReadBufferRect(buffer, blockingRead, bufferOrigin, dstOrigin, region,
        bufferRowPitch, bufferSlicePitch, dstCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingRead,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    HTMLCanvasElement* dstCanvas,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueReadImage(image, blockingRead, origin, region, dstCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingRead,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    HTMLCanvasElement* dstCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueReadImage(image, blockingRead, origin, region, dstCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueReadImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingRead,
    const Vector<unsigned>& origin,
    const Vector<unsigned>& region,
    HTMLCanvasElement* dstCanvas,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueReadImage(image, blockingRead, origin, region, dstCanvas, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    HTMLVideoElement* srcVideo,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    WebCLEvent* event = nullptr;
    impl->enqueueWriteImage(image, blockingWrite, srcVideo, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    HTMLVideoElement* srcVideo,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = nullptr;
    impl->enqueueWriteImage(image, blockingWrite, srcVideo, eventWaitList, event, exceptionState);
}

void WebCLCommandQueueAdaptor::enqueueWriteImage(
    WebCLImageAdaptor* imageAdaptor,
    bool blockingWrite,
    HTMLVideoElement* srcVideo,
    const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
    WebCLEventAdaptor* eventAdaptor,
    ExceptionState& exceptionState)
{
    WebCLCommandQueue* impl = toWebCLImpl();
    WebCLImage* image = imageAdaptor->toWebCLImpl<WebCLImage>();
    Vector<RefPtr<WebCLEvent>> eventWaitList;
    if (eventWaitAdaptorList) {
        for (auto eventWaitAdaptor : eventWaitAdaptorList.get())
            eventWaitList.append(eventWaitAdaptor->toWebCLImpl());
    }
    WebCLEvent* event = eventAdaptor ? eventAdaptor->toWebCLImpl() : nullptr;
    impl->enqueueWriteImage(image, blockingWrite, srcVideo, eventWaitList, event, exceptionState);
}

} // namespace blink
