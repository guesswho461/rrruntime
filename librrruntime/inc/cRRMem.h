/**
 *  \file       cRRMem.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/02/23
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRMEM_H_
#define _CRRMEM_H_

#include <mutex>

#include "tRRType.h"
#include "dRRSysDef.h"

namespace rrruntime {
  /**
   *  \brief to let the share memory declare more easier, declare the mutex and memory pointer at once
   */
  template<typename T, U32 N>
  class cRRMem {
   public:
    cRRMem() : pMem(NULL), Timeout(N) {
      if (this->pMem)
        delete this->pMem;
      this->pMem = new T();
    }

    virtual ~cRRMem() {
      if (this->pMem)
        delete this->pMem;
    }

    /**
     *  \brief handle of the mutex of memory or memory handle
     */
    std::timed_mutex hMutex;

    /**
     *  \brief memory pointer
     */
    T* pMem;

    /**
     *  \brief  mutex timeout time, unit is 1ms
     */
    U32 Timeout;
  };
}

#endif
