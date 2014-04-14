//
//  RKAchievement.h
//  RobotKit
//
//  Created by Jon Carroll on 8/2/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 *  @brief Class that represents a SpheroWorld achievements and handles achievement tracking
 *
 *  Achievements will need to be created and setup on the SpheroWorld website. In order to use
 *  achievements in your application you will need to properly set your appID and secret using
 *  the RKSpheroWorldAuth class when your application starts.  This will also ensure that
 *  driving stats such as distances, drive times, color changes and boosts will be tracked on
 *  the users SpheroWorld profile.
 *  @see RKSpheroWorldAuth
 *
 *  Achievement meta data and progress will automatically be loaded from SpheroWorld if the user
 *  is logged in.  Use the RKSpheroWorldAuth class to present a user with a login screen.
 *  @see RKSpheroWorldAuth
 *
 *  Register for the RKAchievementEarned notification to know when an achievement has been earned.
 *
 *  Call the recordEvent class method to update achievement progress as events in your game happen.
 * 
 *  If you would like to track drive times, distances or color changes to give users achievements
 *  you may register for the RKDriveTimeNotification, RKDriveDistanceNotification or 
 *  RKDriveColorNotification.  The recordEvent class method can then be called from your code
 *  to give users progress towards achievements in a method appropriate to your game.
 */
@interface RKAchievement : NSObject {
   NSString *name;
   NSString *description;
   NSString *img;
   int count_required;
   float percentComplete;
   int points;
}

/*!
 *  The human readable name of the achievement entered on SpheroWorld
 */
@property ( nonatomic, strong ) NSString *name;
/*!
 *  The human readable description of the achievement entered on SpheroWorld
 */
@property ( nonatomic, strong ) NSString *description;
/*!
 *  The URL where the image associated with this achievement can be downloaded from
 */
@property ( nonatomic, strong ) NSString *img;
/*!
 *  The number of times the associated event must be recorded to earn the acheivement
 */
@property int count_required;
/*!
 *  How close the user is to earning the achievement 0.0-1.0
 */
@property float percentComplete;
/*!
 *  The number of points this achievement is worth.
 */
@property int points;

/*!
 *  Call to record an event related to an achievement, this call records the event with a count of 1
 *  @param name the event name that was entered on SpheroWorld when creating achievements
 */
+ (void) recordEvent:(NSString *) name;
/*!
 *  Call to record an event related to an achievement and specify a number of times it happened
 *  @param name the event name that was entered on SpheroWorld when creating achievements
 *  @param count the number of times to record that the event happened
 */
+ (void) recordEvent:(NSString *) name withCount:(int) count;

/*!
 *  Call to get the number of times an event has been recorded.  This might be useful for displaying
 *  stats in a game for the number of times an event has happened.
 *  @param name the event name that is being looked up, same name used in recordEvent: calls.
 *  @return returns the number of times the event with the given identifier has been recorded.
 */
+ (int) getEventCount:(NSString *) name;

/*!
 *  Returns an array of RKAchievement objects showing current user progress
 */
+ (NSArray *) getAchievements;

/*!
 *  Will automatically enable collision detection at the thresholds required for SpheroWorld collision tracking if YES.
 *  If NO all collision detection will be disabled and collisions will not be reported to SpheroWorld.
 *  When YES or if collision detection is enabled elsewhere the RKDriveCollisionNotification will begin to fire whenever
 *  a collision is reported to the SpheroWorld profile of the ball.
 *  @param enabled determines if collision detection should be automatically turned on or off.
 */
+ (void) achievementCollisionDetection:(BOOL) enabled;

@end

//Achievement related notification constants
/*!
 * Notification to register for when achievements are earned.
 */
static NSString *const RKAchievementEarnedNotification = @"RKAchievementEarnedNotification";
/*!
 * Key to pull the achievement object out of the user info dictionary from the RKAchievementEarnedNotification
 */
static NSString *const RKAchievementEarnedAchievementKey = @"RKAchievementEarnedAchievementKey";

//Register for these notifications if you would like to be notified of drive related events for the purpose of achievement tracking.
//Note: These calls will fire quickly and rapidly, distance and time will typically arrive in very small increments.
/*!
 * Notification when a new drive time is calculated, value will be in userInfo dictionary as string in ms
 */
static NSString *const RKDriveTimeNotification = @"RKDriveTimeNotification";
/*!
 * Notification when a new drive distance is calculated, value will be in userInfo dictionary as string in cm
 */
static NSString *const RKDriveDistanceNotification = @"RKDriveDistanceNotification";
/*!
 * Notification of a color change, value will be R,G,B comma seperated string in userInfo dicationary
 */
static NSString *const RKDriveColorChangeNotification = @"RKDriveColorChangeNotification";
/*!
 * Notification that a macro was executed for achievements related to macros.
 */
static NSString *const RKDriveMacroNotification = @"RKDriveMacroNotification";
/*!
 * Notification that a collision was reported to Sphero World for the balls stats, used for collision related achievements.
 * NOTE: You must call [RKAchievement achievementCollisionDetection:YES] or enable collision detection in your own code to recieve this.
 * This will only fire when internal collision requirements are met which may be different that ones set for your game.
 */
static NSString *const RKDriveCollisionNotification = @"RKDriveCollisionNotification";
/*!
 * Key to pull the value out of the user info dictionary in RKDriveTimeNotification, RKDriveDistanceNotification and RKDriveColorChangeNotification
 */
static NSString *const RKDriveStatValueKey = @"RKDriveStatValueKey";
