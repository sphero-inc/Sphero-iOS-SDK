//
//  NameEntryViewController.m
//  RKMultiplayerSample
//
//  Created by Jon Carroll on 4/12/12.
//  Copyright (c) 2012 Orbotix, Inc. All rights reserved.
//

#import "NameEntryViewController.h"
#import <RobotKit/RobotKit.h>

@interface NameEntryViewController ()

@end

@implementation NameEntryViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    nameField.text = [[NSUserDefaults standardUserDefaults] objectForKey:@"playerName"];
    // Do any additional setup after loading the view from its nib.
}

-(void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [nameField becomeFirstResponder];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(IBAction)savePressed:(id)sender {
    [nameField resignFirstResponder];
    [[NSUserDefaults standardUserDefaults] setObject:nameField.text forKey:@"playerName"];
     [RKMultiplayer sharedMultiplayer].localPlayer.name = [[NSUserDefaults standardUserDefaults] objectForKey:@"playerName"];
    [self.navigationController popViewControllerAnimated:YES];
}

@end
