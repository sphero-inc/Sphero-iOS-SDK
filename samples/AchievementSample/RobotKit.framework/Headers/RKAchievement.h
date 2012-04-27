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
@property (nonatomic, retain) NSString *name;
/*!
 *  The human readable description of the achievement entered on SpheroWorld
 */
@property (nonatomic, retain) NSString *description;
/*!
 *  The URL where the image associated with this achievement can be downloaded from
 */
@property (nonatomic, retain) NSString *img;
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
+(void)recordEvent:(NSString*)name;
/*!
 *  Call to record an event related to an achievement and specify a number of times it happened
 *  @param name the event name that was entered on SpheroWorld when creating achievements
 *  @param count the number of times to record that the event happened
 */
+(void)recordEvent:(NSString*)name withCount:(int)count;

/*!
 *  Returns an array of RKAchievement objects showing current user progress
 */
+(NSArray*)getAchievements;

@end

//Achievement related notification constants
/*!
 * Notification to register for when achievements are earned.
 */
static NSString * const RKAchievementEarnedNotification     = @"RKAchievementEarnedNotification";
/*!
 * Key to pull the achievement object out of the user info dictionary from the RKAchievementEarnedNotification
 */
static NSString * const RKAchievementEarnedAchievementKey   = @"RKAchievementEarnedAchievementKey";

//Register for these notifications if you would like to be notified of drive related events for the purpose of achievement tracking.
//Note: These calls will fire quickly and rapidly, distance and time will typically arrive in very small increments.
/*!
 * Notification when a new drive time is calculated, value will be in userInfo dictionary as string in ms
 */
static NSString * const RKDriveTimeNotification             = @"RKDriveTimeNotification";
/*!
 * Notification when a new drive distance is calculated, value will be in userInfo dictionary as string in cm
 */
static NSString * const RKDriveDistanceNotification         = @"RKDriveDistanceNotification";
/*!
 * Notification of a color change, value will be R,G,B comma seperated string in userInfo dicationary
 */
static NSString * const RKDriveColorChangeNotification      = @"RKDriveColorChangeNotification";
/*!
 * Key to pull the value out of the user info dictionary in RKDriveTimeNotification, RKDriveDistanceNotification and RKDriveColorChangeNotification
 */
static NSString * const RKDriveStatValueKey                 = @"RKDriveStatValueKey";
