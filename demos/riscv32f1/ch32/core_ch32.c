#include <stdint.h>
/* Reset and Clock Control */
typedef struct
{
     uint32_t CTLR;
     uint32_t CFGR0;
     uint32_t INTR;
     uint32_t APB2PRSTR;
     uint32_t APB1PRSTR;
     uint32_t AHBPCENR;
     uint32_t APB2PCENR;
     uint32_t APB1PCENR;
     uint32_t BDCTLR;
     uint32_t RSTSCKR;
} RCC_TypeDef;

#define FLASH_BASE                              ((uint32_t)0x08000000) /* FLASH base address in the alias region */
#define SRAM_BASE                               ((uint32_t)0x20000000) /* SRAM base address in the alias region */
#define PERIPH_BASE                             ((uint32_t)0x40000000) /* Peripheral base address in the alias region */
#define APB1PERIPH_BASE                         (PERIPH_BASE)
#define APB2PERIPH_BASE                         (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE                          (PERIPH_BASE + 0x20000)
#define RCC_BASE                                (AHBPERIPH_BASE + 0x1000)
#define RCC                                     ((RCC_TypeDef *)RCC_BASE)

void SystemInit_CH32 (void) {
  RCC->CTLR |= (uint32_t)0x00000001;
  RCC->CFGR0 &= (uint32_t)0xF8FF0000;
  RCC->CTLR &= (uint32_t)0xFEF6FFFF;
  RCC->CTLR &= (uint32_t)0xFFFBFFFF;
  RCC->CFGR0 &= (uint32_t)0xFF80FFFF;
  RCC->INTR = 0x009F0000;
}
