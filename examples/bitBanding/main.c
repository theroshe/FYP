
#include <stdio.h>

#define BITBAND_SRAM_REF 0x20000000
#define BITBAND_SRAM_BASE 0x22000000
#define BITBAND_SRAM(a,b) ((BITBAND_SRAM_BASE + (a-BITBAND_SRAM_REF)*32 \    + (b*4))) // Convert SRAM address

#define BITBAND_PERI_REF 0x40000000
#define BITBAND_PERI_BASE 0x42000000
#define BITBAND_PERI(a,b) ((BITBAND_PERI_BASE + (a-BITBAND_PERI_REF)*32 \    + (b*4))) // Convert PERI address

#define MAILBOX 0x20004000
#define TIMER 0x40004000

// Mailbox bit 0
#define MBX_B0 *((volatile unsigned int *)(BITBAND_SRAM(MAILBOX,0)))

// Mailbox bit 7
#define MBX_B7 *((volatile unsigned int *)(BITBAND_SRAM(MAILBOX,7)))

// Timer bit 0
#define TIMER_B0 *((volatile unsigned char *)(BITBAND_PERI(TIMER,0)))

// Timer bit 7
#define TIMER_B7 *((volatile unsigned char *)(BITBAND_PERI(TIMER,7)))


int main(void)
{
    unsigned int temp = 0;

    MBX_B0 = 1; // Word write
    temp = MBX_B7; // Word read
    TIMER_B0 = temp; // Byte write

    return TIMER_B7; // Byte read
}
