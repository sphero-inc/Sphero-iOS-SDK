/*
    File: vector_inline_implementation.h
Abstract: Vector utilities.
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

#pragma mark vec3f_t

vec3f_t vec3f_init(float x, float y, float z)
{
	vec3f_t v = {x, y, z};
	return v;
}

vec3f_t vec3f_initWithVec4f(vec4f_t v)
{
	vec3f_t o = {v.x, v.y, v.z};
	return o;
}

vec3f_t vec3f_normalize(vec3f_t v)
{
	float s = 1.0f / vec3f_magnitude(v);
	return vec3f_init(s*v.x, s*v.y, s*v.z);
}

vec3f_t vec3f_negate(vec3f_t v)
{
	return vec3f_init(-v.x, -v.y, -v.z);
}

vec3f_t vec3f_crossProduct(vec3f_t a, vec3f_t b)
{
	return vec3f_init(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);	
}

float vec3f_magnitude(vec3f_t v)
{
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

float vec3f_dotProduct(vec3f_t a, vec3f_t b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

vec3f_t vec3f_add(vec3f_t a, vec3f_t b)
{
	vec3f_t v = {a.x+b.x, a.y+b.y, a.z+b.z};
	return v;
}

#pragma mark vec4f_t

vec4f_t vec4f_init(float x, float y, float z, float w)
{
	vec4f_t v = {x,y,z,w};
	return v;
}

vec4f_t vec4f_homogenize(vec4f_t v)
{
	vec4f_t r;
	r.x = v.x/v.w;
	r.y = v.y/v.w;
	r.z = v.z/v.w;
	r.w = 1.0f;
	return r;
}