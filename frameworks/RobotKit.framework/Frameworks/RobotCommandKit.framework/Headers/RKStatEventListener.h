#import <Foundation/Foundation.h>
#import "RKRobotBase.h"

@interface RKStatEventListener : NSObject <RKResponseObserver>

+ (instancetype)sharedListener;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (void)startListener;
- (void)stopListener;

@end