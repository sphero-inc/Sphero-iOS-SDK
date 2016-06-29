#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the APIV2PROCESSOR_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// APIV2PROCESSOR_EXPORTS functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef APIV2PROCESSOR_EXPORTS
#   if WINDOWS_BUILD
#       define APIV2PROCESSOR_API  __declspec(dllexport)
#   else
#       define APIV2PROCESSOR_API
#   endif //WINDOWS_BUILD
#else
#   if WINDOWS_BUILD
#       define APIV2PROCESSOR_API __declspec(dllimport)
#   else
#       define APIV2PROCESSOR_API
#   endif //WINDOWS_BUILD
#endif //APIV2PROCESSOR_EXPORTS

#include <stdint.h>