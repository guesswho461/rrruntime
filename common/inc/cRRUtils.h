/**
 *  \file       cRRUtils.h
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2016/01/06
 *  \copyright  MIT license, see LICENSE file
 */

#ifndef _CRRUTILS_H_
#define _CRRUTILS_H_

#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <chrono>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

#include "tRRType.h"
#include "dRRSysDef.h"
#include "fmt//format.h"
#include "cppfs//FileHandle.h"
#include "cppfs//fs.h"

namespace rrruntime {
  class cRRUtils {
   public:
    /**
     *  \brief
     */
    typedef std::chrono::steady_clock sRRClock;

    /**
     *  \brief to get the base time tick
     *  \return time tick
     */
    static sRRClock::time_point GetBaseTime() {
      return sRRClock::now();
    }

    static I64 GetBaseTime2() {
      return std::chrono::time_point_cast<std::chrono::nanoseconds>
             (sRRClock::now()).time_since_epoch().count();
    }

    /**
     *  \brief to get the travel time from base time tick
     *  \code
     *  sRRClock::time_point _Start = GetBaseTime();
     *  //do something
     *  F32 _Time = GetTravelTime(_Start);
     *  \endcode
     *  \param baseTime base time tick
     *  \return time, uint: [ns]
     */
    static I64 GetTravelTime(sRRClock::time_point baseTime) {
      sRRClock::time_point endTime = sRRClock::now();
      return std::chrono::duration_cast<std::chrono::nanoseconds>
             (endTime - baseTime).count();
    }

    static I64 GetTravelTime2(I64 baseTime) {
      return rrruntime::cRRUtils::GetBaseTime2() - baseTime;
    }

    /**
     *  \brief
     */
    static I32 NewMem(I32 size, void** ppMem) {
      if (size <= 0)
        return dNIL;
      *ppMem = malloc(size);
      if (*ppMem == NULL)
        return dNIL;
      dPZERO(*ppMem, size);
      return size;
    }

    /**
     *  \brief
     */
    static void FreeMem(void* pMem) {
      if (pMem != NULL)
        free(pMem);
    }

    /**
     *  \brief
     */
    static I32 Fls(I32 data) {
      I32 pos = 0;
      if (data > 1) {
        I32 tempData = data - 1;
        for (I32 idx = (tempData >> 1); idx != 0; pos++) {
          idx >>= 1;
        }
      } else {
        pos = -1;
      }
      return pos + 1;
    }

    /**
     *  \brief
     */
    static I32 RoundUpToPowOfTwo(I32 data) {
      return 1 << Fls(data);
    }

    /**
     *  \brief
     *  \return the readed size, dNIL means failed
     */
    static I32 ReadBinFile(std::string fileFullPath, char** ppMem, I32 len) {
      std::ifstream ifs;
      ifs.open(fileFullPath, std::ios::in | std::ios::binary);
      if (ifs.is_open() == false)
        return dNIL;
      ifs.seekg(0, std::ios::end);
      I32 maxLen = ifs.tellg();
      if (len == dNIL) {
        *ppMem = new char[maxLen];
      } else {
        if (len > maxLen)
          return dNIL;
        else
          maxLen = len;
      }
      ifs.seekg(0, std::ios::beg);
      ifs.read(*ppMem, maxLen);
      ifs.close();
      return maxLen;
    }

    /**
     *  \brief
     */
    static void WriteBinFile(std::string fileFullPath, const char* ppMem, I32 len) {
      std::ofstream ofs;
      ofs.open(fileFullPath, std::ios::out | std::ios::binary);
      if (ofs.is_open()) {
        ofs.seekp(0, std::ios::beg);
        ofs.write(ppMem, len);
        ofs.close();
      }
    }

    static F32 Round2N(F32 num, I32 dec) {
      F64 m = (num < 0.0) ? -1.0 : 1.0;   // check if input is negative
      F64 pwr = pow(10, dec);
      return F32((floor(num * m * pwr + 0.5) / pwr) * m);
    }

    static U16* FileMapping(const char* fileName, U32 length) {
      U16* pReg = NULL;
      I32 fd = open(fileName,  O_RDWR | O_SYNC);
      if (fd == -1) {
        umask(0000);
        fd = creat(fileName, S_IRUSR | S_IWUSR |
                   S_IRGRP | S_IWGRP |
                   S_IROTH | S_IWOTH);
        close(fd);
        if (fd >= 0) {
          fd = open(fileName,  O_RDWR | O_SYNC);
          ftruncate(fd, length);
        } else {
          return NULL;
        }
      }
      pReg = (U16*)mmap(0, length,
                        PROT_READ | PROT_WRITE, MAP_SHARED,
                        fd, 0);
      close(fd);
      return pReg;
    }

    /* Normalize the nanoseconds if they are > 1 second */
    static inline void NormT(struct timespec* ts) {
      while (ts->tv_nsec >= dNSEC_PER_SEC) {
        ts->tv_nsec -= dNSEC_PER_SEC;
        ts->tv_sec++;
      }
    }

    /* add ns to timespec */
    static inline void Add2Timespec(struct timespec* ts, I64 addTime) {
      I64 nsec = addTime % dNSEC_PER_SEC;
      I64 sec = (addTime - nsec) / dNSEC_PER_SEC;
      ts->tv_sec += sec;
      ts->tv_nsec += nsec;
      if (ts->tv_nsec > dNSEC_PER_SEC) {
        nsec = ts->tv_nsec % dNSEC_PER_SEC;
        ts->tv_sec += (ts->tv_nsec - nsec) / dNSEC_PER_SEC;
        ts->tv_nsec = nsec;
      }
    }

    static inline I64 DCM(I64 reftime, I64 cycleTime, I64 syncOffset,
                          I32 Kp, I32 Ki, I64* pSyncIntegral) {
      I64 delta = (reftime - syncOffset) % cycleTime;
      if (delta > (cycleTime / 2)) {
        delta = delta - cycleTime;
      }
      if (delta > 0) {
        (*pSyncIntegral)++;
      }
      if (delta < 0) {
        (*pSyncIntegral)--;
      }
      return -(delta / Kp) - ((*pSyncIntegral) / Ki);
    }

    static std::vector<std::string> Split(const std::string& str, char seperator) {
      std::vector<std::string> ret;
      if (str.length() > 0) {
        std::string::size_type prev = 0, pos = 0;
        while ((pos = str.find(seperator, pos)) != std::string::npos) {
          std::string substring(str.substr(prev, pos - prev));
          ret.push_back(substring);
          prev = ++pos;
        }
        ret.push_back(str.substr(prev, pos - prev));   // Last word
      }
      return ret;
    }

    static char* GetCWD(char* absPath, const char* relPath, size_t maxLen) {
      char* ret = NULL;
      assert(absPath && relPath && maxLen > 1);
      if (*relPath == '/') {
        size_t len = strlen(relPath);
        if (len <= maxLen - 1) {
          strcpy(absPath, relPath);
          ret = absPath;
        }
      } else {
        ret = getcwd(absPath, maxLen);
        if (ret) {
          size_t absLen = strlen(absPath);
          size_t relLen = strlen(relPath);
          if (absPath[absLen - 1] != '/' && absLen < maxLen && relLen) {
            absPath[absLen++] = '/';
          }
          if (absLen + relLen < maxLen) {
            strcpy(absPath + absLen, relPath);
            ret = absPath;
          }
        }
      }
      return ret;
    }

    static std::string GetIPv4(struct sockaddr_in addr){
      char clientIPv4Str[INET_ADDRSTRLEN] = {};
      inet_ntop(AF_INET, &addr.sin_addr, clientIPv4Str, INET_ADDRSTRLEN);
      return fmt::format("{}:{}", clientIPv4Str, addr.sin_port);
    }

    static std::string GetIPv4(U32 addr){
      char clientIPv4Str[INET_ADDRSTRLEN] = {};
      inet_ntop(AF_INET, &addr, clientIPv4Str, INET_ADDRSTRLEN);
      return fmt::format("{}", clientIPv4Str);
    }

    static U32 SetIPv4(std::string addr){
      U32 addrNum = 0;
      inet_pton(AF_INET, addr.c_str(), &addrNum);
      return addrNum;
    }

    static std::vector<std::string> GetFiles(std::string path) {
      std::vector<std::string> libs = cppfs::fs::open(path).listFiles();
      for (std::vector<std::string>::iterator it = libs.begin();
           it != libs.end(); ++it) {
        it->assign((fmt::format("{}/{}", path, *it)));
      }
      return libs;
    }

   private:
    /**
     *  \brief constructor
     */
    cRRUtils() { ; }

    /**
     *  \brief to dispose the instance
     */
    virtual ~cRRUtils() { ; }
  };
}
#endif
