#include "ZEN.h"
#include "llvm/IR/Module.h"
#include "TargetInfo/ZENTargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheZENTarget() {
  static Target TheZENTarget;
  return TheZENTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZENTargetInfo() {
  RegisterTarget<Triple::zen, false> X(getTheZENTarget(), "ZEN", "ZEN (32-bit ZEN)", "ZEN");
}