//
//  test.h
//  HelloTriangle
//
//  Created by Cesar Gomez on 08/03/21.
//

#ifndef test_h
#define test_h

#import <UIKit/UIKit.h>

#pragma mark -
#pragma mark DemoViewController

/** The main view controller for the demo storyboard. */
@interface DemoViewController : UIViewController
@end

#pragma mark -
#pragma mark DemoView

/** The Metal-compatibile view for the demo Storyboard. */
@interface DemoView : UIView
@end


@interface Test : NSObject {}
-(id) init;
-(void) setSampleView : (UIView*) pView;
@end

#endif /* test_h */
