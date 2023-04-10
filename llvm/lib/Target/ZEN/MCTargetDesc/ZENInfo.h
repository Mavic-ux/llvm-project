#ifndef LLVM_LIB_TARGET_ZEN_MCTARGETDESC_ZENINFO_H
#define LLVM_LIB_TARGET_ZEN_MCTARGETDESC_ZENINFO_H

#include "llvm/MC/MCInstrDesc.h"

namespace llvm {

namespace ZENCC {
enum CondCode {
  EQ,
  NE,
  LE,
  GT,
  LEU,
  GTU,
  INVALID,
};

CondCode getOppositeBranchCondition(CondCode);

enum BRCondCode {
  BREQ = 0x0,
};
} // end namespace ZENCC

namespace ZENOp {
enum OperandType : unsigned {
  OPERAND_SIMM16 = MCOI::OPERAND_FIRST_TARGET,
  OPERAND_UIMM16,
};
} // namespace ZENOp

} // end namespace llvm

#endif