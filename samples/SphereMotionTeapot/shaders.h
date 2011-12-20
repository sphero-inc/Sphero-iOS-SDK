/*
    File: shaders.h
Abstract: Utilities for loading shaders.
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


#import <sys/stat.h>
#import <sys/time.h>
#import <fcntl.h>

#import <CoreFoundation/CoreFoundation.h>
#import <OpenGLES/ES2/gl.h>


void getFileResourcePath(char *filename, char *filePath, unsigned int len)
{
	CFBundleRef bundle;
	CFURLRef url;
	
	CFStringRef filenameStr = CFStringCreateWithCStringNoCopy(kCFAllocatorDefault, filename, kCFStringEncodingASCII, kCFAllocatorNull);
	
	if (filenameStr) {
		bundle = CFBundleGetMainBundle();
		if (bundle) {
			url = CFBundleCopyResourceURL(bundle, filenameStr, NULL, NULL);
			
			if (url) {
				CFURLGetFileSystemRepresentation(url, false, (unsigned char *)filePath, len);
				CFRelease(url);
			}
		}
		CFRelease(filenameStr);
	}
}

char* read_text_file(const char* filepath)
{
	int fd, result;
	ssize_t bytesRead; 
	char* text;
	struct stat stats;
	
	fd = open(filepath, O_RDONLY, 0);
	if (fd == -1) {
		NSLog(@"Failed to find \"%s\"\n", filepath);
		return NULL;
	}
	
	result = fstat(fd, &stats);
	if (result) {
		fprintf(stderr, "fstat on file \"%s\" failed\n", filepath);
		close(fd);
		return NULL;
	}
	assert(stats.st_size > 0);
	
	text = malloc(stats.st_size + 1);
	bytesRead = read(fd, text, stats.st_size);
	assert(bytesRead == stats.st_size);
	text[stats.st_size] = '\0';
	
	close(fd);
	
	return text;
}

GLuint load_shader(GLenum target, const char* path)
{
	char* shader_source = read_text_file(path);
	if (!shader_source) {
		fprintf(stderr, "Failed to load shader at %s\n", path);
		assert(NULL != shader_source);
	}
	
	GLint status;
	GLuint shader = glCreateShader(target);
	glShaderSource(shader, 1, (const GLchar**)&shader_source, NULL);
	free(shader_source);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLchar shader_info_log[1024];
		glGetShaderInfoLog(shader, 1024, NULL, shader_info_log);
		fprintf(stderr, "Failed to compile shader %s: %s\n", path, (char*)shader_info_log);
	}	
	return shader;
}
