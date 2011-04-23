/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>

struct stage;
typedef struct stage stage;

@interface BallDemoViewController : UIViewController <UIAccelerometerDelegate>
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
