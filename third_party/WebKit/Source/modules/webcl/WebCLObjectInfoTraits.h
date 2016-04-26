// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebCLObjectInfoTraits_h
#define WebCLObjectInfoTraits_h

template<typename T>
class WebCLObjectInfoTraits {
public:
    typedef T ReturnType;
};

template<typename T>
class WebCLObjectInfoTraits<RefPtr<T>> {
public:
    typedef PassRefPtr<T> ReturnType;
};

#endif // WebCLObjectInfoTraits_h
