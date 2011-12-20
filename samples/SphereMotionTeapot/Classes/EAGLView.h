/*
    File: EAGLView.h
Abstract: View to display OpenGL ES teapot, along with UI controls to adjust various motion properties.
 Version: 1.0

*/

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <OpenGLES/EAGLDrawable.h>
#import <CoreMotion/CoreMotion.h>

#import "matrix.h"

@interface EAGLView : UIView
{    
@private
	BOOL animating;
	NSInteger animationFrameInterval;
	CADisplayLink *displayLink;
	EAGLContext *context;
	GLuint viewRenderbuffer, viewFramebuffer;
	GLuint depthRenderbuffer;
	GLint backingWidth;
	GLint backingHeight;
	
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
	
	CMMotionManager *motionManager;
	
	// YES when we're only using the accelerometer, NO when we're using device motion
	BOOL accelMode;
	
	// referenceAttitude
	// Only used when accelMode==NO
	CMAttitude *referenceAttitude;
	
	// Whether translation based on user acceleration is enabled
	// Only used when accelMode==NO
	BOOL translationEnabled;
	
	IBOutlet UISegmentedControl *modeControl;
	
    //latest acceleration data from Sphero
    float lastX;
    float lastY;
    float lastZ;
 }

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;

- (void) startAnimation;
- (void) stopAnimation;
- (void) drawView:(id)sender;
- (void) createFramebuffer;
- (void) destroyFramebuffer;
- (void) initializeGL;

- (IBAction)onModeControlValueChanged:(UISegmentedControl *)sender;

-(void)enableSpheroStreaming;
-(void)disableSpheroStreaming;

@end
