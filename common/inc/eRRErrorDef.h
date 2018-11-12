/**
 *  \file       eRRErrorDef.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/01/06
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _ERRERRORDEF_H_
#define _ERRERRORDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief erroe code, size is 16bits
 */
typedef enum eRRError {
  eNORMAL  = 0x0000,

  /**
   *  \brief  STATE, no need to assemble with part, idx and priority, internal use only
   */

  /**
   *  \brief  ERROR, need to assemble with part, idx and priority to become a full error code to present to user
   */
  eERR_HEAD = 0x1000,
  /* 0x1001 */ eERR_ILLEGAL_ARGUMENT,             /* the arguments of function are illegal */
  /* 0x1002 */ eERR_MUTEX_REQUEST_FAILED,         /* mutex request timeout */
  /* 0x1003 */ eERR_IS_EMPTY,                     /* there are no data in the queue or map */
  /* 0x1004 */ eERR_LOAD_FROM_LIB_FAILED,         /* load funtion from lib failed, maybe no such lib or function */
  /* 0x1005 */ eERR_SET_KEYPAIR_FAILED,           /* insert to map failed */
  /* 0x1006 */ eERR_UNSUPPORTED_FN,               /* unsupported function */
  /* 0x1007 */ eERR_SET_THREAD_PRIORITY_FAILED,   /* set thread's cpu/priority failed */
  eERR_TAIL
} eRRError_T;

#ifdef __cplusplus
}
#endif

#endif
