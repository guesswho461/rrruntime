/**
 *  \file       cRRBase.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/10/04
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRBASE_H_
#define _CRRBASE_H_

#include <mutex>
#include <chrono>

#include "dRRAPIDef.h"
#include "tRRType.h"
#include "cRRMsgBase.h"
#include "cRRError.h"

namespace rrruntime {
  /**
   *  \brief
   */
  class cRRBase : public cRRMsgBase {
   public:
    /**
     *  \brief
     */
    cRRBase() { ; }

    /**
     *  \brief
     */
    virtual ~cRRBase() { ; }

   protected:
    /**
     *  \brief  to invoke the function pointer via C way
     */
    I32 Invoke(const pMsgFn_C_T pToDo,
               const void* pArg,
               void* pRet) {
      I32 rt = eNORMAL;
      if (pToDo) rt = (*pToDo)(pArg, pRet);
      return rt;
    }

    /**
     *  \brief  to invoke the function pointer via C++ way
     */
    I32 Invoke(const cRRMsgBase::pMsgFn_CPP_T pToDo,
               const void* pArg,
               void* pRet) {
      I32 rt = eNORMAL;
      if (pToDo) rt = (this->*pToDo)(pArg, pRet);
      return rt;
    }

    /**
     *  \brief  to accquire the mutex and to do invoke
     */
    I32 DoMemRW(std::timed_mutex* pMutex,
                U32 mutexTimeout,
                const pMsgFn_C_T pToDo,
                U32* pMutexTimeoutCnt,
                const void* pArg,
                void* pRet) {
      I32 rt = eNORMAL;
      bool isLocked = pMutex->try_lock_for(std::chrono::milliseconds(mutexTimeout));
      if (isLocked) {
        rt = this->Invoke(pToDo, pArg, pRet);
        pMutex->unlock();
      } else {
        if (pMutexTimeoutCnt) ++(*pMutexTimeoutCnt);
        rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_00, eERR_MUTEX_REQUEST_FAILED);
      }
      return rt;
    }

    /**
     *  \brief  to accquire the mutex and to do invoke
     */
    I32 DoMemRW(std::timed_mutex* pMutex,
                U32 mutexTimeout,
                const cRRMsgBase::pMsgFn_CPP_T pToDo,
                U32* pMutexTimeoutCnt,
                const void* pArg,
                void* pRet) {
      I32 rt = eNORMAL;
      bool isLocked = pMutex->try_lock_for(std::chrono::milliseconds(mutexTimeout));
      if (isLocked) {
        rt = this->Invoke(pToDo, pArg, pRet);
        pMutex->unlock();
      } else {
        if (pMutexTimeoutCnt) ++(*pMutexTimeoutCnt);
        rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_00, eERR_MUTEX_REQUEST_FAILED);
      }
      return rt;
    }
  };
}

#endif
