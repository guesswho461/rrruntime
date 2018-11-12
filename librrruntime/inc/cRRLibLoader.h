/**
 *  \file       cRRLibLoader.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/01/28
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRLIBLOADER_H_
#define _CRRLIBLOADER_H_

#include <string>
#include <vector>

#if defined(_USING_WIN32_)
#include <windows.h>
#elif defined(_USING_LINUX_)
#include <dlfcn.h>
#endif
#include <stdio.h>

#include "dRRAPIDef.h"
#include "tRRType.h"
#include "cRRError.h"
#include "fmt//format.h"

namespace rrruntime {
  template <typename T>
  class cRRLibLoader {
   public:
    /**
     *  \brief
     */
    class cRRLibFn {
     public:
      cRRLibFn(std::string name, T* pFnPtr)
        : name(name), pFnPtr(pFnPtr) { ; }
      virtual ~cRRLibFn() { ; }
      std::string name;
      T* pFnPtr;
    };

    /**
     *  \brief
     */
    typedef std::vector<cRRLibFn> cRRLibFnList_T;

    /**
     *  \brief
     */
    typedef std::vector<T> cRRLibFnPtrList_T;

    /**
     *  \brief
     */
    cRRLibLoader() { ; }

    /**
     *  \brief
     */
    virtual ~cRRLibLoader() { ; }

    /**
     *  \brief load various lib with same function name
     */
    I32 Load(std::vector<std::string> libs,
             std::string fnName,
             cRRLibFnPtrList_T& pFnPtrList);

    /**
     *  \brief load lib
     */
    I32 Load(std::string libFileName, cRRLibFnList_T fnList);

    /**
     *  \brief load lib name with numbers, i.e. lib4400.so, lib6600.so
     */
    I32 Load(U32 type, cRRLibFnList_T* pFnList);

   private:
    /**
     *  \brief
     */
    T Load(const HMODULE hLib, std::string name);
  };
}

template <typename T>
T rrruntime::cRRLibLoader<T>::
Load(const HMODULE hLib, std::string name) {
  if (hLib == NULL) {
    return NULL;
  }
#if defined(_USING_WIN32_)
  return (T)GetProcAddress(hLib, name.c_str());
#elif defined(_USING_LINUX_)
  return (T)dlsym(hLib, name.c_str());
#endif
}

template <typename T>
I32 rrruntime::cRRLibLoader<T>::
Load(std::vector<std::string> libs,
     std::string fnName,
     cRRLibFnPtrList_T& fnPtrList) {
  for (std::vector<std::string>::const_iterator it = libs.cbegin();
       it != libs.cend(); ++it) {
#if defined(_USING_WIN32_)
    HMODULE hLib = LoadLibrary(libFileName.c_str());
#elif defined(_USING_LINUX_)
    HMODULE hLib = dlopen(it->c_str(), RTLD_LAZY);
#endif
    if (hLib != NULL) {
      T pFnPtr = Load(hLib, fnName);
      if (pFnPtr != NULL) {
        fnPtrList.push_back(pFnPtr);
      }
    }
  }
  return eNORMAL;
}

template <typename T>
I32 rrruntime::cRRLibLoader<T>::
Load(std::string libFileName, cRRLibFnList_T fnList) {
#if defined(_USING_WIN32_)
  HMODULE hLib = LoadLibrary(libFileName.c_str());
#elif defined(_USING_LINUX_)
  HMODULE hLib = dlopen(libFileName.c_str(), RTLD_LAZY);
#endif
  if (hLib == NULL) {
    return cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_15, eERR_LOAD_FROM_LIB_FAILED);
  }
  for (typename cRRLibFnList_T::const_iterator it = fnList.cbegin();
       it != fnList.cend(); ++it) {
    *it->pFnPtr = Load(hLib, it->name);
    if (*it->pFnPtr == NULL) {
      return cRRError::Return(eRR_RRUNTIME, 0, ePRIORITY_15, eERR_LOAD_FROM_LIB_FAILED);
    }
  }
  return eNORMAL;
}

template <typename T>
I32 rrruntime::cRRLibLoader<T>::
Load(U32 type, cRRLibFnList_T* pFnList) {
  return Load(fmt::format("./lib{}.so", type), pFnList);
}

#endif
