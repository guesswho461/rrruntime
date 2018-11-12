/**
 *  \file       eRRMsgPriorityDef.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/03/10
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _ERRMSGPRIORITY_H_
#define _ERRMSGPRIORITY_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief  the priority of msg
 */
typedef enum eRRMsgPriority {
  eSD_MSG,
  eHI_MSG,
  eMAX_MSG_PRIORITY
} eRRMsgPriority_T;

#ifdef __cplusplus
}
#endif

#endif
