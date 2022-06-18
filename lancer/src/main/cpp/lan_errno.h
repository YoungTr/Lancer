// Copyright (c) 2019-present, iQIYI, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

// Created by caikelun on 2019-03-07.

#ifndef LANCER_ERRNO_H
#define LANCER_ERRNO_H 1

#include <errno.h>

#define LANCER_ERRNO_UNKNOWN  1001
#define LANCER_ERRNO_INVAL    1002
#define LANCER_ERRNO_NOMEM    1003
#define LANCER_ERRNO_NOSPACE  1004
#define LANCER_ERRNO_RANGE    1005
#define LANCER_ERRNO_NOTFND   1006
#define LANCER_ERRNO_MISSING  1007
#define LANCER_ERRNO_MEM      1008
#define LANCER_ERRNO_DEV      1009
#define LANCER_ERRNO_PERM     1010
#define LANCER_ERRNO_FORMAT   1011
#define LANCER_ERRNO_ILLEGAL  1012
#define LANCER_ERRNO_NOTSPT   1013
#define LANCER_ERRNO_STATE    1014
#define LANCER_ERRNO_JNI      1015
#define LANCER_ERRNO_FD       1016

#define LANCER_ERRNO_SYS     ((0 != errno) ? errno : LANCER_ERRNO_UNKNOWN)

#endif
