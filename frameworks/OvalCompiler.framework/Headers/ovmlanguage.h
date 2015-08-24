
//
//*****************************************************************************
//                            Orbotix Inc.
//
// File              : ovmlanguage.h								  
//
// Compiler          : MDK-ARM-BASIC
// Date              : 3/5/2014
//
// Supported devices : STM32F372CB
//
// Description       : Primary OVM header.  Configures the OVM and contains important types.
//
// Copyright:
// (C) 2014. Orbotix Inc. (http://www.orbotix.com)
// All Rights Reserved
//
//                            Orbotix Inc.
//*****************************************************************************




#ifndef OVM_ovmlanguage_h
#define OVM_ovmlanguage_h

#include "inttypes.h"

// All opcodes suppored by OVM
enum OvmOpCodes {
    
    OP_PUSH_LIT = 0,        // Push the next literal in the code into the stack
	OP_POP_TO = 1,          // Pop the value from the stack and write it to the memory location

    // Push codes
    OP_CAST_INT_TO_FLOAT,   // Casts the intger value on the top of the stack to a float
    OP_PUSH_FROM,           // Push the value from memory onto the stack
	OP_CALL,				// Jump to the id (in jump table) at the top of the stack
    OP_PUSH_LOCAL,          // Push a value from a memory location relative to the frame pointer
    
    // Pop codes
    OP_POP_LOCAL,           // Pop the value from the stack and write it to a location relative to the frame pointer.
    
    // Float arithmetic codes
	OP_MULTIPLY_FLOAT,      // Multiply the two floating point numbers on the top of the stack
    OP_ADD_FLOAT,           // Add the two floating point numbers on the top of the stack
	OP_SUBTRACT_FLOAT,      // Subtract the two floating point numbers on the top of the stack

// 10
    // Jump relatively (within a function or stream)
	OP_RELJUMP,				// Jump relative to current IP
	OP_RELJUMP_IF,          // Jump relative to current IP if the condition is true
	
    OP_RETURN,              // return

    OP_COMPARE_FLOAT,       // Compares two float numbers on the top of the stack.
    OP_DIVIDE_FLOAT,        // Divide the two floating point numbers on the top of the stack
    OP_POW_FLOAT,           // Exponentiate the two floating point numbers on the top of the stack
    
    // Trig codes
    OP_COS_FLOAT,           // Take the cosine of the number on the top of the stack
    OP_SIN_FLOAT,           // Take the sine of the number on the top of the stack
    OP_TAN_FLOAT,           // Take the tangent of the number on the top of the stack
    OP_ATAN2_FLOAT,         // Take the tangent of the number on the top of the stack and square it
    
// 20

    OP_LN_FLOAT,            // Take the natural log of the number
    
    // Integer arithmetic codes
    OP_ADD_INT,             // Add the two integers on the top of the stack
	OP_SUBTRACT_INT,        // Subtract the two integers on the top of the stack
	OP_MULTIPLY_INT,        // Multiply the two integers on the top of the stack
	OP_DIVIDE_INT,          // Divide the two integers on the top of the stack
    
    //  Casting codes (note other casting code above for compression efficiency)
    // Pushes: 1 if the first number pushed is greater than the second
    //         0 if the numbers are equal,
    //        -1 if the first number pushed is less than the second
    OP_COMPARE_INT,         // Compares two integer numbers on the top of the stack.
    OP_LOGICAL_NOT,         // Returns 1.0f or 0.0f depending on whether arg is bitwise zero.
    OP_LOGICAL_AND,
    OP_LOGICAL_OR,
    // Pushes: 1 if the first number pushed is greater than the second
    //         0 if the numbers are equal,
    //        -1 if the first number pushed is less than the second
    
    // Casting codes
    OP_CAST_FLOAT_TO_INT,   // Casts the float value on the top of the stack to an integer
    
// 30
    OP_YIELD,               // yield to the streaming buffer (or back to a function from the buffer)
    OP_WAIT,                // give up your time slice
    
    // Code stream memory management
    OP_RETAIN,
    OP_RELEASE,
    
    // Stack manipulation
    OP_ALLOCATE,
    
    // Bind a block of code to a value in the
    OP_PROC,
    OP_PROC_END,
    
    // Force a group of instructions to operate as one
    OP_ATOMIC,
    OP_ATOMIC_END,
    
    OP_FAIL,                // Unused.  Intended to represent user defined failures.
		
// 40
	OP_END,                 // Indicates the end of the code
    
    OP_BAD,                 // Bad op code, when blank code is treated as an opcode
		
    OP_CAST_LOCAL_TO_GLOBAL,

	OP_COMPRESSED_PROC,
    
    OP_INCLUSIVE_OR,
    OP_EXCLUSIVE_OR,
    OP_AND,
    OP_LEFT_SHIFT,
    OP_RIGHT_SHIFT,
    OP_BITWISE_NOT,

    // Number of all supported codes
	kNumOpCodes
};

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

typedef unsigned char byte;

//	All OVM data is in chunks of this size.
typedef union {
    float floatValue;
    int32_t intValue;
    uint32_t uintValue;
    int32_t opCode;
    int32_t errCode;
		byte* ref;
}
OvmData_t;

// An OvmCode_t is just the same type as the OvmData_t,
// but the two are semantically different
typedef OvmData_t OvmCode_t;
typedef int32_t OvmOpCode_t;


extern OvmData_t zeroData;
extern OvmCode_t zeroCode;

#endif




























