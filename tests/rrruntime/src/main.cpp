#include <iostream>
#include <atomic>

#include "gtest/gtest.h"
#include "rrruntime.h"
#include "rrruntimeAPI.h"
#include "cRRCalleeBase.h"
#include "cRRMsg.h"

using namespace std;
using namespace rrruntime;

class cRRCallee : public cRRCalleeBase {
 public:
  cRRCallee() {
    this->done = false;
  }

  virtual ~cRRCallee() { ; }

  I32 CallbackFnCPP(I32 errorCode) {
    cout << "i am cpp-style callback, i got " << errorCode << endl;
    this->done = true;
    return 0;
  }

  cRRMsg GetMsg(I32 fnCode, bool async) {
    cRRMsg msg;
    msg.fnIdx = fnCode;
    if (async) {
      //msg.pCCallback = &CallbackFnC;
      msg.pCalleeInst = this;
      msg.pCallbackCPP = (cRRCallee::pMsgCallback_CPP_T)&cRRCallee::CallbackFnCPP;
    }
    return msg;
  }

  bool isDone() {
    return this->done.load();
  }

 private:
  std::atomic_bool done;
};

class rruntimeUnitTests: public ::testing::Test {
 protected:
  rruntimeUnitTests() {
    rrruntimeInitial("./exts", 1, 48, 0);
    dRR_SLEEP(1000);
  }

  virtual ~rruntimeUnitTests() {
    rrruntimeDispose();
  }
};

TEST_F(rruntimeUnitTests, callTestExtMsg1) {
  cRRCallee calle;
  rrruntimeCallAMsgFn(eSD_MSG, calle.GetMsg(0, true));
  while (!calle.isDone());
  EXPECT_TRUE(calle.isDone());
}

TEST_F(rruntimeUnitTests, callTestExtMsg2) {
  cRRCallee calle;
  rrruntimeCallAMsgFn(eSD_MSG, calle.GetMsg(1, true));
  while (!calle.isDone());
  EXPECT_TRUE(calle.isDone());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
