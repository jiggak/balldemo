//
//  BallDemoAppDelegate.h
//  BallDemo
//
//  Created by Josh Kropf on 11-04-09.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class BallDemoViewController;

@interface BallDemoAppDelegate : NSObject <UIApplicationDelegate> {
   UIWindow *window;
   BallDemoViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet BallDemoViewController *viewController;

@end

