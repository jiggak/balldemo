/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
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
	
   logInfo("create(%d, %d)", width, height);

   _stage = new stage(width, height, true);
   if (!_stage->setupGL()) {
      logError("stage::setupGL failed");
      return;
   }
    
   animating = FALSE;
   animationFrameInterval = 1;
   self.displayLink = nil;
   
   [UIAccelerometer sharedAccelerometer].updateInterval = 1.0 / 10.0;
   [UIAccelerometer sharedAccelerometer].delegate = self;
}

- (void)dealloc
{
   if (_stage) {
      delete _stage;
      _stage = NULL;
   }
	
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

   if ([EAGLContext currentContext] == context)
      [EAGLContext setCurrentContext:nil];

   self.context = nil;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
   UITouch *touch = [[event allTouches] anyObject];
   CGPoint point = [touch locationInView:self.view];
   _stage->queueAction(ACTION_TYPE_TOUCH_UP, point.x, point.y);
}

- (void)accelerometer:(UIAccelerometer*)accelerometer didAccelerate:(UIAcceleration*)acceleration
{
   // accelerometer is in the range -1 <> 1; convert to gravity
   // also swap x/y since stage is performing rotation
   // ... and for some reason invert y
   float x = acceleration.y * -9.81f;
   float y = acceleration.x * 9.81f;
   
   _stage->queueAction(ACTION_TYPE_TILT, x, y);
}

- (NSInteger)animationFrameInterval
{
   return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
   // Frame interval defines how many display frames must pass between each
   // time the display link fires. The display link will only fire 30 times
   // a second when the frame internal is two on a display that refreshes
   // 60 times a second. The default frame interval setting of one will
   // fire 60 times a second when the display refreshes at 60 times a second.
   // A frame interval setting of less than one results in undefined behavior.
   if (frameInterval >= 1) {
      animationFrameInterval = frameInterval;
      
      if (animating) {
         [self stopAnimation];
         [self startAnimation];
      }
   }
}

- (void)startAnimation
{
   if (!animating) {
      CADisplayLink *aDisplayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawFrame)];
      [aDisplayLink setFrameInterval:animationFrameInterval];
      [aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
      self.displayLink = aDisplayLink;
      
      animating = TRUE;
   }
}

- (void)stopAnimation
{
   if (animating) {
      [self.displayLink invalidate];
      self.displayLink = nil;
      animating = FALSE;
   }
}

- (void)drawFrame
{
   [(EAGLView *)self.view setFramebuffer];
   
   _stage->render();
   
   [(EAGLView *)self.view presentFramebuffer];
}

@end
