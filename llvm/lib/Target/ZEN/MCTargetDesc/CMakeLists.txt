add_llvm_component_library(LLVMZENDesc
  ZENInstPrinter.cpp
  ZENMCAsmInfo.cpp
  ZENMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  ZENInfo
  Support

  ADD_TO_COMPONENT
  ZEN
  )