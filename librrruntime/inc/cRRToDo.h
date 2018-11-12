/**
 *  \file       cRRToDo.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/02/23
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRTODO_H_
#define _CRRTODO_H_

#include <mutex>
#include <vector>

#include "tRRType.h"
#include "cRRMsgBase.h"

namespace rrruntime {
  /**
   *  \brief  to let the share memory access more easier,
   *          let the framework could call user's function via function pointer
   */
  template<typename T>
  class cRRToDo {
   public:
    cRRToDo(T pToDoFn,
            const void* pArg,
            void* pRet,
            std::timed_mutex* phMutex,
            U32 mutexTimeout,
            U32* pMutexTimeoutCnt) {
      this->pToDoFn = pToDoFn;
      this->pArg = pArg;
      this->pRet = pRet;
      this->phMutex = phMutex;
      this->mutexTimeout = mutexTimeout;
      this->pMutexTimeoutCnt = pMutexTimeoutCnt;
    }

    virtual ~cRRToDo() { ; }

    /**
     *  \brief function pointer, point to the function you want to call in C++ way
     */
    T pToDoFn;

    /**
     *  \brief
     */
    const void* pArg;

    /**
     *  \brief
     */
    void* pRet;

    /**
     *  \brief a handle of the mutex of memory
     */
    std::timed_mutex* phMutex;

    /**
     *  \brief a timeout time of the mutex
     */
    U32 mutexTimeout;

    /**
     *  \brief a timeout counter of this action
     */
    U32* pMutexTimeoutCnt;
  };
}

#endif
