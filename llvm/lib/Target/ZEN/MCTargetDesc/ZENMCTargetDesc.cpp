#include "ZENMCTargetDesc.h"
#include "TargetInfo/ZENTargetInfo.h"
#include "ZENInfo.h"
#include "ZENInstPrinter.h"
#include "ZENMCAsmInfo.h"
#include "ZENTargetStreamer.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "ZENGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "ZENGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "ZENGenRegisterInfo.inc"

static MCInstrInfo *createZENMCInstrInfo() {
  auto *X = new MCInstrInfo();
  InitZENMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createZENMCRegisterInfo(const Triple &TT) {
  auto *X = new MCRegisterInfo();
  InitZENMCRegisterInfo(X, ZEN::R1);
  return X;
}

static MCSubtargetInfo *createZENMCSubtargetInfo(const Triple &TT,
                                                  StringRef CPU, StringRef FS) {
  return createZENMCSubtargetInfoImpl(TT, CPU, /*TuneCPU=*/CPU, FS);
}

static MCAsmInfo *createZENMCAsmInfo(const MCRegisterInfo &MRI,
                                      const Triple &TT,
                                      const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new ZENMCAsmInfo(TT);
  MCRegister SP = MRI.getDwarfRegNum(ZEN::R2, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createZENMCInstPrinter(const Triple &T,
                                              unsigned SyntaxVariant,
                                              const MCAsmInfo &MAI,
                                              const MCInstrInfo &MII,
                                              const MCRegisterInfo &MRI) {
  return new ZENInstPrinter(MAI, MII, MRI);
}

ZENTargetStreamer::ZENTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
ZENTargetStreamer::~ZENTargetStreamer() = default;

static MCTargetStreamer *createTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
  return new ZENTargetStreamer(S);
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZENTargetMC() {
  // Register the MC asm info.
  Target &TheZENTarget = getTheZENTarget();
  RegisterMCAsmInfoFn X(TheZENTarget, createZENMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheZENTarget, createZENMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheZENTarget, createZENMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheZENTarget,
                                          createZENMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheZENTarget, createZENMCInstPrinter);

  TargetRegistry::RegisterAsmTargetStreamer(TheZENTarget,
                                            createTargetAsmStreamer);
}