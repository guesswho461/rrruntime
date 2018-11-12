/**
 *  \file       cRRError.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/01/06
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRERROR_H_
#define _CRRERROR_H_

#include "tRRType.h"
#include "eRRErrorDef.h"
#include "eRRSysPartTypeDef.h"
#include "eRRErrorPriorityDef.h"

namespace rrruntime {
  /**
   * \brief
   */
  class cRRError {
   public:
    /**
     * \brief
     */
    static I32 Return(eRRSysPartType_T type,
                      I32 idx,
                      eRRErrorPriority_T priority,
                      eRRError_T code) {
      I32 error = 0;
      if (code >= eERR_HEAD) {
        error += ((type << 24) +
                  (idx << 20) +
                  (priority << 16));
      }
      error += code;
      return error;
    }

   private:
    /**
     * \brief
     */
    cRRError();

    /**
     * \brief
     */
    virtual ~cRRError();
  };
}

#endif
