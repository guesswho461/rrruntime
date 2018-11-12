/**
 *  \file       cRRRuntime.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/10/09
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRRUNTIME_H_
#define _CRRRUNTIME_H_

#include <vector>
#include <string>

#include "cRRToDo.h"
#include "cRRUtils.h"
#include "cRRBase.h"

namespace rrruntime {
  /**
   *  \brief
   */
  class cRRRuntime : public cRRBase {
   public:
    /**
     *  \brief
     */
    typedef cRRToDo<pMsgFn_C_T> cRRToDo_C_T;

    /**
     *  \brief
     */
    typedef std::vector<cRRToDo_C_T> cRRToDos_C_T;

    /**
     *  \brief
     */
    cRRRuntime(std::string extLibsDirAbsPath);

    /**
     *  \brief
     */
    ~cRRRuntime();

    /**
     *  \brief
     */
    void Routine();

    /**
     *  \brief
     */
    void Add2Todos(cRRToDo_C_T todo);

    /**
     *  \brief
     */
    void LoadExtensions(std::string fnName,
                        std::string extLibsDirAbsPath,
                        cRRToDos_C_T& todos);

    /**
     *  \brief
     */
    void DoTheTodos(cRRToDos_C_T todos);

   private:
    /**
     *  \brief
     */
    cRRToDos_C_T routineTodosC;

    /**
     *  \brief
     */
    cRRUtils::sRRClock::time_point baseTime;

    /**
     *  \brief
     */
    I64 travelTime;

    /**
     *  \brief
     */
    U32 heartBeat;
  };
}

#endif
