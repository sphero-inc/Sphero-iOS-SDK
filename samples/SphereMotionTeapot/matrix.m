/*
    File: matrix.m
Abstract: Matrix utilities.
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


#include "matrix.h"

#include <string.h>
#include <assert.h>
#include <math.h>

void mat3f_from_mat4(const mat4f_t src, mat3f_t dst)
{
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	
	dst[3] = src[4];
	dst[4] = src[5];
	dst[5] = src[6];
	
	dst[6] = src[8];
	dst[7] = src[9];
	dst[8] = src[10];
}

void mat4f_identity(mat4f_t m)
{
	m[0] = 1.0f;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = 0.0f;
	
	m[4] = 0.0f;
	m[5] = 1.0f;
	m[6] = 0.0f;
	m[7] = 0.0f;
	
	m[8] = 0.0f;
	m[9] = 0.0f;
	m[10] = 1.0f;
	m[11] = 0.0f;	

	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 0.0f;
	m[15] = 1.0f;
}

void mat4f_copy(const mat4f_t a, mat4f_t b)
{
	memcpy(b, a, 16*sizeof(float));
}

vec4f_t mat4f_row(const mat4f_t m, uint8_t i)
{
	assert(i <= 3);
	return vec4f_init(m[i*4+0], m[i*4+1], m[i*4+2], m[i*4+3]);
}

vec4f_t mat4f_column(const mat4f_t m, uint8_t i)
{
	assert(i <= 3);
	return vec4f_init(m[0*4+i], m[1*4+i], m[2*4+i], m[3*4+i]);
}

void mat4f_multiplyMatrix(const mat4f_t a, const mat4f_t b, mat4f_t c)
{
	//  FIXME: performance
	uint8_t col, row, i;
	memset(c, 0, 16*sizeof(float));
	
	for (col = 0; col < 4; col++) {
		for (row = 0; row < 4; row++) {
			for (i = 0; i < 4; i++) {
				c[col*4+row] += a[i*4+row]*b[col*4+i];
			}
		}
	}
}

vec4f_t mat4f_multiplyVector(const mat4f_t m, vec4f_t v)
{
	float x = m[0]*v.x + m[4]*v.y + m[8]*v.z + m[12]*v.w;
	float y = m[1]*v.x + m[5]*v.y + m[9]*v.z + m[13]*v.w;
	float z = m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14]*v.w;
	float w = m[3]*v.x + m[7]*v.y + m[11]*v.z + m[15]*v.w;
	return vec4f_init(x, y, z, w);	
}

void mat4f_initXRotation(float radians, mat4f_t m)
{
	float cosrad = cosf(radians);
	float sinrad = sinf(radians);
	
	m[0] = 1.0f;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = 0.0f;
	
	m[4] = 0.0f;
	m[5] = cosrad;
	m[6] = sinrad;
	m[7] = 0.0f;
	
	m[8] = 0.0f;
	m[9] = -sinrad;
	m[10] = cosrad;
	m[11] = 0.0f;	
	
	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 0.0f;
	m[15] = 1.0f;
}

void mat4f_initYRotation(float radians, mat4f_t mout)
{
	float cosrad = cosf(radians);
	float sinrad = sinf(radians);
	
	mout[0] = cosrad;
	mout[1] = 0.0f;
	mout[2] = -sinrad;
	mout[3] = 0.0f;
	
	mout[4] = 0.0f;
	mout[5] = 1.0f;
	mout[6] = 0.0f;
	mout[7] = 0.0f;
	
	mout[8] = sinrad;
	mout[9] = 0.0f;
	mout[10] = cosrad;
	mout[11] = 0.0f;	
	
	mout[12] = 0.0f;
	mout[13] = 0.0f;
	mout[14] = 0.0f;
	mout[15] = 1.0f;
}

void mat4f_initZRotation(float radians, mat4f_t mout)
{
	float cosrad = cosf(radians);
	float sinrad = sinf(radians);
	
	mout[0] = cosrad;
	mout[1] = sinrad;
	mout[2] = 0.0f;
	mout[3] = 0.0f;
	
	mout[4] = -sinrad;
	mout[5] = cosrad;
	mout[6] = 0.0f;
	mout[7] = 0.0f;
	
	mout[8] = 0.0f;
	mout[9] = 0.0f;
	mout[10] = 1.0f;
	mout[11] = 0.0f;	
	
	mout[12] = 0.0f;
	mout[13] = 0.0f;
	mout[14] = 0.0f;
	mout[15] = 1.0f;
}

//  Eq. 3.27 in Real-Time Rendering, 2nd Edition
void mat4f_initRotation(vec3f_t axis, float radians, mat4f_t mout)
{
	axis = vec3f_normalize(axis);
	
	float c = cos(radians);
	float s = sin(radians);
	float c1 = 1-c;
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	
	mout[0] = x*x*c1+c;
	mout[1] = y*x*c1+z*s;
	mout[2] = x*z*c1-y*s;
	mout[3] = 0.0f;
	
	mout[4] = x*y*c1-z*s;
	mout[5] = y*y*c1+c;
	mout[6] = y*z*c1+x*s;
	mout[7] = 0.0f;
	
	mout[8] = x*z*c1+y*s;
	mout[9] = y*z*c1-x*s;
	mout[10] = z*z*c1+c;
	mout[11] = 0.0f;	
	
	mout[12] = 0.0f;
	mout[13] = 0.0f;
	mout[14] = 0.0f;
	mout[15] = 1.0f;
}

void mat4f_initTranslation(vec3f_t v, mat4f_t mout)
{
	mout[0] = 1.0f;
	mout[1] = 0.0f;
	mout[2] = 0.0f;
	mout[3] = 0.0f;
	
	mout[4] = 0.0f;
	mout[5] = 1.0f;
	mout[6] = 0.0f;
	mout[7] = 0.0f;
	
	mout[8] = 0.0f;
	mout[9] = 0.0f;
	mout[10] = 1.0f;
	mout[11] = 0.0f;	
	
	mout[12] = v.x;
	mout[13] = v.y;
	mout[14] = v.z;
	mout[15] = 1.0f;
}

void mat4f_initScale(vec3f_t s, mat4f_t mout)
{
	mout[0] = s.x;
	mout[1] = 0.0f;
	mout[2] = 0.0f;
	mout[3] = 0.0f;
	
	mout[4] = 0.0f;
	mout[5] = s.y;
	mout[6] = 0.0f;
	mout[7] = 0.0f;
	
	mout[8] = 0.0f;
	mout[9] = 0.0f;
	mout[10] = s.z;
	mout[11] = 0.0f;	
	
	mout[12] = 0.0f;
	mout[13] = 0.0f;
	mout[14] = 0.0f;
	mout[15] = 1.0f;
}

void mat4f_initPerspective(float fovy, float aspect, float zNear, float zFar, mat4f_t mout)
{
	float f = 1.0f / tanf(fovy/2.0f);
	
	mout[0] = f / aspect;
	mout[1] = 0.0f;
	mout[2] = 0.0f;
	mout[3] = 0.0f;
	
	mout[4] = 0.0f;
	mout[5] = f;
	mout[6] = 0.0f;
	mout[7] = 0.0f;
	
	mout[8] = 0.0f;
	mout[9] = 0.0f;
	mout[10] = (zFar+zNear) / (zNear-zFar);
	mout[11] = -1.0f;
	
	mout[12] = 0.0f;
	mout[13] = 0.0f;
	mout[14] = 2 * zFar * zNear /  (zNear-zFar);
	mout[15] = 0.0f;
}

void mat4f_initProjectionToPlane(vec3f_t l, plane_t p, mat4f_t mout)
{
	mout[0] = vec3f_dotProduct(l, p.normal) + p.dist - (l.x*p.normal.x);
	mout[1] = -l.y * p.normal.x;
	mout[2] = -l.z * p.normal.x;
	mout[3] = -p.normal.x;
	
	mout[4] = -l.x*p.normal.y;
	mout[5] = vec3f_dotProduct(l, p.normal) + p.dist - (l.y*p.normal.y);
	mout[6] = -l.z*p.normal.y;
	mout[7] = -p.normal.y;
	
	mout[8] = -l.x*p.normal.z;
	mout[9] = -l.y*p.normal.z;
	mout[10] = vec3f_dotProduct(l, p.normal) + p.dist - (l.z*p.normal.z);
	mout[11] = -p.normal.z;
	
	mout[12] = -l.x*p.dist;
	mout[13] = -l.y*p.dist;
	mout[14] = -l.z*p.dist;
	mout[15] = vec3f_dotProduct(l, p.normal);
}

void mat4f_translate(const mat4f_t min, vec3f_t v, mat4f_t mout)
{
	assert((void*)min != mout);
	
	mout[0] = min[0];
	mout[1] = min[1];
	mout[2] = min[2];
	mout[3] = min[3];
	
	mout[4] = min[4];
	mout[5] = min[5];
	mout[6] = min[6];
	mout[7] = min[7];
	
	mout[8] = min[8];
	mout[9] = min[9];
	mout[10] = min[10];
	mout[11] = min[11];
	
	mout[12] = min[0]*v.x + min[4]*v.y + min[8]*v.z + min[12];
	mout[13] = min[1]*v.x + min[5]*v.y + min[9]*v.z + min[13];
	mout[14] = min[2]*v.x + min[6]*v.y + min[10]*v.z + min[14];	
	mout[15] = min[15];
}

void mat4f_translate_accum(mat4f_t m, vec3f_t v)
{
	m[12] += m[0]*v.x + m[4]*v.y + m[8]*v.z;
	m[13] += m[1]*v.x + m[5]*v.y + m[9]*v.z;
	m[14] += m[2]*v.x + m[6]*v.y + m[10]*v.z;		
}

void mat4f_rotate(const mat4f_t min, vec3f_t axis, float radians, mat4f_t mout)
{
	mat4f_t rot;
	
	assert((void*)min != mout);	

	//  FIXME: performance
	mat4f_initRotation(axis, radians, rot);
	mat4f_multiplyMatrix(min, rot, mout);
}

void mat4f_rotate_accum(mat4f_t m, vec3f_t axis, float radians)
{
	mat4f_t temp;
	mat4f_copy(m, temp);
	mat4f_rotate(temp, axis, radians, m);
}

void mat4f_scale_accum(mat4f_t m, vec3f_t s)
{
	m[0]  *= s.x;
	m[1]  *= s.x;
	m[2]  *= s.x;
	m[3]  *= s.x;
	
	m[4]  *= s.y;
	m[5]  *= s.y;
	m[6]  *= s.y;
	m[7]  *= s.y;
	
	m[8] *= s.z;
	m[9] *= s.z;
	m[10] *= s.z;
	m[11] *= s.z;
}

void mat4f_transpose(const mat4f_t min, mat4f_t mout)
{
	mout[0]  = min[0];
	mout[4]  = min[1];
	mout[8]  = min[2];
	mout[12] = min[3];
	mout[1]  = min[4];
	mout[5]  = min[5];
	mout[9]  = min[6];
	mout[13] = min[7];
	mout[2]  = min[8];
	mout[6]  = min[9];
	mout[10] = min[10];
	mout[14] = min[11];
	mout[3]  = min[12];
	mout[7]  = min[13];
	mout[11] = min[14];
	mout[15] = min[15];	
}

void mat4f_inverse(const mat4f_t min, mat4f_t mt2)
{
	float val, val2, val_inv, zero, one;
	int i, j, i4, i8, i12, ind;
	mat4f_t mt1;

	mat4f_copy(min, mt1);
	 
	zero = 0.0f;
	one  = 1.0f;
	mt2[ 0] = one ; mt2[ 1] = zero; mt2[ 2] = zero; mt2[ 3] = zero;
	mt2[ 4] = zero; mt2[ 5] = one ; mt2[ 6] = zero; mt2[ 7] = zero;
	mt2[ 8] = zero; mt2[ 9] = zero; mt2[10] = one ; mt2[11] = zero;
	mt2[12] = zero; mt2[13] = zero; mt2[14] = zero; mt2[15] = one ;
	
	for(i = 0; i != 4; i++)
	{
		val = mt1[(i << 2) + i];
		ind = i;
		
		i4  = i + 4;
		i8  = i + 8;
		i12 = i + 12;
		
		for (j = i + 1; j != 4; j++)
		{
			if(fabsf(mt1[(i << 2) + j]) > fabsf(val))
			{
				ind = j;
				val = mt1[(i << 2) + j];
			}
		}
		
		if(ind != i)
		{
			val2      = mt2[i];
			mt2[i]    = mt2[ind];
			mt2[ind]  = val2;
			
			val2      = mt1[i];
			mt1[i]    = mt1[ind];
			mt1[ind]  = val2;
			
			ind += 4;
			
			val2      = mt2[i4];
			mt2[i4]   = mt2[ind];
			mt2[ind]  = val2;
			
			val2      = mt1[i4];
			mt1[i4]   = mt1[ind];
			mt1[ind]  = val2;
			
			ind += 4;
			
			val2      = mt2[i8];
			mt2[i8]   = mt2[ind];
			mt2[ind]  = val2;
			
			val2      = mt1[i8];
			mt1[i8]   = mt1[ind];
			mt1[ind]  = val2;
			
			ind += 4;
			
			val2      = mt2[i12];
			mt2[i12]  = mt2[ind];
			mt2[ind]  = val2;
			
			val2      = mt1[i12];
			mt1[i12]  = mt1[ind];
			mt1[ind]  = val2;
		}
		
		if(val == zero)
		{
			mt2[ 0] = one ; mt2[ 1] = zero; mt2[ 2] = zero; mt2[ 3] = zero;
			mt2[ 4] = zero; mt2[ 5] = one ; mt2[ 6] = zero; mt2[ 7] = zero;
			mt2[ 8] = zero; mt2[ 9] = zero; mt2[10] = one ; mt2[11] = zero;
			mt2[12] = zero; mt2[13] = zero; mt2[14] = zero; mt2[15] = one ;
			return;
		}
		
		val_inv = one / val;
		
		mt1[i]   *= val_inv;
		mt2[i]   *= val_inv;
		
		mt1[i4]  *= val_inv;
		mt2[i4]  *= val_inv;
		
		mt1[i8]  *= val_inv;
		mt2[i8]  *= val_inv;
		
		mt1[i12] *= val_inv;
		mt2[i12] *= val_inv;
		
		if(i != 0)
		{
			val = mt1[i << 2];
			
			mt1[0]  -= mt1[i]   * val;
			mt2[0]  -= mt2[i]   * val;
			
			mt1[4]  -= mt1[i4]  * val;
			mt2[4]  -= mt2[i4]  * val;
			
			mt1[8]  -= mt1[i8]  * val;
			mt2[8]  -= mt2[i8]  * val;
			
			mt1[12] -= mt1[i12] * val;
			mt2[12] -= mt2[i12] * val;
		}
		
		if(i != 1)
		{
			val = mt1[(i << 2) + 1];
			
			mt1[1]  -= mt1[i]   * val;
			mt2[1]  -= mt2[i]   * val;
			
			mt1[5]  -= mt1[i4]  * val;
			mt2[5]  -= mt2[i4]  * val;
			
			mt1[9]  -= mt1[i8]  * val;
			mt2[9]  -= mt2[i8]  * val;
			
			mt1[13] -= mt1[i12] * val;
			mt2[13] -= mt2[i12] * val;
		}
		
		if(i != 2)
		{
			val = mt1[(i << 2) + 2];
			
			mt1[2]  -= mt1[i]   * val;
			mt2[2]  -= mt2[i]   * val;
			
			mt1[6]  -= mt1[i4]  * val;
			mt2[6]  -= mt2[i4]  * val;
			
			mt1[10] -= mt1[i8]  * val;
			mt2[10] -= mt2[i8]  * val;
			
			mt1[14] -= mt1[i12] * val;
			mt2[14] -= mt2[i12] * val;
		}
		
		if(i != 3)
		{
			val = mt1[(i << 2) + 3];
			
			mt1[3]  -= mt1[i]   * val;
			mt2[3]  -= mt2[i]   * val;
			
			mt1[7]  -= mt1[i4]  * val;
			mt2[7]  -= mt2[i4]  * val;
			
			mt1[11] -= mt1[i8]  * val;
			mt2[11] -= mt2[i8]  * val;
			
			mt1[15] -= mt1[i12] * val;
			mt2[15] -= mt2[i12] * val;
		}
	}
}

void mat4f_inverse_transpose(const mat4f_t min, mat4f_t mt2)
{
	float val, val2, val_inv, zero, one;
	int i, j, i4, i8, i12, ind;
	mat4f_t mt1;
	
	mt1[0]  = min[0];
	mt1[4]  = min[1];
	mt1[8]  = min[2];
	mt1[12] = min[3];
	mt1[1]  = min[4];
	mt1[5]  = min[5];
	mt1[9]  = min[6];
	mt1[13] = min[7];
	mt1[2]  = min[8];
	mt1[6]  = min[9];
	mt1[10] = min[10];
	mt1[14] = min[11];
	mt1[3]  = min[12];
	mt1[7]  = min[13];
	mt1[11] = min[14];
	mt1[15] = min[15];
	
	zero = 0.0f;
	one  = 1.0f;
	mt2[ 0] = one ; mt2[ 1] = zero; mt2[ 2] = zero; mt2[ 3] = zero;
	mt2[ 4] = zero; mt2[ 5] = one ; mt2[ 6] = zero; mt2[ 7] = zero;
	mt2[ 8] = zero; mt2[ 9] = zero; mt2[10] = one ; mt2[11] = zero;
	mt2[12] = zero; mt2[13] = zero; mt2[14] = zero; mt2[15] = one ;
	
	for(i = 0; i != 4; i++)
	{
		val = mt1[(i << 2) + i];
		ind = i;
		
		i4  = i + 4;
		i8  = i + 8;
		i12 = i + 12;
		
		for (j = i + 1; j != 4; j++)
		{
			if(fabsf(mt1[(i << 2) + j]) > fabsf(val))
			{
				ind = j;
				val = mt1[(i << 2) + j];
			}
		}
		
		if(ind != i)
		{
			val2      = mt2[i];
			mt2[i]    = mt2[ind];
			mt2[ind]  = val2;
			
			val2      = mt1[i];
			mt1[i]    = mt1[ind];
			mt1[ind]  = val2;
			
			ind += 4;
			
			val2      = mt2[i4];
			mt2[i4]   = mt2[ind];
			mt2[ind]  = val2;
			
			val2      = mt1[i4];
			mt1[i4]   = mt1[ind];
			mt1[ind]  = val2;
			
			ind += 4;
			
			val2      = mt2[i8];
			mt2[i8]   = mt2[ind];
			mt2[ind]  = val2;
			
			val2      = mt1[i8];
			mt1[i8]   = mt1[ind];
			mt1[ind]  = val2;
			
			ind += 4;
			
			val2      = mt2[i12];
			mt2[i12]  = mt2[ind];
			mt2[ind]  = val2;
			
			val2      = mt1[i12];
			mt1[i12]  = mt1[ind];
			mt1[ind]  = val2;
		}
		
		if(val == zero)
		{
			mt2[ 0] = one ; mt2[ 1] = zero; mt2[ 2] = zero; mt2[ 3] = zero;
			mt2[ 4] = zero; mt2[ 5] = one ; mt2[ 6] = zero; mt2[ 7] = zero;
			mt2[ 8] = zero; mt2[ 9] = zero; mt2[10] = one ; mt2[11] = zero;
			mt2[12] = zero; mt2[13] = zero; mt2[14] = zero; mt2[15] = one ;
			return;
		}
		
		val_inv = one / val;
		
		mt1[i]   *= val_inv;
		mt2[i]   *= val_inv;
		
		mt1[i4]  *= val_inv;
		mt2[i4]  *= val_inv;
		
		mt1[i8]  *= val_inv;
		mt2[i8]  *= val_inv;
		
		mt1[i12] *= val_inv;
		mt2[i12] *= val_inv;
		
		if(i != 0)
		{
			val = mt1[i << 2];
			
			mt1[0]  -= mt1[i]   * val;
			mt2[0]  -= mt2[i]   * val;
			
			mt1[4]  -= mt1[i4]  * val;
			mt2[4]  -= mt2[i4]  * val;
			
			mt1[8]  -= mt1[i8]  * val;
			mt2[8]  -= mt2[i8]  * val;
			
			mt1[12] -= mt1[i12] * val;
			mt2[12] -= mt2[i12] * val;
		}
		
		if(i != 1)
		{
			val = mt1[(i << 2) + 1];
			
			mt1[1]  -= mt1[i]   * val;
			mt2[1]  -= mt2[i]   * val;
			
			mt1[5]  -= mt1[i4]  * val;
			mt2[5]  -= mt2[i4]  * val;
			
			mt1[9]  -= mt1[i8]  * val;
			mt2[9]  -= mt2[i8]  * val;
			
			mt1[13] -= mt1[i12] * val;
			mt2[13] -= mt2[i12] * val;
		}
		
		if(i != 2)
		{
			val = mt1[(i << 2) + 2];
			
			mt1[2]  -= mt1[i]   * val;
			mt2[2]  -= mt2[i]   * val;
			
			mt1[6]  -= mt1[i4]  * val;
			mt2[6]  -= mt2[i4]  * val;
			
			mt1[10] -= mt1[i8]  * val;
			mt2[10] -= mt2[i8]  * val;
			
			mt1[14] -= mt1[i12] * val;
			mt2[14] -= mt2[i12] * val;
		}
		
		if(i != 3)
		{
			val = mt1[(i << 2) + 3];
			
			mt1[3]  -= mt1[i]   * val;
			mt2[3]  -= mt2[i]   * val;
			
			mt1[7]  -= mt1[i4]  * val;
			mt2[7]  -= mt2[i4]  * val;
			
			mt1[11] -= mt1[i8]  * val;
			mt2[11] -= mt2[i8]  * val;
			
			mt1[15] -= mt1[i12] * val;
			mt2[15] -= mt2[i12] * val;
		}
	}
}
