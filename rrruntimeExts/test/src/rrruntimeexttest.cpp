#include "rrruntimeExtension.h"
#include "rrruntimeAPI.h"
#include "dRRSysDef.h"

static I32 Msg1(const void* pArg, void* pRet) {
  dRR_SLEEP(1000);
  return 9527;
}

static I32 Msg2(const void* pArg, void* pRet) {
  dRR_SLEEP(0);
  return 9526;
}

I32 dRRAPI Initial(const void* pArg, void* pRet) {
  rrruntimeSignUpAMsgFn(0, Msg1);
  rrruntimeSignUpAMsgFn(1, Msg2);
  return 0;
}
