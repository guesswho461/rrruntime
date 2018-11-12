/**
 *  \file       uRRMem.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/01/01
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _URRMEM_H_
#define _URRMEM_H_

#include "tRRType.h"
#include "dRRSysDef.h"

/**
 *  \brief  memory map template
 *  \param  L_T     typed raw memory block
 *  \param  T_T     typed raw memory block
 *  \param  N_LT    the size of raw memory block in typed addressing
 *  \param  N_32A   the size of raw memory block in 32bits addressing
 *  \param  N_16A   the size of raw memory block in 16bits addressing
 *  \param  N_08A   the size of raw memory block in 8bits addressing
 */
template<typename L_T, typename T_T, U32 N_LT, U32 N_32A, U32 N_16A, U32 N_08A>
union uRRMem {
  /**
   *  \brief  the raw memory block in 32bits addressing
   */
  U32 U32A[N_32A];

  /**
   *  \brief  the raw memory block in 16bits addressing
   */
  U16 U16A[N_16A];
  I16 I16A[N_16A];

  /**
   *  \brief  the raw memory block in 8bits addressing
   */
  U08 U08A[N_08A];
  I08 I08A[N_08A];

  /**
   *  \brief  the raw memory block in typed addressing
   */
  L_T L[N_LT];

  /**
   *  \brief  the masked memory block
   */
  T_T T;
};

/**
 *  \brief  4bytes union data, in I32, F32, U32, U16 and U08 addressing
 */
typedef uRRMem<I32, F32, 1, 1, 2, 4> uRRUnion_T;

#endif
