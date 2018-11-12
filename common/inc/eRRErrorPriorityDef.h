/**
 *  \file       eRRErrorPriorityDef.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2017/12/31
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _ERRERRORPRIORITYDEF_H_
#define _ERRERRORPRIORITYDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief priority, size is 4bits, the larger the more serious
 */
typedef enum eRRErrorPriority {
  ePRIORITY_00,
  ePRIORITY_01,
  ePRIORITY_02,
  ePRIORITY_03,
  ePRIORITY_04,
  ePRIORITY_05,
  ePRIORITY_06,
  ePRIORITY_07,
  ePRIORITY_08,
  ePRIORITY_09,
  ePRIORITY_10,
  ePRIORITY_11,
  ePRIORITY_12,
  ePRIORITY_13,
  ePRIORITY_14,
  ePRIORITY_15
} eRRErrorPriority_T;

#ifdef __cplusplus
}
#endif

#endif
