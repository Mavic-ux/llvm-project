#ifndef LLVM_LIB_TARGET_ZEN_ZEN_H
#define LLVM_LIB_TARGET_ZEN_ZEN_H

#include "MCTargetDesc/ZENMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class ZENTargetMachine;
class FunctionPass;
class ZENSubtarget;
class AsmPrinter;
class InstructionSelector;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class PassRegistry;

bool lowerZENMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                    AsmPrinter &AP);
bool LowerZENMachineOperandToMCOperand(const MachineOperand &MO,
                                         MCOperand &MCOp, const AsmPrinter &AP);

FunctionPass *createZENISelDag(ZENTargetMachine &TM,
                                CodeGenOpt::Level OptLevel);


namespace ZEN {
enum {
  GP = ZEN::R0,
  RA = ZEN::R1,
  SP = ZEN::R2,
  FP = ZEN::R3,
  BP = ZEN::R4,
};
} // namespace ZEN

} // namespace llvm

#endif