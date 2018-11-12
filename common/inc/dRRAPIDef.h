/**
 *  \file       dRRAPIDef.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/10/11
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _DRRAPIDEF_H_
#define _DRRAPIDEF_H_

#include "tRRType.h"

#ifdef __cplusplus
extern "C" {
#endif

#define dRR_ROUTINE_FN_NAME ("Routine")
#define dRR_INITIAL_FN_NAME ("Initial")

/**
 * \brief make the calling conventions the same
 */
#if defined(_USING_CYGWIN_) && defined(_ARCH_X86_)
#define dRRAPI __attribute__((cdecl))
#elif defined(_USING_LINUX_) && defined(_ARCH_X86_64_)
#define dRRAPI
#define __stdcall
#elif defined(_USING_WIN32_)
#define dRRAPI __cdecl
#endif

/**
 * \brief for win DLL
 */
#if defined(_USING_WIN32_)
#ifdef _DLL_EXPORTS_
#define dRRDLL __declspec(dllexport)
#else
#define dRRDLL __declspec(dllimport)
#endif
#else
#define dRRDLL
#endif

/**
 * \brief define FARPROC for linux
 */
#if defined(_USING_LINUX_)
typedef int (__stdcall* FARPROC)();
#endif

/**
 * \brief c style msg fn callback prototype
 */
typedef I32 (*pMsgCallback_C_T)(I32 errroCode);

/**
 * \brief c style msg fn prototype
 */
typedef I32 (*pMsgFn_C_T)(const void* pArg, void* pRet);

#ifdef __cplusplus
}
#endif

#endif
