//
//  AppDelegate.m
//  OrbBasicLoader
//
//  Created by Brian Smith on 10/1/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "AppDelegate.h"

#import "ViewController.h"

@implementation AppDelegate

- (void)dealloc
{
    [_window release];
    [_viewController release];
    [super dealloc];
}

@synthesize viewController = _viewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Set the default values for user default keys
    [[NSUserDefaults standardUserDefaults] registerDefaults:[NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES]
                                                                                        forKey:@"firstRun"]];
    // Copy the default samples into the document directory on first run.
    if ([[NSUserDefaults standardUserDefaults] boolForKey:@"firstRun"]) {
        [self copyPrebuiltPrograms];
    }
    
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    // Override point for customization after application launch.
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        self.viewController = [[[ViewController alloc] initWithNibName:@"ViewController_iPhone" bundle:nil] autorelease];
    } else {
        self.viewController = [[[ViewController alloc] initWithNibName:@"ViewController_iPad" bundle:nil] autorelease];
    }
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    return YES;
}

-(void)copyPrebuiltPrograms {
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSError *error;
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
    
    //Loop through all files in the bundle resources and  copy any files that are of a managed type
    for(NSString *asset in [fileManager contentsOfDirectoryAtPath:[[NSBundle mainBundle] resourcePath] error:&error]) {
        NSString *type = [[asset componentsSeparatedByString:@"."] lastObject];
        
        if([type isEqualToString:[RKOrbBasicProgram fileExtension]]) {
            error = nil;
            NSString *assetPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:asset];
            NSString *destPath = [documentsDirectory stringByAppendingPathComponent:asset];
            error = nil;
            if(![fileManager copyItemAtPath:assetPath toPath:destPath error:&error]) {
                NSLog(@"AssetManager:: Error copying asset %@", asset);
                if(error) NSLog(@"AssetManager:: %@", [error localizedDescription]);
            } else {
                NSLog(@"AssetManager:: Successfully copied asset %@", asset);
            }
        }
    }
}

@end
