/**
 *  \file       tRRType.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/01/06
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _TRRTYPE_H_
#define _TRRTYPE_H_

#include <stdint.h>
#include <stdio.h>

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

typedef int8_t            I08;
typedef uint8_t           U08;
typedef int16_t           I16;
typedef uint16_t          U16;
typedef int32_t           I32;
typedef uint32_t          U32;
typedef int64_t           I64;
typedef uint64_t          U64;
typedef float             F32;
typedef double            F64;
typedef long unsigned int TIMER_T;
typedef uintptr_t         UPTR;

#ifdef _UNICODE
#else
typedef char RRChar_T;
typedef char* pRRChar_T;
typedef const char* CpRRChar_T;
#endif

#ifndef DWORD
typedef U32 DWORD;
#endif
#ifndef HMODULE
typedef void* HMODULE;
#endif
#ifndef LPCSTR
typedef const char* LPCSTR;
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
