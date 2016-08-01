// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "bindings/modules/v8/V8WebCLCommandQueue.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/V8ArrayBufferView.h"
#include "bindings/core/v8/V8HTMLCanvasElement.h"
#include "bindings/core/v8/V8HTMLImageElement.h"
#include "bindings/core/v8/V8HTMLVideoElement.h"
#include "bindings/core/v8/V8ImageData.h"
#include "bindings/modules/v8/V8WebCLEvent.h"
#include "bindings/modules/v8/V8WebCLImage.h"

namespace blink {

static void enqueueWriteImage1Method(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "enqueueWriteImage", "WebCLCommandQueue", info.Holder(), info.GetIsolate());
    WebCLCommandQueueAdaptor* impl = V8WebCLCommandQueue::toImpl(info.Holder());
    WebCLImageAdaptor* image;
    bool blockingWrite;
    Vector<unsigned> origin;
    Vector<unsigned> region;
    unsigned hostRowPitch;
    DOMArrayBufferView* hostPtr;
    Nullable<HeapVector<Member<WebCLEventAdaptor>>> eventWaitList;
    WebCLEventAdaptor* event;
    {
        int numArgsPassed = info.Length();
        while (numArgsPassed > 0) {
            if (!info[numArgsPassed - 1]->IsUndefined())
                break;
            --numArgsPassed;
        }
        image = V8WebCLImage::toImplWithTypeCheck(info.GetIsolate(), info[0]);
        if (!image) {
            exceptionState.throwTypeError("parameter 1 is not of type 'WebCLImage'.");
            exceptionState.throwIfNeeded();
            return;
        }
        blockingWrite = toBoolean(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        origin = toImplArray<Vector<unsigned>>(info[2], 3, info.GetIsolate(), exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        region = toImplArray<Vector<unsigned>>(info[3], 4, info.GetIsolate(), exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        hostRowPitch = toUInt32(info.GetIsolate(), info[4], NormalConversion, exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        hostPtr = info[5]->IsArrayBufferView() ? V8ArrayBufferView::toImpl(v8::Local<v8::ArrayBufferView>::Cast(info[5])) : 0;
        if (!hostPtr) {
            exceptionState.throwTypeError("parameter 6 is not of type 'ArrayBufferView'.");
            exceptionState.throwIfNeeded();
            return;
        }
        if (UNLIKELY(numArgsPassed <= 6)) {
            impl->enqueueWriteImage(image, blockingWrite, origin, region, hostRowPitch, hostPtr, exceptionState);
            if (exceptionState.hadException()) {
                exceptionState.throwIfNeeded();
                return;
            }
            return;
        }
        if (!isUndefinedOrNull(info[6])) {
            eventWaitList = (toMemberNativeArray<WebCLEvent, V8WebCLEvent>(info[6], 7, info.GetIsolate(), exceptionState));
            if (exceptionState.throwIfNeeded())
                return;
        }
        if (UNLIKELY(numArgsPassed <= 7)) {
            impl->enqueueWriteImage(image, blockingWrite, origin, region, hostRowPitch, hostPtr, eventWaitList, exceptionState);
            if (exceptionState.hadException()) {
                exceptionState.throwIfNeeded();
                return;
            }
            return;
        }
        event = V8WebCLEvent::toImplWithTypeCheck(info.GetIsolate(), info[7]);
        if (!event && !isUndefinedOrNull(info[7])) {
            exceptionState.throwTypeError("parameter 8 is not of type 'WebCLEvent'.");
            exceptionState.throwIfNeeded();
            return;
        }
    }
    impl->enqueueWriteImage(image, blockingWrite, origin, region, hostRowPitch, hostPtr, eventWaitList, event, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void enqueueWriteImage2Method(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "enqueueWriteImage", "WebCLCommandQueue", info.Holder(), info.GetIsolate());
    WebCLCommandQueueAdaptor* impl = V8WebCLCommandQueue::toImpl(info.Holder());
    WebCLImageAdaptor* image;
    bool blockingWrite;
    Vector<unsigned> origin;
    Vector<unsigned> region;
    ImageData* srcPixels;
    Nullable<HeapVector<Member<WebCLEventAdaptor>>> eventWaitList;
    WebCLEventAdaptor* event;
    {
        int numArgsPassed = info.Length();
        while (numArgsPassed > 0) {
            if (!info[numArgsPassed - 1]->IsUndefined())
                break;
            --numArgsPassed;
        }
        image = V8WebCLImage::toImplWithTypeCheck(info.GetIsolate(), info[0]);
        if (!image) {
            exceptionState.throwTypeError("parameter 1 is not of type 'WebCLImage'.");
            exceptionState.throwIfNeeded();
            return;
        }
        blockingWrite = toBoolean(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        origin = toImplArray<Vector<unsigned>>(info[2], 3, info.GetIsolate(), exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        region = toImplArray<Vector<unsigned>>(info[3], 4, info.GetIsolate(), exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        srcPixels = V8ImageData::toImplWithTypeCheck(info.GetIsolate(), info[4]);
        if (!srcPixels) {
            exceptionState.throwTypeError("parameter 5 is not of type 'ImageData'.");
            exceptionState.throwIfNeeded();
            return;
        }
        if (UNLIKELY(numArgsPassed <= 5)) {
            impl->enqueueWriteImage(image, blockingWrite, origin, region, srcPixels, exceptionState);
            if (exceptionState.hadException()) {
                exceptionState.throwIfNeeded();
                return;
            }
            return;
        }
        if (!isUndefinedOrNull(info[5])) {
            eventWaitList = (toMemberNativeArray<WebCLEvent, V8WebCLEvent>(info[5], 6, info.GetIsolate(), exceptionState));
            if (exceptionState.throwIfNeeded())
                return;
        }
        if (UNLIKELY(numArgsPassed <= 6)) {
            impl->enqueueWriteImage(image, blockingWrite, origin, region, srcPixels, eventWaitList, exceptionState);
            if (exceptionState.hadException()) {
                exceptionState.throwIfNeeded();
                return;
            }
            return;
        }
        event = V8WebCLEvent::toImplWithTypeCheck(info.GetIsolate(), info[6]);
        if (!event && !isUndefinedOrNull(info[6])) {
            exceptionState.throwTypeError("parameter 7 is not of type 'WebCLEvent'.");
            exceptionState.throwIfNeeded();
            return;
        }
    }
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcPixels, eventWaitList, event, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void enqueueWriteImage3Method(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "enqueueWriteImage", "WebCLCommandQueue", info.Holder(), info.GetIsolate());
    WebCLCommandQueueAdaptor* impl = V8WebCLCommandQueue::toImpl(info.Holder());
    WebCLImageAdaptor* image;
    bool blockingWrite;
    Vector<unsigned> origin;
    Vector<unsigned> region;
    HTMLCanvasElement* srcCanvas;
    Nullable<HeapVector<Member<WebCLEventAdaptor>>> eventWaitList;
    WebCLEventAdaptor* event;
    {
        int numArgsPassed = info.Length();
        while (numArgsPassed > 0) {
            if (!info[numArgsPassed - 1]->IsUndefined())
                break;
            --numArgsPassed;
        }
        image = V8WebCLImage::toImplWithTypeCheck(info.GetIsolate(), info[0]);
        if (!image) {
            exceptionState.throwTypeError("parameter 1 is not of type 'WebCLImage'.");
            exceptionState.throwIfNeeded();
            return;
        }
        blockingWrite = toBoolean(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        origin = toImplArray<Vector<unsigned>>(info[2], 3, info.GetIsolate(), exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        region = toImplArray<Vector<unsigned>>(info[3], 4, info.GetIsolate(), exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        srcCanvas = V8HTMLCanvasElement::toImplWithTypeCheck(info.GetIsolate(), info[4]);
        if (!srcCanvas) {
            exceptionState.throwTypeError("parameter 5 is not of type 'HTMLCanvasElement'.");
            exceptionState.throwIfNeeded();
            return;
        }
        if (UNLIKELY(numArgsPassed <= 5)) {
            impl->enqueueWriteImage(image, blockingWrite, origin, region, srcCanvas, exceptionState);
            if (exceptionState.hadException()) {
                exceptionState.throwIfNeeded();
                return;
            }
            return;
        }
        if (!isUndefinedOrNull(info[5])) {
            eventWaitList = (toMemberNativeArray<WebCLEvent, V8WebCLEvent>(info[5], 6, info.GetIsolate(), exceptionState));
            if (exceptionState.throwIfNeeded())
                return;
        }
        if (UNLIKELY(numArgsPassed <= 6)) {
            impl->enqueueWriteImage(image, blockingWrite, origin, region, srcCanvas, eventWaitList, exceptionState);
            if (exceptionState.hadException()) {
                exceptionState.throwIfNeeded();
                return;
            }
            return;
        }
        event = V8WebCLEvent::toImplWithTypeCheck(info.GetIsolate(), info[6]);
        if (!event && !isUndefinedOrNull(info[6])) {
            exceptionState.throwTypeError("parameter 7 is not of type 'WebCLEvent'.");
            exceptionState.throwIfNeeded();
            return;
        }
    }
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcCanvas, eventWaitList, event, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void enqueueWriteImage4Method(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "enqueueWriteImage", "WebCLCommandQueue", info.Holder(), info.GetIsolate());
    WebCLCommandQueueAdaptor* impl = V8WebCLCommandQueue::toImpl(info.Holder());
    WebCLImageAdaptor* image;
    bool blockingWrite;
    Vector<unsigned> origin;
    Vector<unsigned> region;
    HTMLImageElement* srcImage;
    Nullable<HeapVector<Member<WebCLEventAdaptor>>> eventWaitList;
    WebCLEventAdaptor* event;
    {
        int numArgsPassed = info.Length();
        while (numArgsPassed > 0) {
            if (!info[numArgsPassed - 1]->IsUndefined())
                break;
            --numArgsPassed;
        }
        image = V8WebCLImage::toImplWithTypeCheck(info.GetIsolate(), info[0]);
        if (!image) {
            exceptionState.throwTypeError("parameter 1 is not of type 'WebCLImage'.");
            exceptionState.throwIfNeeded();
            return;
        }
        blockingWrite = toBoolean(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        origin = toImplArray<Vector<unsigned>>(info[2], 3, info.GetIsolate(), exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        region = toImplArray<Vector<unsigned>>(info[3], 4, info.GetIsolate(), exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        srcImage = V8HTMLImageElement::toImplWithTypeCheck(info.GetIsolate(), info[4]);
        if (!srcImage) {
            exceptionState.throwTypeError("parameter 5 is not of type 'HTMLImageElement'.");
            exceptionState.throwIfNeeded();
            return;
        }
        if (UNLIKELY(numArgsPassed <= 5)) {
            impl->enqueueWriteImage(image, blockingWrite, origin, region, srcImage, exceptionState);
            if (exceptionState.hadException()) {
                exceptionState.throwIfNeeded();
                return;
            }
            return;
        }
        if (!isUndefinedOrNull(info[5])) {
            eventWaitList = (toMemberNativeArray<WebCLEvent, V8WebCLEvent>(info[5], 6, info.GetIsolate(), exceptionState));
            if (exceptionState.throwIfNeeded())
                return;
        }
        if (UNLIKELY(numArgsPassed <= 6)) {
            impl->enqueueWriteImage(image, blockingWrite, origin, region, srcImage, eventWaitList, exceptionState);
            if (exceptionState.hadException()) {
                exceptionState.throwIfNeeded();
                return;
            }
            return;
        }
        event = V8WebCLEvent::toImplWithTypeCheck(info.GetIsolate(), info[6]);
        if (!event && !isUndefinedOrNull(info[6])) {
            exceptionState.throwTypeError("parameter 7 is not of type 'WebCLEvent'.");
            exceptionState.throwIfNeeded();
            return;
        }
    }
    impl->enqueueWriteImage(image, blockingWrite, origin, region, srcImage, eventWaitList, event, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void enqueueWriteImage5Method(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "enqueueWriteImage", "WebCLCommandQueue", info.Holder(), info.GetIsolate());
    WebCLCommandQueueAdaptor* impl = V8WebCLCommandQueue::toImpl(info.Holder());
    WebCLImageAdaptor* image;
    bool blockingWrite;
    HTMLVideoElement* srcVideo;
    Nullable<HeapVector<Member<WebCLEventAdaptor>>> eventWaitList;
    WebCLEventAdaptor* event;
    {
        int numArgsPassed = info.Length();
        while (numArgsPassed > 0) {
            if (!info[numArgsPassed - 1]->IsUndefined())
                break;
            --numArgsPassed;
        }
        image = V8WebCLImage::toImplWithTypeCheck(info.GetIsolate(), info[0]);
        if (!image) {
            exceptionState.throwTypeError("parameter 1 is not of type 'WebCLImage'.");
            exceptionState.throwIfNeeded();
            return;
        }
        blockingWrite = toBoolean(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        srcVideo = V8HTMLVideoElement::toImplWithTypeCheck(info.GetIsolate(), info[2]);
        if (!srcVideo) {
            exceptionState.throwTypeError("parameter 3 is not of type 'HTMLVideoElement'.");
            exceptionState.throwIfNeeded();
            return;
        }
        if (UNLIKELY(numArgsPassed <= 3)) {
            impl->enqueueWriteImage(image, blockingWrite, srcVideo, exceptionState);
            if (exceptionState.hadException()) {
                exceptionState.throwIfNeeded();
                return;
            }
            return;
        }
        if (!isUndefinedOrNull(info[3])) {
            eventWaitList = (toMemberNativeArray<WebCLEvent, V8WebCLEvent>(info[3], 4, info.GetIsolate(), exceptionState));
            if (exceptionState.throwIfNeeded())
                return;
        }
        if (UNLIKELY(numArgsPassed <= 4)) {
            impl->enqueueWriteImage(image, blockingWrite, srcVideo, eventWaitList, exceptionState);
            if (exceptionState.hadException()) {
                exceptionState.throwIfNeeded();
                return;
            }
            return;
        }
        event = V8WebCLEvent::toImplWithTypeCheck(info.GetIsolate(), info[4]);
        if (!event && !isUndefinedOrNull(info[4])) {
            exceptionState.throwTypeError("parameter 5 is not of type 'WebCLEvent'.");
            exceptionState.throwIfNeeded();
            return;
        }
    }
    impl->enqueueWriteImage(image, blockingWrite, srcVideo, eventWaitList, event, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

void V8WebCLCommandQueue::enqueueWriteImageMethodCustom(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "enqueueWriteImage", "WebCLCommandQueue", info.Holder(), info.GetIsolate());
    switch (std::min(8, info.Length())) {
    case 3:
        if (true) {
            enqueueWriteImage5Method(info);
            return;
        }
        break;
    case 4:
        if (true) {
            enqueueWriteImage5Method(info);
            return;
        }
        break;
    case 5:
        if (V8HTMLVideoElement::hasInstance(info[2], info.GetIsolate())) {
            enqueueWriteImage5Method(info);
            return;
        }
        if (info[2]->IsArray()) {
            if (V8ImageData::hasInstance(info[4], info.GetIsolate())) {
                enqueueWriteImage2Method(info);
                return;
            }
            if (V8HTMLCanvasElement::hasInstance(info[4], info.GetIsolate())) {
                enqueueWriteImage3Method(info);
                return;
            }
            if (V8HTMLImageElement::hasInstance(info[4], info.GetIsolate())) {
                enqueueWriteImage4Method(info);
                return;
            }
        }
        break;
    case 6:
        if (V8ImageData::hasInstance(info[4], info.GetIsolate())) {
            enqueueWriteImage2Method(info);
            return;
        }
        if (V8HTMLCanvasElement::hasInstance(info[4], info.GetIsolate())) {
            enqueueWriteImage3Method(info);
            return;
        }
        if (V8HTMLImageElement::hasInstance(info[4], info.GetIsolate())) {
            enqueueWriteImage4Method(info);
            return;
        }
        if (true) {
            enqueueWriteImage1Method(info);
            return;
        }
        break;
    case 7:
        if (V8ImageData::hasInstance(info[4], info.GetIsolate())) {
            enqueueWriteImage2Method(info);
            return;
        }
        if (V8HTMLCanvasElement::hasInstance(info[4], info.GetIsolate())) {
            enqueueWriteImage3Method(info);
            return;
        }
        if (V8HTMLImageElement::hasInstance(info[4], info.GetIsolate())) {
            enqueueWriteImage4Method(info);
            return;
        }
        if (true) {
            enqueueWriteImage1Method(info);
            return;
        }
        break;
    case 8:
        if (true) {
            enqueueWriteImage1Method(info);
            return;
        }
        break;
    default:
        break;
    }
    if (info.Length() < 3) {
        exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(3, info.Length()));
        exceptionState.throwIfNeeded();
        return;
    }
    exceptionState.throwTypeError("No function was found that matched the signature provided.");
    exceptionState.throwIfNeeded();
    return;
}

} // namespace blink
