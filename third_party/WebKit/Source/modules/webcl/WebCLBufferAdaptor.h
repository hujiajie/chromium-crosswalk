// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLBufferAdaptor_h
#define WebCLBufferAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "modules/webcl/WebCLMemoryObjectAdaptor.h"

namespace blink {

class WebCLBuffer;

class WebCLBufferAdaptor final : public WebCLMemoryObjectAdaptor {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLBufferAdaptor* create(WebCLBuffer*);
    ~WebCLBufferAdaptor();

    WebCLBufferAdaptor* createSubBuffer(unsigned memFlags, unsigned origin, unsigned sizeInBytes, ExceptionState&);

private:
    WebCLBufferAdaptor(WebCLBuffer*);
};

} // namespace blink

#endif // WebCLBufferAdaptor_h
