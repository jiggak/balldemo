//
//  BallDemoViewController.h
//  BallDemo
//
//  Created by Josh Kropf on 11-04-09.
//  Copyright 2011 slashdev.ca. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>

struct stage;
typedef struct stage stage;

@interface BallDemoViewController : UIViewController
{
   EAGLContext *context;
   stage *_stage;
   
   BOOL animating;
   NSInteger animationFrameInterval;
   CADisplayLink *displayLink;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;

- (void)startAnimation;
- (void)stopAnimation;

@end
