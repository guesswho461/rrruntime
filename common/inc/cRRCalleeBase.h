/**
 *  \file       cRRCalleeBase.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/08/02
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRCALLEEBASE_H_
#define _CRRCALLEEBASE_H_

#include "tRRType.h"
#include "dRRAPIDef.h"
#include "cRRMsgBase.h"

namespace rrruntime {
  /**
   *  \brief
   */
  class cRRCalleeBase : public cRRMsgBase {
   public:
    /**
     *  \brief
     */
    cRRCalleeBase() { ; }

    /**
     *  \brief
     */
    virtual ~cRRCalleeBase() { ; }

    /**
     *  \brief
     */
    virtual I32 CallbackFnCPP(I32) = 0;
  };
}

#endif
