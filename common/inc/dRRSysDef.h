/**
 *  \file       dRRSysDef.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/01/06
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _DRRSYSDEF_H_
#define _DRRSYSDEF_H_

#include <string.h>
#include <math.h>

#include <mutex>
#include <thread>

#include "tRRType.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief define the meaning of 1 and 0
 */
typedef enum eRROKNG {
  eOK = 0,
  eNG = 1
} eRROKNG_T;

/**
 * \brief define the meaning of 1 and 0
 */
typedef enum eRRYesNo {
  eNO = 0,
  eYES = 1
} eRRYesNo_T;

/**
 * \brief define the meaning of 1 and 0
 */
typedef enum eRROnOff {
  eOFF = 0,
  eON = 1
} eRROnOff_T;

/**
 * \brief define the meaning of 1 and 0
 */
typedef enum eRRTrueFalse {
  eFALSE = 0,
  eTRUE = 1
} eRRTrueFalse_T;

/**
 * \brief define the meaning of 1 and 0
 */
typedef enum eRRLeftRight {
  eRIGHT = 0,
  eLEFT = 1
} eRRLeftRight_T;

/**
 * \brief define the meaning of 1 and 0
 */
typedef enum eRRUpDown {
  eUP = 0,
  eDOWN = 1
} eRRUpDown_T;

/**
 * \brief define the meaning of 1 and 0
 */
typedef enum eRRPosNeg {
  eNOR = 0,
  ePOS = 1,
  eNEG = 2
} eRRPosNeg_T;

/* 8bits addressing */
#define dSIZE_64MB_08A (67108864)  /* 64MB     = 67108864  bytes U08 */
#define dSIZE_32MB_08A (33554432)  /* 32MB     = 33554432  bytes U08 */
#define dSIZE_16MB_08A (16777216)  /* 16MB     = 16777216  bytes U08 */
#define dSIZE_08MB_08A (8388608)   /* 08MB     = 8388608   bytes U08 */
#define dSIZE_04MB_08A (4194304)   /* 04MB     = 4194304   bytes U08 */
#define dSIZE_02MB_08A (2097152)   /* 02MB     = 2097152   bytes U08 */
#define dSIZE_01MB_08A (1048576)   /* 01MB     = 1048576   bytes U08 */
#define dSIZE_d5MB_08A (524288)    /* 512kB    = 524288    bytes U08 */
#define dSIZE_128k_08A (131072)    /* 128kB    = 131072    bytes U08 */
#define dSIZE_64kB_08A (65536)     /* 65kB     = 65536     bytes U08 */
#define dSIZE_32kB_08A (32768)     /* 32kB     = 32768     bytes U08 */
#define dSIZE_16kB_08A (16384)     /* 16kB     = 16384     bytes U08 */
#define dSIZE_08kB_08A (8192)      /* 08kB     = 8192      bytes U08 */
#define dSIZE_04kB_08A (4096)      /* 04kB     = 4096      bytes U08 */
#define dSIZE_02kB_08A (2048)      /* 02kB     = 2048      bytes U08 */
#define dSIZE_01kB_08A (1024)      /* 01kB     = 1024      bytes U08 */
#define dSIZE_512B_08A (512)       /* 512B     = 512       bytes U08 */
#define dSIZE_256B_08A (256)       /* 256B     = 256       bytes U08 */
#define dSIZE_128B_08A (128)       /* 128B     = 128       bytes U08 */
#define dSIZE_064B_08A (64)        /* 64B      = 64        bytes U08 */
#define dSIZE_032B_08A (32)        /* 32B      = 32        bytes U08 */
#define dSIZE_016B_08A (16)        /* 16B      = 16        bytes U08 */
#define dSIZE_008B_08A (8)         /* 8B       = 8         bytes U08 */
#define dSIZE_004B_08A (4)         /* 4B       = 4         bytes U08 */

/* 16bits addressing */
#define dSIZE_64MB_16A (33554432)  /* 64MB     = 67108864  bytes / 2 = 33554432    U16  */
#define dSIZE_32MB_16A (16777216)  /* 32MB     = 33554432  bytes / 2 = 16777216    U16  */
#define dSIZE_16MB_16A (8388608)   /* 16MB     = 16777216  bytes / 2 = 8388608     U16  */
#define dSIZE_08MB_16A (4194304)   /* 08MB     = 8388608   bytes / 2 = 4194304     U16  */
#define dSIZE_04MB_16A (2097152)   /* 04MB     = 4194304   bytes / 2 = 2097152     U16  */
#define dSIZE_02MB_16A (1048576)   /* 02MB     = 2097152   bytes / 2 = 1048576     U16  */
#define dSIZE_01MB_16A (524288)    /* 01MB     = 1048576   bytes / 2 = 524288      U16  */
#define dSIZE_d5MB_16A (262144)    /* 512kB    = 524288    bytes / 2 = 262144      U16  */
#define dSIZE_128k_16A (65536)     /* 128kB    = 131072    bytes / 2 = 65536       U16  */
#define dSIZE_64kB_16A (32768)     /* 65kB     = 65536     bytes / 2 = 32768       U16  */
#define dSIZE_32kB_16A (16384)     /* 32kB     = 32768     bytes / 2 = 16384       U16  */
#define dSIZE_16kB_16A (8192)      /* 16kB     = 16384     bytes / 2 = 8192        U16  */
#define dSIZE_08kB_16A (4096)      /* 08kB     = 8192      bytes / 2 = 4096        U16  */
#define dSIZE_04kB_16A (2048)      /* 04kB     = 4096      bytes / 2 = 2048        U16  */
#define dSIZE_02kB_16A (1024)      /* 02kB     = 2048      bytes / 2 = 1024        U16  */
#define dSIZE_01kB_16A (512)       /* 01kB     = 1024      bytes / 2 = 512         U16  */
#define dSIZE_512B_16A (256)       /* 512B     = 512       bytes / 2 = 256         U16  */
#define dSIZE_256B_16A (128)       /* 256B     = 256       bytes / 2 = 128         U16  */
#define dSIZE_128B_16A (64)        /* 128B     = 128       bytes / 2 = 64          U16  */
#define dSIZE_064B_16A (32)        /* 64B      = 64        bytes / 2 = 32          U16  */
#define dSIZE_032B_16A (16)        /* 32B      = 32        bytes / 2 = 16          U16  */
#define dSIZE_016B_16A (8)         /* 16B      = 16        bytes / 2 = 8           U16  */
#define dSIZE_008B_16A (4)         /* 8B       = 8         bytes / 2 = 4           U16  */
#define dSIZE_004B_16A (2)         /* 4B       = 4         bytes / 2 = 2           U16  */

/* 32bits addressing */
#define dSIZE_64MB_32A (16777216)  /* 64MB     = 67108864  bytes / 4 = 16777216    U32 */
#define dSIZE_32MB_32A (8388608)   /* 32MB     = 33554432  bytes / 4 = 8388608     U32 */
#define dSIZE_16MB_32A (4194304)   /* 16MB     = 16777216  bytes / 4 = 4194304     U32 */
#define dSIZE_08MB_32A (2097152)   /* 08MB     = 8388608   bytes / 4 = 2097152     U32 */
#define dSIZE_04MB_32A (1048576)   /* 04MB     = 4194304   bytes / 4 = 1048576     U32 */
#define dSIZE_02MB_32A (524288)    /* 02MB     = 2097152   bytes / 4 = 524288      U32 */
#define dSIZE_01MB_32A (262144)    /* 01MB     = 1048576   bytes / 4 = 262144      U32 */
#define dSIZE_d5MB_32A (131072)    /* 512kB    = 524288    bytes / 4 = 131072      U32 */
#define dSIZE_128k_32A (32768)     /* 128kB    = 131072    bytes / 4 = 32768       U32 */
#define dSIZE_64kB_32A (16384)     /* 65kB     = 65536     bytes / 4 = 16384       U32 */
#define dSIZE_32kB_32A (8192)      /* 32kB     = 32768     bytes / 4 = 8192        U32 */
#define dSIZE_16kB_32A (4096)      /* 16kB     = 16384     bytes / 4 = 4096        U32 */
#define dSIZE_08kB_32A (2048)      /* 08kB     = 8192      bytes / 4 = 2048        U32 */
#define dSIZE_04kB_32A (1024)      /* 04kB     = 4096      bytes / 4 = 1024        U32 */
#define dSIZE_02kB_32A (512)       /* 02kB     = 2048      bytes / 4 = 512         U32 */
#define dSIZE_01kB_32A (256)       /* 01kB     = 1024      bytes / 4 = 256         U32 */
#define dSIZE_512B_32A (128)       /* 512B     = 512       bytes / 4 = 128         U32 */
#define dSIZE_256B_32A (64)        /* 256B     = 256       bytes / 4 = 64          U32 */
#define dSIZE_128B_32A (32)        /* 128B     = 128       bytes / 4 = 32          U32 */
#define dSIZE_064B_32A (16)        /* 64B      = 64        bytes / 4 = 16          U32 */
#define dSIZE_032B_32A (8)         /* 32B      = 32        bytes / 4 = 8           U32 */
#define dSIZE_016B_32A (4)         /* 16B      = 16        bytes / 4 = 4           U32 */
#define dSIZE_008B_32A (2)         /* 8B       = 8         bytes / 4 = 2           U32 */
#define dSIZE_004B_32A (1)         /* 4B       = 4         bytes / 4 = 1           U32 */

/* for uRRMem template */
#define dSIZE_64MB dSIZE_64MB_32A, dSIZE_64MB_16A, dSIZE_64MB_08A
#define dSIZE_32MB dSIZE_32MB_32A, dSIZE_32MB_16A, dSIZE_32MB_08A
#define dSIZE_16MB dSIZE_16MB_32A, dSIZE_16MB_16A, dSIZE_16MB_08A
#define dSIZE_08MB dSIZE_08MB_32A, dSIZE_08MB_16A, dSIZE_08MB_08A
#define dSIZE_04MB dSIZE_04MB_32A, dSIZE_04MB_16A, dSIZE_04MB_08A
#define dSIZE_02MB dSIZE_02MB_32A, dSIZE_02MB_16A, dSIZE_02MB_08A
#define dSIZE_01MB dSIZE_01MB_32A, dSIZE_01MB_16A, dSIZE_01MB_08A
#define dSIZE_d5MB dSIZE_d5MB_32A, dSIZE_d5MB_16A, dSIZE_d5MB_08A
#define dSIZE_128k dSIZE_128k_32A, dSIZE_128k_16A, dSIZE_128k_08A
#define dSIZE_64kB dSIZE_64kB_32A, dSIZE_64kB_16A, dSIZE_64kB_08A
#define dSIZE_32kB dSIZE_32kB_32A, dSIZE_32kB_16A, dSIZE_32kB_08A
#define dSIZE_16kB dSIZE_16kB_32A, dSIZE_16kB_16A, dSIZE_16kB_08A
#define dSIZE_08kB dSIZE_08kB_32A, dSIZE_08kB_16A, dSIZE_08kB_08A
#define dSIZE_04kB dSIZE_04kB_32A, dSIZE_04kB_16A, dSIZE_04kB_08A
#define dSIZE_02kB dSIZE_02kB_32A, dSIZE_02kB_16A, dSIZE_02kB_08A
#define dSIZE_01kB dSIZE_01kB_32A, dSIZE_01kB_16A, dSIZE_01kB_08A
#define dSIZE_512B dSIZE_512B_32A, dSIZE_512B_16A, dSIZE_512B_08A
#define dSIZE_256B dSIZE_256B_32A, dSIZE_256B_16A, dSIZE_256B_08A
#define dSIZE_128B dSIZE_128B_32A, dSIZE_128B_16A, dSIZE_128B_08A
#define dSIZE_064B dSIZE_064B_32A, dSIZE_064B_16A, dSIZE_064B_08A
#define dSIZE_032B dSIZE_032B_32A, dSIZE_032B_16A, dSIZE_032B_08A
#define dSIZE_016B dSIZE_016B_32A, dSIZE_016B_16A, dSIZE_016B_08A
#define dSIZE_008B dSIZE_008B_32A, dSIZE_008B_16A, dSIZE_008B_08A
#define dSIZE_004B dSIZE_004B_32A, dSIZE_004B_16A, dSIZE_004B_08A

#define dDEG_TO_RAD     (0.017453292519943295769236907685f)     /* pi/180 */
#define dRAD_TO_DEG     (57.295779513082320876798154814105f)    /* 180/pi */
#define dRADPMS_TO_RPM  (9549.2965855137201461330258023509f)    /* rad/ms -> rpm : 1000*60/(2*pi) */
#define dMY_PI          (3.141592653589793238462643383280f)     /* pi */
#define dDOUBLE_PI      (6.283185307179586476925286766559f)     /* 2*pi */
#define dHALF_PI        (1.570796326794896619231321691640f)     /* pi/2 */
#define dINV_DOUBLE_PI  (0.159154943091895335768883763373f)     /* 1/2/pi */
#define dGRAVITY        (9.80665f)                              /* kg * m * s^-2 */

#define dI08_MAX        (127)
#define dI08_MIN        (-128)
#define dU08_MAX        (255)
#define dU08_MIN        (0)

#define dI16_MAX        (32767)
#define dI16_MIN        (-32768)
#define dU16_MAX        (65535)
#define dU16_MIN        (0)
#define d16B_MAX        (65536)

#define dI32_MAX        (2147483647)
#define dI32_MIN        (-2147483648)
#define dU32_MAX        (4294967295)
#define dU32_MIN        (0)
#define d32B_MAX        (4294967296)

#define dF32_MAX        (3.402823466e+38f)
#define dF32_MIN        (-dF32_MAX)

#define dNIL                (-1)
#define dMAX_CHAR_LEN       (128)
#define dSMALLEST           (5e-3f)
#define dENABLE_STR         ("enable")
#define dDISABLE_STR        ("disable")
#define dPERCENT            (100.0f)
#define dINV_PERCENT        (0.01f)
#define dSTD_MUTEX_TIMEOUT  (1)
#define dNSEC_PER_SEC       (1000000000)
#define dUSEC_PER_SEC       (1000000)
#define dNSEC_PER_MSEC      (1000000)
#define dNSEC_PER_USEC      (1000)
#define dMSEC_PER_SEC       (1000)

#define dNILZE(_dst)                      (memset((void *)&_dst,    dNIL,                   sizeof(_dst)))
#define dPNILZE(_pDst_, _size_)           (memset((void *)_pDst_,   dNIL,                   _size_))
#define dZERO(_dst)                       (memset((void *)&_dst,    0,                      sizeof(_dst)))
#define dPZERO(_pDst_, _size_)            (memset((void *)_pDst_,   0,                      _size_))
#define d___COPY(_dst, _src_)             (memcpy((void *)&_dst,    (const void *)&_src_,   sizeof(_src_)))
#define d__SCOPY(_dst, _src_, _size_)     (memcpy((void *)&_dst,    (const void *)&_src_,   _size_))
#define d_PSCOPY(_dst, _pSrc_, _size_)    (memcpy((void *)&_dst,    (const void *)_pSrc_,   _size_))
#define d_P_COPY(_dst, _pSrc_)            (memcpy((void *)&_dst,    (const void *)_pSrc_,   sizeof(_dst)))
#define dP_SCOPY(_pDst_, _src_, _size_)   (memcpy((void *)_pDst_,   (const void *)&_src_,   _size_))
#define dP__COPY(_pDst_, _src_)           (memcpy((void *)_pDst_,   (const void *)&_src_,   sizeof(_src_)))
#define dPP_COPY(_pDst_, _pSrc_)          (memcpy((void *)_pDst_,   (const void *)_pSrc_,   sizeof(_pSrc_)))
#define dPPSCOPY(_pDst_, _pSrc_, _size_)  (memcpy((void *)_pDst_,   (const void *)_pSrc_,   _size_))

#define dSQUARE(_value_) (pow(_value_, 2))
#define dMARCO_HEAD(_todo_) do { _todo_ } while(0)

/* unitity the unit to ms */
#define dRR_SLEEP(_time_) std::this_thread::sleep_for(std::chrono::milliseconds(_time_))

/* bit index start from 0 */
#define dRR_GET_2_POWER(_bitIdx_) (1 << _bitIdx_)
#define dRR_SET_BIT_0_WITH_VALUE(_data_, _value_) (_data_ &= ~_value_)
#define dRR_SET_BIT_0(_data_, _bitIdx_) (_data_ &= ~dRR_GET_2_POWER(_bitIdx_))
#define dRR_SET_BIT_1(_data_, _bitIdx_) (_data_ |= dRR_GET_2_POWER(_bitIdx_))
#define dRR_GET_BIT(_data_, _bitIdx_) (_data_ & dRR_GET_2_POWER(_bitIdx_)) /* the return is greater than zero */
#define dRR_GET_U16_LOW_BYTE(_data_) (_data_ & 0x00FF)
#define dRR_GET_U16_HIGH_BYTE(_data_) (_data_ & 0xFF00)

/* in case of the reentrance */
#define dLOCK std::mutex _key_; std::lock_guard<std::mutex> _guard_(_key_)
#define dLOCK_KEY(_key_) std::lock_guard<std::mutex> _guard_(_key_)

#ifdef __cplusplus
}
#endif

#endif
