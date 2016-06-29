#import <Foundation/Foundation.h>

@interface RKMacroCommand : NSObject

- (RKMacroCommand *)initWithBytes:(NSData *)data;
- (NSString *)description;
- (NSData *)getByteRepresentation;
- (int)length;
- (NSString *)name;

@end
