//
//  ViewController.m
//  HelloWorld_OSX
//
//  Created by wes on 11/21/14.
//  Copyright (c) 2014 Sphero. All rights reserved.
//

#import "ViewController.h"
#import <RobotKit_OSX/RobotKit.h>

@interface ViewController()

@property (strong) IBOutlet NSTextField *statusLabel;
@property (strong) IBOutlet NSColorWell *colorWell;
@property (strong) IBOutlet NSButton *sleepButton;
@property (strong) RKConvenienceRobot *robot;
@end

@implementation ViewController

- (void)viewDidLoad {
	[super viewDidLoad];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleAvailable:) name:kRobotIsAvailableNotification object:nil];
	[[RKRobotDiscoveryAgentLE sharedAgent] addNotificationObserver:self selector:@selector(handleRobotChangeState:)];
	[RKRobotDiscoveryAgentLE startDiscovery];
}

-(void) handleAvailable:(RKRobotAvailableNotification*) n{
	NSLog(@"%@", n);
}

-(void) handleRobotChangeState:(RKRobotChangedStateNotification*)n{
	NSLog(@"OSX %@", n);
	_robot = [[RKConvenienceRobot alloc] initWithRobot:n.robot];
    
	switch(n.type){
		case RKRobotConnecting: {
			[_statusLabel setStringValue:[NSString stringWithFormat:@"Connecting %@", _robot.name]];
			break;
		}
		case RKRobotOnline: {
			[_statusLabel setStringValue:_robot.name];
            [_robot setLEDWithRed:0.0 green:1.0 blue:1.0];
			[_sleepButton setHidden:NO];
			[_colorWell setHidden:NO];
			break;
		}
		case RKRobotDisconnected: {
			[_statusLabel setStringValue:@"disconnected"];
			[_sleepButton setHidden:YES];
			[_colorWell setHidden:YES];
			_robot = nil;
            break;
        }
        default:
        break;
	}
}

- (IBAction)handleColorChange:(id)sender {
	NSColor* color = _colorWell.color;
	[_robot sendCommand:[RKRGBLEDOutputCommand commandWithRed:color.redComponent green:color.greenComponent blue:color.blueComponent]];
}


- (void)setRepresentedObject:(id)representedObject {
	[super setRepresentedObject:representedObject];
	
	// Update the view, if already loaded.
}

- (IBAction)handleDisconnect:(id)sender {
	// TODO disconnect!?  confusing - sleep
	[_robot sleep];
}

@end
