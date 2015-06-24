//
//  Debug.h
//  Oval
//
//  Created by Fabrizio Polo on 3/7/14.
//  Copyright (c) 2014 Fabrizio Polo. All rights reserved.
//

#ifndef __Oval__Debug__
#define __Oval__Debug__


#include "ovmlanguage.h"
#include <vector>
#include <string>
#include <sstream>

class AstNode;

class Debug {
    
public:
    static void breakPoint();
	static std::stringstream* renderBinaryToStream(std::vector<OvmCode_t> code, bool indentProcedures = true, bool guessFloatValues = true, bool showPush = false);
    static void renderBinary(std::vector<OvmCode_t> code);
    static const char* opCodeName(OvmCode_t opCode);
    static const char* errorCodeDescription(uint8_t errCode);
    
    static void showResults(AstNode* node);
    
};

#endif /* defined(__Oval__Debug__) */
