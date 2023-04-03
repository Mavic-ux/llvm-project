//===-- ZenRegisterInfo.td - Zen Register defs -----------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the Zen register file
//===----------------------------------------------------------------------===//

// ~~~~~~~~~~~~~~~~~~~~~~
// ~~~From RISC-V spec~~~
// ~~~~~~~~~~~~~~~~~~~~~~

// For tablegen(... -gen-emitter)  in CMakeLists.txt
let Namespace = "Zen" in {

class ZenReg<bits<5> Enc, string n, list<string> alt = []> : Register<n> {
  let HWEncoding{4-0} = Enc;
  let AltNames = alt;
}

} // Namespace = "Zen"

def ABIRegAltName : RegAltNameIndex;

// Integer registers
// CostPerUse is set higher for registers that may not be compressible as they
// are not part of GPRC, the most restrictive register class used by the
// compressed instruction set. This will influence the greedy register
// allocator to reduce the use of registers that can't be encoded in 16 bit
// instructions.
let RegAltNameIndices = [ABIRegAltName] in {
  let isConstant = true in
  def X0  : ZenReg<0, "x0", ["zero"]>, DwarfRegNum<[0]>;
  let CostPerUse = [0, 1] in {
  def X1  : ZenReg<1, "x1", ["ra"]>, DwarfRegNum<[1]>;
  def X2  : ZenReg<2, "x2", ["sp"]>, DwarfRegNum<[2]>;
  def X3  : ZenReg<3, "x3", ["gp"]>, DwarfRegNum<[3]>;
  def X4  : ZenReg<4, "x4", ["tp"]>, DwarfRegNum<[4]>;
  def X5  : ZenReg<5, "x5", ["t0"]>, DwarfRegNum<[5]>;
  def X6  : ZenReg<6, "x6", ["t1"]>, DwarfRegNum<[6]>;
  def X7  : ZenReg<7, "x7", ["t2"]>, DwarfRegNum<[7]>;
  }
  def X8  : ZenReg<8, "x8", ["s0", "fp"]>, DwarfRegNum<[8]>;
  def X9  : ZenReg<9, "x9", ["s1"]>, DwarfRegNum<[9]>;
  def X10 : ZenReg<10,"x10", ["a0"]>, DwarfRegNum<[10]>;
  def X11 : ZenReg<11,"x11", ["a1"]>, DwarfRegNum<[11]>;
  def X12 : ZenReg<12,"x12", ["a2"]>, DwarfRegNum<[12]>;
  def X13 : ZenReg<13,"x13", ["a3"]>, DwarfRegNum<[13]>;
  def X14 : ZenReg<14,"x14", ["a4"]>, DwarfRegNum<[14]>;
  def X15 : ZenReg<15,"x15", ["a5"]>, DwarfRegNum<[15]>;
  let CostPerUse = [0, 1] in {
  def X16 : ZenReg<16,"x16", ["a6"]>, DwarfRegNum<[16]>;
  def X17 : ZenReg<17,"x17", ["a7"]>, DwarfRegNum<[17]>;
  def X18 : ZenReg<18,"x18", ["s2"]>, DwarfRegNum<[18]>;
  def X19 : ZenReg<19,"x19", ["s3"]>, DwarfRegNum<[19]>;
  def X20 : ZenReg<20,"x20", ["s4"]>, DwarfRegNum<[20]>;
  def X21 : ZenReg<21,"x21", ["s5"]>, DwarfRegNum<[21]>;
  def X22 : ZenReg<22,"x22", ["s6"]>, DwarfRegNum<[22]>;
  def X23 : ZenReg<23,"x23", ["s7"]>, DwarfRegNum<[23]>;
  def X24 : ZenReg<24,"x24", ["s8"]>, DwarfRegNum<[24]>;
  def X25 : ZenReg<25,"x25", ["s9"]>, DwarfRegNum<[25]>;
  def X26 : ZenReg<26,"x26", ["s10"]>, DwarfRegNum<[26]>;
  def X27 : ZenReg<27,"x27", ["s11"]>, DwarfRegNum<[27]>;
  def X28 : ZenReg<28,"x28", ["t3"]>, DwarfRegNum<[28]>;
  def X29 : ZenReg<29,"x29", ["t4"]>, DwarfRegNum<[29]>;
  def X30 : ZenReg<30,"x30", ["t5"]>, DwarfRegNum<[30]>;
  def X31 : ZenReg<31,"x31", ["t6"]>, DwarfRegNum<[31]>;
  }
}

defvar Zen32 = DefaultMode;
def XLenVT : ValueTypeByHwMode<[Zen32],
                               [i32]>;
def XLenRI : RegInfoByHwMode<
      [Zen32],
      [RegInfo<32,32,32>]>;

// The order of registers represents the preferred allocation sequence.
// Registers are listed in the order caller-save, callee-save, specials.
def GPR : RegisterClass<"Zen", [XLenVT], 32, (add
    (sequence "X%u", 10, 17),
    (sequence "X%u", 5, 7),
    (sequence "X%u", 28, 31),
    (sequence "X%u", 8, 9),
    (sequence "X%u", 18, 27),
    (sequence "X%u", 0, 4)
  )> {
  let RegInfos = XLenRI;
}