#ifndef LLVM_LIB_TARGET_ZEN_MCTARGETDESC_ZENMCTARGETDESC_H
#define LLVM_LIB_TARGET_ZEN_MCTARGETDESC_ZENMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

#include <memory>

namespace llvm {
class Target;
class Triple;

extern Target TheZENTarget;

} // End llvm namespace

// Defines symbolic names for ZEN registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "ZENGenRegisterInfo.inc"

// Defines symbolic names for the ZEN instructions.
#define GET_INSTRINFO_ENUM
#include "ZENGenInstrInfo.inc"

#endif