//
//  NameEntryViewController.h
//  RKMultiplayerSample
//
//  Created by Jon Carroll on 4/12/12.
//  Copyright (c) 2012 Orbotix, Inc. All rights reserved.
//
//  A view controller for changing the player name seen by other players

#import <UIKit/UIKit.h>

@interface NameEntryViewController : UIViewController {
    IBOutlet UITextField *nameField;
}

-(IBAction)savePressed:(id)sender;

@end
