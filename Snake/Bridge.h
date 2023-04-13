#pragma once

#import <GLKit/GLKit.h>
#import <Foundation/Foundation.h>

@interface Bridge : NSObject

@property bool Moving;
@property bool Rotating;
@property CGFloat CameraZoom;
@property CGPoint CameraRotation;

- (void)setup:(GLKView *)view;
- (void)loadModels;
- (void)update;
- (void)draw:(CGRect)drawRect;
- (void)setDir:(int)dir;
- (void)resetGame;
- (int)getScore;
- (bool)getIsGameOver;
- (bool)getPlaySound;
- (void)setPlaySound:(bool)yn;

@end
