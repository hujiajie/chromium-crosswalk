// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLImageAdaptor_h
#define WebCLImageAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "modules/webcl/WebCLMemoryObjectAdaptor.h"

namespace blink {

class WebCLImage;
class WebCLImageDescriptor;

class WebCLImageAdaptor final : public WebCLMemoryObjectAdaptor {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLImageAdaptor* create(WebCLImage*);
    ~WebCLImageAdaptor();

    void getInfo(ExceptionState&, WebCLImageDescriptor&);

private:
    WebCLImageAdaptor(WebCLImage*);
};

} // namespace blink

#endif // WebCLImageAdaptor_h
