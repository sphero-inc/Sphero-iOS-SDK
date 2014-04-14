//
//  RUINoSpheroConnectedViewController.h
//  RobotUIKit
//
//  Created by Michael DePhillips on 12/5/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RUIModalLayerViewController.h"

@interface RUINoSpheroConnectedViewController : RUIModalLayerViewController {
    NSString* customURL;
}

/*!
 * Use this custom URL to coordinate with Orbotix to get rewards
 * for users clicking "Get A Sphero" in your app and actually buying one
 * 
 * defaults to nil
 */
@property (nonatomic, assign) NSString* customURL;

/*!
 * Called when the Get A Sphero button is pressed
 */
-(IBAction)getASpheroPressed:(id)sender;

@end
