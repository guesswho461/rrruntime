/**
 *  \file       rrruntimeAPI.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/10/11
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _RRRUNTIMEAPI_H_
#define _RRRUNTIMEAPI_H_

#include "tRRType.h"
#include "dRRAPIDef.h"
#include "cRRMsg.h"
#include "eRRMsgPriorityDef.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief
 */
dRRDLL I32 dRRAPI rrruntimeSignUpAMsgFn(U32 msgID, pMsgFn_C_T msgFn);

/**
 *  \brief
 */
dRRDLL I32 dRRAPI rrruntimeCallAMsgFn(eRRMsgPriority_T priority, rrruntime::cRRMsg msg);

#ifdef __cplusplus
}
#endif

#endif
