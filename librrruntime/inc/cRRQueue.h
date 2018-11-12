/**
 *  \file       cRRQueue.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/09/25
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRQUEUE_H_
#define _CRRQUEUE_H_

#include <queue>
#include <vector>

#include "tRRType.h"
#include "cRRBase.h"
#include "cRRMem.h"
#include "cRRError.h"

namespace rrruntime {
  template <typename T, U32 N>
  class cRRQueue : public cRRBase {
   public:
    /**
     *  \brief
     */
    typedef std::vector<T> cDataVector_T;

    /**
     *  \brief constructor
     */
    cRRQueue();

    /**
     *  \brief  to dispose the instance
     */
    virtual ~cRRQueue();

    /**
     *  \brief
     */
    void Flush();

    /**
     *  \brief
     */
    U32 GetDataCount();

    /**
     *  \brief
     */
    I32 Push(const T* pData);

    /**
     *  \brief
     */
    I32 PushHead(const T* pData);

    /**
     *  \brief
     */
    I32 Pop(T* pData);

    /**
     *  \brief
     */
    I32 GetFront(T* pData);

    /**
     *  \brief
     */
    I32 GetBack(T* pData);

    /**
     *  \brief
     */
    I32 PopBack(T* pData);

    /**
     *  \brief
     */
    I32 Pop(U32 cnt, cDataVector_T* pDataVec);

   private:
    /**
     *  \brief
     */
    typedef std::deque<T> cMem_T;

    /**
     *  \brief
     */
    typedef cRRMem<cMem_T, N> cBuf_T;

    /**
     *  \brief
     */
    class cRRQueuePopRet {
     public:
      cRRQueuePopRet(cMem_T* pMem, T* pData, U32 cnt = 1, cDataVector_T* pDataVec = NULL)
        : pMem(pMem), pData(pData), rt(eNORMAL), cnt(cnt), pDataVec(pDataVec) { ; }
      ~cRRQueuePopRet() { ; }
      cMem_T* pMem;
      T* pData;
      I32 rt;
      U32 cnt;
      cDataVector_T* pDataVec;
    };

    /**
     *  \brief
     */
    I32 Initial(const void* pArg, void* pRet);

    /**
     *  \brief
     */
    I32 Dispose(const void* pArg, void* pRet);

    /**
     *  \brief
     */
    I32 Flush(const void* pArg, void* pRet);

    /**
     *  \brief
     */
    I32 GetDataCount(const void* pArg, void* pRet);

    /**
     *  \brief
     */
    I32 GetBack(const void* pArg, void* pRet);

    /**
     *  \brief
     */
    I32 Push(const void* pArg, void* pRet);

    /**
     *  \brief
     */
    I32 PushHead(const void* pArg, void* pRet);

    /**
     *  \brief
     */
    I32 Pop(const void* pArg, void* pRet);

    /**
     *  \brief
     */
    I32 PopBack(const void* pArg, void* pRet);

    /**
     *  \brief
     */
    cBuf_T* pBuf;
  };
}

template <typename T, U32 N>
rrruntime::cRRQueue<T, N>::cRRQueue()
  : cRRBase() {
  this->pBuf = new cBuf_T();
}

template <typename T, U32 N>
rrruntime::cRRQueue<T, N>::~cRRQueue() {
  if (this->pBuf) delete this->pBuf;
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
Flush(const void* pArg, void* pRet) {
  I32 rt = eNORMAL;
  if (pRet)
    ((cMem_T*)pRet)->clear();
  else
    rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_01, eERR_ILLEGAL_ARGUMENT);
  return rt;
}

template <typename T, U32 N>
void rrruntime::cRRQueue<T, N>::
Flush() {
  DoMemRW(&this->pBuf->hMutex,
          this->pBuf->Timeout,
          (pMsgFn_CPP_T)&cRRQueue::Flush,
          NULL,
          NULL,
          this->pBuf->pMem);
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
GetDataCount(const void* pArg, void* pRet) {
  I32 rt = eNORMAL;
  if (pArg && pRet)
    * ((U32*)pRet) = ((const cMem_T*)pArg)->size();
  else
    rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_01, eERR_ILLEGAL_ARGUMENT);
  return rt;
}

template <typename T, U32 N>
U32 rrruntime::cRRQueue<T, N>::
GetDataCount() {
  U32 cnt = 0;
  DoMemRW(&this->pBuf->hMutex,
          this->pBuf->Timeout,
          (pMsgFn_CPP_T)&cRRQueue::GetDataCount,
          NULL,
          this->pBuf->pMem,
          &cnt);
  return cnt;
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
Push(const void* pArg, void* pRet) {
  I32 rt = eNORMAL;
  if (pArg && pRet)
    ((cMem_T*)pRet)->push_back(* (const T*)pArg);
  else
    rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_01, eERR_ILLEGAL_ARGUMENT);
  return rt;
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
Push(const T* pData) {
  return DoMemRW(&this->pBuf->hMutex,
                 this->pBuf->Timeout,
                 (pMsgFn_CPP_T)&cRRQueue::Push,
                 NULL,
                 pData,
                 this->pBuf->pMem);
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
PushHead(const void* pArg, void* pRet) {
  I32 rt = eNORMAL;
  if (pArg && pRet)
    ((cMem_T*)pRet)->push_front(* (const T*)pArg);
  else
    rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_01, eERR_ILLEGAL_ARGUMENT);
  return rt;
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
PushHead(const T* pData) {
  return DoMemRW(&this->pBuf->hMutex,
                 this->pBuf->Timeout,
                 (pMsgFn_CPP_T)&cRRQueue::PushHead,
                 NULL,
                 pData,
                 this->pBuf->pMem);
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
Pop(const void* pArg, void* pRet) {
  I32 rt = eNORMAL;
  if (pRet) {
    cRRQueuePopRet* localpRet = (cRRQueuePopRet*)pRet;
    U32 size = localpRet->pMem->size();
    if (size) {
      U32 dataSize = size < localpRet->cnt ?
                     size : localpRet->cnt;
      if (dataSize == 1) {
        if (localpRet->pData) *localpRet->pData = localpRet->pMem->front();
        localpRet->pMem->pop_front();
      } else {
        for (U32 k = 0; k < dataSize; k++) {
          localpRet->pDataVec->push_back(localpRet->pMem->front());
          localpRet->pMem->pop_front();
        }
      }
      localpRet->rt = eNORMAL;
    } else {
      localpRet->rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_00, eERR_IS_EMPTY);
    }
  } else {
    rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_01, eERR_ILLEGAL_ARGUMENT);
  }
  return rt;
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
Pop(T* pData) {
  cRRQueuePopRet ret(this->pBuf->pMem, pData);
  I32 rt = DoMemRW(&this->pBuf->hMutex,
                   this->pBuf->Timeout,
                   (pMsgFn_CPP_T)&cRRQueue::Pop,
                   NULL,
                   NULL,
                   &ret);
  if (rt != eNORMAL) return rt;
  else return ret.rt;
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
GetBack(const void* pArg, void* pRet) {
  I32 rt = eNORMAL;
  if (pRet) {
    cRRQueuePopRet* localpRet = (cRRQueuePopRet*)pRet;
    U32 size = localpRet->pMem->size();
    if (size) {
      if (localpRet->pData) *localpRet->pData = localpRet->pMem->back();
      localpRet->rt = eNORMAL;
    } else {
      localpRet->rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_00, eERR_IS_EMPTY);
    }
  } else {
    rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_01, eERR_ILLEGAL_ARGUMENT);
  }
  return rt;
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
GetBack(T* pData) {
  cRRQueuePopRet ret(this->pBuf->pMem, pData);
  I32 rt = DoMemRW(&this->pBuf->hMutex,
                   this->pBuf->Timeout,
                   (pMsgFn_CPP_T)&cRRQueue::GetBack,
                   NULL,
                   NULL,
                   &ret);
  if (rt) return rt;
  else return ret.rt;
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
PopBack(const void* pArg, void* pRet) {
  I32 rt = eNORMAL;
  if (pRet) {
    cRRQueuePopRet* localpRet = (cRRQueuePopRet*)pRet;
    U32 size = localpRet->pMem->size();
    if (size) {
      if (localpRet->pData) *localpRet->pData = localpRet->pMem->back();
      localpRet->pMem->pop_back();
      localpRet->rt = eNORMAL;
    } else {
      localpRet->rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_00, eERR_IS_EMPTY);
    }
  } else {
    rt = cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_01, eERR_ILLEGAL_ARGUMENT);
  }
  return rt;
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
PopBack(T* pData) {
  cRRQueuePopRet ret(this->pBuf->pMem, pData);
  I32 rt = DoMemRW(&this->pBuf->hMutex,
                   this->pBuf->Timeout,
                   (pMsgFn_CPP_T)&cRRQueue::PopBack,
                   NULL,
                   NULL,
                   &ret);
  if (rt) return rt;
  else return ret.rt;
}

template <typename T, U32 N>
I32 rrruntime::cRRQueue<T, N>::
Pop(U32 cnt, cDataVector_T* pDataVec) {
  cRRQueuePopRet ret(this->pBuf->pMem, NULL, cnt, pDataVec);
  I32 rt = DoMemRW(&this->pBuf->hMutex,
                   this->pBuf->Timeout,
                   (pMsgFn_CPP_T)&cRRQueue::Pop,
                   NULL,
                   NULL,
                   &ret);
  if (rt) return rt;
  else return ret.rt;
}

#endif
