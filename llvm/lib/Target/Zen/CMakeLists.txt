add_llvm_component_group(Zen)

set(LLVM_TARGET_DEFINITIONS Zen.td)

tablegen(LLVM ZenGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM ZenGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM ZenGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM ZenGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM ZenGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM ZenGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM ZenGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(ZenCommonTableGen)

add_llvm_target(ZenCodeGen
  ZenTargetMachine.cpp

  LINK_COMPONENTS
  AsmPrinter
  CodeGen
  Core
  MC
  Support
  Target
  ZenDesc
  ZenInfo

  ADD_TO_COMPONENT
  Zen
  )

add_subdirectory(AsmParser)
add_subdirectory(Disassembler)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)

