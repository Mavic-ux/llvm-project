add_llvm_component_group(ZEN)

set(LLVM_TARGET_DEFINITIONS ZEN.td)

# Generate ZENGenRegisterInfo.inc and ZENGenInstrInfo.inc which included by
#  your hand code C++ files.
# ZENGenRegisterInfo.inc came from ZENRegisterInfo.td, ZENGenInstrInfo.inc
#  came from ZENInstrInfo.td.
tablegen(LLVM ZENGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM ZENGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM ZENGenCallingConv.inc -gen-callingconv)
tablegen(LLVM ZENGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM ZENGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM ZENGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM ZENGenDAGISel.inc -gen-dag-isel)

#tablegen(LLVM ZENGenDisassemblerTables.inc -gen-disassembler)

# ZENCommonTableGen must be defined
add_public_tablegen_target(ZENCommonTableGen)

# ZENCodeGen should match with LLVMBuild.txt ZENCodeGen
add_llvm_target(ZENCodeGen
  ZENAsmPrinter.cpp
  ZENFrameLowering.cpp
  ZENInstrInfo.cpp
  ZENISelDagToDag.cpp
  ZENISelLowering.cpp
  ZENMachineFunctionInfo.cpp
  ZENMCInstLower.cpp
  ZENRegisterInfo.cpp
  ZENSubtarget.cpp
  ZENTargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  ZENDesc
  ZENInfo
  SelectionDAG
  Support
  Target
  GlobalISel

  ADD_TO_COMPONENT
  ZEN
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)