@interface RKMajorMinorVersion : NSObject

@property (nonatomic, strong, readonly, nonnull) NSString *major;
@property (nonatomic, strong, readonly, nonnull) NSString *minor;

- (nullable instancetype)initWithVersionString:(nonnull NSString *)versionString;
- (NSComparisonResult)compare:(nonnull RKMajorMinorVersion *)version;
- (BOOL)isGreaterThan:(nonnull RKMajorMinorVersion *)version;
- (BOOL)isLessThan:(nonnull RKMajorMinorVersion *)version;
- (nonnull NSString *)versionString;

@end
