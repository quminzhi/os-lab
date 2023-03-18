#include <stdint.h>
#include <assert.h>
#include <stdio.h>

union reg_tt {
  uint32_t _32;
  struct {
    union {
      uint8_t _8[2];
      uint16_t _16;
    };
    uint16_t _pad;
  };
};

struct {
  union {
    union reg_tt gpr[8];
    struct { uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi; };
  };
  uint32_t cpu;
} CPU_State;

#define cpu CPU_State

int main() {
  assert(&cpu.gpr[0]._32 == &cpu.eax);
  assert(&cpu.gpr[1]._32 == &cpu.ecx);

  printf("sizeof reg_tt = %lu\n", sizeof(union reg_tt));
  printf("sizeof CPU_State = %lu\n", sizeof(CPU_State));
  return 0;
}
