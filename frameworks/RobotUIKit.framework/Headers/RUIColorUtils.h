//
//  RUIColorUtils.h
//  RobotKit
//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

struct HSBColors {
	float h;
	float s;
	float b;
};

@interface RUIColorUtils : NSObject {

}

+(struct HSBColors) getHSBFromRed:(float)r green:(float)g blue:(float)b;

@end
