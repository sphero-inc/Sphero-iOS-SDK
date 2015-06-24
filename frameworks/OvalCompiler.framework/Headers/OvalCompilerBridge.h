//
//  OvalCompilerBridge.h
//  OvalLanguage
//
//  Created by Fabrizio Polo on 6/30/14.
//  Copyright (c) 2014 Fabrizio Polo. All rights reserved.
//

#ifndef __OvalLanguage__OvalCompilerBridge__
#define __OvalLanguage__OvalCompilerBridge__


#include "ovmlanguage.h"
#include "ovm.h"


#ifdef __cplusplus
extern "C" {
#endif

    typedef struct CompiledOvalLengths {
        int32_t codeLength;
        int32_t sizesLength;
        int32_t messageLength;
        int32_t errorOccurred;
    } CompiledOvalLengths;


    CompiledOvalLengths ovalCompileCompressAndPacketize(const char* source, byte*& new_obj, int*& new_packetSizes, char*& message);
    void forceGlobalAllocation();
    void ovalResetLinker(void);
    
    
#ifdef __cplusplus
}
#endif

    
#endif /* defined(__OvalLanguage__OvalCompilerBridge__) */
