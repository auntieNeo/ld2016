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
#include "components.h"

namespace ld2016 {
  #define COMP_DEFN_REQD(comp, flags) template<> compMask Component<comp>::requiredComps = flags
  #define COMP_DEFN_DEPN(comp, flags) template<> compMask Component<comp>::dependentComps = flags

  COMP_DEFN_REQD(Existence, NONE);
  COMP_DEFN_REQD(Position, ENUM_Existence);
  COMP_DEFN_REQD(LinearVel, ENUM_Existence | ENUM_Position);
  COMP_DEFN_REQD(Orientation, ENUM_Existence);
  COMP_DEFN_REQD(AngularVel, ENUM_Existence | ENUM_Orientation);
  COMP_DEFN_REQD(CameraView, ENUM_Existence | ENUM_Position | ENUM_Orientation);
  COMP_DEFN_REQD(WasdControls, ENUM_Existence | ENUM_Position | ENUM_LinearVel | ENUM_Orientation | ENUM_AngularVel);

  COMP_DEFN_DEPN(Existence, ALL);
  COMP_DEFN_DEPN(Position, ENUM_LinearVel | ENUM_CameraView | ENUM_WasdControls);
  COMP_DEFN_DEPN(LinearVel, ENUM_WasdControls);
  COMP_DEFN_DEPN(Orientation, ENUM_AngularVel | ENUM_CameraView | ENUM_WasdControls);
  COMP_DEFN_DEPN(AngularVel, ENUM_WasdControls);
  COMP_DEFN_DEPN(CameraView, NONE);
  COMP_DEFN_DEPN(WasdControls, NONE);

  #undef COMP_DEFN_REQD
  #undef COMP_DEFN_DEPN
}
