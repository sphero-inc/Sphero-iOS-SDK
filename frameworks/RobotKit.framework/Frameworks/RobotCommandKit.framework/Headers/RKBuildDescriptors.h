#import <Foundation/Foundation.h>

@interface RKBuildDescriptors : NSObject

+ (NSUInteger)majorVersion;
+ (NSUInteger)minorVersion;
+ (NSUInteger)buildNumber;
+ (NSString *)versionString;

@end
