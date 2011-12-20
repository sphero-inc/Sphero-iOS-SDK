//
//  CircularUIView.m
//  Sphero
//
//  Created by Brian Alexander on 4/25/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import "CircularUIView.h"


@implementation CircularUIView


- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
    }
    return self;
}

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event {
	CGFloat radius = (MIN(self.bounds.size.width, self.bounds.size.height) / 2.0);
	CGFloat x = (point.x - radius) / radius;
	CGFloat y = (point.y - radius) / radius;
	CGFloat h = hypot(x, y);
	return( h < 1.0 ); 
}

- (void)dealloc {
    [super dealloc];
}


@end
