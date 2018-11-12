/**
 *  \file       eRRSysPartTypeDef.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/10/17
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _ERRSYSPARTTYPEDEF_H_
#define _ERRSYSPARTTYPEDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief size is 8bits
 */
typedef enum eRRSysPartType {
  eRR_NULL = 0,
  eRR_RRUNTIME,
  SYSPARTTYPE_NUM
} eRRSysPartType_T;

#ifdef __cplusplus
}
#endif

#endif
