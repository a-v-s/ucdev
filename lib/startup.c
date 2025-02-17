#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// As this is a demo for replacing the startup files this is a little glue
// that still needs to be cleaned up
#define __NVIC_PRIO_BITS 4U /*!< STM32 uses 4 Bits for the Priority Levels    */
typedef int IRQn_Type;
#define SysTick_IRQn -1
#define IRQ_COUNT 64
#include "../ext/CMSIS_5/CMSIS/Core/Include/core_cm3.h"


int irq_count() { return 32 * (1 + SCnSCB->ICTR); }

typedef void (*interrupt_handler_func)(void);

void __attribute__((interrupt)) exception_handler() {}

void __attribute__((interrupt)) interrupt_handler() {
    if ((SCB->ICSR & 0x1FF) < 16)
        exception_handler();

    int irq = (SCB->ICSR & 0x1FF) - 16;
    printf("In interrupt %d\n", irq);
}

void __attribute__((weak)) SystemInit(void) {}

void __attribute__((interrupt)) reset_handler();
void Reset_Handler(void) __attribute__((weak, alias("reset_handler")));

void NMI_Handler(void) __attribute__((weak, alias("exception_handler")));
void HardFault_Handler(void) __attribute__((weak, alias("exception_handler")));
void MemManage_Handler(void) __attribute__((weak, alias("exception_handler")));
void BusFault_Handler(void) __attribute__((weak, alias("exception_handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("exception_handler")));
void SecureFault_Handler(void) __attribute__((weak, alias("exception_handler")));
void SVC_Handler(void) __attribute__((weak, alias("exception_handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("exception_handler")));
void PendSV_Handler(void) __attribute__((weak, alias("exception_handler")));
void SysTick_Handler(void) __attribute__((weak, alias("exception_handler")));

void Interrupt0_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt1_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt2_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt3_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt4_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt5_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt6_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt7_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt8_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt9_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt10_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt11_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt12_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt13_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt14_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt15_Handler(void) __attribute__((weak, alias("interrupt_handler")));
#if IRQ_COUNT > 32
void Interrupt16_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt17_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt18_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt19_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt20_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt21_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt22_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt23_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt24_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt25_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt26_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt27_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt28_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt29_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt30_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt31_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt32_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt33_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt34_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt35_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt36_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt37_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt38_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt39_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt40_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt41_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt42_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt43_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt44_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt45_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt46_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt47_Handler(void) __attribute__((weak, alias("interrupt_handler")));
#if IRQ_COUNT > 64
void Interrupt48_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt49_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt50_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt51_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt52_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt53_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt54_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt55_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt56_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt57_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt58_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt59_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt60_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt61_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt62_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt63_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt64_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt65_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt66_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt67_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt68_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt69_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt70_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt71_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt72_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt73_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt74_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt75_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt76_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt77_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt78_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt79_Handler(void) __attribute__((weak, alias("interrupt_handler")));
#if IRQ_COUNT > 96
void Interrupt80_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt81_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt82_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt83_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt84_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt85_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt86_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt87_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt88_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt89_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt90_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt91_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt92_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt93_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt94_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt95_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt96_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt97_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt98_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt99_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt100_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt101_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt102_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt103_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt104_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt105_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt106_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt107_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt108_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt109_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt110_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt111_Handler(void) __attribute__((weak, alias("interrupt_handler")));
#if IRQ_COUNT > 128
void Interrupt112_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt113_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt114_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt115_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt116_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt117_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt118_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt119_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt120_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt121_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt122_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt123_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt124_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt125_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt126_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt127_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt128_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt129_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt130_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt131_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt132_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt133_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt134_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt135_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt136_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt137_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt138_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt139_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt140_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt141_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt142_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt143_Handler(void) __attribute__((weak, alias("interrupt_handler")));
#if IRQ_COUNT > 160
void Interrupt144_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt145_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt146_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt147_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt148_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt149_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt150_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt151_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt152_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt153_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt154_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt155_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt156_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt157_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt158_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt159_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt160_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt161_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt162_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt163_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt164_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt165_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt166_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt167_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt168_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt169_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt170_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt171_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt172_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt173_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt174_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt175_Handler(void) __attribute__((weak, alias("interrupt_handler")));
#if IRQ_COUNT > 192
void Interrupt176_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt177_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt178_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt179_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt180_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt181_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt182_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt183_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt184_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt185_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt186_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt187_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt188_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt189_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt190_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt191_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt192_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt193_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt194_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt195_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt196_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt197_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt198_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt199_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt200_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt201_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt202_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt203_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt204_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt205_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt206_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt207_Handler(void) __attribute__((weak, alias("interrupt_handler")));
#if IRQ_COUNT > 224
void Interrupt208_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt209_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt210_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt211_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt212_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt213_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt214_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt215_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt216_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt217_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt218_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt219_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt220_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt221_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt222_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt223_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt224_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt225_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt226_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt227_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt228_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt229_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt230_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt231_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt232_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt233_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt234_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt235_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt236_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt237_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt238_Handler(void) __attribute__((weak, alias("interrupt_handler")));
void Interrupt239_Handler(void) __attribute__((weak, alias("interrupt_handler")));
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern uint32_t __StackTop, __StackLimit, __StackSeal;

#define StackTop (interrupt_handler_func)(&__StackTop)
interrupt_handler_func vtor[IRQ_COUNT] __attribute__((section(".vectors"))) = {
    StackTop,            //     Initial Stack Pointer
    Reset_Handler,       //     Reset Handler
    NMI_Handler,         // -14 NMI Handler
    HardFault_Handler,   // -13 Hard Fault Handler
    MemManage_Handler,   // -12 MPU Fault Handler
    BusFault_Handler,    // -11 Bus Fault Handler
    UsageFault_Handler,  // -10 Usage Fault Handler
    SecureFault_Handler, //  -9 Secure Fault Handler
    exception_handler,   //  -8 Reserved
    exception_handler,   //  -7 Reserved
    exception_handler,   //  -6 Reserved
    SVC_Handler,         //  -5 SVC Handler
    DebugMon_Handler,    //  -4 Debug Monitor Handler
    exception_handler,   //  -3 Reserved
    PendSV_Handler,      //  -2 PendSV Handler
    SysTick_Handler,     //  -1 SysTick Handler
    Interrupt0_Handler,  //   0 Interrupt 0
    Interrupt1_Handler,  //   1 Interrupt 1
    Interrupt2_Handler,  //   2 Interrupt 2
    Interrupt3_Handler,  //   3 Interrupt 3
    Interrupt4_Handler,  //   4 Interrupt 4
    Interrupt5_Handler,  //   5 Interrupt 5
    Interrupt6_Handler,  //   6 Interrupt 6
    Interrupt7_Handler,  //   7 Interrupt 7
    Interrupt8_Handler,  //   8 Interrupt 8
    Interrupt9_Handler,  //   9 Interrupt 9
    Interrupt10_Handler, //   10 Interrupt 10
    Interrupt11_Handler, //   11 Interrupt 11
    Interrupt12_Handler, //   12 Interrupt 12
    Interrupt13_Handler, //   13 Interrupt 13
    Interrupt14_Handler, //   14 Interrupt 14
    Interrupt15_Handler, //   15 Interrupt 15
#if IRQ_COUNT > 32
    Interrupt16_Handler, //   16 Interrupt 16
    Interrupt17_Handler, //   17 Interrupt 17
    Interrupt18_Handler, //   18 Interrupt 18
    Interrupt19_Handler, //   19 Interrupt 19
    Interrupt20_Handler, //   20 Interrupt 20
    Interrupt21_Handler, //   21 Interrupt 21
    Interrupt22_Handler, //   22 Interrupt 22
    Interrupt23_Handler, //   23 Interrupt 23
    Interrupt24_Handler, //   24 Interrupt 24
    Interrupt25_Handler, //   25 Interrupt 25
    Interrupt26_Handler, //   26 Interrupt 26
    Interrupt27_Handler, //   27 Interrupt 27
    Interrupt28_Handler, //   28 Interrupt 28
    Interrupt29_Handler, //   29 Interrupt 29
    Interrupt30_Handler, //   30 Interrupt 30
    Interrupt31_Handler, //   31 Interrupt 31
    Interrupt32_Handler, //   32 Interrupt 32
    Interrupt33_Handler, //   33 Interrupt 33
    Interrupt34_Handler, //   34 Interrupt 34
    Interrupt35_Handler, //   35 Interrupt 35
    Interrupt36_Handler, //   36 Interrupt 36
    Interrupt37_Handler, //   37 Interrupt 37
    Interrupt38_Handler, //   38 Interrupt 38
    Interrupt39_Handler, //   39 Interrupt 39
    Interrupt40_Handler, //   40 Interrupt 40
    Interrupt41_Handler, //   41 Interrupt 41
    Interrupt42_Handler, //   42 Interrupt 42
    Interrupt43_Handler, //   43 Interrupt 43
    Interrupt44_Handler, //   44 Interrupt 44
    Interrupt45_Handler, //   45 Interrupt 45
    Interrupt46_Handler, //   46 Interrupt 46
    Interrupt47_Handler, //   47 Interrupt 47
#if IRQ_COUNT > 64
    Interrupt48_Handler, //   48 Interrupt 48
    Interrupt49_Handler, //   49 Interrupt 49
    Interrupt50_Handler, //   50 Interrupt 50
    Interrupt51_Handler, //   51 Interrupt 51
    Interrupt52_Handler, //   52 Interrupt 52
    Interrupt53_Handler, //   53 Interrupt 53
    Interrupt54_Handler, //   54 Interrupt 54
    Interrupt55_Handler, //   55 Interrupt 55
    Interrupt56_Handler, //   56 Interrupt 56
    Interrupt57_Handler, //   57 Interrupt 57
    Interrupt58_Handler, //   58 Interrupt 58
    Interrupt59_Handler, //   59 Interrupt 59
    Interrupt60_Handler, //   60 Interrupt 60
    Interrupt61_Handler, //   61 Interrupt 61
    Interrupt62_Handler, //   62 Interrupt 62
    Interrupt63_Handler, //   63 Interrupt 63
    Interrupt64_Handler, //   64 Interrupt 64
    Interrupt65_Handler, //   65 Interrupt 65
    Interrupt66_Handler, //   66 Interrupt 66
    Interrupt67_Handler, //   67 Interrupt 67
    Interrupt68_Handler, //   68 Interrupt 68
    Interrupt69_Handler, //   69 Interrupt 69
    Interrupt70_Handler, //   70 Interrupt 70
    Interrupt71_Handler, //   71 Interrupt 71
    Interrupt72_Handler, //   72 Interrupt 72
    Interrupt73_Handler, //   73 Interrupt 73
    Interrupt74_Handler, //   74 Interrupt 74
    Interrupt75_Handler, //   75 Interrupt 75
    Interrupt76_Handler, //   76 Interrupt 76
    Interrupt77_Handler, //   77 Interrupt 77
    Interrupt78_Handler, //   78 Interrupt 78
    Interrupt79_Handler, //   79 Interrupt 79
#if IRQ_COUNT > 96
    Interrupt80_Handler,  //   80 Interrupt 80
    Interrupt81_Handler,  //   81 Interrupt 81
    Interrupt82_Handler,  //   82 Interrupt 82
    Interrupt83_Handler,  //   83 Interrupt 83
    Interrupt84_Handler,  //   84 Interrupt 84
    Interrupt85_Handler,  //   85 Interrupt 85
    Interrupt86_Handler,  //   86 Interrupt 86
    Interrupt87_Handler,  //   87 Interrupt 87
    Interrupt88_Handler,  //   88 Interrupt 88
    Interrupt89_Handler,  //   89 Interrupt 89
    Interrupt90_Handler,  //   90 Interrupt 90
    Interrupt91_Handler,  //   91 Interrupt 91
    Interrupt92_Handler,  //   92 Interrupt 92
    Interrupt93_Handler,  //   93 Interrupt 93
    Interrupt94_Handler,  //   94 Interrupt 94
    Interrupt95_Handler,  //   95 Interrupt 95
    Interrupt96_Handler,  //   96 Interrupt 96
    Interrupt97_Handler,  //   97 Interrupt 97
    Interrupt98_Handler,  //   98 Interrupt 98
    Interrupt99_Handler,  //   99 Interrupt 99
    Interrupt100_Handler, //   100 Interrupt 100
    Interrupt101_Handler, //   101 Interrupt 101
    Interrupt102_Handler, //   102 Interrupt 102
    Interrupt103_Handler, //   103 Interrupt 103
    Interrupt104_Handler, //   104 Interrupt 104
    Interrupt105_Handler, //   105 Interrupt 105
    Interrupt106_Handler, //   106 Interrupt 106
    Interrupt107_Handler, //   107 Interrupt 107
    Interrupt108_Handler, //   108 Interrupt 108
    Interrupt109_Handler, //   109 Interrupt 109
    Interrupt110_Handler, //   110 Interrupt 110
    Interrupt111_Handler, //   111 Interrupt 111
#if IRQ_COUNT > 128
    Interrupt112_Handler, //   112 Interrupt 112
    Interrupt113_Handler, //   113 Interrupt 113
    Interrupt114_Handler, //   114 Interrupt 114
    Interrupt115_Handler, //   115 Interrupt 115
    Interrupt116_Handler, //   116 Interrupt 116
    Interrupt117_Handler, //   117 Interrupt 117
    Interrupt118_Handler, //   118 Interrupt 118
    Interrupt119_Handler, //   119 Interrupt 119
    Interrupt120_Handler, //   120 Interrupt 120
    Interrupt121_Handler, //   121 Interrupt 121
    Interrupt122_Handler, //   122 Interrupt 122
    Interrupt123_Handler, //   123 Interrupt 123
    Interrupt124_Handler, //   124 Interrupt 124
    Interrupt125_Handler, //   125 Interrupt 125
    Interrupt126_Handler, //   126 Interrupt 126
    Interrupt127_Handler, //   127 Interrupt 127
    Interrupt128_Handler, //   128 Interrupt 128
    Interrupt129_Handler, //   129 Interrupt 129
    Interrupt130_Handler, //   130 Interrupt 130
    Interrupt131_Handler, //   131 Interrupt 131
    Interrupt132_Handler, //   132 Interrupt 132
    Interrupt133_Handler, //   133 Interrupt 133
    Interrupt134_Handler, //   134 Interrupt 134
    Interrupt135_Handler, //   135 Interrupt 135
    Interrupt136_Handler, //   136 Interrupt 136
    Interrupt137_Handler, //   137 Interrupt 137
    Interrupt138_Handler, //   138 Interrupt 138
    Interrupt139_Handler, //   139 Interrupt 139
    Interrupt140_Handler, //   140 Interrupt 140
    Interrupt141_Handler, //   141 Interrupt 141
    Interrupt142_Handler, //   142 Interrupt 142
    Interrupt143_Handler, //   143 Interrupt 143
#if IRQ_COUNT > 160
    Interrupt144_Handler, //   144 Interrupt 144
    Interrupt145_Handler, //   145 Interrupt 145
    Interrupt146_Handler, //   146 Interrupt 146
    Interrupt147_Handler, //   147 Interrupt 147
    Interrupt148_Handler, //   148 Interrupt 148
    Interrupt149_Handler, //   149 Interrupt 149
    Interrupt150_Handler, //   150 Interrupt 150
    Interrupt151_Handler, //   151 Interrupt 151
    Interrupt152_Handler, //   152 Interrupt 152
    Interrupt153_Handler, //   153 Interrupt 153
    Interrupt154_Handler, //   154 Interrupt 154
    Interrupt155_Handler, //   155 Interrupt 155
    Interrupt156_Handler, //   156 Interrupt 156
    Interrupt157_Handler, //   157 Interrupt 157
    Interrupt158_Handler, //   158 Interrupt 158
    Interrupt159_Handler, //   159 Interrupt 159
    Interrupt160_Handler, //   160 Interrupt 160
    Interrupt161_Handler, //   161 Interrupt 161
    Interrupt162_Handler, //   162 Interrupt 162
    Interrupt163_Handler, //   163 Interrupt 163
    Interrupt164_Handler, //   164 Interrupt 164
    Interrupt165_Handler, //   165 Interrupt 165
    Interrupt166_Handler, //   166 Interrupt 166
    Interrupt167_Handler, //   167 Interrupt 167
    Interrupt168_Handler, //   168 Interrupt 168
    Interrupt169_Handler, //   169 Interrupt 169
    Interrupt170_Handler, //   170 Interrupt 170
    Interrupt171_Handler, //   171 Interrupt 171
    Interrupt172_Handler, //   172 Interrupt 172
    Interrupt173_Handler, //   173 Interrupt 173
    Interrupt174_Handler, //   174 Interrupt 174
    Interrupt175_Handler, //   175 Interrupt 175
#if IRQ_COUNT > 192
    Interrupt176_Handler, //   176 Interrupt 176
    Interrupt177_Handler, //   177 Interrupt 177
    Interrupt178_Handler, //   178 Interrupt 178
    Interrupt179_Handler, //   179 Interrupt 179
    Interrupt180_Handler, //   180 Interrupt 180
    Interrupt181_Handler, //   181 Interrupt 181
    Interrupt182_Handler, //   182 Interrupt 182
    Interrupt183_Handler, //   183 Interrupt 183
    Interrupt184_Handler, //   184 Interrupt 184
    Interrupt185_Handler, //   185 Interrupt 185
    Interrupt186_Handler, //   186 Interrupt 186
    Interrupt187_Handler, //   187 Interrupt 187
    Interrupt188_Handler, //   188 Interrupt 188
    Interrupt189_Handler, //   189 Interrupt 189
    Interrupt190_Handler, //   190 Interrupt 190
    Interrupt191_Handler, //   191 Interrupt 191
    Interrupt192_Handler, //   192 Interrupt 192
    Interrupt193_Handler, //   193 Interrupt 193
    Interrupt194_Handler, //   194 Interrupt 194
    Interrupt195_Handler, //   195 Interrupt 195
    Interrupt196_Handler, //   196 Interrupt 196
    Interrupt197_Handler, //   197 Interrupt 197
    Interrupt198_Handler, //   198 Interrupt 198
    Interrupt199_Handler, //   199 Interrupt 199
    Interrupt200_Handler, //   200 Interrupt 200
    Interrupt201_Handler, //   201 Interrupt 201
    Interrupt202_Handler, //   202 Interrupt 202
    Interrupt203_Handler, //   203 Interrupt 203
    Interrupt204_Handler, //   204 Interrupt 204
    Interrupt205_Handler, //   205 Interrupt 205
    Interrupt206_Handler, //   206 Interrupt 206
    Interrupt207_Handler, //   207 Interrupt 207
#if IRQ_COUNT > 224
    Interrupt208_Handler, //   208 Interrupt 208
    Interrupt209_Handler, //   209 Interrupt 209
    Interrupt210_Handler, //   210 Interrupt 210
    Interrupt211_Handler, //   211 Interrupt 211
    Interrupt212_Handler, //   212 Interrupt 212
    Interrupt213_Handler, //   213 Interrupt 213
    Interrupt214_Handler, //   214 Interrupt 214
    Interrupt215_Handler, //   215 Interrupt 215
    Interrupt216_Handler, //   216 Interrupt 216
    Interrupt217_Handler, //   217 Interrupt 217
    Interrupt218_Handler, //   218 Interrupt 218
    Interrupt219_Handler, //   219 Interrupt 219
    Interrupt220_Handler, //   220 Interrupt 220
    Interrupt221_Handler, //   221 Interrupt 221
    Interrupt222_Handler, //   222 Interrupt 222
    Interrupt223_Handler, //   223 Interrupt 223
    Interrupt224_Handler, //   224 Interrupt 224
    Interrupt225_Handler, //   225 Interrupt 225
    Interrupt226_Handler, //   226 Interrupt 226
    Interrupt227_Handler, //   227 Interrupt 227
    Interrupt228_Handler, //   228 Interrupt 228
    Interrupt229_Handler, //   229 Interrupt 229
    Interrupt230_Handler, //   230 Interrupt 230
    Interrupt231_Handler, //   231 Interrupt 231
    Interrupt232_Handler, //   232 Interrupt 232
    Interrupt233_Handler, //   233 Interrupt 233
    Interrupt234_Handler, //   234 Interrupt 234
    Interrupt235_Handler, //   235 Interrupt 235
    Interrupt236_Handler, //   236 Interrupt 236
    Interrupt237_Handler, //   237 Interrupt 237
    Interrupt238_Handler, //   238 Interrupt 238
    Interrupt239_Handler, //   239 Interrupt 239
#endif
#endif
#endif
#endif
#endif
#endif
#endif

};

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

void __attribute__((interrupt)) reset_handler() {
    __set_PSP((uint32_t)(&__StackTop));

#if ((defined(__ARM_ARCH_8M_MAIN__) && (__ARM_ARCH_8M_MAIN__ == 1)) ||                                                             \
     (defined(__ARM_ARCH_8M_BASE__) && (__ARM_ARCH_8M_BASE__ == 1)))
    __set_MSPLIM((uint32_t)(&__StackLimit));
    __set_PSPLIM((uint32_t)(&__StackLimit));
#endif

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    __TZ_set_STACKSEAL_S((uint32_t *)(&__StackSeal));
#endif

#if defined(__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
    SCB->VTOR = (uint32_t)&(__VECTOR_TABLE[0]);
#endif

#if defined(__FPU_USED) && (__FPU_USED == 1U)
    SCB->CPACR |= ((3U << 10U * 2U) | /* enable CP10 Full Access */
                   (3U << 11U * 2U)); /* enable CP11 Full Access */
#endif

    SystemInit();      /* CMSIS System Initialization */
    __PROGRAM_START(); /* Enter PreMain (C library entry point) */
}
