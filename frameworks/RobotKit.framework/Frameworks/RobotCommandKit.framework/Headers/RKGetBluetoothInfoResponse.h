#import "RKDeviceResponse.h"

@interface RKGetBluetoothInfoResponse : RKDeviceResponse

@property (nonatomic, strong, readonly) NSString *name;
@property (nonatomic, strong, readonly) NSString *address;

@end
