#ifndef MBOX_PROCESSOR_HPP_INCLUDED
#define MBOX_PROCESSOR_HPP_INCLUDED


#include"mbox_instruction.hpp"
#include"mbox_memory.hpp"




struct
Processor
{
  int32_t  regdev[32];

  uint32_t  pc;

  Memory*  memory;

  int32_t  get_value(            const RegisterSpecifier&  spec) const;
  void     put_value(int32_t  v, const RegisterSpecifier&  spec)      ;

  int32_t  get_value(            const Pointer&  ptr) const;
  void     put_value(int32_t  v, const Pointer&  ptr)      ;

  int32_t  get_rs1_value(           const Instruction&  inst) const;
  int32_t  get_rs2_value(           const Instruction&  inst) const;
  int32_t  get_rd_value(            const Instruction&  inst) const;
  void     put_rd_value(int32_t  v, const Instruction&  inst)      ;

  void  process_fn8(const Instruction&  inst);
  void  step();

};




#endif




