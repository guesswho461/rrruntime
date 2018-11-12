/**
 *  \file       rrruntime.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/10/11
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _RRRUNTIME_H_
#define _RRRUNTIME_H_

#include <string>

#include "tRRType.h"
#include "dRRAPIDef.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief
 */
dRRDLL I32 dRRAPI rrruntimeInitial(std::string extLibsDirAbsPath,
                                   I32 mainCPUIdx,
                                   I32 mainTaskPriority,
                                   I32 auxCPUIdx);

/**
 *  \brief
 */
dRRDLL void dRRAPI rrruntimeDispose();

#ifdef __cplusplus
}
#endif

#endif
