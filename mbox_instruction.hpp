#ifndef MBOX_INSTRUCTION_HPP_INCLUDED
#define MBOX_INSTRUCTION_HPP_INCLUDED


#include<cstdint>
#include<cstddef>


enum class
Fn8
{
  add_sym,
  sub_sym,
  mul_sym,
  div_sym,
  rem_sym,
  sll_sym,
  srl_sym,
  sra_sym,
  and_sym,
  or_sym,
  xor_sym,
  eq_sym,
  neq_sym,
  lt_sym,
  lte_sym,
  gt_sym,
  gte_sym,

  END,

};


enum class
Opcode
{
  fn8_sym,

  addi_sym,
  subi_sym,
  muli_sym,
  divi_sym,
  remi_sym,
  slli_sym,
  srli_sym,
  srai_sym,
  andi_sym,
  ori_sym,
  xori_sym,
  eqi_sym,
  neqi_sym,
  lti_sym,
  ltei_sym,
  gti_sym,
  gtei_sym,
  brz_sym,
  brnz_sym,
  jmp_sym,
  lui_sym,
  ld_sym,
  st_sym,

  END,

};


struct
RegisterSpecifier
{
  int  index;

constexpr RegisterSpecifier(int  i=0): index(i&0b111111){}

};


struct
Instruction
{
//
//+-----+-----+-----+----+--------+
//|  8  |  6  |  6  |  6 |    6   |
//+-----+-----+-----+----+--------+
//| fn8 | rs2 | rs1 | rd | opcode |
//+-----+-----+-----+----+--------+
//
//
//+-----------+-----+----+--------+
//|     14    |  6  |  6 |    6   |
//+-----------+-----+----+--------+
//|    imm    | rs1 | rd | opcode |
//+-----------+-----+----+--------+
//
//
//+-----------+----+--------+
//|     20    |  6 |    6   |
//+-----------+----+--------+
//|    imm    | rd | opcode |
//+-----------+----+--------+
//
//

  uint32_t  code;

public:
  Instruction(uint32_t  code_=0);

  Opcode  get_opcode() const;
  Fn8        get_fn8() const;

  RegisterSpecifier  get_rd() const;
  RegisterSpecifier  get_rs1() const;
  RegisterSpecifier  get_rs2() const;

   int32_t  get_imm14() const;
  uint32_t  get_imm20() const;
  
};




#endif




