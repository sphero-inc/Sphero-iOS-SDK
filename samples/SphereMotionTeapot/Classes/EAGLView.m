/*
    File: EAGLView.m
Abstract: View to display OpenGL ES teapot, along with UI controls to adjust various motion properties.
 Version: 1.0

*/

#import "EAGLView.h"

#import "vector.h"
#import "teapot.h"
#import "shaders.h"

#import <CoreMotion/CoreMotion.h>

#import <RobotKit/RobotKit.h>

static const double kDegreesToRadians = M_PI / 180.0;
static const double kUserAccelerationFilterConstant = 0.1;

static const double kMinCutoffFrequency = 1;

static const double kUserAccelerationHpfCutoffFrequency = 1000.0;
static const double kUserAccelerationLpfCutoffFrequency = 10.0;

enum {
	kSegmentIndexAccelerometer = 0,
	kSegmentIndexDeviceMotion = 1
};

const GLfloat	kLightDirection[] = {0.0f, 0.0f, 1.0f};
const GLfloat	kLightHalfPlane[] = {0.0f, 0.0f, 0.0f};
const GLfloat kLightAmbient[] = {0.2, 0.2, 0.2, 1.0f};
const GLfloat kLightDiffuse[] = {1.0f, 0.6, 0.0f, 1.0f};
const GLfloat kLightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat kMaterialAmbient[] = {0.6, 0.6, 0.6, 1.0f};
const GLfloat	kMaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};	
const GLfloat	kMaterialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat	kMaterialSpecularExponent = 10.0f;

CMRotationMatrix rotationMatrixFromGravity(float x, float y, float z)
{	
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

@implementation EAGLView

@synthesize animating;
@dynamic animationFrameInterval;

// You must implement this method
+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

-(void)enableSpheroStreaming {
    //SPHERO SENSOR STREAMING CODE
    // Send command to start the accelerometer data streaming from Sphero and add ourself as an observer
    NSLog(@"Turning on data streaming, divisor %@", [[NSUserDefaults standardUserDefaults] stringForKey:@"rateDivisor"]);
    [[RKDeviceMessenger sharedMessenger] addDataStreamingObserver:self selector:@selector(handleDataStreaming:)];
    [RKSetDataStreamingCommand sendCommandWithSampleRateDivisor:[[[NSUserDefaults standardUserDefaults] stringForKey:@"rateDivisor"] intValue] packetFrames:[[[NSUserDefaults standardUserDefaults] stringForKey:@"framesPacket"] intValue] sensorMask:RKDataStreamingMaskAccelerometerXFiltered | RKDataStreamingMaskAccelerometerYFiltered | RKDataStreamingMaskAccelerometerZFiltered | RKDataStreamingMaskIMUYawAngleFiltered | RKDataStreamingMaskIMUPitchAngleFiltered | RKDataStreamingMaskIMURollAngleFiltered packetCount:[[[NSUserDefaults standardUserDefaults] stringForKey:@"packetCount"] intValue]];
    //END SPHERO SENSOR STREAMING CODE
}

-(void)disableSpheroStreaming {
    //SPHERO SENSOR STREAMING CODE
    //Disable sensor data streaming from Sphero by removing ourself as the observer
    NSLog(@"Turning off data streaming");
    [[RKDeviceMessenger sharedMessenger] removeDataStreamingObserver:self];
    // Send command to stop the data streaming from Sphero
    [RKSetDataStreamingCommand sendCommandWithSampleRateDivisor:0 packetFrames:0 sensorMask:RKDataStreamingMaskOff packetCount:0];
    //END SPHERO SENSOR STREAMING CODE
}

- (IBAction)onModeControlValueChanged:(UISegmentedControl *)sender
{
	accelMode = (sender.selectedSegmentIndex == kSegmentIndexAccelerometer);
	
	if (accelMode) {
		// If we're now in accelerometer mode, our old mode must have been device motion,
		// so stop device motion and start accelerometer updates
		// Note: The relevant update intervals were specified in startAnimation
		[motionManager stopDeviceMotionUpdates];
		[motionManager startAccelerometerUpdates];
	} else {
		// If we're now in device motion mode, our old mode must have been accelerometer,
		// so stop accelerometer and start device motion
		// Note: The relevant update intervals were specified in startAnimation
		[motionManager stopAccelerometerUpdates];
		[motionManager startDeviceMotionUpdates];
	}
}

//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id) initWithCoder:(NSCoder*)coder
{
	if ((self = [super initWithCoder:coder]))
	{
		// Get the layer
		CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
		eaglLayer.opaque = TRUE;
		eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys: [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];

		animating = FALSE;
		animationFrameInterval = 1;
		displayLink = nil;
		motionManager = nil;
		referenceAttitude = nil;
		modeControl.selectedSegmentIndex = kSegmentIndexAccelerometer;
		accelMode = (modeControl.selectedSegmentIndex == kSegmentIndexAccelerometer);
		
		context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
		
		mat4f_identity(modelViewMatrix);
		mat4f_identity(projectionMatrix);
        
		if (context == nil || ![EAGLContext setCurrentContext:context]) {
			[self release];
			return nil;
		}
		[self initializeGL];
	}
	return self;
}

- (void) renderTeapotUsingRotation:(CMRotationMatrix)rotation andTranslation:(vec3f_t)translation
{
	[EAGLContext setCurrentContext:context];
    
	glBindFramebuffer(GL_FRAMEBUFFER, viewFramebuffer);
	
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
	glViewport(0, 0, backingWidth, backingHeight);
   
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
	
	glBindRenderbuffer(GL_RENDERBUFFER, viewRenderbuffer);
	[context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void) drawView:(id)sender
{
	// The translation and rotation components of the modelview matrix
	vec3f_t translation = {0.0f, 0.0f, -0.40f};
	CMRotationMatrix rotation;
	//CMAcceleration userAcceleration;
    
    
    if(accelMode) { //if accelerometer mode
        //Create a rotation based on the latest data from Sphero
        rotation = rotationMatrixFromGravity(lastX, lastY, lastZ);
    }
	
	// renderTeapotUsingRotation:andTranslation:translation: will rotate the teapot by the inverse
	// of rotation and translate it by translation
	[self renderTeapotUsingRotation:rotation andTranslation:translation];
}

- (void) layoutSubviews
{
	[EAGLContext setCurrentContext:context];
	[self destroyFramebuffer];
	[self createFramebuffer];
	
	// Re-compute projection matrix
	mat4f_initPerspective(60.0f * kDegreesToRadians, (float) backingWidth*1.0f/backingHeight, 0.1f, 10.0f, projectionMatrix);
		
	[self drawView:nil];
}

- (NSInteger) animationFrameInterval
{
	return animationFrameInterval;
}

- (void) setAnimationFrameInterval:(NSInteger)frameInterval
{
	// Frame interval defines how many display frames must pass between each time the
	// display link fires. The display link will only fire 30 times a second when the
	// frame internal is two on a display that refreshes 60 times a second. The default
	// frame interval setting of one will fire 60 times a second when the display refreshes
	// at 60 times a second. A frame interval setting of less than one results in undefined
	// behavior.
	if (frameInterval >= 1)
	{
		animationFrameInterval = frameInterval;
		
		if (animating)
		{
			[self stopAnimation];
			[self startAnimation];
		}
	}
}

- (void) startAnimation
{
	if (!animating)
	{
        lastX = 0.0;
        lastY = 0.0;
        lastZ = -1.0;
        
		referenceAttitude = nil;
				
		displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(drawView:)];
		[displayLink setFrameInterval:animationFrameInterval];
		[displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

		animating = TRUE;
	}
}

- (void)stopAnimation
{
	if (animating)
	{
        [self disableSpheroStreaming];
		[motionManager stopAccelerometerUpdates];
		[motionManager stopDeviceMotionUpdates];
		[motionManager release];
		motionManager = nil;
	
		[displayLink invalidate];
		displayLink = nil;
		animating = FALSE;
	}
}

//SPHERO SENSOR STREAMING CODE
//Observer method that will be called as sensor data arrives from Sphero
- (void)handleDataStreaming:(RKDeviceAsyncData *)data
{
    //NSLog(@"handleDataStreaming: data - %@", data);
    if ([data isKindOfClass:[RKDeviceSensorsAsyncData class]]) {
        RKDeviceSensorsAsyncData *sensors_data = (RKDeviceSensorsAsyncData *)data;
        //NSLog(@"sensors_data.dataFrames - %@", sensors_data.dataFrames);
        for (RKDeviceSensorsData *data in sensors_data.dataFrames) {
            if(accelMode) {
                RKAccelerometerData *accelerometer_data = data.accelerometerData;
                lastX = accelerometer_data.acceleration.x;
                lastY = accelerometer_data.acceleration.y;
                lastZ = (accelerometer_data.acceleration.z * -1.0); //Invert the z axis value
            } 
        }
    }
}
//END SPHERO SENSOR STREAMING CODE

- (void) dealloc
{
	[self stopAnimation];
    
	if ([EAGLContext currentContext] == context) {
		[EAGLContext setCurrentContext:nil];
	}
	[context release];
	
	[super dealloc];
}

- (void)createFramebuffer
{
    
	glGenFramebuffers(1, &viewFramebuffer);
	glGenRenderbuffers(1, &viewRenderbuffer);
    
	glBindFramebuffer(GL_FRAMEBUFFER, viewFramebuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, viewRenderbuffer);
	[context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)self.layer];
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, viewRenderbuffer);
    
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);
  
	glGenRenderbuffers(1, &depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, backingWidth, backingHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
    
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		NSLog(@"createFramebuffer failed %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
	} else {
		NSLog(@"Created framebuffer with backing width, height = (%d, %d)", backingWidth, backingHeight);
	}
}


- (void)destroyFramebuffer
{
	glDeleteFramebuffers(1, &viewFramebuffer);
	viewFramebuffer = 0;
	glDeleteRenderbuffers(1, &viewRenderbuffer);
	viewRenderbuffer = 0;
	glDeleteRenderbuffers(1, &depthRenderbuffer);
	depthRenderbuffer = 0;
}

- (void) initializeGL
{
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
