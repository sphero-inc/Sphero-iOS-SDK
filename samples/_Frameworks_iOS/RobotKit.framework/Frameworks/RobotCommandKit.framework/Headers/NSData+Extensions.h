//
//  NSData+Extensions.h
//  RobotKitLE
//
//  Created by wes on 12/8/13.
//  Copyright (c) 2013 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (Extensions)

+(id) dataWithHexString:(NSString*) hexString;

- (NSString *)hexStringRepresentation;

-(NSMutableArray*) chunkWithMax:(int) maxlen;



@end
