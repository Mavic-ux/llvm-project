add_llvm_component_library(LLVMZenInfo
  ZenTargetInfo.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  Zen
  )