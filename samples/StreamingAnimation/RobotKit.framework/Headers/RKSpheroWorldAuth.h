//
//  RKSpheroWorldAuth.h
//  RobotKit
//
//  Created by Jon Carroll on 8/2/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

/*!
 *  @brief Main class used to integrate your application with SpheroWorld and allow users to login
 *
 *  Use this class to authenticate your application with SpheroWorld.  Use the setAppID:secret:
 *  class method before you make any other RobotKit calls in the applicationDidFinishLaunching
 *  method of your app delegate. This will ensure that stats such as drive times, drive distances,
 *  color changes and boosts that happen in your application will be associated with the user's
 *  SpheroWorld profile.
 *
 *  The second purpose of this class is to allow the user to login to SpheroWorld and display
 *  the achievements associated with your application along with their progress toward earning
 *  the achievements.  Simply present this view controller as a modalViewController in your
 *  app and set the presenter as the delegate.  If has never logged in with your application
 *  they will be presented with a login screen, otherwise the user will be shown a list of
 *  the achievements for your application along with their progress.
 *
 *  Achievements need to be setup on SpheroWorld and progress tracked through the RKAchievement
 *  class.
 *  @see RKAchievement
 */
@interface RKSpheroWorldAuth : UIViewController <UIWebViewDelegate, UIGestureRecognizerDelegate> {
@private
   NSString *appID;
   NSString *appSecret;
   UIWebView *webView;
   UIView *loadingView;
   BOOL redirecting;
}

/*!
 *  The view controller presenting this one as modal.  Required so this view can dismiss itself when done.
 */
@property ( /*weak,*/ nonatomic ) UIViewController *delegate;

/*!
 *  Call to authorize your app with SpheroWorld and ensure statistics are tracked to the user's profile
 *  Should be called in applicationDidFinishLaunching method of application delegate. Required if app
 *  uses SpheroWorld achievements.
 *  @param appid The application id assigned to the application on the SpheroWorld developer site.
 *  @param secret The application's secret string assigned when the app was created on SpheroWorld
 */
+ (void) setAppID:(NSString *) appid secret:(NSString *) secret;

/*!
 *  Get the unique SpheroWorld appID for the application running.
 *  @return appID string of the application that is running, returns nil if setAppID:secret: was never called.
 */
+ (NSString *) getAppID;

@end
