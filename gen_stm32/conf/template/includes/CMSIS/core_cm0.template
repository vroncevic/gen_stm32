/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * core_cm0.h
 * 
 * CMSIS Cortex-M Core Instruction Access Header File
 * 
 * Version V2.10
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2009-2011 ARM Limited. All rights reserved.
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * CMSIS DSP Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * CMSIS DSP Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#if defined(__ICCARM__)
    #pragma system_include
#endif

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef __CORE_CM0_H_GENERIC
#define __CORE_CM0_H_GENERIC

/**
 * CMSIS Cortex-M0
 * Documentation describes the CMSIS Cortex-M Core Peripheral Access Layer.
 * It consists of:
 * 
 *  - Cortex-M Core Register Definitions
 *  - Cortex-M functions
 *  - Cortex-M instructions
 * 
 * The CMSIS Cortex-M0 Core Peripheral Access Layer contains C and assembly
 * functions that ease access to the Cortex-M Core.
 * 
 * CMSIS violates following MISRA-C2004 Rules:
 * 
 * - Violates MISRA 2004 Required Rule 8.5, object/function definition in
 *   header file. Function definitions in header files are used to allow
 *   'inlining'.
 * 
 * - Violates MISRA 2004 Required Rule 18.4, declaration of union type
 *   or object of union type: '{...}'. Unions are used for effective
 *   representation of core registers.
 * 
 * - Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
 *   Function-like macros are used to allow more efficient code.
 */

/* CMSIS CM0 definitions */
#define __CM0_CMSIS_VERSION_MAIN (0x02)
#define __CM0_CMSIS_VERSION_SUB (0x10)
#define __CM0_CMSIS_VERSION ( \
    (__CM0_CMSIS_VERSION_MAIN << 16) | __CM0_CMSIS_VERSION_SUB \
)
#define __CORTEX_M (0x00)

#if defined(__CC_ARM)
    #define __ASM __asm
    #define __INLINE __inline
#elif defined(__ICCARM__)
  #define __ASM __asm
  #define __INLINE inline
#elif defined(__GNUC__)
  #define __ASM __asm
  #define __INLINE inline
#elif defined(__TASKING__)
  #define __ASM __asm
  #define __INLINE inline
#endif

/**
 * __FPU_USED to be checked prior to making use of FPU specific
 * registers and functions 
 */
#define __FPU_USED 0

#if defined(__CC_ARM)
    #if defined(__TARGET_FPU_VFP)
        #warning "Compiler generates FPU instructions"
        #warning "Device without an FPU (check __FPU_PRESENT)"
    #endif
#elif defined(__ICCARM__)
    #if defined(__ARMVFP__)
        #warning "Compiler generates FPU instructions"
        #warning "Device without an FPU (check __FPU_PRESENT)"
    #endif
#elif defined(__GNUC__)
    #if defined(__VFP_FP__) && !defined(__SOFTFP__)
        #warning "Compiler generates FPU instructions"
        #warning "Device without an FPU (check __FPU_PRESENT)"
    #endif
#elif defined(__TASKING__)
    /* add preprocessor checks */
#endif

#include <stdint.h>
#include "core_cmInstr.h"
#include "core_cmFunc.h"

#endif

#ifndef __CMSIS_GENERIC

#ifndef __CORE_CM0_H_DEPENDANT
#define __CORE_CM0_H_DEPENDANT

/* Check device defines and use defaults */
#if defined __CHECK_DEVICE_DEFINES
    #ifndef __CM0_REV
        #define __CM0_REV 0x0000
        #warning "__CM0_REV not defined in device header file"
        #warning "Using default!"
    #endif
    #ifndef __NVIC_PRIO_BITS
        #define __NVIC_PRIO_BITS 2
        #warning "__NVIC_PRIO_BITS not defined in device header file"
        #warning "Using default!"
    #endif
    #ifndef __Vendor_SysTickConfig
        #define __Vendor_SysTickConfig 0
        #warning "__Vendor_SysTickConfig not defined in device header file"
        #warning "Using default!"
    #endif
#endif

/* IO definitions (access restrictions to peripheral registers) */
#ifdef __cplusplus
    #define __I volatile /* defines 'read only' permissions */
#else
    #define __I volatile const /* defines 'read only' permissions */
#endif

#define __O volatile /* defines 'write only' permissions */
#define __IO volatile /* defines 'read/write' permissions */

/**
 * Core Register contain:
 * - Core Register
 * - Core NVIC Register
 * - Core SCB Register
 * - Core SysTick Register
*/

/**
 * Union type to access the Application Program Status Register (APSR).
 */
typedef union {
    struct {
#if (__CORTEX_M != 0x04)
        /* bit: 0..26 Reserved */
        uint32_t _reserved0:27;
#else
        /* bit: 0..15 Reserved */
        uint32_t _reserved0:16;
        /* bit: 16..19 Greater than or Equal flags */
        uint32_t GE:4;
        /* bit: 20..26 Reserved */
        uint32_t _reserved1:7;
#endif
        /* bit: 27 Saturation condition flag */
        uint32_t Q:1;
        /* bit: 28 Overflow condition code flag */
        uint32_t V:1;
        /* bit: 29 Carry condition code flag */
        uint32_t C:1;
        /* bit: 30 Zero condition code flag */
        uint32_t Z:1;
        /* bit: 31 Negative condition code flag */
        uint32_t N:1;
    } b;
    uint32_t w; /* Type used for word access */
} APSR_Type;

/**
 * Union type to access the Interrupt Program Status Register (IPSR).
 */
typedef union {
    struct {
        /* bit: 0..8 Exception number */
        uint32_t ISR:9;
        /* bit: 9..31 Reserved */
        uint32_t _reserved0:23;
    } b;
    uint32_t w; /* Type used for word access */
} IPSR_Type;

/**
 * Union type to access the Special-Purpose Program Status Registers (xPSR).
 */
typedef union {
    struct {
        /* bit: 0..8 Exception number */
        uint32_t ISR:9;
#if (__CORTEX_M != 0x04)
        /* bit: 9..23 Reserved */
        uint32_t _reserved0:15;
#else
        /* bit: 9..15 Reserved */
        uint32_t _reserved0:7;
        /* bit: 16..19 Greater than or Equal flags */
        uint32_t GE:4;
        /* bit: 20..23 Reserved */
        uint32_t _reserved1:4;
#endif
        /* bit: 24 Thumb bit (read 0) */
        uint32_t T:1;
        /* bit: 25..26 saved IT state (read 0) */
        uint32_t IT:2;
        /* bit: 27 Saturation condition flag */
        uint32_t Q:1;
        /* bit: 28 Overflow condition code flag */
        uint32_t V:1;
        /* bit: 29 Carry condition code flag */
        uint32_t C:1;
        /* bit: 30 Zero condition code flag */
        uint32_t Z:1;
        /* bit: 31 Negative condition code flag */
        uint32_t N:1;
    } b;
    uint32_t w; /* Type used for word access */
} xPSR_Type;

/**
 * Union type to access the Control Registers (CONTROL).
 */
typedef union {
    struct {
        /* bit: 0  Execution privilege in Thread mode */
        uint32_t nPRIV:1;
        /* bit: 1  Stack to be used */
        uint32_t SPSEL:1;
        /* bit: 2 FP extension active flag */
        uint32_t FPCA:1;
        /* bit: 3..31 Reserved */
        uint32_t _reserved0:29;
    } b;
    /* Type used for word access */
    uint32_t w;
} CONTROL_Type;

/**
 * Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct {
    /* Offset: 0x000 (R/W) Interrupt Set Enable Register */
    __IO uint32_t ISER[1];
    uint32_t RESERVED0[31];
    /* Offset: 0x080 (R/W) Interrupt Clear Enable Register */
    __IO uint32_t ICER[1];
    uint32_t RSERVED1[31];
    /* Offset: 0x100 (R/W) Interrupt Set Pending Register */
    __IO uint32_t ISPR[1];
    uint32_t RESERVED2[31];
    /* Offset: 0x180 (R/W) Interrupt Clear Pending Register */
    __IO uint32_t ICPR[1];
       uint32_t RESERVED3[31];
    uint32_t RESERVED4[64];
    /* Offset: 0x300 (R/W) Interrupt Priority Register */
    __IO uint32_t IP[8];
}  NVIC_Type;

/**
 * Structure type to access the System Control Block (SCB).
 */
typedef struct {
    /* Offset: 0x000 (R/ ) CPUID Base Register */
    __I  uint32_t CPUID;
    /* Offset: 0x004 (R/W) Interrupt Control and State Register */
    __IO uint32_t ICSR;
    uint32_t RESERVED0;
    /* Offset: 0x00C (R/W) Application Interrupt and Reset Control Register */
    __IO uint32_t AIRCR;
    /* Offset: 0x010 (R/W) System Control Register */
    __IO uint32_t SCR;
    /* Offset: 0x014 (R/W) Configuration Control Register */
    __IO uint32_t CCR;
    uint32_t RESERVED1;
    /* Offset: 0x01C (R/W) System Handlers Priority Regs. [0] is RESERVED */
    __IO uint32_t SHP[2];
    /* Offset: 0x024 (R/W)  System Handler Control and State Register */
    __IO uint32_t SHCSR;
} SCB_Type;

/* SCB CPUID Register Definitions */
#define SCB_CPUID_IMPLEMENTER_Pos 24
#define SCB_CPUID_IMPLEMENTER_Msk (0xFFUL << SCB_CPUID_IMPLEMENTER_Pos)

#define SCB_CPUID_VARIANT_Pos 20
#define SCB_CPUID_VARIANT_Msk (0xFUL << SCB_CPUID_VARIANT_Pos)

#define SCB_CPUID_ARCHITECTURE_Pos 16
#define SCB_CPUID_ARCHITECTURE_Msk (0xFUL << SCB_CPUID_ARCHITECTURE_Pos)

#define SCB_CPUID_PARTNO_Pos 4
#define SCB_CPUID_PARTNO_Msk (0xFFFUL << SCB_CPUID_PARTNO_Pos)

#define SCB_CPUID_REVISION_Pos 0
#define SCB_CPUID_REVISION_Msk (0xFUL << SCB_CPUID_REVISION_Pos)

/* SCB Interrupt Control State Register Definitions */
#define SCB_ICSR_NMIPENDSET_Pos 31
#define SCB_ICSR_NMIPENDSET_Msk (1UL << SCB_ICSR_NMIPENDSET_Pos)

#define SCB_ICSR_PENDSVSET_Pos 28
#define SCB_ICSR_PENDSVSET_Msk (1UL << SCB_ICSR_PENDSVSET_Pos)

#define SCB_ICSR_PENDSVCLR_Pos 27
#define SCB_ICSR_PENDSVCLR_Msk (1UL << SCB_ICSR_PENDSVCLR_Pos)

#define SCB_ICSR_PENDSTSET_Pos 26
#define SCB_ICSR_PENDSTSET_Msk (1UL << SCB_ICSR_PENDSTSET_Pos)

#define SCB_ICSR_PENDSTCLR_Pos 25
#define SCB_ICSR_PENDSTCLR_Msk (1UL << SCB_ICSR_PENDSTCLR_Pos)

#define SCB_ICSR_ISRPREEMPT_Pos 23
#define SCB_ICSR_ISRPREEMPT_Msk (1UL << SCB_ICSR_ISRPREEMPT_Pos)

#define SCB_ICSR_ISRPENDING_Pos 22
#define SCB_ICSR_ISRPENDING_Msk (1UL << SCB_ICSR_ISRPENDING_Pos)

#define SCB_ICSR_VECTPENDING_Pos 12
#define SCB_ICSR_VECTPENDING_Msk (0x1FFUL << SCB_ICSR_VECTPENDING_Pos)

#define SCB_ICSR_VECTACTIVE_Pos 0
#define SCB_ICSR_VECTACTIVE_Msk (0x1FFUL << SCB_ICSR_VECTACTIVE_Pos)

/* SCB Application Interrupt and Reset Control Register Definitions */
#define SCB_AIRCR_VECTKEY_Pos 16
#define SCB_AIRCR_VECTKEY_Msk (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)

#define SCB_AIRCR_VECTKEYSTAT_Pos 16
#define SCB_AIRCR_VECTKEYSTAT_Msk (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_Pos)

#define SCB_AIRCR_ENDIANESS_Pos 15
#define SCB_AIRCR_ENDIANESS_Msk (1UL << SCB_AIRCR_ENDIANESS_Pos)

#define SCB_AIRCR_SYSRESETREQ_Pos 2
#define SCB_AIRCR_SYSRESETREQ_Msk (1UL << SCB_AIRCR_SYSRESETREQ_Pos)

#define SCB_AIRCR_VECTCLRACTIVE_Pos 1
#define SCB_AIRCR_VECTCLRACTIVE_Msk (1UL << SCB_AIRCR_VECTCLRACTIVE_Pos)

/* SCB System Control Register Definitions */
#define SCB_SCR_SEVONPEND_Pos 4
#define SCB_SCR_SEVONPEND_Msk (1UL << SCB_SCR_SEVONPEND_Pos)

#define SCB_SCR_SLEEPDEEP_Pos 2
#define SCB_SCR_SLEEPDEEP_Msk (1UL << SCB_SCR_SLEEPDEEP_Pos)

#define SCB_SCR_SLEEPONEXIT_Pos 1
#define SCB_SCR_SLEEPONEXIT_Msk (1UL << SCB_SCR_SLEEPONEXIT_Pos)

/* SCB Configuration Control Register Definitions */
#define SCB_CCR_STKALIGN_Pos 9
#define SCB_CCR_STKALIGN_Msk (1UL << SCB_CCR_STKALIGN_Pos)

#define SCB_CCR_UNALIGN_TRP_Pos 3
#define SCB_CCR_UNALIGN_TRP_Msk (1UL << SCB_CCR_UNALIGN_TRP_Pos)

/* SCB System Handler Control and State Register Definitions */
#define SCB_SHCSR_SVCALLPENDED_Pos 15
#define SCB_SHCSR_SVCALLPENDED_Msk (1UL << SCB_SHCSR_SVCALLPENDED_Pos)

/**
 *   Structure type to access the System Timer (SysTick).
 */
typedef struct {
    /* Offset: 0x000 (R/W) SysTick Control and Status Register */
    __IO uint32_t CTRL;
    /* Offset: 0x004 (R/W) SysTick Reload Value Register */
    __IO uint32_t LOAD;
    /* Offset: 0x008 (R/W) SysTick Current Value Register */
    __IO uint32_t VAL;
    /* Offset: 0x00C (R/ ) SysTick Calibration Register */
    __I  uint32_t CALIB;
} SysTick_Type;

/* SysTick Control / Status Register Definitions */
#define SysTick_CTRL_COUNTFLAG_Pos 16
#define SysTick_CTRL_COUNTFLAG_Msk (1UL << SysTick_CTRL_COUNTFLAG_Pos)

#define SysTick_CTRL_CLKSOURCE_Pos 2
#define SysTick_CTRL_CLKSOURCE_Msk (1UL << SysTick_CTRL_CLKSOURCE_Pos)

#define SysTick_CTRL_TICKINT_Pos 1
#define SysTick_CTRL_TICKINT_Msk (1UL << SysTick_CTRL_TICKINT_Pos)

#define SysTick_CTRL_ENABLE_Pos 0
#define SysTick_CTRL_ENABLE_Msk (1UL << SysTick_CTRL_ENABLE_Pos)

/* SysTick Reload Register Definitions */
#define SysTick_LOAD_RELOAD_Pos 0
#define SysTick_LOAD_RELOAD_Msk (0xFFFFFFUL << SysTick_LOAD_RELOAD_Pos)

/* SysTick Current Register Definitions */
#define SysTick_VAL_CURRENT_Pos 0
#define SysTick_VAL_CURRENT_Msk (0xFFFFFFUL << SysTick_VAL_CURRENT_Pos)

/* SysTick Calibration Register Definitions */
#define SysTick_CALIB_NOREF_Pos 31
#define SysTick_CALIB_NOREF_Msk (1UL << SysTick_CALIB_NOREF_Pos)

#define SysTick_CALIB_SKEW_Pos 30
#define SysTick_CALIB_SKEW_Msk (1UL << SysTick_CALIB_SKEW_Pos)

#define SysTick_CALIB_TENMS_Pos 0
#define SysTick_CALIB_TENMS_Msk (0xFFFFFFUL << SysTick_VAL_CURRENT_Pos)

/* Memory mapping of Cortex-M0 Hardware */
#define SCS_BASE (0xE000E000UL)
#define CoreDebug_BASE (0xE000EDF0UL)
#define SysTick_BASE (SCS_BASE + 0x0010UL)
#define NVIC_BASE (SCS_BASE + 0x0100UL)
#define SCB_BASE (SCS_BASE + 0x0D00UL)

#define SCB ((SCB_Type *) SCB_BASE)
#define SysTick ((SysTick_Type *) SysTick_BASE)
#define NVIC ((NVIC_Type *) NVIC_BASE)

/* Interrupt Priorities are WORD accessible only under ARMv6M */
/* Following MACROS handle generation of the register offset and byte masks */
#define _BIT_SHIFT(IRQn) ((((uint32_t)(IRQn)) & 0x03) * 8)
#define _SHP_IDX(IRQn) (((((uint32_t)(IRQn) & 0x0F)-8) >> 2))
#define _IP_IDX(IRQn) (((uint32_t)(IRQn) >> 2))

/**
 * Enable External Interrupt
 * This function enables a device specific interrupt in the NVIC
 * interrupt controller. The interrupt number cannot be a negative value.
 * param IRQn Number of the external interrupt to enable
 */
static __INLINE void NVIC_EnableIRQ(IRQn_Type IRQn) {
    NVIC->ISER[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Disable External Interrupt
 * This function disables a device specific interrupt in the NVIC
 * interrupt controller. The interrupt number cannot be a negative value.
 * param IRQn Number of the external interrupt to disable
 */
static __INLINE void NVIC_DisableIRQ(IRQn_Type IRQn) {
    NVIC->ICER[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Get Pending Interrupt
 * This function reads the pending register in the NVIC and returns
 * the pending bit for the specified interrupt.
 * param IRQn  Number of the interrupt for get pending
 * return 0 Interrupt status is not pending
 * return 1 Interrupt status is pending
 */
static __INLINE uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn) {
    return (
        (uint32_t) ((NVIC->ISPR[0] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0)
    );
}

/**
 * Set Pending Interrupt
 * This function sets the pending bit for the specified interrupt.
 * The interrupt number cannot be a negative value.
 * param IRQn Number of the interrupt for set pending
 */
static __INLINE void NVIC_SetPendingIRQ(IRQn_Type IRQn) {
    NVIC->ISPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Clear Pending Interrupt
 * This function clears the pending bit for the specified interrupt.
 * The interrupt number cannot be a negative value.
 * param IRQn  Number of the interrupt for clear pending
 */
static __INLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn) {
    NVIC->ICPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Set Interrupt Priority
 * This function sets the priority for the specified interrupt.
 * Interrupt number can be positive to specify an external (device specific)
 * interrupt, or negative to specify an internal (core) interrupt.
 * Note: The priority cannot be set for every core interrupt.
 * param IRQn  Number of the interrupt for set priority
 * param priority  Priority to set
 */
static __INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority) {
    if (IRQn < 0) {
        SCB->SHP[_SHP_IDX(IRQn)] = (
            SCB->SHP[_SHP_IDX(IRQn)] & ~(0xFF << _BIT_SHIFT(IRQn))
        ) | (
            ((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(IRQn)
        );
    } else {
        NVIC->IP[_IP_IDX(IRQn)] = (
            NVIC->IP[_IP_IDX(IRQn)] & ~(0xFF << _BIT_SHIFT(IRQn))
        ) | (
            ((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(IRQn)
        );
    }
}

/**
 * Get Interrupt Priority
 * This function reads the priority for the specified interrupt.
 * Interrupt number can be positive to specify an external (device specific)
 * interrupt, or negative to specify an internal (core) interrupt.
 * The returned priority value is automatically aligned to the implemented
 * priority bits of the microcontroller.
 * param IRQn  Number of the interrupt for get priority
 * return Interrupt Priority
 */
static __INLINE uint32_t NVIC_GetPriority(IRQn_Type IRQn) {
    if(IRQn < 0) {
        /* get priority for Cortex-M0 system interrupts */
        return (
            (uint32_t) (
                (SCB->SHP[_SHP_IDX(IRQn)] >> _BIT_SHIFT(IRQn)) >>
                (8 - __NVIC_PRIO_BITS)
            )
        );
    } else {
        /* get priority for device specific interrupts */
        return (
            (uint32_t) (
                (NVIC->IP[ _IP_IDX(IRQn)] >> _BIT_SHIFT(IRQn) ) >>
                (8 - __NVIC_PRIO_BITS)
            )
        );
    }
}

/**
 * System Reset
 * This function initiate a system reset request to reset the MCU.
 */
static __INLINE void NVIC_SystemReset(void) {
    /**
     * Ensure all outstanding memory accesses included buffered write
     * are completed before reset.
     */
    __DSB();
    SCB->AIRCR  = (
        (0x5FA << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk
    );
    __DSB(); /* Ensure completion of memory access */
    while(1); /* wait until reset */
}

#if (__Vendor_SysTickConfig == 0)

/**
 * System Tick Configuration
 * This function initialises the system tick timer and its interrupt
 * and start the system tick timer.Counter is in free running mode to
 * generate periodical interrupts.
 * param ticks Number of ticks between two interrupts
 * return 0 Function succeeded
 * return 1 Function failed
 */
static __INLINE uint32_t SysTick_Config(uint32_t ticks) {
    if (ticks > SysTick_LOAD_RELOAD_Msk) {
        return (1);
    }
    SysTick->LOAD = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;
    /* set Priority for Cortex-M0 System Interrupts */
    NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
    SysTick->VAL = 0; /* Load the SysTick Counter Value */
    SysTick->CTRL = (
        SysTick_CTRL_CLKSOURCE_Msk |
        SysTick_CTRL_TICKINT_Msk |
        SysTick_CTRL_ENABLE_Msk
    );
    /* Enable SysTick IRQ and SysTick Timer */
  return (0);
}

#endif

#endif

#endif

#ifdef __cplusplus
    }
#endif

