#include"mbox_instruction.hpp"




Instruction::
Instruction(uint32_t  code_):
code(code_)
{
}




Opcode  Instruction::get_opcode() const{return static_cast<Opcode>(code&0b111111);}
Fn8        Instruction::get_fn8() const{return static_cast<Fn8   >(code>>     24);}

RegisterSpecifier  Instruction::get_rd()  const{return RegisterSpecifier((code&0b000000000000111111000000)>> 6);}
RegisterSpecifier  Instruction::get_rs1() const{return RegisterSpecifier((code&0b000000111111000000000000)>>12);}
RegisterSpecifier  Instruction::get_rs2() const{return RegisterSpecifier((code&0b111111000000000000000000)>>18);}


int32_t
Instruction::
get_imm14() const
{
  bool  sign_bit = (code&0x80000000);

  uint32_t  imm = (code>>18);

  return static_cast<int32_t>(sign_bit? imm&0b11111111111111111100000000000000:imm);
}


uint32_t  Instruction::get_imm20() const{return(code>>12);}




