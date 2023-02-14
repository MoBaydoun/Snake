#pragma once

#import <GLKit/GLKit.h>
#import <Foundation/Foundation.h>

@interface Renderer : NSObject

- (void)setup:(GLKView *)view;
- (void)loadModels;
- (void)update;
- (void)draw:(CGRect)drawRect;

@end
