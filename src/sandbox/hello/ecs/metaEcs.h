/*
 * Copyright (c) 2016 Galen Cochrane
 * Galen Cochrane <galencochrane@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef LD2016_TYPES_H
#define LD2016_TYPES_H

#include <stdint.h>

namespace ld2016 {
  typedef uint32_t entityId;
  typedef uint32_t compMask;

  enum ComponentTypes {
    NONE              = 0     ,
    ALL               = -1    ,
    ENUM_Existence    = 1 << 0,
    ENUM_Position     = 1 << 1,
    ENUM_LinearVel    = 1 << 2,
    ENUM_Orientation  = 1 << 3,
    ENUM_AngularVel   = 1 << 4,
    ENUM_CameraView   = 1 << 5,
    ENUM_WasdControls = 1 << 6,
  };
  enum CompOpReturn {
    SUCCESS,
    NONEXISTANT,
    REDUNDANT,
    PREREQ_FAIL,
    INVALID_STATE,
  };
}

#endif //LD2016_TYPES_H
