//
//  Copyright (c) 2014 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol RKLinkDelegate <NSObject>

-(void) didConnect;
-(void) didWake;
-(void) didDisconnect;
-(void) didUpdateRssi;

@end
