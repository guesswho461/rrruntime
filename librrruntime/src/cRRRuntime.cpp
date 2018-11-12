/**
 *  \file       cRRRuntime.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/10/09
 *  \copyright  MIT license, see LICENSE file
 */

#include "cRRRuntime.h"

#include <array>

#include "cRRLibLoader.h"
#include "cppfs//FileHandle.h"
#include "cppfs//fs.h"
#include "fmt//format.h"
#include "dRRAPIDef.h"

rrruntime::cRRRuntime::cRRRuntime(std::string extLibsDirAbsPath) {
  this->heartBeat = 0;
  this->LoadExtensions(dRR_ROUTINE_FN_NAME,
                       extLibsDirAbsPath,
                       this->routineTodosC);
}

rrruntime::cRRRuntime::~cRRRuntime() {
  ;
}

void rrruntime::cRRRuntime::LoadExtensions(std::string fnName,
                                      std::string extLibsDirAbsPath,
                                      cRRToDos_C_T& todos) {
  typedef cRRLibLoader<pMsgFn_C_T> cRRRuntimeLibLoader;
  cRRRuntimeLibLoader::cRRLibFnPtrList_T fnList;
  cRRRuntimeLibLoader libLoader;
  std::vector<std::string> libs = cRRUtils::GetFiles(extLibsDirAbsPath);
  libLoader.Load(libs, fnName, fnList);
  for (cRRRuntimeLibLoader::cRRLibFnPtrList_T::const_iterator it = fnList.cbegin();
       it != fnList.cend(); ++it) {
    todos.emplace_back(cRRToDo_C_T(*it, NULL, NULL, NULL, 0, NULL));
  }
}

void rrruntime::cRRRuntime::DoTheTodos(cRRToDos_C_T todos) {
  for (cRRToDos_C_T::const_iterator it = todos.cbegin();
       it != todos.cend(); ++it) {
    if (it->phMutex) {
      this->DoMemRW(it->phMutex,
                    it->mutexTimeout,
                    it->pToDoFn,
                    it->pMutexTimeoutCnt,
                    it->pArg,
                    it->pRet);
    } else {
      this->Invoke(it->pToDoFn, it->pArg, it->pRet);
    }
  }
}

void rrruntime::cRRRuntime::Routine() {
  this->baseTime = cRRUtils::GetBaseTime();
  this->heartBeat = !this->heartBeat;
  this->DoTheTodos(this->routineTodosC);
  this->travelTime = cRRUtils::GetTravelTime(this->baseTime);
}

void rrruntime::cRRRuntime::Add2Todos(cRRToDo_C_T todo) {
  this->routineTodosC.push_back(todo);
}
