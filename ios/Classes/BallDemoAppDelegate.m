/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
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
