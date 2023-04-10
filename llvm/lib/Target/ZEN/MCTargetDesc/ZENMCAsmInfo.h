#ifndef LLVM_LIB_TARGET_ZEN_MCTARGETDESC_ZENMCASMINFO_H
#define LLVM_LIB_TARGET_ZEN_MCTARGETDESC_ZENMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class ZENMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit ZENMCAsmInfo(const Triple &TT);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_ZEN_MCTARGETDESC_ZENMCASMINFO_H
