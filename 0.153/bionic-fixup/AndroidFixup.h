/*
 * Copyright 2013, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_FIXUP_H
#define ANDROID_FIXUP_H

#include <libgen.h> // for basename

/* workaround for stpcpy */
static inline char *stpcpy(char *dst, const char *src)
{
    while (*src) {
        *dst++ = *src++;
    }
    // Need to copy the NULL terminator
    *dst = *src;
    return dst;
}

/* _mempcpy and mempcpy */
#ifndef __mempcpy
#define __mempcpy(dest, src, n)  mempcpy(dest, src, n)
#endif

#ifndef mempcpy
#include <string.h>

static inline void *mempcpy(void *dest, const void *src, size_t n)
{
    char *ptr = memcpy(dest, src, n);
    return ptr + n;
}
#endif

/* rawmemchr */
static inline void *rawmemchr(const void *s, int c)
{
    const unsigned char *ptr = s;
    while (1) {
        if (*ptr == c) return (void *) ptr;
        ptr++;
    }
}

/* workaround for canonicalize_file_name */
#define canonicalize_file_name(path) realpath(path, NULL)

/* workaround for open64 */
#define open64(path, flags)     open(path, ((flags) | O_LARGEFILE))

#endif /* ANDROID_FIXUP_H */
