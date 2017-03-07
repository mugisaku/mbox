#include"mbox_memory.hpp"




Memory::
Memory()
{
  fill();
}




void
Memory::
fill(uint8_t  v)
{
    for(auto&  dst: array)
    {
      dst = v;
    }
}


      int32_t&  Memory::refer(const Pointer&  ptr)      {return *reinterpret_cast<      int32_t*>(&array[ptr.value&mask]);}
const int32_t&  Memory::refer(const Pointer&  ptr) const{return *reinterpret_cast<const int32_t*>(&array[ptr.value&mask]);}




