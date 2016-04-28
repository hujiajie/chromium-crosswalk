// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLUserEventAdaptor_h
#define WebCLUserEventAdaptor_h

#include "bindings/core/v8/ExceptionState.h"
#include "modules/webcl/WebCLEventAdaptor.h"

namespace blink {

class WebCLUserEvent;

class WebCLUserEventAdaptor final : public WebCLEventAdaptor {
    DEFINE_WRAPPERTYPEINFO();
public:
    static WebCLUserEventAdaptor* create(WebCLUserEvent*);
    ~WebCLUserEventAdaptor();

    void setStatus(int executionStatus, ExceptionState&);

private:
    WebCLUserEventAdaptor(WebCLUserEvent*);
};

} // namespace blink

#endif // WebCLUserEventAdaptor_h
