//
//*****************************************************************************
//                            Orbotix Inc.
//
// File              : ovm.h								  
//
// Compiler          : MDK-ARM-BASIC
// Date              : 3/5/2014
//
// Supported devices : STM32F372CB
//
// Description       : OVM Public functions.
//
// Copyright:
// (C) 2014. Orbotix Inc. (http://www.orbotix.com)
// All Rights Reserved
//
//                            Orbotix Inc.
//*****************************************************************************
#ifndef _OWM_H
#define _OWM_H

#include "inttypes.h"
#include "sphero_types.h"
#include "ovmlanguage.h"
#include "platform_ovm.h"

//#define BUILD_OVM_PERF		//	Build-in the performance tracking code

#define OVM_VERSION 7

typedef unsigned char byte;

#ifdef __cplusplus
extern "C" {
#endif

extern OvmData_t ovmStack[OVM_STACK_SIZE];

//////////////////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////////////////
	
//	This MUST be a multiple of 32 bits long
typedef struct OvmLibraryHeaderStruct
{
	int32_t lengthInBytes;
	uint32_t hashCode;
	uint32_t flashPageNumber;
}
  OvmLibraryHeader_t;


//////////////////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////////////////

void ovmInit(void);

void ovmSetIsRunning(bool);				//	cmd.c
bool ovmIsRunning(void);
bool ovmIsBlocked(void);
void ovmLockStream(bool locked);
bool ovmStreamIsLocked(void);

void ovmResetRuntime(void);				//	cmd.c
void ovmResetLibrary(void);

bool ovmLibraryIsValid(void);

void ovmUpdateExecutionState(void);
void ovmAsynchronousUpdate(void);
void ovmExecuteCodeBlock(void);

OvmData_t ovmPeekStack(void);
OvmCode_t ovmPeekCode(void);

bool ovmAppendCode(OvmCode_t* code, int codeLength);
bool ovmAppendCompressedCode(byte* code, int codeLength);
int32_t ovmGetInternalError(void);
void ovmClearInternalError(void);

int getOvmLibrarySize(void);

uint16_t ovmGetVersion(void);				//	cmd.c

typedef void (*OvmInternalErrorCallback_t)(int32_t errorCode);
void ovmSetInternalErrorCallback(OvmInternalErrorCallback_t callBack);

//	DON'T ABUSE THIS FUNCTION.  It's ONLY here in order to allow sharing memory with Orb Basic.
void* ovmGetCodeMemoryBlock(int* size_out);

//	These functions exist to support saving and loading the code library
OvmLibraryHeader_t* ovmGetCodeLibraryHeader(void);

void* getOvmCodeStashStartAndSize(int* lengthInBytes_out);
void ovmSetCodeLibraryHead(void* head);
bool ovmCallStackNotEmpty(void);

typedef void (*OvmOpCodeFunction_t)(void);

int ovmUnpackProcedure(uint32_t id, OvmCode_t* code_out);

//	Call an OVM function from the jump table
void ovmAsyncInvokeFunction(int32_t functionId);
typedef int32_t DeferredFunctionCall_t;
void init_ovmDeferredFunctionCall(DeferredFunctionCall_t* deferred);
void ovmAsyncInvokeDeferredFunction(DeferredFunctionCall_t* deferred, int32_t functionId);
void ovmAsyncForceInvokeDeferredFunction(DeferredFunctionCall_t* deferred);

#ifdef BUILD_OVM_PERF
extern uint32_t numInstructionsThisSecond;
#endif

#ifdef INCLUDE_DEBUG_TOOLS
extern uint32_t ovmMaxObservedStackDepth;
#endif


#define NO_OVM_FUNCTION -1

    
#ifdef __cplusplus
}
#endif

#endif












