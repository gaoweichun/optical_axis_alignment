//
// MATLAB Compiler: 7.0 (R2018b)
// Date: Tue Sep 15 10:24:41 2020
// Arguments: "-B""macro_default""-W""cpplib:YourLib""-T""link:lib""sfrmat5.m"
//

#ifndef __YourLib_h
#define __YourLib_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_YourLib_C_API 
#define LIB_YourLib_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_YourLib_C_API 
bool MW_CALL_CONV YourLibInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_YourLib_C_API 
bool MW_CALL_CONV YourLibInitialize(void);

extern LIB_YourLib_C_API 
void MW_CALL_CONV YourLibTerminate(void);

extern LIB_YourLib_C_API 
void MW_CALL_CONV YourLibPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_YourLib_C_API 
bool MW_CALL_CONV mlxSfrmat5(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_YourLib
#define PUBLIC_YourLib_CPP_API __declspec(dllexport)
#else
#define PUBLIC_YourLib_CPP_API __declspec(dllimport)
#endif

#define LIB_YourLib_CPP_API PUBLIC_YourLib_CPP_API

#else

#if !defined(LIB_YourLib_CPP_API)
#if defined(LIB_YourLib_C_API)
#define LIB_YourLib_CPP_API LIB_YourLib_C_API
#else
#define LIB_YourLib_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_YourLib_CPP_API void MW_CALL_CONV sfrmat5(int nargout, mwArray& mtf502, const mwArray& a);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
