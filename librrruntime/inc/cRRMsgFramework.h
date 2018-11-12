/**
 *  \file       cRRMsgFramework.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/10/09
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRMSGFRAMEWORK_H_
#define _CRRMSGFRAMEWORK_H_

#include <unordered_map>
#include <array>

#include "dRRAPIDef.h"
#include "cRRQueue.h"
#include "cRRMsg.h"
#include "cRRMsgBase.h"
#include "eRRMsgPriorityDef.h"
#include "eRRMsgStateDef.h"

namespace rrruntime {
  /**
   *  \brief
   */
  class cRRMsgFramework : public cRRMsgBase {
   public:
    /**
     *  \brief
     */
    typedef U32 sRRMsgFnMapKey_T;

    /**
     *  \brief
     */
    typedef pMsgFn_C_T sRRMsgFnMapValue_T;

    /**
     *  \brief
     */
    cRRMsgFramework(I32 msgCPUIdx);

    /**
     *  \brief
     */
    ~cRRMsgFramework();

    /**
     *  \brief
     */
    void DoTheMsg(eRRMsgPriority_T priority) ;

    /**
     *  \brief
     */
    I32 Set(sRRMsgFnMapKey_T key, sRRMsgFnMapValue_T msgFn);

    /**
     *  \brief
     */
    I32 Push(eRRMsgPriority_T priority, cRRMsg msg);

   private:
    /**
     *  \brief
     */
    class cRRMsgQueue {
     public:
      /**
       *  \brief
       */
      cRRMsgQueue() {
        state = eMSG_DONE;
        pMsgFnC = NULL;
        pMsgImpInst = NULL;
        pMsgFnCPP = NULL;
      }

      /**
       *  \brief
       */
      ~cRRMsgQueue() { ; }

      /**
       *  \brief
       */
      cRRQueue<cRRMsg, dSTD_MUTEX_TIMEOUT> queue;

      /**
       *  \brief
       */
      cRRMsg calleeMsg;

      /**
       *  \brief
       */
      eRRMsgState_T state;

      /**
       *  \brief
       */
      pMsgFn_C_T pMsgFnC;

      /**
       *  \brief
       */
      rrruntime::cRRMsgBase* pMsgImpInst;

      /**
       *  \brief
       */
      rrruntime::cRRMsgBase::pMsgFn_CPP_T pMsgFnCPP;
    };

    /**
     *  \brief
     */
    typedef std::unordered_map<sRRMsgFnMapKey_T, sRRMsgFnMapValue_T> cRRMsgFnMap_T;

    /**
     *  \brief
     */
    typedef std::pair<cRRMsgFnMap_T::iterator, bool> sRRMsgFnMapInsertRet_T;

    /**
     *  \brief
     */
    void DoTheMsg(eRRMsgPriority_T priority,
                  const pMsgFn_C_T pMsgFnC,
                  cRRMsgBase *pMsgImpInst,
                  const rrruntime::cRRMsgBase::pMsgFn_CPP_T pMsgFnCPP,
                  const cRRMsg* pCalleeMsg);

    /**
     *  \brief
     */
    void FrameworkCallback(I32 priority);

    /**
     *  \brief
     */
    std::array<cRRMsgQueue, eMAX_MSG_PRIORITY> msgList;

    /**
     *  \brief
     */
    cRRMsgFnMap_T msgFnMap;

    /**
     *  \brief
     */
    I32 msgCPUIdx;
  };
}

#endif
