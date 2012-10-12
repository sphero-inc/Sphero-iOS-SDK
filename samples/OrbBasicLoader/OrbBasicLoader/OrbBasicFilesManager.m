//
//  OrbBasicFilesManager.m
//  OrbBasicLoader
//
//  Created by Brian Smith on 10/2/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RobotKit.h>

#import "OrbBasicFilesManager.h"


@implementation OrbBasicFilesManager

+ (NSArray *)orbBasicFiles {
    static NSMutableArray *files = nil;
    
    if (files != nil)
        return files;
    
    files = [[NSMutableArray alloc] init];
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *basePath = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
    NSArray *dirContents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:basePath error:nil];
    
    // Go through contents of document directory and only add files with orbbas as the extension.
    for(NSString* filePath in dirContents) {
        if( [[filePath pathExtension] isEqualToString:@"orbbas"]) {
            RKOrbBasicProgram *program = [[RKOrbBasicProgram alloc] initWithFilePath:filePath
                                                                   directoryPath:basePath
                                                                           error:nil];
            if (program != nil) {
                [files addObject:program];
                [program release];
            } else {
                NSLog(@"Failed to load file %@", filePath);
            }
        }
    }
    
    return files;
}

@end
