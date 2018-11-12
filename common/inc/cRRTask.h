/**
 *  \file       cRRTask.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/04/18
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRTASK_H_
#define _CRRTASK_H_

#include <vector>
#include <thread>

#include "tRRType.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*pRRTask_C_T)(const void* pArg);

#ifdef __cplusplus
}
#endif

namespace rrruntime {
  /**
   *  \brief
   */
  class cRRTask {
   public:
    cRRTask(pRRTask_C_T taskFn,
            const void* pArg,
            I32 schedPolicy,
            I32 schedPriority,
            I32 cpuIdx)
      : taskFn(taskFn)
      , pArg(pArg)
      , schedPolicy(schedPolicy)
      , schedPriority(schedPriority)
      , cpuIdx(cpuIdx) { ; }

    virtual ~cRRTask() { ; }

    pRRTask_C_T taskFn;
    const void* pArg;
    I32 schedPolicy;
    I32 schedPriority;
    I32 cpuIdx;
  };
}

typedef std::vector<std::thread> cRRThreadList_T;
typedef std::vector<rrruntime::cRRTask> cRRTaskList_T;

#endif
