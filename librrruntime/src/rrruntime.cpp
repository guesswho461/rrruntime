/**
 *  \file       rrruntime.cpp
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/10/11
 *  \copyright  MIT license, see LICENSE file
 */

#include "rrruntime.h"

#include <atomic>

#include "rrruntimeAPI.h"
#include "cRRRuntime.h"
#include "cRRMsgFramework.h"
#include "cRRThread.h"
#include "cRRTask.h"

static rrruntime::cRRRuntime* pRuntime = NULL;
static rrruntime::cRRMsgFramework* pMsgFramework = NULL;
static std::atomic_int IsInitiated(eNO);
static cRRThreadList_T threadList;

static I32 MsgFrameworkRoutine(const void* pArg, void* pRet) {
  pMsgFramework->DoTheMsg(eHI_MSG);
  pMsgFramework->DoTheMsg(eSD_MSG);
  return eNORMAL;
}

static void rrruntimeRoutine(const void* pArg) {
  dLOCK;
#ifdef _USING_LINUX_
  I64 toff = 0;
  I64 ecSyncIntegral = 0;
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  while (IsInitiated == eYES) {
    //    rrruntime::cRRUtils::Add2Timespec(&t, toff + dCYCLE_TIME_NS);
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
    pRuntime->Routine();
    //    toff = rrruntime::cRRUtils::DCM(ec_DCtime,
    //                               dCYCLE_TIME_NS,
    //                               dCYCLE_SYNC_OFFSET,
    //                               dDCM_P_GAIN,
    //                               dDCM_I_GAIN,
    //                               &ecSyncIntegral);
  }
#else
  while (IsInitiated == eYES) {
    pRuntime->Routine();
    dRR_SLEEP(1);
  }
#endif
}

I32 rrruntimeInitial(std::string extLibsDirAbsPath,
                     I32 mainCPUIdx,
                     I32 mainTaskPriority,
                     I32 auxCPUIdx) {
  I32 rt = eNORMAL;
  pMsgFramework = new rrruntime::cRRMsgFramework(auxCPUIdx);
  pRuntime = new rrruntime::cRRRuntime(extLibsDirAbsPath);
  pRuntime->Add2Todos(rrruntime::cRRRuntime::cRRToDo_C_T(MsgFrameworkRoutine,
                      NULL, NULL, NULL, 0, NULL));
  rrruntime::cRRRuntime::cRRToDos_C_T extLibInitTodosC;
  pRuntime->LoadExtensions(dRR_INITIAL_FN_NAME,
                           extLibsDirAbsPath,
                           extLibInitTodosC);
  pRuntime->DoTheTodos(extLibInitTodosC);
  IsInitiated = eYES;
  cRRTaskList_T taskList;
  taskList.emplace_back(&rrruntimeRoutine, (const void*)NULL, SCHED_FIFO, mainTaskPriority, mainCPUIdx);
  I32 cnt = 0;
  for (cRRTaskList_T::const_iterator it = taskList.cbegin();
       it != taskList.cend(); ++it) {
    threadList.emplace_back(it->taskFn, it->pArg);
    rt = rrruntime::cRRThread::setScheduling(threadList.at(cnt++),
                                            it->schedPolicy,
                                            it->schedPriority,
                                            it->cpuIdx);
    if (rt != eNORMAL) break;
  }
  return rt;
}

void dRRAPI rrruntimeDispose() {
  IsInitiated = eNO;
  for (cRRThreadList_T::iterator it = threadList.begin();
       it != threadList.end(); ++it) {
    if (it->joinable()) it->join();
  }
  if (pRuntime) delete pRuntime;
  if (pMsgFramework) delete pMsgFramework;
}

I32 dRRAPI rrruntimeSignUpAMsgFn(U32 msgID, pMsgFn_C_T msgFn) {
  return pMsgFramework->Set(msgID, msgFn);
}

I32 dRRAPI rrruntimeCallAMsgFn(eRRMsgPriority_T priority, rrruntime::cRRMsg msg) {
  return pMsgFramework->Push(priority, msg);
}
