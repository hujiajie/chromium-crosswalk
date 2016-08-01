// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLCommandQueueAdaptor_h
#define WebCLCommandQueueAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/Nullable.h"
#include "bindings/core/v8/ScriptValue.h"
#include "bindings/core/v8/ScriptWrappable.h"
#include "modules/webcl/WebCLScriptWrappableAdaptor.h"
#include "platform/heap/Handle.h"
#include "wtf/Vector.h"

namespace blink {

class DOMArrayBufferView;
class HTMLCanvasElement;
class HTMLImageElement;
class HTMLVideoElement;
class ImageData;
class ScriptState;
class WebCLBufferAdaptor;
class WebCLCallback;
class WebCLCommandQueue;
class WebCLEventAdaptor;
class WebCLImageAdaptor;
class WebCLKernelAdaptor;

class WebCLCommandQueueAdaptor final : public GarbageCollectedFinalized<WebCLCommandQueueAdaptor>, public WebCLScriptWrappableAdaptor<WebCLCommandQueue>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLCommandQueueAdaptor* create(WebCLCommandQueue*);
    ~WebCLCommandQueueAdaptor();

    void enqueueCopyBuffer(
        WebCLBufferAdaptor* srcBufferAdaptor,
        WebCLBufferAdaptor* dstBufferAdaptor,
        unsigned srcOffset,
        unsigned dstOffset,
        unsigned numBytes,
        ExceptionState&);
    void enqueueCopyBuffer(
        WebCLBufferAdaptor* srcBufferAdaptor,
        WebCLBufferAdaptor* dstBufferAdaptor,
        unsigned srcOffset,
        unsigned dstOffset,
        unsigned numBytes,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueCopyBuffer(
        WebCLBufferAdaptor* srcBufferAdaptor,
        WebCLBufferAdaptor* dstBufferAdaptor,
        unsigned srcOffset,
        unsigned dstOffset,
        unsigned numBytes,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueCopyBufferRect(
        WebCLBufferAdaptor* srcBufferAdaptor,
        WebCLBufferAdaptor* dstBufferAdaptor,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& dstOrigin,
        const Vector<unsigned>& region,
        unsigned srcRowPitch,
        unsigned srcSlicePitch,
        unsigned dstRowPitch,
        unsigned dstSlicePitch,
        ExceptionState&);
    void enqueueCopyBufferRect(
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
        ExceptionState&);
    void enqueueCopyBufferRect(
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
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueCopyImage(
        WebCLImageAdaptor* srcImageAdaptor,
        WebCLImageAdaptor* dstImageAdaptor,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& dstOrigin,
        const Vector<unsigned>& region,
        ExceptionState&);
    void enqueueCopyImage(
        WebCLImageAdaptor* srcImageAdaptor,
        WebCLImageAdaptor* dstImageAdaptor,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& dstOrigin,
        const Vector<unsigned>& region,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueCopyImage(
        WebCLImageAdaptor* srcImageAdaptor,
        WebCLImageAdaptor* dstImageAdaptor,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& dstOrigin,
        const Vector<unsigned>& region,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueCopyImageToBuffer(
        WebCLImageAdaptor* srcImageAdaptor,
        WebCLBufferAdaptor* dstBufferAdaptor,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& srcRegion,
        unsigned dstOffset,
        ExceptionState&);
    void enqueueCopyImageToBuffer(
        WebCLImageAdaptor* srcImageAdaptor,
        WebCLBufferAdaptor* dstBufferAdaptor,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& srcRegion,
        unsigned dstOffset,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueCopyImageToBuffer(
        WebCLImageAdaptor* srcImageAdaptor,
        WebCLBufferAdaptor* dstBufferAdaptor,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& srcRegion,
        unsigned dstOffset,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueCopyBufferToImage(
        WebCLBufferAdaptor* srcBufferAdaptor,
        WebCLImageAdaptor* dstImageAdaptor,
        unsigned srcOffset,
        const Vector<unsigned>& dstOrigin,
        const Vector<unsigned>& dstRegion,
        ExceptionState&);
    void enqueueCopyBufferToImage(
        WebCLBufferAdaptor* srcBufferAdaptor,
        WebCLImageAdaptor* dstImageAdaptor,
        unsigned srcOffset,
        const Vector<unsigned>& dstOrigin,
        const Vector<unsigned>& dstRegion,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueCopyBufferToImage(
        WebCLBufferAdaptor* srcBufferAdaptor,
        WebCLImageAdaptor* dstImageAdaptor,
        unsigned srcOffset,
        const Vector<unsigned>& dstOrigin,
        const Vector<unsigned>& dstRegion,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueReadBuffer(
        WebCLBufferAdaptor*,
        bool blockingRead,
        unsigned bufferOffset,
        unsigned numBytes,
        DOMArrayBufferView*,
        ExceptionState&);
    void enqueueReadBuffer(
        WebCLBufferAdaptor*,
        bool blockingRead,
        unsigned bufferOffset,
        unsigned numBytes,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueReadBuffer(
        WebCLBufferAdaptor*,
        bool blockingRead,
        unsigned bufferOffset,
        unsigned numBytes,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueReadBufferRect(
        WebCLBufferAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& hostOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        unsigned hostRowPitch,
        unsigned hostSlicePitch,
        DOMArrayBufferView*,
        ExceptionState&);
    void enqueueReadBufferRect(
        WebCLBufferAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& hostOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        unsigned hostRowPitch,
        unsigned hostSlicePitch,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueReadBufferRect(
        WebCLBufferAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& hostOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        unsigned hostRowPitch,
        unsigned hostSlicePitch,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueReadImage(
        WebCLImageAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        unsigned hostRowPitch,
        DOMArrayBufferView*,
        ExceptionState&);
    void enqueueReadImage(
        WebCLImageAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        unsigned hostRowPitch,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueReadImage(
        WebCLImageAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        unsigned hostRowPitch,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        unsigned numBytes,
        DOMArrayBufferView*,
        ExceptionState&);
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        unsigned numBytes,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        unsigned numBytes,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& hostOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        unsigned hostRowPitch,
        unsigned hostSlicePitch,
        DOMArrayBufferView*,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& hostOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        unsigned hostRowPitch,
        unsigned hostSlicePitch,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& hostOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        unsigned hostRowPitch,
        unsigned hostSlicePitch,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        unsigned hostRowPitch,
        DOMArrayBufferView*,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        unsigned hostRowPitch,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        unsigned hostRowPitch,
        DOMArrayBufferView*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueNDRangeKernel(
        WebCLKernelAdaptor*,
        unsigned workDim,
        const Nullable<Vector<unsigned>>& globalWorkOffset,
        const Vector<unsigned>& globalWorkSize,
        ExceptionState&);
    void enqueueNDRangeKernel(
        WebCLKernelAdaptor*,
        unsigned workDim,
        const Nullable<Vector<unsigned>>& globalWorkOffset,
        const Vector<unsigned>& globalWorkSize,
        const Nullable<Vector<unsigned>>& localWorkSize,
        ExceptionState&);
    void enqueueNDRangeKernel(
        WebCLKernelAdaptor*,
        unsigned workDim,
        const Nullable<Vector<unsigned>>& globalWorkOffset,
        const Vector<unsigned>& globalWorkSize,
        const Nullable<Vector<unsigned>>& localWorkSize,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueNDRangeKernel(
        WebCLKernelAdaptor*,
        unsigned workDim,
        const Nullable<Vector<unsigned>>& globalWorkOffset,
        const Vector<unsigned>& globalWorkSize,
        const Nullable<Vector<unsigned>>& localWorkSize,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueMarker(WebCLEventAdaptor*, ExceptionState&);
    void enqueueBarrier(ExceptionState&);
    void enqueueWaitForEvents(const HeapVector<Member<WebCLEventAdaptor>>& eventWaitAdaptorList, ExceptionState&);
    void finish(WebCLCallback*, ExceptionState&);
    void flush(ExceptionState&);
    ScriptValue getInfo(ScriptState*, unsigned name, ExceptionState&);
    void release();

    // WEBCL_html_image extension
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        ImageData*,
        ExceptionState&);
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        ImageData*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        ImageData*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        HTMLCanvasElement*,
        ExceptionState&);
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        HTMLImageElement*,
        ExceptionState&);
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        HTMLImageElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteBuffer(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        unsigned bufferOffset,
        HTMLImageElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        ImageData*,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        ImageData*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        ImageData*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        HTMLCanvasElement*,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        HTMLImageElement*,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        HTMLImageElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteBufferRect(
        WebCLBufferAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& srcOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        HTMLImageElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        ImageData*,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        ImageData*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        ImageData*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        HTMLCanvasElement*,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        HTMLImageElement*,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        HTMLImageElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        HTMLImageElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueReadBuffer(
        WebCLBufferAdaptor*,
        bool blockingRead,
        unsigned bufferOffset,
        unsigned numBytes,
        HTMLCanvasElement*,
        ExceptionState&);
    void enqueueReadBuffer(
        WebCLBufferAdaptor*,
        bool blockingRead,
        unsigned bufferOffset,
        unsigned numBytes,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueReadBuffer(
        WebCLBufferAdaptor*,
        bool blockingRead,
        unsigned bufferOffset,
        unsigned numBytes,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueReadBufferRect(
        WebCLBufferAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& dstOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        HTMLCanvasElement*,
        ExceptionState&);
    void enqueueReadBufferRect(
        WebCLBufferAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& dstOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueReadBufferRect(
        WebCLBufferAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& bufferOrigin,
        const Vector<unsigned>& dstOrigin,
        const Vector<unsigned>& region,
        unsigned bufferRowPitch,
        unsigned bufferSlicePitch,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);
    void enqueueReadImage(
        WebCLImageAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        HTMLCanvasElement*,
        ExceptionState&);
    void enqueueReadImage(
        WebCLImageAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueReadImage(
        WebCLImageAdaptor*,
        bool blockingRead,
        const Vector<unsigned>& origin,
        const Vector<unsigned>& region,
        HTMLCanvasElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);

    // WEBCL_html_video extension
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        HTMLVideoElement*,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        HTMLVideoElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        ExceptionState&);
    void enqueueWriteImage(
        WebCLImageAdaptor*,
        bool blockingWrite,
        HTMLVideoElement*,
        const Nullable<HeapVector<Member<WebCLEventAdaptor>>>& eventWaitAdaptorList,
        WebCLEventAdaptor*,
        ExceptionState&);

    DEFINE_INLINE_TRACE() { }

private:
    WebCLCommandQueueAdaptor(WebCLCommandQueue*);
};

} // namespace blink

#endif // WebCLCommandQueueAdaptor_h
