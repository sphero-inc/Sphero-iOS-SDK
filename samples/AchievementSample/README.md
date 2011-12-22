![logo](http://update.orbotix.com/developer/sphero-small.png)

# Developer Guide: SpheroWorld and Achievements


## Overview
 
This guide will walk you through the basics of adding achievements to the SpheroWorld back end and adding their tracking to an iOS application.  

There is an achievement sample code project in the dev center that has an example implementation of achievements and SpheroWorld that may be a helpful companion to this guide.

### Create an application in SpheroWorld (Universal)

Click on the “Dev” link in the top right corner of SpheroWorld after you are logged in to create a new application for your app.  The same application can be used for both Android and iOS applications.


![image01.png](https://github.com/orbotix/Sphero-iOS-SDK/raw/master/samples/AchievementSample/assets/image01.png)

### Add achievements to your Sphero World application (Universal)

Once your application has been created you can add achievements by clicking on the achievements tap when viewing the application details.  You can then click the “add achievement” button to add an achievement.

![yadda.png](https://github.com/orbotix/Sphero-iOS-SDK/raw/master/samples/AchievementSample/assets/image02.png)

After clicking **Add Achievement** you will see this screen:


![newache.png](https://github.com/orbotix/Sphero-iOS-SDK/raw/master/samples/AchievementSample/assets/image03.png)



*All fields are required when adding an achievement:*

- **Achievement Name** - This is the short, human readable name displayed in achievements lists to identify the achievement.  (e.g. “Master Ball Handler” or “Speed Demon”)

- **Point Value** - This is the number of points the achievement is worth.  All of an app’s achievements can add up to no more than 1,000 points, but can be less.

- **Image** - This is the badge that is displayed in Sphero World to represent the acheivement.

- **Description** - This is the description of the achievement displayed to the user. (e.g. “Drive Sphero 1 Mile” or “Collect 100 Widgets”).

- **Event Type** - This is a non-human readable string representing the event that happens to trigger the earning of this achievement.  This is never displayed by the user and only used inside your code to track achievement events. (e.g. an achievement that requires five holes in one for a golf game might use “holeInOne”)

- **Threshold** - This is an integer indicating how many events of this achievement’s type must happen before the achievement is earned.  This allows you to easily create progressive achievements for the same type of event while also allowing you to track more complex achievements in your own game code and make the threshold 1. (e.g. using the 5 hole-in-one achievement example from above you would put 5 as the threshold)

- **Notification When Won** - This is the message displayed to the user on Sphero World when the acheivement has been earned.


## Integrating SpheroWorld into your Application (iOS) 

### Connect your application to SpheroWorld

The first step when integrating your iOS application with any part of Sphero World is to be sure you are setting your app id and app secret when your application first launches.  You can find these two pieces of information by viewing your application while logged into SpheroWorld.


![catball.png](https://github.com/orbotix/Sphero-iOS-SDK/raw/master/samples/AchievementSample/assets/image04.png) 

In the *applicaiton:didFinishLaunchingWithOptions:* method inside of the application delegate of your iOS application you will need to set the application id and secret before using any Sphero World functionality.  It is easiest to ensure this happens by making it your first line of code.  **You will need to be sure to import RobotKit.h in your app delegate.**  See example below:
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
    {
    	//Set our Sphero World app id  and secret as soon as the app starts before we do anything else
        //These values will be specific for your application
        [RKSpheroWorldAuth setAppID:@"sphe31bfdd87d4ef0877f9757772258f50ed" secret:@"sAPzGibRzGq25krvGzbi"];

### Allowing app users to login to SpheroWorld

You will need to provide a way for users to login to Sphero World within your applicaiton’s UI in order for them to track achievements.  The user should only need to login once to authorize your application, a view controller is provided to make this easy.  After the first time this view is displayed it will show the list of your game’s achievements along with the users progress.
    -(IBAction)spheroWorldPressed:(id)sender {
	    //Display the SpheroWorld authorization view, it will display the user's achievements if already logged in
	    RKSpheroWorldAuth *spheroWorld = [[RKSpheroWorldAuth alloc] init];
	    spheroWorld.delegate = self;
	    [self presentModalViewController:spheroWorld animated:YES];
	    [spheroWorld release];
    }
There isn’t a delegate protocol yet, just be sure the delegate is the view controller that presents it and it will dismiss itself when the user is done.


### Add achievement event tracking to your game

You will need to add a line of code to log each event type you setup when creating achievements.  A few examples are shown below.
    -(IBAction)redPressed:(id)sender {
	    //Record that red was pressed so it is counted toward achievement progress
	    [RKAchievement recordEvent:@"red"];
	    //Change Sphero's color to red
	    [RKRGBLEDOutputCommand sendCommandWithRed:1.0 green:0.0 blue:0.0];
    }
This example shows how to record an event type with a default count of 1.
    -(void)gotPoints:(int)points {
	    //The user just earned points, report it to RKAchievement
	    [RKAchievement recordEvent:@"totalPoints" withCount:points];
    }
This example shows how to record an event multiple times by passing in a dynamic count.  This particular example could be used to give the user achievements for total points earned over all time.
    if(mySuperSpecialCondition) [RKAchievement recordEvent:@"capturedAllTheBasesAndKilledAllTheDudes"];
This example shows how achievements with complex threshold conditions can be tracked internally within your game and used with SpheroWorld achievements with a threshold of 1.

If everything was setup correctly up to this point you should be able to start seeing progress towards earning the achievements in SpheroWorld as you play the game.

### Notifying the user of earned achievements

You can register to receive an NSNotification whenever a user has earned an achievement as shown below.
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(spheroWorldAchievementEarned:) name:RKAchievementEarnedNotification object:nil];
When the notification fires you can extract the RKAchievement object the user earned from the user info dictionary.  You can use the information in the RKAchievement object to display a notification to the user.  An example is shown below.
    -(void)spheroWorldAchievementEarned:(NSNotification*)notification {
	    //Get the achievement that was earned from the userInfo dictionary
	    RKAchievement *achievement = [notification.userInfo objectForKey:RKAchievementEarnedAchievementKey];
	    
	    //This would be the appropriate time to play a sound a let the user know they earned an achievment
	    //RobotUIKit has a view made for doing this, we are going to show how to use it
	    
	    //RobotUIKit resources like images and nib files stored in an external bundle and the path must be specified
	    NSString* rootpath = [[NSBundle mainBundle] bundlePath];
	    NSString* ruirespath = [NSBundle pathForResource:@"RobotUIKit" ofType:@"bundle" inDirectory:rootpath];
	    NSBundle* ruiBundle = [NSBundle bundleWithPath:ruirespath];
	    
	    RUIAchievementEarnedViewController *controller = [[RUIAchievementEarnedViewController alloc] initWithNibName:@"RUIAchievementEarnedViewController" bundle:ruiBundle];
	    [controller setAchievement:achievement];
	    [controller displayInView:self.view];
	    [controller release];
	    //This will automatically animate itself off screen after 5 second and release any resources.
    }
## Integrating SpheroWorld into your Application (Android)

### Connect your application to SpheroWorld

The first step to integrate your application with SpheroWorld is to pass in your applicaion id and secret string (*obtained from SpheroWorld as shown below*) when your main activity starts before you make any calls to RobotLibrary. 

![catball.png](https://github.com/orbotix/Sphero-iOS-SDK/raw/master/samples/AchievementSample/assets/image04.png) 

 An example of setting up the Achievement Manager is shown below.
    @Override
    protected void onStart() {
    	super.onStart();
       	AchievementManager.setupApplication("sphe31bfdd87d4ef0877f9757772258f50ed", "sAPzGibRzGq25krvGzbi", this);
    }
In the main activity’s onStop method you also need to inform the achievement manager that the app is stopping so that it can gracefully close the database and free up resources.  An example is shown below
    @Override
    protected void onStop() {
    	 super.onStop();
         AchievementManager.onStop();
    }
### Allowing app users to login to SpheroWorld

You can allow users to login to SpheroWorld and authorize your application by presenting the SpheroWorldWebView activity.  If a user hasn’t logged in and authorized your application they will be presented with a login screen.  If the user has already logged in they will be presented with a list of achievements and their progress towards earning them. Example code is shown below.
    Intent intent = new Intent(this, SpheroWorldWebView.class);
    startActivity(intent);
### Add achievement event tracking to your application

You will need to add code throughout your app to track achievement related events.  A few examples are shown below.
    public void redPressed() {
		AchievementManager.recordEvent(“red”);
    }
This example shows how to record an event with a count of 1.
    public void gotScore(int score) {
		AchievementManager.recordEvent(“totalPoints”, score);
    }
This example shows how to record an event by passing in a dynamic count other than 1.  This particular example could be used to give the user achievements for total points earned over all time.
    public void gameOver() {
	    if(mySuperSpecialCondition)  {
            AchievementManager.recordEvent(“capturedAllTheBasesAndKilledAllTheDudes”);
        }
    }
This example shows how achievements with complex threshold conditions can be tracked internally within your game and used with SpheroWorld achievements with a threshold of 1.

### Notifying the user of earned achievements

You can listen for the AchievementManager.AchievementEarnedIntent so you can notify the player when the user has earned an achievement.  A JSON string containing the achievement meta data can be found as a string extra attached to the intent under the key “achievementJSON”.  Currently RobotLibrary on Android doesn’t provide a UI to notify users they earned an achievement. 
