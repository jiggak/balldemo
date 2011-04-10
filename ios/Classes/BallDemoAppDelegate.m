//
//  BallDemoAppDelegate.m
//  BallDemo
//
//  Created by Josh Kropf on 11-04-09.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "BallDemoAppDelegate.h"
#import "BallDemoViewController.h"

@implementation BallDemoAppDelegate

@synthesize window;
@synthesize viewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
   [self.window addSubview:self.viewController.view];
   return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
   [self.viewController stopAnimation];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
   [self.viewController startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
   [self.viewController stopAnimation];
}

- (void)dealloc
{
   [viewController release];
   [window release];
   
   [super dealloc];
}

@end
