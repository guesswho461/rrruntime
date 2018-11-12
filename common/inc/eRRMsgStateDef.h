/**
 *  \file       eRRMsgStateDef.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/03/01
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _ERRMSGSTATEDEF_H_
#define _ERRMSGSTATEDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief represent the state of msg fn doing,
 */
typedef enum eRRMsgState {
  eMSG_DONE,     /* the msg has been done */
  eMSG_RECIEVED, /* got the msg form queue */
  eMSG_DOING     /* msg is doing */
} eRRMsgState_T;

#ifdef __cplusplus
}
#endif

#endif
