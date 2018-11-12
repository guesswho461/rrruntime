/**
 *  \file       rruntimeExtension.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/10/11
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _RRUNTIMEEXTENSION_H_
#define _RRUNTIMEEXTENSION_H_

#include "tRRType.h"
#include "dRRAPIDef.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief
 */
dRRDLL I32 dRRAPI Initial(const void* pArg, void* pRet);

/**
 *  \brief
 */
dRRDLL I32 dRRAPI Routine(const void* pArg, void* pRet);

/**
 *  \brief
 */
//dRRDLL void dRRAPI SignUpARPCService(RABDgRPC::Greeter::AsyncService* pAyncService,
//                                     grpc::ServerCompletionQueue* pCq);

/**
 *  \brief
 */
//dRRDLL void dRRAPI SignUpALuaAPI(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif
