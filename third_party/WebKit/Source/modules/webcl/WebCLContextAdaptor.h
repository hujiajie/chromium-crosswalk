// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLContextAdaptor_h
#define WebCLContextAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/Nullable.h"
#include "bindings/core/v8/ScriptValue.h"
#include "bindings/core/v8/ScriptWrappable.h"
#include "modules/webcl/WebCLImageDescriptor.h"
#include "modules/webcl/WebCLScriptWrappableAdaptor.h"
#include "platform/heap/Handle.h"
#include "wtf/text/WTFString.h"

namespace blink {

class DOMArrayBufferView;
class HTMLCanvasElement;
class HTMLImageElement;
class HTMLVideoElement;
class ImageData;
class ScriptState;
class WebCLBufferAdaptor;
class WebCLCommandQueueAdaptor;
class WebCLContext;
class WebCLDeviceAdaptor;
class WebCLImageAdaptor;
class WebCLProgramAdaptor;
class WebCLSamplerAdaptor;
class WebCLUserEventAdaptor;

class WebCLContextAdaptor final : public GarbageCollectedFinalized<WebCLContextAdaptor>, public WebCLScriptWrappableAdaptor<WebCLContext>, public ScriptWrappable {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLContextAdaptor* create(WebCLContext*);
    ~WebCLContextAdaptor();

    WebCLBufferAdaptor* createBuffer(unsigned memFlags, unsigned sizeInBytes, ExceptionState&);
    WebCLBufferAdaptor* createBuffer(unsigned memFlags, unsigned sizeInBytes, DOMArrayBufferView*, ExceptionState&);
    WebCLCommandQueueAdaptor* createCommandQueue(ExceptionState&);
    WebCLCommandQueueAdaptor* createCommandQueue(WebCLDeviceAdaptor*, ExceptionState&);
    WebCLCommandQueueAdaptor* createCommandQueue(WebCLDeviceAdaptor*, unsigned properties, ExceptionState&);
    WebCLImageAdaptor* createImage(unsigned memFlags, const WebCLImageDescriptor&, ExceptionState&);
    WebCLImageAdaptor* createImage(unsigned memFlags, const WebCLImageDescriptor&, DOMArrayBufferView*, ExceptionState&);
    WebCLProgramAdaptor* createProgram(const String& source, ExceptionState&);
    WebCLSamplerAdaptor* createSampler(bool normalizedCoords, unsigned addressingMode, unsigned filterMode, ExceptionState&);
    WebCLUserEventAdaptor* createUserEvent(ExceptionState&);
    ScriptValue getInfo(ScriptState*, unsigned name, ExceptionState&);
    Nullable<HeapVector<WebCLImageDescriptor>> getSupportedImageFormats(ExceptionState&);
    Nullable<HeapVector<WebCLImageDescriptor>> getSupportedImageFormats(unsigned memFlags, ExceptionState&);
    void release();
    void releaseAll();

    // WEBCL_html_image extension
    WebCLBufferAdaptor* createBuffer(unsigned memFlags, ImageData*, ExceptionState&);
    WebCLBufferAdaptor* createBuffer(unsigned memFlags, HTMLCanvasElement*, ExceptionState&);
    WebCLBufferAdaptor* createBuffer(unsigned memFlags, HTMLImageElement*, ExceptionState&);
    WebCLImageAdaptor* createImage(unsigned memFlags, ImageData*, ExceptionState&);
    WebCLImageAdaptor* createImage(unsigned memFlags, HTMLCanvasElement*, ExceptionState&);
    WebCLImageAdaptor* createImage(unsigned memFlags, HTMLImageElement*, ExceptionState&);

    // WEBCL_html_video extension
    WebCLImageAdaptor* createImage(unsigned memFlags, HTMLVideoElement*, ExceptionState&);

    DEFINE_INLINE_TRACE() { }

private:
    WebCLContextAdaptor(WebCLContext*);
};

} // namespace blink

#endif // WebCLContextAdaptor_h
