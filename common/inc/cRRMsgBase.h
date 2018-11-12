/**
 *  \file       cRRMsgBase.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/08/02
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRMSGBASE_H_
#define _CRRMSGBASE_H_

#include "tRRType.h"
#include "dRRAPIDef.h"

namespace rrruntime {
  /**
   *  \brief
   */
  class cRRMsgBase {
   public:
    /**
     *  \brief
     */
    typedef I32(rrruntime::cRRMsgBase::*pMsgFn_CPP_T)(const void* pArg, void* pRet);

    /**
     *  \brief
     */
    typedef I32(rrruntime::cRRMsgBase::*pMsgCallback_CPP_T)(I32);

    /**
     *  \brief
     */
    cRRMsgBase() { ; }

    /**
     *  \brief
     */
    virtual ~cRRMsgBase() { ; }
  };
}

#endif
