/**
 *  \file       cRRMsgFramework.cpp
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/10/09
 *  \copyright  MIT license, see LICENSE file
 */

#include "cRRMsgFramework.h"

#include <thread>

#include "cRRThread.h"
#include "cRRTask.h"

rrruntime::cRRMsgFramework::cRRMsgFramework(I32 msgCPUIdx) {
  this->msgCPUIdx = msgCPUIdx;
}

rrruntime::cRRMsgFramework::~cRRMsgFramework() {
  ;
}

void rrruntime::cRRMsgFramework::DoTheMsg(eRRMsgPriority_T priority) {
  switch (this->msgList.at(priority).state) {
    default:
      break;
    case eMSG_RECIEVED: {
        this->msgList.at(priority).pMsgFnC =
          this->msgFnMap.at(this->msgList.at(priority).calleeMsg.fnIdx);
        std::thread msgThread([this, priority]() {
          DoTheMsg(priority,
                   this->msgList.at(priority).pMsgFnC,
                   this->msgList.at(priority).pMsgImpInst,
                   this->msgList.at(priority).pMsgFnCPP,
                   &this->msgList.at(priority).calleeMsg);
        });
        cRRThread::setScheduling(msgThread,
                                 SCHED_OTHER,
                                 0,
                                 this->msgCPUIdx);
        msgThread.detach();
        this->msgList.at(priority).state = eMSG_DOING;
      }
      break;
    case eMSG_DONE: {
        U32 cnt = this->msgList.at(priority).queue.GetDataCount();
        if (cnt) {
          this->msgList.at(priority).queue.Pop(&this->msgList.at(priority).calleeMsg);
          this->msgList.at(priority).state = eMSG_RECIEVED;
        }
      }
      break;
  }
}

I32 rrruntime::cRRMsgFramework::Push(eRRMsgPriority_T priority, cRRMsg msg) {
  return this->msgList.at(priority).queue.Push(&msg);
}

I32 rrruntime::cRRMsgFramework::Set(sRRMsgFnMapKey_T key, sRRMsgFnMapValue_T msgFn) {
  sRRMsgFnMapInsertRet_T rt = this->msgFnMap.insert(std::make_pair(key, msgFn));
  if (rt.second)
    return eNORMAL;
  else
    return cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_01, eERR_SET_KEYPAIR_FAILED);
}

void rrruntime::cRRMsgFramework::DoTheMsg(eRRMsgPriority_T priority,
    const pMsgFn_C_T pMsgFnC,
    cRRMsgBase* pMsgImpInst,
    const pMsgFn_CPP_T pMsgFnCPP,
    const cRRMsg* pCalleeMsg) {
  I32 rt = eNORMAL;
  if (pMsgFnC) {
    rt = (*(pMsgFnC))
         ((const void*)pCalleeMsg->arg, (void*)pCalleeMsg->ret);
  } else {
    if (pMsgImpInst && pMsgFnCPP) {
      rt = ((pMsgImpInst)->*(pMsgFnCPP))
           ((const void*)pCalleeMsg->arg, (void*)pCalleeMsg->ret);
    }
  }
  std::thread frameworkCallbackThread([this, priority]() {
    this->FrameworkCallback(priority);
  });
  cRRThread::setScheduling(frameworkCallbackThread,
                           SCHED_OTHER,
                           0,
                           this->msgCPUIdx);
  frameworkCallbackThread.detach();
  if (pCalleeMsg->pCallbackC) {
    std::thread calleeCCallbackThread(pCalleeMsg->pCallbackC, rt);
    cRRThread::setScheduling(calleeCCallbackThread,
                             SCHED_OTHER,
                             0,
                             this->msgCPUIdx);
    calleeCCallbackThread.detach();
  } else {
    if (pCalleeMsg->pCalleeInst && pCalleeMsg->pCallbackCPP) {
      std::thread calleeCppCallbackThread([pCalleeMsg, rt]() {
        ((pCalleeMsg->pCalleeInst)->*pCalleeMsg->pCallbackCPP)(rt);
      });
      cRRThread::setScheduling(calleeCppCallbackThread,
                               SCHED_OTHER,
                               0,
                               this->msgCPUIdx);
      calleeCppCallbackThread.detach();
    }
  }
}

void rrruntime::cRRMsgFramework::FrameworkCallback(I32 priority) {
  this->msgList.at(priority).state = eMSG_DONE;
}
