#include"mbox_processor.hpp"




int32_t
Processor::
get_value(const RegisterSpecifier&  spec) const
{
  return spec.index? regdev[spec.index]:0;
}


void
Processor::
put_value(int32_t  v, const RegisterSpecifier&  spec)
{
    if(spec.index)
    {
      regdev[spec.index] = v;
    }
}




int32_t  Processor::get_value(            const Pointer&  ptr) const{return memory->refer(ptr)    ;}
void     Processor::put_value(int32_t  v, const Pointer&  ptr)      {       memory->refer(ptr) = v;}




int32_t  Processor::get_rs1_value(           const Instruction&  inst) const{return get_value(inst.get_rs1());}
int32_t  Processor::get_rs2_value(           const Instruction&  inst) const{return get_value(inst.get_rs2());}
int32_t  Processor::get_rd_value(            const Instruction&  inst) const{return get_value(inst.get_rd());}
void     Processor::put_rd_value(int32_t  v, const Instruction&  inst)      {put_value(v,inst.get_rd());}




void
Processor::
process_fn8(const Instruction&  inst)
{
    switch(inst.get_fn8())
    {
  case(Fn8::add_sym): put_rd_value(get_rs1_value(inst)+get_rs2_value(inst),inst);break;
  case(Fn8::sub_sym): put_rd_value(get_rs1_value(inst)-get_rs2_value(inst),inst);break;
  case(Fn8::mul_sym): put_rd_value(get_rs1_value(inst)*get_rs2_value(inst),inst);break;

  case(Fn8::div_sym):
    {
      auto  v = get_rs2_value(inst);

        if(!v)
        {
          v = 1;
        }


      put_rd_value(get_rs1_value(inst)/v,inst);
    } break;
  case(Fn8::rem_sym):
    {
      auto  v = get_rs2_value(inst);

        if(!v)
        {
          v = 1;
        }


      put_rd_value(get_rs1_value(inst)%v,inst);
    } break;

  case(Fn8::sll_sym): put_rd_value(get_rs1_value(inst)<<get_rs2_value(inst),inst);break;
  case(Fn8::srl_sym): put_rd_value(get_rs1_value(inst)>>get_rs2_value(inst),inst);break;
  case(Fn8::sra_sym): put_rd_value(get_rs1_value(inst)>>get_rs2_value(inst),inst);break;
  case(Fn8::and_sym): put_rd_value(get_rs1_value(inst)&get_rs2_value(inst),inst);break;
  case(Fn8::or_sym ): put_rd_value(get_rs1_value(inst)|get_rs2_value(inst),inst);break;
  case(Fn8::xor_sym): put_rd_value(get_rs1_value(inst)^get_rs2_value(inst),inst);break;
  case(Fn8::eq_sym ): put_rd_value((get_rs1_value(inst) == get_rs2_value(inst))? 1:0,inst);break;
  case(Fn8::neq_sym): put_rd_value((get_rs1_value(inst) != get_rs2_value(inst))? 1:0,inst);break;
  case(Fn8::lt_sym ): put_rd_value((get_rs1_value(inst) <  get_rs2_value(inst))? 1:0,inst);break;
  case(Fn8::lte_sym): put_rd_value((get_rs1_value(inst) <= get_rs2_value(inst))? 1:0,inst);break;
  case(Fn8::gt_sym ): put_rd_value((get_rs1_value(inst) >  get_rs2_value(inst))? 1:0,inst);break;
  case(Fn8::gte_sym): put_rd_value((get_rs1_value(inst) >= get_rs2_value(inst))? 1:0,inst);break;
    }
}


void
Processor::
step()
{
  auto  ptr = &memory->array[pc&0xFFFFFFFC];

  pc += 4;

  Instruction  inst(*reinterpret_cast<const uint32_t*>(ptr));

    switch(inst.get_opcode())
    {
  case(Opcode::fn8_sym):
      process_fn8(inst);
      break;
  case(Opcode::addi_sym): put_rd_value(get_rs1_value(inst)+inst.get_imm14(),inst);break;
  case(Opcode::subi_sym): put_rd_value(get_rs1_value(inst)-inst.get_imm14(),inst);break;
  case(Opcode::muli_sym): put_rd_value(get_rs1_value(inst)*inst.get_imm14(),inst);break;
  case(Opcode::divi_sym): put_rd_value(get_rs1_value(inst)/inst.get_imm14(),inst);break;
  case(Opcode::remi_sym): put_rd_value(get_rs1_value(inst)%inst.get_imm14(),inst);break;
  case(Opcode::slli_sym): put_rd_value(get_rs1_value(inst)<<inst.get_imm14(),inst);break;
  case(Opcode::srli_sym): put_rd_value(get_rs1_value(inst)>>inst.get_imm14(),inst);break;
  case(Opcode::srai_sym): put_rd_value(get_rs1_value(inst)>>inst.get_imm14(),inst);break;
  case(Opcode::andi_sym): put_rd_value(get_rs1_value(inst)&inst.get_imm14(),inst);break;
  case(Opcode::ori_sym ): put_rd_value(get_rs1_value(inst)|inst.get_imm14(),inst);break;
  case(Opcode::xori_sym): put_rd_value(get_rs1_value(inst)^inst.get_imm14(),inst);break;

  case(Opcode::eqi_sym ): put_rd_value((get_rs1_value(inst) == inst.get_imm14())? 1:0,inst);break;
  case(Opcode::neqi_sym): put_rd_value((get_rs1_value(inst) != inst.get_imm14())? 1:0,inst);break;
  case(Opcode::lti_sym ): put_rd_value((get_rs1_value(inst) <  inst.get_imm14())? 1:0,inst);break;
  case(Opcode::ltei_sym): put_rd_value((get_rs1_value(inst) <= inst.get_imm14())? 1:0,inst);break;
  case(Opcode::gti_sym ): put_rd_value((get_rs1_value(inst) >  inst.get_imm14())? 1:0,inst);break;
  case(Opcode::gtei_sym): put_rd_value((get_rs1_value(inst) >= inst.get_imm14())? 1:0,inst);break;

  case(Opcode::jmp_sym):
      pc = inst.get_imm20()*4;

      put_rd_value(pc,inst);
      break;
  case(Opcode::lui_sym):
      put_rd_value(inst.get_imm20()<<12,inst);
      break;
  case(Opcode::ld_sym):
      put_rd_value(memory->refer(get_rs1_value(inst)+(inst.get_imm14()*4)),inst);
      break;
  case(Opcode::st_sym):
      memory->refer(get_rd_value(inst)+(inst.get_imm14()*4)) = get_rs1_value(inst);
      break;
  case(Opcode::brz_sym):
        if(!get_rs1_value(inst))
        {
          pc = inst.get_imm14()*4;

          put_rd_value(pc,inst);
        }

      break;
  case(Opcode::brnz_sym):
        if(get_rs1_value(inst))
        {
          pc = inst.get_imm14()*4;

          put_rd_value(pc,inst);
        }

      break;
    }
}




