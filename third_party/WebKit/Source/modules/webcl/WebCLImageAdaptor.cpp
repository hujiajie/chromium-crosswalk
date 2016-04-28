// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLImageAdaptor.h"

#include "modules/webcl/WebCLImage.h"
#include "modules/webcl/WebCLImageDescriptor.h"

namespace blink {

WebCLImageAdaptor* WebCLImageAdaptor::create(WebCLImage* impl)
{
    return new WebCLImageAdaptor(impl);
}

WebCLImageAdaptor::WebCLImageAdaptor(WebCLImage* impl)
    : WebCLMemoryObjectAdaptor(impl)
{
}

WebCLImageAdaptor::~WebCLImageAdaptor()
{
}

void WebCLImageAdaptor::getInfo(ExceptionState& exceptionState, WebCLImageDescriptor& descriptor)
{
    WebCLImage* impl = toWebCLImpl<WebCLImage>();
    impl->getInfo(exceptionState, descriptor);
}

} // namespace blink
