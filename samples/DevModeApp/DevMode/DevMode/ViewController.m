//
//  ViewController.m
//  DevMode
//
//  Created by wes on 10/29/14.
//  Copyright (c) 2014 Sphero. All rights reserved.
//

#import "ViewController.h"
#import <RobotKitLE/RobotKitLE.h>

@interface ViewController ()
@property (strong, nonatomic) IBOutlet UITextView *textView;

@end

@implementation ViewController

-(void) viewDidLoad{
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didRobotChangeState:) name:kRobotDidChangeStateNotification object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillForeground:)
												 name:UIApplicationWillEnterForegroundNotification object:nil];
}

-(void) appWillForeground:(NSNotification*) n{
	[[RKRobotDiscoveryAgentLE sharedAgent] startDiscovery];
	[_textView setText:@"Starting Disco - touch Ollie to Phone to enable Dev Mode"];
}

-(void)viewDidAppear:(BOOL)animated{
	NSLog(@"viewDidAppear");
	//	[[RKRobotDiscoveryAgentLE sharedAgent] addNotificationObserver:self selector:@selector(didRobotChangeState:)]; // broken - connects dont show up
}


-(void) didRobotChangeState:(RKRobotChangedStateNotification*) note{
	[_textView setText:[NSString stringWithFormat:@"%@\n%@", _textView.text, note.description]];
	switch(note.type){
		case RKRobotOnline:{
			RKRobotLE* robot = (RKRobotLE*) note.robot;
			[robot.radioLink setDeveloperMode:YES];
			[robot sendCommand:[RKGoToSleepCommand command]];
			[_textView setText:[NSString stringWithFormat:@"%@\n%@ - UPDATED TO DEV MODE", _textView.text, robot.name]];
			break;
		}
		case RKRobotDisconnected:
		{
			[[RKRobotDiscoveryAgentLE sharedAgent] startDiscovery];
			break;
		}
        default:
            break;
	}
}




@end
