//
//  test.m
//  HelloTriangle
//
//  Created by Cesar Gomez on 08/03/21.
//

#import <Foundation/Foundation.h>
#import <iostream>
#include "test.h"
#include "Samples.h"

static UIView* sampleView;        // Global variable to pass UIView to LunarG sample code

@interface Test()<NSObject>
@end

@implementation Test

-(id) init {
    auto test  = std::string();
    return self;
}

-(void) setSampleView : (UIView*) pView{
    sampleView = pView;
}

@end

/**
 * Called from sample.
 * Initialize sample from view, and resize view in accordance with the sample.
 */
void init_window(struct sample_info &info) {
    info.caMetalLayer = sampleView.layer;
    sampleView.bounds = CGRectMake(0, 0, info.width, info.height);
}

/** Called from sample. Return path to resource folder. */
std::string get_base_data_dir() {
    return [NSBundle.mainBundle.resourcePath stringByAppendingString: @"/"].UTF8String;
}

extern "C" int sample_mainFromCPP(void){
    sample_main(0, NULL);
    return 0;
}





#pragma mark -
#pragma mark DemoViewController

@implementation DemoViewController {}

/** Since this is a single-view app, init Vulkan when the view is loaded. */
-(void) viewDidLoad {
    [super viewDidLoad];

    sampleView = self.view;            // Pass the view to the sample code
    sample_main(0, NULL);            // Run the LunarG sample
}

@end

#pragma mark -
#pragma mark DemoView

@implementation DemoView

/** Returns a Metal-compatible layer. */
+(Class) layerClass { return [CAMetalLayer class]; }

@end
