// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webcl/WebCLKernelArgInfoAdaptor.h"

#include "modules/webcl/WebCLKernelArgInfo.h"

namespace blink {

WebCLKernelArgInfoAdaptor* WebCLKernelArgInfoAdaptor::create(WebCLKernelArgInfo* impl)
{
    return new WebCLKernelArgInfoAdaptor(impl);
}

WebCLKernelArgInfoAdaptor::WebCLKernelArgInfoAdaptor(WebCLKernelArgInfo* impl)
    : WebCLScriptWrappableAdaptor<WebCLKernelArgInfo>(impl)
{
}

WebCLKernelArgInfoAdaptor::~WebCLKernelArgInfoAdaptor()
{
}

const String& WebCLKernelArgInfoAdaptor::name()
{
    WebCLKernelArgInfo* impl = toWebCLImpl();
    return impl->name();
}

const String& WebCLKernelArgInfoAdaptor::typeName()
{
    WebCLKernelArgInfo* impl = toWebCLImpl();
    return impl->typeName();
}

const String& WebCLKernelArgInfoAdaptor::addressQualifier()
{
    WebCLKernelArgInfo* impl = toWebCLImpl();
    return impl->addressQualifier();
}

const String& WebCLKernelArgInfoAdaptor::accessQualifier()
{
    WebCLKernelArgInfo* impl = toWebCLImpl();
    return impl->accessQualifier();
}

} // namespace blink
