/**
 *  \file       main.cpp
 *  \brief
 *  \author     guesswho461
 *  \version
 *  \date       2018/10/09
 *  \copyright  MIT license, see LICENSE file
 */

#include <iostream>
#include <thread>

#include "rrruntime.h"
#include "gflags//gflags.h"
#include "glog//logging.h"
#include "fmt//format.h"
#include "eRRErrorDef.h"

DEFINE_string(extDir, "./exts/", "the extension directory path");
DEFINE_int32(mainCPUIdx, 3, "which cpu will execute the runtime task");
DEFINE_int32(mainTaskPriority, 48, "the priority of the runtime task");
DEFINE_int32(auxCPUIdx, 0, "which cpu will execute the async msg task");

int main(int argc, char* argv[]) {
  I32 rt = eNORMAL;
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  rt = rrruntimeInitial(FLAGS_extDir,
                        FLAGS_mainCPUIdx,
                        FLAGS_mainTaskPriority,
                        FLAGS_auxCPUIdx);
  if (rt == eNORMAL) {
    LOG(INFO) << "rrruntime initiated";
    for (;;);
  } else {
    LOG(ERROR) << fmt::format("rrruntime initiate failed 0x{:08X}", rt);
  }
  rrruntimeDispose();
  LOG(INFO) << "rrruntime disposed";
  return 0;
}
