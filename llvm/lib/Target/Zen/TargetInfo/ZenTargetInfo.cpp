//===-- ZenTargetInfo.cpp - Zen Target Implementation -------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Zen.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target llvm::TheZenTarget;

extern "C" void LLVMInitializeZenTargetInfo() {
  RegisterTarget<Triple::Zen,
                 /*HasJIT=*/false>
      X(TheZenTarget, "Zen", "Zen RISC-Vasilii arch", "Zen");
}