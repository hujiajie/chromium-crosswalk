// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLUserEventAdaptor.h"

#include "modules/webcl/WebCLUserEvent.h"

namespace blink {

WebCLUserEventAdaptor* WebCLUserEventAdaptor::create(WebCLUserEvent* impl)
{
    return new WebCLUserEventAdaptor(impl);
}

WebCLUserEventAdaptor::WebCLUserEventAdaptor(WebCLUserEvent* impl)
    : WebCLEventAdaptor(impl)
{
}

WebCLUserEventAdaptor::~WebCLUserEventAdaptor()
{
}

void WebCLUserEventAdaptor::setStatus(int executionStatus, ExceptionState& exceptionState)
{
    WebCLUserEvent* impl = toWebCLImpl<WebCLUserEvent>();
    impl->setStatus(executionStatus, exceptionState);
}

} // namespace blink
