
//===-- Zen.h - Top-level interface for Zen representation ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM Zen back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Zen_Zen_H
#define LLVM_LIB_TARGET_Zen_Zen_H

#include "MCTargetDesc/ZenMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
  class ZenTargetMachine;
  class FunctionPass;

} // end namespace llvm;

#endif