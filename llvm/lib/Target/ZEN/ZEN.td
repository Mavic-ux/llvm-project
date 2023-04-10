//===----------------------------------------------------------------------===//
// This is the top level entry point for the ZEN target.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// ZEN Subtarget features
//===----------------------------------------------------------------------===//

//def FeatureDummy
//    : SubtargetFeature<"dummy", "Dummy", "true",
//                       "Dummy feature">;

//===----------------------------------------------------------------------===//
// Target-dependent interfaces
//===----------------------------------------------------------------------===//

include "ZENRegisterInfo.td"

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "ZENCallingConv.td"

include "ZENInstrInfo.td"
def ZENInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// ZEN processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;
//def : Proc<"dummy-st", []>;

// Will generate ZENGenAsmWrite.inc included by ZENInstPrinter.cpp, contents
//  as follows,
// void ZENInstPrinter::printInstruction(const MCInst *MI, raw_ostream &O) {...}
// const char *ZENInstPrinter::getRegisterName(unsigned RegNo) {...}
def ZEN : Target {
  let InstructionSet = ZENInstrInfo;
}