//
//  RUIAchievementEarnedViewController.h
//  RobotUIKit
//
//  Created by Jon Carroll on 10/5/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotKit/RKAchievement.h>
#import "RUIModalLayerViewController.h"

/*!
 *  @brief View controller for notifying a user that they earned an achievement
 *
 *  This will controller will animate an overlay in at the top of the screen notifying
 *  a user that they earned an achievement.  Call the setAchievement method then 
 *  displayInView.  You can release the view controller at this point, it will
 *  automatically load the achievement image, display the notification and release
 *  resources when done.
 */
 
@interface RUIAchievementEarnedViewController : RUIModalLayerViewController {
    @private
    IBOutlet UIImageView    *notificationBackground;
    IBOutlet UILabel        *messageLabel;
    IBOutlet UIImageView    *badgeIcon;
    NSString                *iconURL;
    NSMutableData           *imageData;
    BOOL                    movedUp;
}

/*!
 *  The achievement to display a notification for
 *  @param achievement the achievement to display the notification for
 */
-(void)setAchievement:(RKAchievement*)achievement;

/*!
 *  Display the notification in a view, usually the current fullscreen view
 *  @param view the view to display the notification in
 */
-(void)displayInView:(UIView*)view;

@end
