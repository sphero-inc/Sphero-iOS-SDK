//
//  Copyright (c) 2012-2014 Orbotix Inc. All rights reserved.
//

#import "OFViewController.h"

@interface OFViewController()

@property (strong, nonatomic) IBOutlet UISwitch *preventSleepInChargerSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *enableVectorDrive;
@property (strong, nonatomic) IBOutlet UISwitch *disableSelfLevelInCharger;
@property (strong, nonatomic) IBOutlet UISwitch *tailLightAlwaysOn;
@property (strong, nonatomic) IBOutlet UISwitch *enableMotionTimeout;
@property (strong, nonatomic) IBOutlet UILabel *status;
@property (strong, nonatomic) RKConvenienceRobot *robot;

@end

@implementation OFViewController

- (void)viewDidLoad {
	[super viewDidLoad];
	[[RKRobotDiscoveryAgent sharedAgent] addNotificationObserver:self selector:@selector(handleRobotStateChangeNotification:)];
	
	/*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];
}

- (void)handleRobotStateChangeNotification:(RKRobotChangedStateNotification*)n {
    switch(n.type) {
        case RKRobotConnecting:
            [self handleConnecting];
            break;
        case RKRobotOnline: {
            // Do not allow the robot to connect if the application is not running
            RKConvenienceRobot *convenience = [RKConvenienceRobot convenienceWithRobot:n.robot];
            if ([[UIApplication sharedApplication] applicationState] != UIApplicationStateActive) {
                [convenience disconnect];
                return;
            }
            self.robot = convenience;
            [self handleConnected];
            break;
        }
        case RKRobotDisconnected:
            [self handleDisconnected];
            self.robot = nil;
            [RKRobotDiscoveryAgent startDiscovery];
            break;
        default:
            break;
    }
}

- (void)handleConnecting {
    [_status setText:@"Connecting"];
}

- (void)handleConnected {
    [_status setText:@"Connected"];
    [_robot addResponseObserver:self];
    [_robot sendCommand:[[RKGetOptionFlagsCommand alloc] init]];
    [_robot sendCommand:[RKRGBLEDOutputCommand commandWithRed:0.0 green:.2 blue:.2]];
}

- (void)handleDisconnected {
    [_status setText:@"Disconnected"];
}

- (void)appWillResignActive:(NSNotification*)notification {
	[RKRobotDiscoveryAgent stopDiscovery];
    [RKRobotDiscoveryAgent disconnectAll];
}

- (void)appDidBecomeActive:(NSNotification*)notification {
	[RKRobotDiscoveryAgent startDiscovery];
}

- (void) handleResponse:(RKDeviceResponse*) response forRobot:(id<RKRobotBase>) robot{
	// Only respond to get option flags responses
	if( [response isKindOfClass:[RKGetOptionFlagsResponse class]] ) {
		RKGetOptionFlagsResponse* optionFlagsResponse = (RKGetOptionFlagsResponse*) response;
		[_preventSleepInChargerSwitch setOn:optionFlagsResponse.isPreventSleepInCharger];
		[_enableVectorDrive setOn:optionFlagsResponse.isVectorDrive];
		[_disableSelfLevelInCharger setOn:optionFlagsResponse.isPreventSelfLevelInCharger];
		[_tailLightAlwaysOn setOn:optionFlagsResponse.isTailLightAlwaysOn];
		[_enableMotionTimeout setOn:optionFlagsResponse.isMotionTimeout];
		NSLog(@"%@",optionFlagsResponse.description);
	}
	
	if([response isKindOfClass:[RKSetOptionFlagsCommand class]] && response.code == RKResponseCodeOK){
		[_status setText:@"commited"];
	}
}

- (NSString *)getBitStringForInt:(int)value {
	NSString *bits = @"";
	for(int i = 0; i < 8; i ++) {
		bits = [NSString stringWithFormat:@"%i%@", value & (1 << i) ? 1 : 0, bits];
	}
	return bits;
}

- (IBAction)setOptionFlagsPressed:(id)sender {
	RKGetOptionFlagsMask optionFlags = 0;
	
	// Add prevent sleep in charger flag value
	if( _preventSleepInChargerSwitch.isOn ) optionFlags |= RKGetOptionFlagsPreventSleepInCharger;
	
	// Add enable vector drive flag value
	if( _enableVectorDrive.isOn ) optionFlags |= RKGetOptionFlagsEnableVectorDrive;
	
	// Add disable self level in charger flag level
	if( _disableSelfLevelInCharger.isOn) optionFlags |= RKGetOptionFlagsDisableSelfLevelInCharger;
	
	// Add tail light always on flag
	if( _tailLightAlwaysOn.isOn) optionFlags |= RKGetOptionFlagsTailLightAlwaysOn;
	
	// Add enable motion timeout flag
	if( _enableMotionTimeout.isOn) optionFlags |= RKGetOptionFlagsEnableMotionTimeout;
	
	// Send command to set option flags
	RKSetOptionFlagsCommand* cmd = [[RKSetOptionFlagsCommand alloc] initWithOptionFlags:optionFlags];
	[self.robot sendCommand:cmd];
}
                         
- (void)viewDidUnload {
	self.preventSleepInChargerSwitch = nil;
	self.enableVectorDrive = nil;
	self.disableSelfLevelInCharger = nil;
	self.tailLightAlwaysOn = nil;
	self.enableMotionTimeout = nil;
	[super viewDidUnload];
}

@end
