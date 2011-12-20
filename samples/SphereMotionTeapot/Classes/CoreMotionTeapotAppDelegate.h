/*
    File: CoreMotionTeapotAppDelegate.h
Abstract: CoreMotionTeapot's app delegate.
 Version: 1.0

*/


#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>

@class EAGLView;

@interface CoreMotionTeapotAppDelegate : NSObject <UIApplicationDelegate> {
	IBOutlet UIWindow *window;
  IBOutlet EAGLView *glView;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet EAGLView *glView;

@end

