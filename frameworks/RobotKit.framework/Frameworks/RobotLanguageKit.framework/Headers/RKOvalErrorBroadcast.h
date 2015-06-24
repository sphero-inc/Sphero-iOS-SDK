//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

#ifndef  OVM_ERROR_CODES
#define OVM_ERROR_CODES
// All of the error codes that can be used by the OVM
enum OvmErrorCodes {
	ERR_NONE = 0,                   // No error
	ERR_DIV_0,                      // Divided by 0
	ERR_LABEL_OUT_OF_BOUNDS,        // Accessed a label not in the label table
	ERR_INVALID_OP_CODE,            // Op code not recognized by the OVM
	ERR_MEM_ACCESS_OUT_OF_BOUNDS,   // Tried to access plain memory outside of its bounds
	
	// 5
	ERR_MEM_MAP_OUT_OF_BOUNDS,      // Tried to access the memory map outside of its bounds
	ERR_INVALID_MEM_MAP_LOCATION,	// Tried to access memory map location that isn't bound to anything
	ERR_BAD_OP_CALLED,              // Tried to use a blank data space as an opcode
	ERR_STACK_OVERFLOW,             // Tried to allocate more on the stack than is allowed
	ERR_STACK_UNDERFLOW,            // Tried to pop from an empty stack
	
	// 10
	ERR_READ_FROM_WRITE_ONLY,       // Tried to read from a write only location
	ERR_WRITE_TO_READ_ONLY,         // Tried to write to a read only location
	ERR_EXEC_OUT_OF_BOUNDS,         // Tried to execute an out of bounds memory location
	ERR_STREAM_BUFFER_OVERFLOW,     // Tried to append more data to the stream than will fit
	
	// 14
	ERR_LIBRARY_OVERFLOW,           // Tried to add a new procedure and ran out of space
	ERR_CALL_STACK_OVERFLOW,        // Tried to call more total functions than we have space for
	ERR_CALL_STACK_UNDERFLOW,       // More returns than calls
	ERR_UNBOUND_PROC_END,           // OP_PROC_END called with no preceeding OP_PROC.
	ERR_CODE_STREAM_OVER_RELEASE,   // Tried to call op_release when retain count == 0
	
	ERR_ATOMIC_LOCK_OVER_RELEASE,   // Called opAtomicEnd when atomic lock count == 0
	ERR_PLATFORM_FAILURE,			// Platform-specific error.
	
	// 21
	ERR_IMPLEMENTATION_ERROR,		// Reserved for things that "shouldn't happen" like violated preconditions.
	
	ERR_INCOMPRESSIBLE_CPROC,		// Received a compressed procedure with more than 128 uncompressible literals.
	ERR_CALL_UNBOUND_PROC_ID,        // Call a procedure with an ID not bound to any procedure
	ERR_SET_LIBRARY_FROM_LIBRARY,		//	Call set library function while the VM is executing library code
};

#endif


@interface RKOvalErrorBroadcast : RKAsyncMessage

@property (nonatomic) enum OvmErrorCodes errorCode;

- (NSString *)errorDescription;

@end
