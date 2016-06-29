#import <Foundation/Foundation.h>
#import "RKRollCommand.h"

@interface RKStatOdometerHack : NSObject

+ (void)recordStatForPacket:(NSData *)packet andMac:(NSString *)mac;

@end
