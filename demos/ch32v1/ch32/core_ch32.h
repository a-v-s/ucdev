/********************************** (C) COPYRIGHT  *******************************
 * File Name          : core_riscv.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2020/04/30
 * Description        : RISC-V Core Peripheral Access Layer Header File
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#ifndef __CORE_RISCV_H__
#define __CORE_RISCV_H__

#include <stdint.h>

/* IO definitions */
#ifdef __cplusplus
  #define     __I     volatile                /*!< defines 'read only' permissions      */
#else
  #define     __I     volatile const          /*!< defines 'read only' permissions     */
#endif
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */

/* Standard Peripheral Library old types (maintained for legacy purpose) */
typedef __I uint32_t vuc32;  /* Read Only */
typedef __I uint16_t vuc16;  /* Read Only */
typedef __I uint8_t vuc8;   /* Read Only */

typedef const uint32_t uc32;  /* Read Only */
typedef const uint16_t uc16;  /* Read Only */
typedef const uint8_t uc8;   /* Read Only */

typedef __I int32_t vsc32;  /* Read Only */
typedef __I int16_t vsc16;  /* Read Only */
typedef __I int8_t vsc8;   /* Read Only */

typedef const int32_t sc32;  /* Read Only */
typedef const int16_t sc16;  /* Read Only */
typedef const int8_t sc8;   /* Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

#define   RV_STATIC_INLINE  static  inline

/* memory mapped structure for Program Fast Interrupt Controller (PFIC) */
typedef struct{
  __I  uint32_t ISR[8];
  __I  uint32_t IPR[8];
  __IO uint32_t ITHRESDR;
  __IO uint32_t FIBADDRR;
  __IO uint32_t CFGR;
  __I  uint32_t GISR;
  uint8_t RESERVED0[0x10];
  __IO uint32_t FIOFADDRR[4];
  uint8_t RESERVED1[0x90];
  __O  uint32_t IENR[8];
  uint8_t RESERVED2[0x60];
  __O  uint32_t IRER[8];
  uint8_t RESERVED3[0x60];
  __O  uint32_t IPSR[8];
  uint8_t RESERVED4[0x60];
  __O  uint32_t IPRR[8];
  uint8_t RESERVED5[0x60];
  __IO uint32_t IACTR[8];
  uint8_t RESERVED6[0xE0];
  __IO uint8_t IPRIOR[256];
  uint8_t RESERVED7[0x810];
  __IO uint32_t SCTLR;
}PFIC_Type;

/* memory mapped structure for SysTick */
typedef struct
{
  __IO uint32_t CTLR;
  __IO uint8_t CNTL0;
  __IO uint8_t CNTL1;
  __IO uint8_t CNTL2;
  __IO uint8_t CNTL3;
  __IO uint8_t CNTH0;
  __IO uint8_t CNTH1;
  __IO uint8_t CNTH2;
  __IO uint8_t CNTH3;
  __IO uint8_t CMPLR0;
  __IO uint8_t CMPLR1;
  __IO uint8_t CMPLR2;
  __IO uint8_t CMPLR3;
  __IO uint8_t CMPHR0;
  __IO uint8_t CMPHR1;
  __IO uint8_t CMPHR2;
  __IO uint8_t CMPHR3;
}SysTick_Type;


#define PFIC            	((PFIC_Type *) 		0xE000E000)
#define PFIC_KEY1       	((uint32_t)			0xFA050000)
#define	PFIC_KEY2			((uint32_t)			0xBCAF0000)
#define	PFIC_KEY3			((uint32_t)			0xBEEF0000)
#define SysTick         	((SysTick_Type *) 	0xE000F000)


/*********************************************************************
 * @fn      __NOP
 *
 * @brief   nop
 *
 * @return  none
 */
//RV_STATIC_INLINE void __NOP()
//{
//  __asm volatile ("nop");
//}

/*********************************************************************
 * @fn      PFIC_EnableIRQ
 *
 * @brief   Enable Interrupt
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  none
 */
RV_STATIC_INLINE void PFIC_EnableIRQ(IRQn_Type IRQn){
  PFIC->IENR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/*********************************************************************
 * @fn      PFIC_DisableIRQ
 *
 * @brief   Disable Interrupt
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  none
 */
RV_STATIC_INLINE void PFIC_DisableIRQ(IRQn_Type IRQn)
{
  uint32_t t;

  t = PFIC->ITHRESDR;
  PFIC->ITHRESDR = 0x10;
  PFIC->IRER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
  PFIC->ITHRESDR = t;
}

/*********************************************************************
 * @fn      PFIC_GetStatusIRQ
 *
 * @brief   Get Interrupt Enable State
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  1 - Interrupt Enable
 *          0 - Interrupt Disable
 */
RV_STATIC_INLINE uint32_t PFIC_GetStatusIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((PFIC->ISR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));
}

/*********************************************************************
 * @fn      PFIC_GetPendingIRQ
 *
 * @brief   Get Interrupt Pending State
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  1 - Interrupt Pending Enable
 *          0 - Interrupt Pending Disable
 */
RV_STATIC_INLINE uint32_t PFIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((PFIC->IPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));
}

/*********************************************************************
 * @fn      PFIC_SetPendingIRQ
 *
 * @brief   Set Interrupt Pending
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  None
 */
RV_STATIC_INLINE void PFIC_SetPendingIRQ(IRQn_Type IRQn)
{
  PFIC->IPSR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/*********************************************************************
 * @fn      PFIC_ClearPendingIRQ
 *
 * @brief   Clear Interrupt Pending
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  None
 */
RV_STATIC_INLINE void PFIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  PFIC->IPRR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/*********************************************************************
 * @fn      PFIC_GetActive
 *
 * @brief   Get Interrupt Active State
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  1 - Interrupt Active
 *          0 - Interrupt No Active
 */
RV_STATIC_INLINE uint32_t PFIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((PFIC->IACTR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));
}

/*********************************************************************
 * @fn      PFIC_SetPriority
 *
 * @brief   Set Interrupt Priority
 *
 * @param   IRQn - Interrupt Numbers
 *          priority -
 *              bit7 - pre-emption priority
 *              bit6~bit4 - subpriority
 * @return  None
 */
RV_STATIC_INLINE void PFIC_SetPriority(IRQn_Type IRQn, uint8_t priority)
{
  PFIC->IPRIOR[(uint32_t)(IRQn)] = priority;
}

/*********************************************************************
 * @fn      __WFI
 *
 * @brief   Wait for Interrupt
 *
 * @return  None
 */
//__attribute__( ( always_inline ) ) RV_STATIC_INLINE void __WFI(void)
//{
//  PFIC->SCTLR &= ~(1<<3);	// wfi
//  asm volatile ("wfi");
//}

/*********************************************************************
 * @fn      __WFE
 *
 * @brief   Wait for Events
 *
 * @return  None
 */
//__attribute__( ( always_inline ) ) RV_STATIC_INLINE void __WFE(void)
//{
//  PFIC->SCTLR |= (1<<3)|(1<<5);		// (wfi->wfe)+(__sev)
//  asm volatile ("wfi");
//  PFIC->SCTLR |= (1<<3);
//  asm volatile ("wfi");
//}

/*********************************************************************
 * @fn      PFIC_SetFastIRQ
 *
 * @brief   Set VTF Interrupt
 *
 * @param   add - VTF interrupt service function base address.
 *          IRQn -Interrupt Numbers
 *          num - VTF Interrupt Numbers
 * @return  None
 */
RV_STATIC_INLINE void PFIC_SetFastIRQ(uint32_t addr, IRQn_Type IRQn, uint8_t num)
{
  if(num > 3)  return ;
  PFIC->FIBADDRR = addr;
  PFIC->FIOFADDRR[num] = ((uint32_t)IRQn<<24)|(addr&0xfffff);
}

/*********************************************************************
 * @fn      PFIC_SystemReset
 *
 * @brief   Initiate a system reset request
 *
 * @return  None
 */
RV_STATIC_INLINE void PFIC_SystemReset(void)
{
  PFIC->CFGR = PFIC_KEY3|(1<<7);
}

/*********************************************************************
 * @fn      PFIC_HaltPushCfg
 *
 * @brief   Enable Hardware Stack
 *
 * @param   NewState - DISABLE or ENABLE
 
 * @return  None
 */
RV_STATIC_INLINE void PFIC_HaltPushCfg(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
  	PFIC->CFGR = PFIC_KEY1;
  }
  else{
  	PFIC->CFGR = PFIC_KEY1|(1<<0);
  }
}

/*********************************************************************
 * @fn      PFIC_INTNestCfg
 *
 * @brief   Enable Interrupt Nesting
 *
 * @param   NewState - DISABLE or ENABLE
 
 * @return  None
 */
RV_STATIC_INLINE void PFIC_INTNestCfg(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
  	PFIC->CFGR = PFIC_KEY1;
  }
  else
  {
  	PFIC->CFGR = PFIC_KEY1|(1<<1);
  }
}


#endif/* __CORE_RISCV_H__ */





