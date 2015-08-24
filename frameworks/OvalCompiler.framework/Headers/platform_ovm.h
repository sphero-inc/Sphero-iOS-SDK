
// Total size for executing OVM code
#   define OVM_CODE_SIZE                    3072
#        define OVM_STREAMING_CODE_SIZE                    ((255*9)/4)        //    Assume best decompression ratio = 9
#   define OVM_DECOMPRESSION_BUFFER_SIZE    20
// Total size for the OVM stack
#   define OVM_STACK_SIZE                   384
// Total size for the associative array used
// for jump operations
#   define OVM_JUMP_TABLE_SIZE              192
#   define OVM_MEM_MAP_TABLE_SIZE           66
#   define OVM_PLATFORM_OP_TABLE_SIZE       15
//  The call stack has a max depth for now
#   define OVM_CALL_STACK_SIZE              32
//    Build robot-specific functionality into the VM.
#        define OVM_PLATFORM_HEADER                            "mock_spheroovm.h"
#   define OVM_PLATFORM_MEM_HEADER          "mock_spheroovmmem.h"
#   define OVM_PLATFORM_MEM_INIT(MEM_MAP)   initSpheroOvmMemMap(MEM_MAP)
#   define OVM_PLATFORM_OP_HEADER           "mock_spheroovmops.h"
#   define OVM_PLATFORM_OP_INIT(OP_TABLE)   initSpheroOvmOps(OP_TABLE)
#        define OVM_NUM_INSTRUCTIONS_IN_UPDATE        100
#        define OVM_MAX_INSTRUCTIONS_IN_UPDATE        150

#   define INCLUDE_DEBUG_TOOLS
#   define _OVM_INLINE					//	#define this to be nothing = no inlining
