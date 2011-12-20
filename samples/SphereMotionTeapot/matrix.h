/*
    File: matrix.h
Abstract: n/a
 Version: 1.0

Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple
Inc. ("Apple") in consideration of your agreement to the following
terms, and your use, installation, modification or redistribution of
this Apple software constitutes acceptance of these terms.  If you do
not agree with these terms, please do not use, install, modify or
redistribute this Apple software.

In consideration of your agreement to abide by the following terms, and
subject to these terms, Apple grants you a personal, non-exclusive
license, under Apple's copyrights in this original Apple software (the
"Apple Software"), to use, reproduce, modify and redistribute the Apple
Software, with or without modifications, in source and/or binary forms;
provided that if you redistribute the Apple Software in its entirety and
without modifications, you must retain this notice and the following
text and disclaimers in all such redistributions of the Apple Software.
Neither the name, trademarks, service marks or logos of Apple Inc. may
be used to endorse or promote products derived from the Apple Software
without specific prior written permission from Apple.  Except as
expressly stated in this notice, no other rights or licenses, express or
implied, are granted by Apple herein, including but not limited to any
patent rights that may be infringed by your derivative works or by other
works in which the Apple Software may be incorporated.

The Apple Software is provided by Apple on an "AS IS" basis.  APPLE
MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION
THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND
OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.

IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL
OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION,
MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED
AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE),
STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

Copyright (C) 2010 Apple Inc. All Rights Reserved.

*/

#include "vector.h"
#include "plane.h"

#include <stdint.h>

#ifndef MATRIX_H_GUARD
#define MATRIX_H_GUARD

//  column major order
typedef float mat4f_t[16];
typedef float mat3f_t[9];

void mat3f_from_mat4(const mat4f_t src, mat3f_t dst);

//  simple creation
void mat4f_identity(mat4f_t m);
void mat4f_copy(const mat4f_t src, mat4f_t dst);

//  basic transforms
void mat4f_initXRotation(float radians, mat4f_t mout);
void mat4f_initYRotation(float radians, mat4f_t mout);
void mat4f_initZRotation(float radians, mat4f_t mout);
void mat4f_initRotation(vec3f_t axis, float radians, mat4f_t mout);
void mat4f_initScale(vec3f_t s, mat4f_t mout);
void mat4f_initTranslation(vec3f_t t, mat4f_t mout);
void mat4f_initPerspective(float fovy_radians, float aspect, float zNear, float zFar, mat4f_t mout);

//  complex transforms
void mat4f_initProjectionToPlane(vec3f_t point, plane_t plane, mat4f_t mout);

//  accessors
vec4f_t mat4f_row(const mat4f_t m, uint8_t i);
vec4f_t mat4f_column(const mat4f_t m, uint8_t i);

//  matrix operations
void mat4f_transpose(const mat4f_t min, mat4f_t mout);
void mat4f_translate(const mat4f_t min, vec3f_t v, mat4f_t mout);
void mat4f_rotate(const mat4f_t min, vec3f_t axis, float radians, mat4f_t mout);
void mat4f_multiplyMatrix(const mat4f_t a, const mat4f_t b, mat4f_t mout);
void mat4f_inverse(const mat4f_t a, mat4f_t mout);
void mat4f_inverse_transpose(const mat4f_t a, mat4f_t mout);

//  in-place variants for matrix operations
void mat4f_translate_accum(mat4f_t m, vec3f_t v);
void mat4f_rotate_accum(mat4f_t m, vec3f_t axis, float radians);
void mat4f_scale_accum(mat4f_t m, vec3f_t s);

//  vector operations
vec4f_t mat4f_multiplyVector(const mat4f_t m, vec4f_t v);

#endif
