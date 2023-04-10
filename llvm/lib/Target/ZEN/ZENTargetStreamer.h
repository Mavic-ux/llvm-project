#ifndef LLVM_LIB_TARGET_ZEN_ZENTARGETSTREAMER_H
#define LLVM_LIB_TARGET_ZEN_ZENTARGETSTREAMER_H

#include "llvm/MC/MCStreamer.h"

namespace llvm {

class ZENTargetStreamer : public MCTargetStreamer {
public:
  ZENTargetStreamer(MCStreamer &S);
  ~ZENTargetStreamer() override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_ZEN_ZENTARGETSTREAMER_H