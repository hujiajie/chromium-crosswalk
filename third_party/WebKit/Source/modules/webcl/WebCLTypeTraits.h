// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLTypeTraits_h
#define WebCLTypeTraits_h

namespace blink {

template<typename T>
class WebCLTypeTraits {
};

#define DEFINE_WEBCLTYPETRAITS(T) \
class T; \
class T##Adaptor; \
template<> class WebCLTypeTraits<T> { \
public: \
    typedef T##Adaptor AdaptorType; \
}

DEFINE_WEBCLTYPETRAITS(WebCL);
DEFINE_WEBCLTYPETRAITS(WebCLBuffer);
DEFINE_WEBCLTYPETRAITS(WebCLCommandQueue);
DEFINE_WEBCLTYPETRAITS(WebCLContext);
DEFINE_WEBCLTYPETRAITS(WebCLDevice);
DEFINE_WEBCLTYPETRAITS(WebCLEvent);
DEFINE_WEBCLTYPETRAITS(WebCLImage);
DEFINE_WEBCLTYPETRAITS(WebCLKernel);
DEFINE_WEBCLTYPETRAITS(WebCLKernelArgInfo);
DEFINE_WEBCLTYPETRAITS(WebCLMemoryObject);
DEFINE_WEBCLTYPETRAITS(WebCLPlatform);
DEFINE_WEBCLTYPETRAITS(WebCLProgram);
DEFINE_WEBCLTYPETRAITS(WebCLSampler);
DEFINE_WEBCLTYPETRAITS(WebCLUserEvent);

#undef DEFINE_WEBCLTYPETRAITS

} // namespace blink

#endif // WebCLTypeTraits_h
