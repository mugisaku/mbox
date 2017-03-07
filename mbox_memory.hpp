#ifndef MBOX_MEMORY_HPP_INCLUDED
#define MBOX_MEMORY_HPP_INCLUDED


#include"mbox_instruction.hpp"




struct
Pointer
{
  int32_t  value;

constexpr Pointer(int32_t  v=0): value(v){}

};


struct
Memory
{
  static constexpr size_t  size = 0x10000  ;
  static constexpr size_t  mask = 0x10000-3;

  uint8_t  array[size];

public:
  Memory();

  void  fill(uint8_t  v=0);

        int32_t&  refer(const Pointer&  ptr)      ;
  const int32_t&  refer(const Pointer&  ptr) const;

};




#endif




