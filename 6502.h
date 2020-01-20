#include "kernel.h"

struct cpuReg{
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint8_t P; //Flags, Order: NVssDISC
    uint8_t S;
    uint16_t PC;
    uint32_t Clock;

};

void init(uint32_t romAddr);
void emulate(uint8_t opcode);