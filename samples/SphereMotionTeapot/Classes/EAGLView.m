//
//  Copyright (c) 2011-2014 Orbotix, Inc. All rights reserved.
//

#import <CoreMotion/CoreMotion.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <OpenGLES/EAGLDrawable.h>

#import "matrix.h"
#import "EAGLView.h"

#import "vector.h"
#import "teapot.h"
#import "shaders.h"

static const double kDegreesToRadians = M_PI / 180.0;

enum {
	kSegmentIndexAccelerometer = 0,
	kSegmentIndexDeviceMotion = 1
};

const GLfloat kLightDirection[] = {0.0f, 0.0f, 1.0f};
const GLfloat kLightHalfPlane[] = {0.0f, 0.0f, 0.0f};
const GLfloat kLightAmbient[] = {0.2, 0.2, 0.2, 1.0f};
const GLfloat kLightDiffuse[] = {1.0f, 0.6, 0.0f, 1.0f};
const GLfloat kLightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat kMaterialAmbient[] = {0.6, 0.6, 0.6, 1.0f};
const GLfloat kMaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat kMaterialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat kMaterialSpecularExponent = 10.0f;

CMRotationMatrix rotationMatrixFromGravity(float x, float y, float z) {
	// The Z axis of our rotated frame is opposite gravity
	vec3f_t zAxis = vec3f_normalize(vec3f_init(-x, -y, -z));
	
	// The Y axis of our rotated frame is an arbitrary vector perpendicular to gravity
	// Note that this convention will have problems as zAxis.x approaches +/-1 since the magnitude of
	// [0, zAxis.z, -zAxis.y] will approach 0
	vec3f_t yAxis = vec3f_normalize(vec3f_init(0, zAxis.z, -zAxis.y));
	
	// The X axis is just the cross product of Y and Z
	vec3f_t xAxis = vec3f_crossProduct(yAxis, zAxis);
    
	CMRotationMatrix mat = {
		xAxis.x, yAxis.x, zAxis.x,
		xAxis.y, yAxis.y, zAxis.y,
		xAxis.z, yAxis.z, zAxis.z};

	return mat;
}

@interface EAGLView() {
    mat4f_t projectionMatrix;
    mat4f_t modelViewMatrix;
    
    struct {
        // Handle to a program object
        GLuint prog;
        
        // Attributes
        GLint position;
        GLint normal;
        
        // Uniforms
        GLint mvpMatrix;
        GLint modelViewMatrix;
        GLint lightDirection;
        GLint lightHalfPlane;
        GLint lightAmbientColor;
        GLint lightDiffuseColor;
        GLint lightSpecularColor;
        GLint materialAmbientColor;
        GLint materialDiffuseColor;
        GLint materialSpecularColor;
        GLint materialSpecularExponent;
    } glHandles;
}

@property (nonatomic) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;
@property (nonatomic) CADisplayLink *displayLink;
@property (nonatomic) EAGLContext *context;
@property (nonatomic) GLuint viewRenderbuffer, viewFramebuffer;
@property (nonatomic) GLuint depthRenderbuffer;
@property (nonatomic) GLint backingWidth;
@property (nonatomic) GLint backingHeight;
@property (nonatomic) BOOL accelMode;
@property (nonatomic) BOOL translationEnabled;
@property (nonatomic) float lastX;
@property (nonatomic) float lastY;
@property (nonatomic) float lastZ;

@end

@implementation EAGLView

// You must implement this method
+ (Class) layerClass {
	return [CAEAGLLayer class];
}

//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id) initWithCoder:(NSCoder*)coder {
	if ((self = [super initWithCoder:coder]))
	{
		// Get the layer
		CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
		eaglLayer.opaque = TRUE;
		eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys: [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];

        self.animating = FALSE;
        self.translationEnabled = NO;
        self.animationFrameInterval = 1;
        self.displayLink = nil;
        self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
		
		mat4f_identity(modelViewMatrix);
		mat4f_identity(projectionMatrix);
        
		if (self.context == nil || ![EAGLContext setCurrentContext:self.context]) {
			return nil;
		}
		[self initializeGL];
	}
	return self;
}

- (void)setRotationWithAccelerometerX:(float)x Y:(float)y Z:(float)z {
    self.lastX = x;
    self.lastY = y;
    self.lastZ = z;
}

- (void) renderTeapotUsingRotation:(CMRotationMatrix)rotation andTranslation:(vec3f_t)translation {
	[EAGLContext setCurrentContext:self.context];
    
	glBindFramebuffer(GL_FRAMEBUFFER, self.viewFramebuffer);
	
	mat3f_t modelView3;
	mat4f_initTranslation(translation, modelViewMatrix);
	
	// Rotate by inverse (=transpose) of attitude
	modelViewMatrix[0] = rotation.m11;
	modelViewMatrix[1] = rotation.m21;
	modelViewMatrix[2] = rotation.m31;
	modelViewMatrix[4] = rotation.m12;
	modelViewMatrix[5] = rotation.m22;
	modelViewMatrix[6] = rotation.m32;
	modelViewMatrix[8] = rotation.m13;
	modelViewMatrix[9] = rotation.m23;
	modelViewMatrix[10] = rotation.m33;
	
	// Rotate -90 degrees about X
	float temp[3];
	memcpy(temp, &modelViewMatrix[8], sizeof(temp));
	modelViewMatrix[8] = -modelViewMatrix[4];
	modelViewMatrix[9] = -modelViewMatrix[5];
	modelViewMatrix[10] = -modelViewMatrix[6];
	memcpy(&modelViewMatrix[4], temp, sizeof(temp));
	
	// Extract 3x3 rotation portion of 4x4 model view matrix
	mat3f_from_mat4(modelViewMatrix, modelView3);
	
	// model-view * projection matrix
	mat4f_t mvp;
	mat4f_multiplyMatrix(projectionMatrix, modelViewMatrix, mvp);

	// Set the viewport
	glViewport(0, 0, self.backingWidth, self.backingHeight);
   
	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 
	// Load the vertices and normals
	glVertexAttribPointer(glHandles.position, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), teapot_vertices);
	glVertexAttribPointer(glHandles.normal, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), teapot_normals);
   
	glEnableVertexAttribArray(glHandles.position);
	glEnableVertexAttribArray(glHandles.normal);
   
	// Set the uniforms
	glUniformMatrix3fv(glHandles.modelViewMatrix, 1, GL_FALSE, (GLfloat*) modelView3);
	glUniformMatrix4fv(glHandles.mvpMatrix, 1, GL_FALSE, (GLfloat*) mvp);
	glUniform3fv(glHandles.lightDirection, 1, kLightDirection);
	glUniform3fv(glHandles.lightHalfPlane, 1, kLightHalfPlane);
	glUniform4fv(glHandles.lightAmbientColor, 1, kLightAmbient);
	glUniform4fv(glHandles.lightDiffuseColor, 1, kLightDiffuse);
	glUniform4fv(glHandles.lightSpecularColor, 1, kLightSpecular);
	glUniform4fv(glHandles.materialAmbientColor, 1, kMaterialAmbient);
	glUniform4fv(glHandles.materialDiffuseColor, 1, kMaterialDiffuse);
	glUniform4fv(glHandles.materialSpecularColor, 1, kMaterialSpecular);
	glUniform1fv(glHandles.materialSpecularExponent, 1, &kMaterialSpecularExponent);

	// Draw teapot. The new_teapot_indicies array is an RLE (run-length encoded) version of the teapot_indices array in teapot.h
	for(int i = 0; i < num_teapot_indices; i += new_teapot_indicies[i] + 1)
	{
		glDrawElements(GL_TRIANGLE_STRIP, new_teapot_indicies[i], GL_UNSIGNED_SHORT, &new_teapot_indicies[i+1]);
	}
	
	glBindRenderbuffer(GL_RENDERBUFFER, self.viewRenderbuffer);
	[self.context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void) drawView:(id)sender {
	// The translation and rotation components of the modelview matrix
	vec3f_t translation = {0.0f, 0.0f, -0.40f};
    
    // Create rotation matrix from latest data
	CMRotationMatrix rotation = rotationMatrixFromGravity(self.lastX, self.lastY, self.lastZ);
	
	// renderTeapotUsingRotation:andTranslation:translation: will rotate the teapot by the inverse
	// of rotation and translate it by translation
	[self renderTeapotUsingRotation:rotation andTranslation:translation];
}

- (void) layoutSubviews {
	[EAGLContext setCurrentContext:self.context];
	[self destroyFramebuffer];
	[self createFramebuffer];
	
	// Re-compute projection matrix
	mat4f_initPerspective(60.0f * kDegreesToRadians, (float) self.backingWidth*1.0f/self.backingHeight, 0.1f, 10.0f, projectionMatrix);
		
	[self drawView:nil];
}

- (void) setAnimationFrameInterval:(NSInteger)frameInterval {
	// Frame interval defines how many display frames must pass between each time the
	// display link fires. The display link will only fire 30 times a second when the
	// frame internal is two on a display that refreshes 60 times a second. The default
	// frame interval setting of one will fire 60 times a second when the display refreshes
	// at 60 times a second. A frame interval setting of less than one results in undefined
	// behavior.
	if (frameInterval >= 1)
	{
		_animationFrameInterval = frameInterval;
		
		if (self.animating)
		{
			[self stopAnimation];
			[self startAnimation];
		}
	}
}

- (void)startAnimation {
	if (!self.animating) {
        self.lastX = 0.0;
        self.lastY = 0.0;
        self.lastZ = -1.0;
				
		self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
		[self.displayLink setFrameInterval:self.animationFrameInterval];
		[self.displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

		self.animating = TRUE;
	}
}

- (void)stopAnimation {
	if (self.animating) {
		[self.displayLink invalidate];
		self.displayLink = nil;
		self.animating = FALSE;
	}
}

- (void) dealloc {
	[self stopAnimation];
    
	if ([EAGLContext currentContext] == self.context) {
		[EAGLContext setCurrentContext:nil];
	}
    self.context = nil;
}

- (void)createFramebuffer {
	glGenFramebuffers(1, &_viewFramebuffer);
	glGenRenderbuffers(1, &_viewRenderbuffer);
    
	glBindFramebuffer(GL_FRAMEBUFFER, _viewFramebuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, _viewRenderbuffer);
	[self.context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)self.layer];
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, self.viewRenderbuffer);
    
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &_backingWidth);
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &_backingHeight);
  
	glGenRenderbuffers(1, &_depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, self.depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.backingWidth, self.backingHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, self.depthRenderbuffer);
    
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		NSLog(@"createFramebuffer failed %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
	} else {
		NSLog(@"Created framebuffer with backing width, height = (%d, %d)", self.backingWidth, self.backingHeight);
	}
}


- (void)destroyFramebuffer {
	glDeleteFramebuffers(1, &_viewFramebuffer);
	self.viewFramebuffer = 0;
	glDeleteRenderbuffers(1, &_viewRenderbuffer);
	self.viewRenderbuffer = 0;
	glDeleteRenderbuffers(1, &_depthRenderbuffer);
	self.depthRenderbuffer = 0;
}

- (void) initializeGL {
	char vertexFilePath[1024];
	char fragFilePath[1024];
	getFileResourcePath("vertex.shader", vertexFilePath, 1024);
	getFileResourcePath("fragment.shader", fragFilePath, 1024);
	GLuint vertex_shader = load_shader(GL_VERTEX_SHADER, vertexFilePath);
	GLuint fragment_shader = load_shader(GL_FRAGMENT_SHADER, fragFilePath);
	if (vertex_shader == 0 || fragment_shader == 0) {
		NSLog(@"Failed to load shaders: %d %d\n", vertex_shader, fragment_shader);
		abort();
	}
	
	glHandles.prog = glCreateProgram();
	glAttachShader(glHandles.prog, vertex_shader);
	glAttachShader(glHandles.prog, fragment_shader);
	glLinkProgram(glHandles.prog);
	
	GLint status;
	glGetProgramiv(glHandles.prog, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLchar info_log[1024];
		glGetProgramInfoLog(glHandles.prog, 1024, NULL, info_log);
		NSLog(@"Failed to link program: %s\n", (char*)info_log);
		abort();
	}
	
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// Get the attribute locations
	glHandles.position = glGetAttribLocation(glHandles.prog, "a_position");
	glHandles.normal = glGetAttribLocation(glHandles.prog, "a_normal");

	// Get the uniform locations
	glHandles.mvpMatrix = glGetUniformLocation(glHandles.prog, "u_mvpMatrix");
	glHandles.modelViewMatrix = glGetUniformLocation(glHandles.prog, "u_modelViewMatrix");
	glHandles.lightDirection = glGetUniformLocation(glHandles.prog, "u_light.direction");
	glHandles.lightHalfPlane = glGetUniformLocation(glHandles.prog, "u_light.halfplane");
	glHandles.lightAmbientColor = glGetUniformLocation(glHandles.prog, "u_light.ambient_color");
	glHandles.lightDiffuseColor = glGetUniformLocation(glHandles.prog, "u_light.diffuse_color");
	glHandles.lightSpecularColor = glGetUniformLocation(glHandles.prog, "u_light.specular_color");
	glHandles.materialAmbientColor = glGetUniformLocation(glHandles.prog, "u_material.ambient_color");
	glHandles.materialDiffuseColor = glGetUniformLocation(glHandles.prog, "u_material.diffuse_color");
	glHandles.materialSpecularColor = glGetUniformLocation(glHandles.prog, "u_material.specular_color");
	glHandles.materialSpecularExponent = glGetUniformLocation(glHandles.prog, "u_material.specular_exponent");
	 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepthf(1.0f);
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	// Use the program object
	glUseProgram(glHandles.prog);

}

@end
