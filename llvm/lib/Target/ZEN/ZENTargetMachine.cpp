//===----------------------------------------------------------------------===//
//
// Implements the info about ZEN target spec.
//
//===----------------------------------------------------------------------===//

#include "ZENTargetMachine.h"
#include "ZEN.h"
//#include "ZENTargetTransformInfo.h"
#include "TargetInfo/ZENTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetOptions.h"

#define DEBUG_TYPE "ZEN"

using namespace llvm;

static Reloc::Model getRelocModel(Optional<Reloc::Model> RM) {
  return RM.getValueOr(Reloc::Static);
}

/// ZENTargetMachine ctor - Create an ILP32 Architecture model
ZENTargetMachine::ZENTargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     Optional<Reloc::Model> RM,
                                     Optional<CodeModel::Model> CM,
                                     CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T,
                        "e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i32:32:32-"
                        "f32:32:32-i64:32-f64:32-a:0:32-n32",
                        TT, CPU, FS, Options, getRelocModel(RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

ZENTargetMachine::~ZENTargetMachine() = default;

namespace {

/// ZEN Code Generator Pass Configuration Options.
class ZENPassConfig : public TargetPassConfig {
public:
  ZENPassConfig(ZENTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  ZENTargetMachine &getZENTargetMachine() const {
    return getTM<ZENTargetMachine>();
  }

  bool addInstSelector() override;
  // void addPreEmitPass() override;
  // void addPreRegAlloc() override;
};

} // end anonymous namespace

TargetPassConfig *ZENTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new ZENPassConfig(*this, PM);
}

bool ZENPassConfig::addInstSelector() {
  addPass(createZENISelDag(getZENTargetMachine(), getOptLevel()));
  return false;
}

// void ZENPassConfig::addPreEmitPass() { llvm_unreachable(""); }

// void ZENPassConfig::addPreRegAlloc() { llvm_unreachable(""); }

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZENTarget() {
  RegisterTargetMachine<ZENTargetMachine> X(getTheZENTarget());
}

#if 0
TargetTransformInfo
ZENTargetMachine::getTargetTransformInfo(const Function &F) {
  return TargetTransformInfo(ZENTTIImpl(this, F));
}
#endif