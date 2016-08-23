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
#ifndef LD2016_ECSCOREAUTOGENFOREACH_H
#define LD2016_ECSCOREAUTOGENFOREACH_H

// Provides variadic argument count
#define _GET_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, \
                  _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _N, ...) _N

// The individual iterations of the for each (see DO_FOR_EACH below)
#define _i0(action, ...)
#define _i1(action, arg)      action(arg, 0)
#define _i2(action, arg, ...) action(arg, 1) _i1(action, __VA_ARGS__)
#define _i3(action, arg, ...) action(arg, 2) _i2(action, __VA_ARGS__)
#define _i4(action, arg, ...) action(arg, 3) _i3(action, __VA_ARGS__)
#define _i5(action, arg, ...) action(arg, 4) _i4(action, __VA_ARGS__)
#define _i6(action, arg, ...) action(arg, 5) _i5(action, __VA_ARGS__)
#define _i7(action, arg, ...) action(arg, 6) _i6(action, __VA_ARGS__)
#define _i8(action, arg, ...) action(arg, 7) _i7(action, __VA_ARGS__)
#define _i9(action, arg, ...) action(arg, 8) _i8(action, __VA_ARGS__)
#define _i10(action, arg, ...) action(arg, 9) _i9(action, __VA_ARGS__)
#define _i11(action, arg, ...) action(arg, 10) _i10(action, __VA_ARGS__)
#define _i12(action, arg, ...) action(arg, 11) _i11(action, __VA_ARGS__)
#define _i13(action, arg, ...) action(arg, 12) _i12(action, __VA_ARGS__)
#define _i14(action, arg, ...) action(arg, 13) _i13(action, __VA_ARGS__)
#define _i15(action, arg, ...) action(arg, 14) _i14(action, __VA_ARGS__)
#define _i16(action, arg, ...) action(arg, 15) _i15(action, __VA_ARGS__)
#define _i17(action, arg, ...) action(arg, 16) _i16(action, __VA_ARGS__)
#define _i18(action, arg, ...) action(arg, 17) _i17(action, __VA_ARGS__)
#define _i19(action, arg, ...) action(arg, 18) _i18(action, __VA_ARGS__)
#define _i20(action, arg, ...) action(arg, 19) _i19(action, __VA_ARGS__)
#define _i21(action, arg, ...) action(arg, 20) _i20(action, __VA_ARGS__)
#define _i22(action, arg, ...) action(arg, 21) _i21(action, __VA_ARGS__)
#define _i23(action, arg, ...) action(arg, 22) _i22(action, __VA_ARGS__)
#define _i24(action, arg, ...) action(arg, 23) _i23(action, __VA_ARGS__)
#define _i25(action, arg, ...) action(arg, 24) _i24(action, __VA_ARGS__)
#define _i26(action, arg, ...) action(arg, 25) _i25(action, __VA_ARGS__)
#define _i27(action, arg, ...) action(arg, 26) _i26(action, __VA_ARGS__)
#define _i28(action, arg, ...) action(arg, 27) _i27(action, __VA_ARGS__)
#define _i29(action, arg, ...) action(arg, 28) _i28(action, __VA_ARGS__)
#define _i30(action, arg, ...) action(arg, 29) _i29(action, __VA_ARGS__)
#define _i31(action, arg, ...) action(arg, 30) _i30(action, __VA_ARGS__)
#define _i32(action, arg, ...) action(arg, 31) _i31(action, __VA_ARGS__)

/**
 * Variadic Macro For-each. 'action' must be a macro which takes two arguments,
 * the second one being an iteration counter.
 * 'action' may be followed by up to 32 comma separated items
 * which will consecutively be given to the 'action' macro.
 */
#define DO_FOR_EACH(action, ...) \
    _GET_ARG_N(placeholder, ##__VA_ARGS__, \
    _i32, _i31, _i30, _i29, _i28, _i27, _i26, _i25, _i24, _i23, _i22, _i21, _i20, _i19, _i18, _i17, _i16, \
    _i15, _i14, _i13, _i12, _i11, _i10, _i9, _i8, _i7, _i6, _i5, _i4, _i3, _i2, _i1, _i0) \
    (action, ##__VA_ARGS__)

/*// Used in DO_FOR_EACH_PAIR below.
#define _a0(action, ...)
#define _a2(action, arg0, arg1, ...) action(arg0, arg1) _a0(action, __VA_ARGS__)
#define _a4(action, arg0, arg1, ...) action(arg0, arg1) _a2(action, __VA_ARGS__)
#define _a6(action, arg0, arg1, ...) action(arg0, arg1) _a4(action, __VA_ARGS__)
#define _a8(action, arg0, arg1, ...) action(arg0, arg1) _a6(action, __VA_ARGS__)
#define _a10(action, arg0, arg1, ...) action(arg0, arg1) _a8(action, __VA_ARGS__)
#define _a12(action, arg0, arg1, ...) action(arg0, arg1) _a10(action, __VA_ARGS__)
#define _a14(action, arg0, arg1, ...) action(arg0, arg1) _a12(action, __VA_ARGS__)
#define _a16(action, arg0, arg1, ...) action(arg0, arg1) _a14(action, __VA_ARGS__)
#define _a18(action, arg0, arg1, ...) action(arg0, arg1) _a16(action, __VA_ARGS__)
#define _a20(action, arg0, arg1, ...) action(arg0, arg1) _a18(action, __VA_ARGS__)
#define _a22(action, arg0, arg1, ...) action(arg0, arg1) _a20(action, __VA_ARGS__)
#define _a24(action, arg0, arg1, ...) action(arg0, arg1) _a22(action, __VA_ARGS__)
#define _a26(action, arg0, arg1, ...) action(arg0, arg1) _a24(action, __VA_ARGS__)
#define _a28(action, arg0, arg1, ...) action(arg0, arg1) _a26(action, __VA_ARGS__)
#define _a30(action, arg0, arg1, ...) action(arg0, arg1) _a28(action, __VA_ARGS__)
#define _a32(action, arg0, arg1, ...) action(arg0, arg1) _a30(action, __VA_ARGS__)

*//**
 * Also iterates through variadic macro, but does so two at a time.
 * Accepts action, therefore, that acts upon two arguments.
 * If an odd number of variadic argments are provided, the last is neglected.
 *//*
#define DO_FOR_EACH_PAIR(action, ...) \
    _GET_ARG_N(placeholder, ##__VA_ARGS__, \
    _a32, _a30, _a30, _a28, _a28, _a26, _a26, _a24, _a24, _a22, _a22, _a20, _a20, _a18, _a18, _a16, _a16, \
    _a14, _a14, _a12, _a12, _a10, _a10, _a8, _a8, _a6, _a6, _a4, _a4, _a2, _a2, _a0, _a0) \
    (action, ##__VA_ARGS__)*/

/*#define _p0(action, ...)
#define _p1(action, arg)      action(arg, 0)
#define _p2(action, arg, ...) action(arg, 1) _p1(action, __VA_ARGS__)
#define _p3(action, arg, ...) action(arg, 2) _p2(action, __VA_ARGS__)
#define _p4(action, arg, ...) action(arg, 3) _p3(action, __VA_ARGS__)
#define _p5(action, arg, ...) action(arg, 4) _p4(action, __VA_ARGS__)
#define _p6(action, arg, ...) action(arg, 5) _p5(action, __VA_ARGS__)
#define _p7(action, arg, ...) action(arg, 6) _p6(action, __VA_ARGS__)
#define _p8(action, arg, ...) action(arg, 7) _p7(action, __VA_ARGS__)
#define _p9(action, arg, ...) action(arg, 8) _p8(action, __VA_ARGS__)
#define _p10(action, arg, ...) action(arg, 9) _p9(action, __VA_ARGS__)
#define _p11(action, arg, ...) action(arg, 10) _p10(action, __VA_ARGS__)
#define _p12(action, arg, ...) action(arg, 11) _p11(action, __VA_ARGS__)
#define _p13(action, arg, ...) action(arg, 12) _p12(action, __VA_ARGS__)
#define _p14(action, arg, ...) action(arg, 13) _p13(action, __VA_ARGS__)
#define _p15(action, arg, ...) action(arg, 14) _p14(action, __VA_ARGS__)
#define _p16(action, arg, ...) action(arg, 15) _p15(action, __VA_ARGS__)
#define _p17(action, arg, ...) action(arg, 16) _p16(action, __VA_ARGS__)
#define _p18(action, arg, ...) action(arg, 17) _p17(action, __VA_ARGS__)
#define _p19(action, arg, ...) action(arg, 18) _p18(action, __VA_ARGS__)
#define _p20(action, arg, ...) action(arg, 19) _p19(action, __VA_ARGS__)
#define _p21(action, arg, ...) action(arg, 20) _p20(action, __VA_ARGS__)
#define _p22(action, arg, ...) action(arg, 21) _p21(action, __VA_ARGS__)
#define _p23(action, arg, ...) action(arg, 22) _p22(action, __VA_ARGS__)
#define _p24(action, arg, ...) action(arg, 23) _p23(action, __VA_ARGS__)
#define _p25(action, arg, ...) action(arg, 24) _p24(action, __VA_ARGS__)
#define _p26(action, arg, ...) action(arg, 25) _p25(action, __VA_ARGS__)
#define _p27(action, arg, ...) action(arg, 26) _p26(action, __VA_ARGS__)
#define _p28(action, arg, ...) action(arg, 27) _p27(action, __VA_ARGS__)
#define _p29(action, arg, ...) action(arg, 28) _p28(action, __VA_ARGS__)
#define _p30(action, arg, ...) action(arg, 29) _p29(action, __VA_ARGS__)
#define _p31(action, arg, ...) action(arg, 30) _p30(action, __VA_ARGS__)
#define _p32(action, arg, ...) action(arg, 31) _p31(action, __VA_ARGS__)*/

#endif //LD2016_ECSCOREAUTOGENFOREACH_H
