//===-- ZenMCTargetDesc.h - Zen Target Descriptions -----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Zen specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Zen_MCTARGETDESC_ZenMCTARGETDESC_H
#define LLVM_LIB_TARGET_Zen_MCTARGETDESC_ZenMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

#include <memory>

namespace llvm {
class Target;
class Triple;

extern Target TheZenTarget;

} // End llvm namespace

// Defines symbolic names for Zen registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "ZenGenRegisterInfo.inc"

// Defines symbolic names for the Zen instructions.
#define GET_INSTRINFO_ENUM
#include "ZenGenInstrInfo.inc"

#endif