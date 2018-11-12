/**
 *  \file       cRRMsg.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/10/08
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRMSG_H_
#define _CRRMSG_H_

#include "tRRType.h"
#include "dRRSysDef.h"
#include "cRRCalleeBase.h"

namespace rrruntime {
  class cRRMsg {
   public:
    cRRMsg() {
      dZERO(this->arg);
      dZERO(this->ret);
      this->fnIdx = 0;
      this->fnErrCode = 0;
      this->pCallbackC = NULL;
      this->pCalleeInst = NULL;
      this->pCallbackCPP = NULL;
    }

    virtual ~cRRMsg() { ; }

    U32 arg[dSIZE_512B_32A];
    U32 ret[dSIZE_128B_32A];
    I32 fnIdx;
    I32 fnErrCode;
    pMsgCallback_C_T pCallbackC; //the c style callback function of callee
    rrruntime::cRRCalleeBase* pCalleeInst; //the instance of callee
    rrruntime::cRRCalleeBase::pMsgCallback_CPP_T pCallbackCPP; //the c++ style callback function of callee
  };
}

#endif
