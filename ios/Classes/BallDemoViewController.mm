//
//  BallDemoViewController.m
//  BallDemo
//
//  Created by Josh Kropf on 11-04-09.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "BallDemoViewController.h"
#import "EAGLView.h"

#import "logging.h"
#import "stage.h"
#import "sprite.h"


@interface BallDemoViewController (/* private */)
@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) CADisplayLink *displayLink;
@end

@implementation BallDemoViewController

@synthesize animating, context, displayLink;

- (void)awakeFromNib
{
    context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!context) {
		logError("failed to create EAGL context");
		return;
    } else if (![EAGLContext setCurrentContext:context]) {
		logError("failed to set EAGL context as current");
		return;
	}
	
	EAGLView *eaglView = (EAGLView *)self.view;
	
	[eaglView setContext:context];
    [eaglView setFramebuffer];
    
	GLint width = eaglView.framebufferWidth;
	GLint height = eaglView.framebufferHeight;
	
	logInfo("init(%d, %d)", width, height);
	
	if (!stage::setupGL(width, height)) {
		logError("sprite::setupGL failed");
		return;
	}
	
	_stage = new stage(width, height);
	_stage->addSprite(sprite::ballSprite(*_stage, width/2, height/2));
    
    animating = FALSE;
    animationFrameInterval = 1;
    self.displayLink = nil;
}

- (void)dealloc
{
    if (_stage) {
		delete _stage;
		_stage = NULL;
	}
	
    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
    
    [context release];
    
    [super dealloc];
}

- (void)viewWillAppear:(BOOL)animated
{
    [self startAnimation];
    
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self stopAnimation];
    
    [super viewWillDisappear:animated];
}

- (void)viewDidUnload
{
	[super viewDidUnload];
	
    if (_stage) {
		delete _stage;
		_stage = NULL;
	}

    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	
	self.context = nil;	
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    /*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
    if (frameInterval >= 1)
    {
        animationFrameInterval = frameInterval;
        
        if (animating)
        {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)startAnimation
{
    if (!animating)
    {
        CADisplayLink *aDisplayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawFrame)];
        [aDisplayLink setFrameInterval:animationFrameInterval];
        [aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        self.displayLink = aDisplayLink;
        
        animating = TRUE;
    }
}

- (void)stopAnimation
{
    if (animating)
    {
        [self.displayLink invalidate];
        self.displayLink = nil;
        animating = FALSE;
    }
}

- (void)drawFrame
{
    [(EAGLView *)self.view setFramebuffer];
	
	_stage->advance();
	_stage->render();
    
    [(EAGLView *)self.view presentFramebuffer];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

@end
