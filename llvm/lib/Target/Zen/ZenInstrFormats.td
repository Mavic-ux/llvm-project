//===-- ZenInstrFormats.td - Zen Instruction Formats -----*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//


class InstFormat<bits<5> val> {
  bits<5> Value = val;
}

def InstFormatR      : InstFormat<0>;
def InstFormatI      : InstFormat<1>;
def InstFormatS      : InstFormat<2>;
def InstFormatB      : InstFormat<3>;
def InstFormatU      : InstFormat<4>;
def InstFormatJ      : InstFormat<5>;

class ZenOpcode<string name, bits<7> val> {
  string Name = name;
  bits<7> Value = val;
}

class ZenInst<dag outs, dag ins, string opcodestr, string argstr,
             list<dag> pattern, InstFormat format>
    : Instruction {

  let Namespace = "Zen";
  let DecoderNamespace = "Zen";
  let Size = 4;

  field bits<32> Inst;

  bits<7> Opcode = 0;
  let Inst{6-0} = Opcode;

  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = opcodestr # "\t" # argstr;
  let Pattern = pattern;
}

class ZenInstR<bits<7> funct7, bits<3> funct3, ZenOpcode opcode, dag outs,
              dag ins, string opcodestr, string argstr>
    : ZenInst<outs, ins, opcodestr, argstr, [], InstFormatR> {
  bits<5> rs2;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-25} = funct7;
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}


class ZenInstI<bits<3> funct3, ZenOpcode opcode, dag outs, dag ins,
              string opcodestr, string argstr>
    : ZenInst<outs, ins, opcodestr, argstr, [], InstFormatI> {
  bits<12> imm12;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-20} = imm12;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}


class ZenInstS<bits<3> funct3, ZenOpcode opcode, dag outs, dag ins,
              string opcodestr, string argstr>
    : ZenInst<outs, ins, opcodestr, argstr, [], InstFormatS> {
  bits<12> imm12;
  bits<5> rs2;
  bits<5> rs1;

  let Inst{31-25} = imm12{11-5};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = imm12{4-0};
  let Opcode = opcode.Value;
}

class ZenInstB<bits<3> funct3, ZenOpcode opcode, dag outs, dag ins,
              string opcodestr, string argstr>
    : ZenInst<outs, ins, opcodestr, argstr, [], InstFormatB> {
  bits<12> imm12;
  bits<5> rs2;
  bits<5> rs1;

  let Inst{31} = imm12{11};
  let Inst{30-25} = imm12{9-4};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-8} = imm12{3-0};
  let Inst{7} = imm12{10};
  let Opcode = opcode.Value;
}

class ZenInstU<ZenOpcode opcode, dag outs, dag ins, string opcodestr,
              string argstr>
    : ZenInst<outs, ins, opcodestr, argstr, [], InstFormatU> {
  bits<20> imm20;
  bits<5> rd;

  let Inst{31-12} = imm20;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}

class ZenInstJ<ZenOpcode opcode, dag outs, dag ins, string opcodestr,
              string argstr>
    : ZenInst<outs, ins, opcodestr, argstr, [], InstFormatJ> {
  bits<20> imm20;
  bits<5> rd;

  let Inst{31} = imm20{19};
  let Inst{30-21} = imm20{9-0};
  let Inst{20} = imm20{10};
  let Inst{19-12} = imm20{18-11};
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}

def OPC_LOAD      : ZenOpcode<"LOAD",      0b0000011>;
def OPC_LOAD_FP   : ZenOpcode<"LOAD_FP",   0b0000111>;
def OPC_CUSTOM_0  : ZenOpcode<"CUSTOM_0",  0b0001011>;
def OPC_MISC_MEM  : ZenOpcode<"MISC_MEM",  0b0001111>;
def OPC_OP_IMM    : ZenOpcode<"OP_IMM",    0b0010011>;
def OPC_AUIPC     : ZenOpcode<"AUIPC",     0b0010111>;
def OPC_OP_IMM_32 : ZenOpcode<"OP_IMM_32", 0b0011011>;
def OPC_STORE     : ZenOpcode<"STORE",     0b0100011>;
def OPC_STORE_FP  : ZenOpcode<"STORE_FP",  0b0100111>;
def OPC_CUSTOM_1  : ZenOpcode<"CUSTOM_1",  0b0101011>;
def OPC_AMO       : ZenOpcode<"AMO",       0b0101111>;
def OPC_OP        : ZenOpcode<"OP",        0b0110011>;
def OPC_LUI       : ZenOpcode<"LUI",       0b0110111>;
def OPC_OP_32     : ZenOpcode<"OP_32",     0b0111011>;
def OPC_MADD      : ZenOpcode<"MADD",      0b1000011>;
def OPC_MSUB      : ZenOpcode<"MSUB",      0b1000111>;
def OPC_NMSUB     : ZenOpcode<"NMSUB",     0b1001011>;
def OPC_NMADD     : ZenOpcode<"NMADD",     0b1001111>;
def OPC_OP_FP     : ZenOpcode<"OP_FP",     0b1010011>;
def OPC_OP_V      : ZenOpcode<"OP_V",      0b1010111>;
def OPC_CUSTOM_2  : ZenOpcode<"CUSTOM_2",  0b1011011>;
def OPC_BRANCH    : ZenOpcode<"BRANCH",    0b1100011>;
def OPC_JALR      : ZenOpcode<"JALR",      0b1100111>;
def OPC_JAL       : ZenOpcode<"JAL",       0b1101111>;
def OPC_SYSTEM    : ZenOpcode<"SYSTEM",    0b1110011>;
def OPC_CUSTOM_3  : ZenOpcode<"CUSTOM_3",  0b1111011>;