#import "RKAsyncMessage.h"

struct RKCollisionAcceleration {
   float x;
   float y;
   float z;
};
typedef struct RKCollisionAcceleration RKCollisionAcceleration;

struct RKCollisionAxis {
   bool x : 1;
   bool y : 1;
};
typedef struct RKCollisionAxis RKCollisionAxis;

struct RKCollisionPower {
   int x;
   int y;
};
typedef struct RKCollisionPower RKCollisionPower;

@interface RKCollisionDetectedAsyncData : RKAsyncMessage

@property ( nonatomic, readonly ) RKCollisionAcceleration impactAcceleration;
@property ( nonatomic, readonly ) RKCollisionAxis impactAxis;
@property ( nonatomic, readonly ) RKCollisionPower impactPower;
@property ( nonatomic, readonly ) float impactSpeed;
@property ( nonatomic, readonly ) NSTimeInterval impactTimeStamp;

@end
