/**
 *  \file       cRRThread.h
 *  \brief
 *  \author     guesswho
 *  \version
 *  \date       2017/12/19
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRTHREAD_H_
#define _CRRTHREAD_H_

#ifndef _USING_WIN32_
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <pthread.h>
#include <sched.h>
#endif

#include <thread>

#include "dRRSysDef.h"
#include "cRRError.h"

namespace rrruntime {
  /**
   *  \brief
   */
  class cRRThread : public std::thread {
   public:
    /**
     *  \brief
     */
    static I32 setScheduling(std::thread& th, int policy, int priority, int cpuIdx) {
#ifdef _USING_LINUX_
      I32 rt = eNORMAL;
      struct sched_param schParams;
      dZERO(schParams);
      int max = sched_get_priority_max(policy);
      int min = sched_get_priority_min(policy);
      schParams.sched_priority = priority > max ? max : priority;
      schParams.sched_priority = priority < min ? min : priority;
      if (pthread_setschedparam(th.native_handle(), policy, &schParams)) {
        rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_00, eERR_SET_THREAD_PRIORITY_FAILED);
      } else {
        cpu_set_t cpuAffMask;
        cpu_set_t cpuset;
        CPU_ZERO(&cpuAffMask);
        CPU_SET(cpuIdx, &cpuAffMask);
        if (pthread_setaffinity_np(th.native_handle(), sizeof(cpu_set_t), &cpuAffMask)) {
          rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_00, eERR_SET_THREAD_PRIORITY_FAILED);
        } else {
          if (pthread_getaffinity_np(th.native_handle(), sizeof(cpu_set_t), &cpuset)) {
            rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_00, eERR_SET_THREAD_PRIORITY_FAILED);
          } else {
            if (CPU_EQUAL(&cpuAffMask, &cpuset)) {
              rt = eNORMAL;
            } else {
              rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_00, eERR_SET_THREAD_PRIORITY_FAILED);
            }
          }
        }
      }
      return rt;
#else
      return cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_00, eERR_UNSUPPORTED_FN);
#endif
    }

   private:
    cRRThread() { ; }
    virtual ~cRRThread() { ; }
  };
}

#endif
