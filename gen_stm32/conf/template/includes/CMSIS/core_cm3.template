/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * core_cm3.h
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

#ifndef __CORE_CM3_H_GENERIC
#define __CORE_CM3_H_GENERIC

/**
 * CMSIS Cortex-M3
 * 
 * Documentation describes the CMSIS Cortex-M Core Peripheral Access Layer.
 * It consists of:
 * 
 *    - Cortex-M Core Register Definitions
 *    - Cortex-M functions
 *    - Cortex-M instructions
 * 
 * The CMSIS Cortex-M3 Core Peripheral Access Layer contains C and assembly
 * functions that ease access to the Cortex-M Core
 * 
 * CMSIS violates following MISRA-C2004 Rules:
 * 
 *  - Violates MISRA 2004 Required Rule 8.5, object/function definition
 *    in header file. Function definitions in header files are used to
 *    allow 'inlining'.
 * 
 *  - Violates MISRA 2004 Required Rule 18.4, declaration of union type
 *    or object of union type: '{...}'. Unions are used for effective
 *    representation of core registers.
 * 
 *  - Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
 *    Function-like macros are used to allow more efficient code.
 * 
 * This file defines all structures and symbols for CMSIS core:
 *  - CMSIS version number
 *  - Cortex-M core
 *  - Cortex-M core Revision Number
 */

/* CMSIS CM3 definitions */
#define __CM3_CMSIS_VERSION_MAIN (0x02)
#define __CM3_CMSIS_VERSION_SUB (0x10)
#define __CM3_CMSIS_VERSION ( \
    (__CM3_CMSIS_VERSION_MAIN << 16) | __CM3_CMSIS_VERSION_SUB \
)

#define __CORTEX_M (0x03)

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
 * __FPU_USED to be checked prior to making use of FPU
 * specific registers and functions.
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

#ifndef __CORE_CM3_H_DEPENDANT
#define __CORE_CM3_H_DEPENDANT

/* check device defines and use defaults */
#if defined __CHECK_DEVICE_DEFINES
    #ifndef __CM3_REV
        #define __CM3_REV 0x0200
        #warning "__CM3_REV not defined in device header file"
        #warning "Using default!"
    #endif
    #ifndef __MPU_PRESENT
        #define __MPU_PRESENT 0
        #warning "__MPU_PRESENT not defined in device header file"
        #warning "Using default!"
    #endif
    #ifndef __NVIC_PRIO_BITS
        #define __NVIC_PRIO_BITS 4
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
  Core Register contain:
  - Core Register
  - Core NVIC Register
  - Core SCB Register
  - Core SysTick Register
  - Core Debug Register
  - Core MPU Register
*/

/**
 * Union type to access the Application Program Status Register (APSR).
 */
typedef union {
    struct {
#if (__CORTEX_M != 0x04)
        /* bit:  0..26 Reserved */
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
    /* Type used for word access */
    uint32_t w;
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
    /* Type used for word access */
    uint32_t w;
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
        /* bit: 25.26 saved IT state (read 0) */
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
    /* Type used for word access */
    uint32_t w;
} xPSR_Type;

/**
 * Union type to access the Control Registers (CONTROL).
 */
typedef union {
    struct {
        /* bit: 0 Execution privilege in Thread mode */
        uint32_t nPRIV:1;
        /* bit: 1 Stack to be used */
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
    __IO uint32_t ISER[8];
    uint32_t RESERVED0[24];
    /* Offset: 0x080 (R/W) Interrupt Clear Enable Register */
    __IO uint32_t ICER[8];
    uint32_t RSERVED1[24];
    /* Offset: 0x100 (R/W) Interrupt Set Pending Register */
    __IO uint32_t ISPR[8];
    uint32_t RESERVED2[24];
    /* Offset: 0x180 (R/W) Interrupt Clear Pending Register */
    __IO uint32_t ICPR[8];
    uint32_t RESERVED3[24];
    /* Offset: 0x200 (R/W) Interrupt Active bit Register */
    __IO uint32_t IABR[8];
    uint32_t RESERVED4[56];
    /* Offset: 0x300 (R/W) Interrupt Priority Register (8Bit wide) */
    __IO uint8_t  IP[240];
    uint32_t RESERVED5[644];
    /* Offset: 0xE00 ( /W) Software Trigger Interrupt Register */
    __O  uint32_t STIR;
}  NVIC_Type;

/* Software Triggered Interrupt Register Definitions */
#define NVIC_STIR_INTID_Pos 0
#define NVIC_STIR_INTID_Msk (0x1FFUL << NVIC_STIR_INTID_Pos)

/**
 * Structure type to access the System Control Block (SCB).
 */
typedef struct {
    /* Offset: 0x000 (R/ ) CPUID Base Register */
    __I  uint32_t CPUID;
    /* Offset: 0x004 (R/W) Interrupt Control and State Register */
    __IO uint32_t ICSR;
    /* Offset: 0x008 (R/W) Vector Table Offset Register */
    __IO uint32_t VTOR;
    /* Offset: 0x00C (R/W) Application Interrupt and Reset Control Register */
    __IO uint32_t AIRCR;
    /* Offset: 0x010 (R/W) System Control Register */
    __IO uint32_t SCR;
    /* Offset: 0x014 (R/W) Configuration Control Register */
    __IO uint32_t CCR;
    /* Offset: 0x018 (R/W) System Handlers Priority Regs (4-7, 8-11, 12-15) */
    __IO uint8_t  SHP[12];
    /* Offset: 0x024 (R/W) System Handler Control and State Register */
    __IO uint32_t SHCSR;
    /* Offset: 0x028 (R/W) Configurable Fault Status Register */
    __IO uint32_t CFSR;
    /* Offset: 0x02C (R/W) HardFault Status Register */
    __IO uint32_t HFSR;
    /* Offset: 0x030 (R/W) Debug Fault Status Register */
    __IO uint32_t DFSR;
    /* Offset: 0x034 (R/W) MemManage Fault Address Register */
    __IO uint32_t MMFAR;
    /* Offset: 0x038 (R/W) BusFault Address Register */
    __IO uint32_t BFAR;
    /* Offset: 0x03C (R/W) Auxiliary Fault Status Register */
    __IO uint32_t AFSR;
    /* Offset: 0x040 (R/ ) Processor Feature Register */
    __I  uint32_t PFR[2];
    /* Offset: 0x048 (R/ ) Debug Feature Register */
    __I  uint32_t DFR;
    /* Offset: 0x04C (R/ ) Auxiliary Feature Register */
    __I  uint32_t ADR;
    /* Offset: 0x050 (R/ ) Memory Model Feature Register */
    __I  uint32_t MMFR[4];
    /* Offset: 0x060 (R/ ) Instruction Set Attributes Register */
    __I  uint32_t ISAR[5];
    uint32_t RESERVED0[5];
    /* Offset: 0x088 (R/W) Coprocessor Access Control Register */
    __IO uint32_t CPACR;
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

#define SCB_ICSR_RETTOBASE_Pos 11
#define SCB_ICSR_RETTOBASE_Msk (1UL << SCB_ICSR_RETTOBASE_Pos)

#define SCB_ICSR_VECTACTIVE_Pos 0
#define SCB_ICSR_VECTACTIVE_Msk (0x1FFUL << SCB_ICSR_VECTACTIVE_Pos)

/* SCB Vector Table Offset Register Definitions */
#define SCB_VTOR_TBLOFF_Pos 7
#define SCB_VTOR_TBLOFF_Msk (0x1FFFFFFUL << SCB_VTOR_TBLOFF_Pos)

/* SCB Application Interrupt and Reset Control Register Definitions */
#define SCB_AIRCR_VECTKEY_Pos 16
#define SCB_AIRCR_VECTKEY_Msk (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)

#define SCB_AIRCR_VECTKEYSTAT_Pos 16
#define SCB_AIRCR_VECTKEYSTAT_Msk (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_Pos)

#define SCB_AIRCR_ENDIANESS_Pos 15
#define SCB_AIRCR_ENDIANESS_Msk (1UL << SCB_AIRCR_ENDIANESS_Pos)

#define SCB_AIRCR_PRIGROUP_Pos 8
#define SCB_AIRCR_PRIGROUP_Msk (7UL << SCB_AIRCR_PRIGROUP_Pos)

#define SCB_AIRCR_SYSRESETREQ_Pos 2
#define SCB_AIRCR_SYSRESETREQ_Msk (1UL << SCB_AIRCR_SYSRESETREQ_Pos)

#define SCB_AIRCR_VECTCLRACTIVE_Pos 1
#define SCB_AIRCR_VECTCLRACTIVE_Msk (1UL << SCB_AIRCR_VECTCLRACTIVE_Pos)

#define SCB_AIRCR_VECTRESET_Pos 0
#define SCB_AIRCR_VECTRESET_Msk (1UL << SCB_AIRCR_VECTRESET_Pos)

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

#define SCB_CCR_BFHFNMIGN_Pos 8
#define SCB_CCR_BFHFNMIGN_Msk (1UL << SCB_CCR_BFHFNMIGN_Pos)

#define SCB_CCR_DIV_0_TRP_Pos 4
#define SCB_CCR_DIV_0_TRP_Msk (1UL << SCB_CCR_DIV_0_TRP_Pos)

#define SCB_CCR_UNALIGN_TRP_Pos 3
#define SCB_CCR_UNALIGN_TRP_Msk (1UL << SCB_CCR_UNALIGN_TRP_Pos)

#define SCB_CCR_USERSETMPEND_Pos 1
#define SCB_CCR_USERSETMPEND_Msk (1UL << SCB_CCR_USERSETMPEND_Pos)

#define SCB_CCR_NONBASETHRDENA_Pos 0
#define SCB_CCR_NONBASETHRDENA_Msk (1UL << SCB_CCR_NONBASETHRDENA_Pos)

/* SCB System Handler Control and State Register Definitions */
#define SCB_SHCSR_USGFAULTENA_Pos 18
#define SCB_SHCSR_USGFAULTENA_Msk (1UL << SCB_SHCSR_USGFAULTENA_Pos)

#define SCB_SHCSR_BUSFAULTENA_Pos 17
#define SCB_SHCSR_BUSFAULTENA_Msk (1UL << SCB_SHCSR_BUSFAULTENA_Pos)

#define SCB_SHCSR_MEMFAULTENA_Pos 16
#define SCB_SHCSR_MEMFAULTENA_Msk (1UL << SCB_SHCSR_MEMFAULTENA_Pos)

#define SCB_SHCSR_SVCALLPENDED_Pos 15
#define SCB_SHCSR_SVCALLPENDED_Msk (1UL << SCB_SHCSR_SVCALLPENDED_Pos)

#define SCB_SHCSR_BUSFAULTPENDED_Pos 14
#define SCB_SHCSR_BUSFAULTPENDED_Msk (1UL << SCB_SHCSR_BUSFAULTPENDED_Pos)

#define SCB_SHCSR_MEMFAULTPENDED_Pos 13
#define SCB_SHCSR_MEMFAULTPENDED_Msk (1UL << SCB_SHCSR_MEMFAULTPENDED_Pos)

#define SCB_SHCSR_USGFAULTPENDED_Pos 12
#define SCB_SHCSR_USGFAULTPENDED_Msk (1UL << SCB_SHCSR_USGFAULTPENDED_Pos)

#define SCB_SHCSR_SYSTICKACT_Pos 11
#define SCB_SHCSR_SYSTICKACT_Msk (1UL << SCB_SHCSR_SYSTICKACT_Pos)

#define SCB_SHCSR_PENDSVACT_Pos 10
#define SCB_SHCSR_PENDSVACT_Msk (1UL << SCB_SHCSR_PENDSVACT_Pos)

#define SCB_SHCSR_MONITORACT_Pos 8
#define SCB_SHCSR_MONITORACT_Msk (1UL << SCB_SHCSR_MONITORACT_Pos)

#define SCB_SHCSR_SVCALLACT_Pos 7
#define SCB_SHCSR_SVCALLACT_Msk (1UL << SCB_SHCSR_SVCALLACT_Pos)

#define SCB_SHCSR_USGFAULTACT_Pos 3
#define SCB_SHCSR_USGFAULTACT_Msk (1UL << SCB_SHCSR_USGFAULTACT_Pos)

#define SCB_SHCSR_BUSFAULTACT_Pos 1
#define SCB_SHCSR_BUSFAULTACT_Msk (1UL << SCB_SHCSR_BUSFAULTACT_Pos)

#define SCB_SHCSR_MEMFAULTACT_Pos 0
#define SCB_SHCSR_MEMFAULTACT_Msk (1UL << SCB_SHCSR_MEMFAULTACT_Pos)

/* SCB Configurable Fault Status Registers Definitions */
#define SCB_CFSR_USGFAULTSR_Pos 16
#define SCB_CFSR_USGFAULTSR_Msk (0xFFFFUL << SCB_CFSR_USGFAULTSR_Pos)

#define SCB_CFSR_BUSFAULTSR_Pos 8
#define SCB_CFSR_BUSFAULTSR_Msk (0xFFUL << SCB_CFSR_BUSFAULTSR_Pos)

#define SCB_CFSR_MEMFAULTSR_Pos 0
#define SCB_CFSR_MEMFAULTSR_Msk (0xFFUL << SCB_CFSR_MEMFAULTSR_Pos)

/* SCB Hard Fault Status Registers Definitions */
#define SCB_HFSR_DEBUGEVT_Pos 31
#define SCB_HFSR_DEBUGEVT_Msk (1UL << SCB_HFSR_DEBUGEVT_Pos)

#define SCB_HFSR_FORCED_Pos 30
#define SCB_HFSR_FORCED_Msk (1UL << SCB_HFSR_FORCED_Pos)

#define SCB_HFSR_VECTTBL_Pos 1
#define SCB_HFSR_VECTTBL_Msk (1UL << SCB_HFSR_VECTTBL_Pos)

/* SCB Debug Fault Status Register Definitions */
#define SCB_DFSR_EXTERNAL_Pos 4
#define SCB_DFSR_EXTERNAL_Msk (1UL << SCB_DFSR_EXTERNAL_Pos)

#define SCB_DFSR_VCATCH_Pos 3
#define SCB_DFSR_VCATCH_Msk (1UL << SCB_DFSR_VCATCH_Pos)

#define SCB_DFSR_DWTTRAP_Pos 2
#define SCB_DFSR_DWTTRAP_Msk (1UL << SCB_DFSR_DWTTRAP_Pos)

#define SCB_DFSR_BKPT_Pos 1
#define SCB_DFSR_BKPT_Msk (1UL << SCB_DFSR_BKPT_Pos)

#define SCB_DFSR_HALTED_Pos 0
#define SCB_DFSR_HALTED_Msk (1UL << SCB_DFSR_HALTED_Pos)

/**
 * Structure type to access the System Control and ID Register not in the SCB.
 */
typedef struct {
    uint32_t RESERVED0[1];
    /* Offset: 0x004 (R/ ) Interrupt Controller Type Register */
    __I  uint32_t ICTR;
#if ((defined __CM3_REV) && (__CM3_REV >= 0x200))
    /* Offset: 0x008 (R/W) Auxiliary Control Register */
    __IO uint32_t ACTLR;
#else
    uint32_t RESERVED1[1];
#endif
} SCnSCB_Type;

/* Interrupt Controller Type Register Definitions */
#define SCnSCB_ICTR_INTLINESNUM_Pos 0
#define SCnSCB_ICTR_INTLINESNUM_Msk (0xFUL << SCnSCB_ICTR_INTLINESNUM_Pos)

/* Auxiliary Control Register Definitions */
#define SCnSCB_ACTLR_DISFOLD_Pos 2
#define SCnSCB_ACTLR_DISFOLD_Msk (1UL << SCnSCB_ACTLR_DISFOLD_Pos)

#define SCnSCB_ACTLR_DISDEFWBUF_Pos 1
#define SCnSCB_ACTLR_DISDEFWBUF_Msk (1UL << SCnSCB_ACTLR_DISDEFWBUF_Pos)

#define SCnSCB_ACTLR_DISMCYCINT_Pos 0
#define SCnSCB_ACTLR_DISMCYCINT_Msk (1UL << SCnSCB_ACTLR_DISMCYCINT_Pos)

/**
 * Structure type to access the System Timer (SysTick).
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

/**
 * Structure type to access the Instrumentation Trace Macrocell Register (ITM).
 */
typedef struct {
    __O  union {
        /* Offset: 0x000 ( /W) ITM Stimulus Port 8-bit */
        __O  uint8_t u8;
        /* Offset: 0x000 ( /W) ITM Stimulus Port 16-bit */
        __O  uint16_t u16;
        /* Offset: 0x000 ( /W) ITM Stimulus Port 32-bit */
        __O  uint32_t u32;
    }  PORT [32]; /* Offset: 0x000 ( /W) ITM Stimulus Port Registers */
    uint32_t RESERVED0[864];
    /* Offset: 0xE00 (R/W) ITM Trace Enable Register */
    __IO uint32_t TER;
    uint32_t RESERVED1[15];
    /* Offset: 0xE40 (R/W) ITM Trace Privilege Register */
    __IO uint32_t TPR;
    uint32_t RESERVED2[15];
    /* Offset: 0xE80 (R/W) ITM Trace Control Register */
    __IO uint32_t TCR;
} ITM_Type;

/* ITM Trace Privilege Register Definitions */
#define ITM_TPR_PRIVMASK_Pos 0
#define ITM_TPR_PRIVMASK_Msk (0xFUL << ITM_TPR_PRIVMASK_Pos)

/* ITM Trace Control Register Definitions */
#define ITM_TCR_BUSY_Pos 23
#define ITM_TCR_BUSY_Msk (1UL << ITM_TCR_BUSY_Pos)

#define ITM_TCR_TraceBusID_Pos 16
#define ITM_TCR_TraceBusID_Msk (0x7FUL << ITM_TCR_TraceBusID_Pos)

#define ITM_TCR_GTSFREQ_Pos 10
#define ITM_TCR_GTSFREQ_Msk (3UL << ITM_TCR_GTSFREQ_Pos)

#define ITM_TCR_TSPrescale_Pos 8
#define ITM_TCR_TSPrescale_Msk (3UL << ITM_TCR_TSPrescale_Pos)

#define ITM_TCR_SWOENA_Pos 4
#define ITM_TCR_SWOENA_Msk (1UL << ITM_TCR_SWOENA_Pos)

#define ITM_TCR_TXENA_Pos 3
#define ITM_TCR_TXENA_Msk (1UL << ITM_TCR_TXENA_Pos)

#define ITM_TCR_SYNCENA_Pos 2
#define ITM_TCR_SYNCENA_Msk (1UL << ITM_TCR_SYNCENA_Pos)

#define ITM_TCR_TSENA_Pos 1
#define ITM_TCR_TSENA_Msk (1UL << ITM_TCR_TSENA_Pos)

#define ITM_TCR_ITMENA_Pos 0
#define ITM_TCR_ITMENA_Msk (1UL << ITM_TCR_ITMENA_Pos)

#if (__MPU_PRESENT == 1)

/**
 * Structure type to access the Memory Protection Unit (MPU).
 */
typedef struct {
    /* Offset: 0x000 (R/ ) MPU Type Register */
    __I  uint32_t TYPE;
    /* Offset: 0x004 (R/W) MPU Control Register */
    __IO uint32_t CTRL;
    /* Offset: 0x008 (R/W) MPU Region RNRber Register */
    __IO uint32_t RNR;
    /* Offset: 0x00C (R/W) MPU Region Base Address Register */
    __IO uint32_t RBAR;
    /* Offset: 0x010 (R/W) MPU Region Attribute and Size Register */
    __IO uint32_t RASR;
    /* Offset: 0x014 (R/W) MPU Alias 1 Region Base Address Register */
    __IO uint32_t RBAR_A1;
    /* Offset: 0x018 (R/W) MPU Alias 1 Region Attribute and Size Register */
    __IO uint32_t RASR_A1;
    /* Offset: 0x01C (R/W) MPU Alias 2 Region Base Address Register */
    __IO uint32_t RBAR_A2;
    /* Offset: 0x020 (R/W) MPU Alias 2 Region Attribute and Size Register */
    __IO uint32_t RASR_A2;
    /* Offset: 0x024 (R/W) MPU Alias 3 Region Base Address Register */
    __IO uint32_t RBAR_A3;
    /* Offset: 0x028 (R/W) MPU Alias 3 Region Attribute and Size Register */
    __IO uint32_t RASR_A3;
} MPU_Type;

/* MPU Type Register */
#define MPU_TYPE_IREGION_Pos 16
#define MPU_TYPE_IREGION_Msk (0xFFUL << MPU_TYPE_IREGION_Pos)

#define MPU_TYPE_DREGION_Pos 8
#define MPU_TYPE_DREGION_Msk (0xFFUL << MPU_TYPE_DREGION_Pos)

#define MPU_TYPE_SEPARATE_Pos 0
#define MPU_TYPE_SEPARATE_Msk (1UL << MPU_TYPE_SEPARATE_Pos)

/* MPU Control Register */
#define MPU_CTRL_PRIVDEFENA_Pos 2
#define MPU_CTRL_PRIVDEFENA_Msk (1UL << MPU_CTRL_PRIVDEFENA_Pos)

#define MPU_CTRL_HFNMIENA_Pos 1
#define MPU_CTRL_HFNMIENA_Msk (1UL << MPU_CTRL_HFNMIENA_Pos)

#define MPU_CTRL_ENABLE_Pos 0
#define MPU_CTRL_ENABLE_Msk (1UL << MPU_CTRL_ENABLE_Pos)

/* MPU Region Number Register */
#define MPU_RNR_REGION_Pos 0
#define MPU_RNR_REGION_Msk (0xFFUL << MPU_RNR_REGION_Pos)

/* MPU Region Base Address Register */
#define MPU_RBAR_ADDR_Pos 5
#define MPU_RBAR_ADDR_Msk (0x7FFFFFFUL << MPU_RBAR_ADDR_Pos)

#define MPU_RBAR_VALID_Pos 4
#define MPU_RBAR_VALID_Msk (1UL << MPU_RBAR_VALID_Pos)

#define MPU_RBAR_REGION_Pos 0
#define MPU_RBAR_REGION_Msk (0xFUL << MPU_RBAR_REGION_Pos)

/* MPU Region Attribute and Size Register */
#define MPU_RASR_ATTRS_Pos 16
#define MPU_RASR_ATTRS_Msk (0xFFFFUL << MPU_RASR_ATTRS_Pos)

#define MPU_RASR_SRD_Pos 8
#define MPU_RASR_SRD_Msk (0xFFUL << MPU_RASR_SRD_Pos)

#define MPU_RASR_SIZE_Pos 1
#define MPU_RASR_SIZE_Msk (0x1FUL << MPU_RASR_SIZE_Pos)

#define MPU_RASR_ENABLE_Pos 0
#define MPU_RASR_ENABLE_Msk (1UL << MPU_RASR_ENABLE_Pos)

#endif

/**
 * Structure type to access the Core Debug Register (CoreDebug).
 */
typedef struct {
    /* Offset: 0x000 (R/W) Debug Halting Control and Status Register */
    __IO uint32_t DHCSR;
    /* Offset: 0x004 ( /W) Debug Core Register Selector Register */
    __O  uint32_t DCRSR;
    /* Offset: 0x008 (R/W) Debug Core Register Data Register */
    __IO uint32_t DCRDR;
    /* Offset: 0x00C (R/W) Debug Exception and Monitor Control Register */
    __IO uint32_t DEMCR;
} CoreDebug_Type;

/* Debug Halting Control and Status Register */
#define CoreDebug_DHCSR_DBGKEY_Pos 16
#define CoreDebug_DHCSR_DBGKEY_Msk (0xFFFFUL << CoreDebug_DHCSR_DBGKEY_Pos)

#define CoreDebug_DHCSR_S_RESET_ST_Pos 25
#define CoreDebug_DHCSR_S_RESET_ST_Msk (1UL << CoreDebug_DHCSR_S_RESET_ST_Pos)

#define CoreDebug_DHCSR_S_RETIRE_ST_Pos 24
#define CoreDebug_DHCSR_S_RETIRE_ST_Msk ( \
    1UL << CoreDebug_DHCSR_S_RETIRE_ST_Pos \
)

#define CoreDebug_DHCSR_S_LOCKUP_Pos 19
#define CoreDebug_DHCSR_S_LOCKUP_Msk (1UL << CoreDebug_DHCSR_S_LOCKUP_Pos)

#define CoreDebug_DHCSR_S_SLEEP_Pos 18
#define CoreDebug_DHCSR_S_SLEEP_Msk (1UL << CoreDebug_DHCSR_S_SLEEP_Pos)

#define CoreDebug_DHCSR_S_HALT_Pos 17
#define CoreDebug_DHCSR_S_HALT_Msk (1UL << CoreDebug_DHCSR_S_HALT_Pos)

#define CoreDebug_DHCSR_S_REGRDY_Pos 16
#define CoreDebug_DHCSR_S_REGRDY_Msk (1UL << CoreDebug_DHCSR_S_REGRDY_Pos)

#define CoreDebug_DHCSR_C_SNAPSTALL_Pos 5
#define CoreDebug_DHCSR_C_SNAPSTALL_Msk ( \
    1UL << CoreDebug_DHCSR_C_SNAPSTALL_Pos \
)

#define CoreDebug_DHCSR_C_MASKINTS_Pos 3
#define CoreDebug_DHCSR_C_MASKINTS_Msk (1UL << CoreDebug_DHCSR_C_MASKINTS_Pos)

#define CoreDebug_DHCSR_C_STEP_Pos 2
#define CoreDebug_DHCSR_C_STEP_Msk (1UL << CoreDebug_DHCSR_C_STEP_Pos)

#define CoreDebug_DHCSR_C_HALT_Pos 1
#define CoreDebug_DHCSR_C_HALT_Msk (1UL << CoreDebug_DHCSR_C_HALT_Pos)

#define CoreDebug_DHCSR_C_DEBUGEN_Pos 0
#define CoreDebug_DHCSR_C_DEBUGEN_Msk (1UL << CoreDebug_DHCSR_C_DEBUGEN_Pos)

/* Debug Core Register Selector Register */
#define CoreDebug_DCRSR_REGWnR_Pos 16
#define CoreDebug_DCRSR_REGWnR_Msk (1UL << CoreDebug_DCRSR_REGWnR_Pos)

#define CoreDebug_DCRSR_REGSEL_Pos 0
#define CoreDebug_DCRSR_REGSEL_Msk (0x1FUL << CoreDebug_DCRSR_REGSEL_Pos)

/* Debug Exception and Monitor Control Register */
#define CoreDebug_DEMCR_TRCENA_Pos 24
#define CoreDebug_DEMCR_TRCENA_Msk (1UL << CoreDebug_DEMCR_TRCENA_Pos)

#define CoreDebug_DEMCR_MON_REQ_Pos 19
#define CoreDebug_DEMCR_MON_REQ_Msk (1UL << CoreDebug_DEMCR_MON_REQ_Pos)

#define CoreDebug_DEMCR_MON_STEP_Pos 18
#define CoreDebug_DEMCR_MON_STEP_Msk (1UL << CoreDebug_DEMCR_MON_STEP_Pos)

#define CoreDebug_DEMCR_MON_PEND_Pos 17
#define CoreDebug_DEMCR_MON_PEND_Msk (1UL << CoreDebug_DEMCR_MON_PEND_Pos)

#define CoreDebug_DEMCR_MON_EN_Pos 16
#define CoreDebug_DEMCR_MON_EN_Msk (1UL << CoreDebug_DEMCR_MON_EN_Pos)

#define CoreDebug_DEMCR_VC_HARDERR_Pos 10
#define CoreDebug_DEMCR_VC_HARDERR_Msk (1UL << CoreDebug_DEMCR_VC_HARDERR_Pos)

#define CoreDebug_DEMCR_VC_INTERR_Pos 9
#define CoreDebug_DEMCR_VC_INTERR_Msk (1UL << CoreDebug_DEMCR_VC_INTERR_Pos)

#define CoreDebug_DEMCR_VC_BUSERR_Pos 8
#define CoreDebug_DEMCR_VC_BUSERR_Msk (1UL << CoreDebug_DEMCR_VC_BUSERR_Pos)

#define CoreDebug_DEMCR_VC_STATERR_Pos 7
#define CoreDebug_DEMCR_VC_STATERR_Msk (1UL << CoreDebug_DEMCR_VC_STATERR_Pos)

#define CoreDebug_DEMCR_VC_CHKERR_Pos 6
#define CoreDebug_DEMCR_VC_CHKERR_Msk (1UL << CoreDebug_DEMCR_VC_CHKERR_Pos)

#define CoreDebug_DEMCR_VC_NOCPERR_Pos 5
#define CoreDebug_DEMCR_VC_NOCPERR_Msk (1UL << CoreDebug_DEMCR_VC_NOCPERR_Pos)

#define CoreDebug_DEMCR_VC_MMERR_Pos 4
#define CoreDebug_DEMCR_VC_MMERR_Msk (1UL << CoreDebug_DEMCR_VC_MMERR_Pos)

#define CoreDebug_DEMCR_VC_CORERESET_Pos 0
#define CoreDebug_DEMCR_VC_CORERESET_Msk ( \
    1UL << CoreDebug_DEMCR_VC_CORERESET_Pos \
)

/* Memory mapping of Cortex-M3 Hardware */
#define SCS_BASE (0xE000E000UL)
#define ITM_BASE (0xE0000000UL)
#define CoreDebug_BASE (0xE000EDF0UL)
#define SysTick_BASE (SCS_BASE + 0x0010UL)
#define NVIC_BASE (SCS_BASE + 0x0100UL)
#define SCB_BASE (SCS_BASE + 0x0D00UL)

#define SCnSCB ((SCnSCB_Type *) SCS_BASE)
#define SCB ((SCB_Type *) SCB_BASE)
#define SysTick ((SysTick_Type *) SysTick_BASE)
#define NVIC ((NVIC_Type *) NVIC_BASE)
#define ITM ((ITM_Type *) ITM_BASE)
#define CoreDebug ((CoreDebug_Type *) CoreDebug_BASE)

#if (__MPU_PRESENT == 1)
    #define MPU_BASE (SCS_BASE + 0x0D90UL)
    #define MPU ((MPU_Type *) MPU_BASE)
#endif

/**
 * Core Function Interface contains:
 * - Core NVIC Functions
 * - Core SysTick Functions
 * - Core Debug Functions
 * - Core Register Access Functions
 */

/**
 * Set Priority Grouping
 * Function sets priority grouping field using the required unlock sequence.
 * Parameter PriorityGroup is assigned to SCB->AIRCR [10:8] PRIGROUP field.
 * Only values from 0..7 are used.
 * In case of a conflict between priority grouping and available priority
 * bits (__NVIC_PRIO_BITS) the smallest possible priority group is set.
 * param PriorityGroup Priority grouping field
 */
static __INLINE void NVIC_SetPriorityGrouping(uint32_t PriorityGroup) {
    uint32_t reg_value;
    /* only values 0..7 are used */
    uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07);
    reg_value = SCB->AIRCR; /* read old register configuration */
    /* clear bits to change */
    reg_value &= ~(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk);
    reg_value = (
        reg_value |
        ((uint32_t)0x5FA << SCB_AIRCR_VECTKEY_Pos) |
        (PriorityGroupTmp << 8)
    ); /* Insert write key and priorty group */
    SCB->AIRCR =  reg_value;
}

/**
 * Get Priority Grouping
 * This function gets the priority grouping from NVIC Interrupt Controller.
 * Priority grouping is SCB->AIRCR [10:8] PRIGROUP field.
 * return Priority grouping field
 */
static __INLINE uint32_t NVIC_GetPriorityGrouping(void) {
    /* read priority grouping field */
    return ((SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos);
}

/**
 * Enable External Interrupt
 * Function enables device specific interrupt in the NVIC interrupt controller.
 * Interrupt number cannot be a negative value.
 * param IRQn Number of the external interrupt to enable
 */
static __INLINE void NVIC_EnableIRQ(IRQn_Type IRQn) {
    /* enable interrupt */
    NVIC->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Disable External Interrupt
 * Function disables device specific interrupt in NVIC interrupt controller.
 * The interrupt number cannot be a negative value.
 * param IRQn Number of the external interrupt to disable
 */
static __INLINE void NVIC_DisableIRQ(IRQn_Type IRQn) {
    /* disable interrupt */
    NVIC->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Get Pending Interrupt
 * Function reads the pending register in the NVIC and returns the pending bit
 * for the specified interrupt.
 * param IRQn Number of the interrupt for get pending
 * return 0 Interrupt status is not pending
 * return 1 Interrupt status is pending
 */
static __INLINE uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn) {
    return (
        (uint32_t) (
            (
                NVIC->ISPR[(uint32_t)(IRQn) >> 5] &
                (1 << ((uint32_t)(IRQn) & 0x1F))
            ) ? 1 : 0
        )
    ); /* Return 1 if pending else 0 */
}

/**
 * Set Pending Interrupt
 * Function sets the pending bit for the specified interrupt.
 * The interrupt number cannot be a negative value.
 * param IRQn Number of the interrupt for set pending
 */
static __INLINE void NVIC_SetPendingIRQ(IRQn_Type IRQn) {
    /* set interrupt pending */
    NVIC->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Clear Pending Interrupt
 * Function clears the pending bit for the specified interrupt.
 * The interrupt number cannot be a negative value.
 * param IRQn Number of the interrupt for clear pending
 */
static __INLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn) {
    /* Clear pending interrupt */
    NVIC->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Get Active Interrupt
 * Function reads the active register in NVIC and returns the active bit.
 * param IRQn  Number of the interrupt for get active
 * return 0 Interrupt status is not active
 * return 1 Interrupt status is active
 */
static __INLINE uint32_t NVIC_GetActive(IRQn_Type IRQn) {
    return (
        (uint32_t) (
            (
                NVIC->IABR[(uint32_t)(IRQn) >> 5] &
                (1 << ((uint32_t)(IRQn) & 0x1F))
            ) ? 1 : 0
        )
    ); /* Return 1 if active else 0 */
}

/**
 * Set Interrupt Priority
 * Function sets the priority for the specified interrupt. The interrupt
 * number can be positive to specify an external (device specific)
 * interrupt, or negative to specify an internal (core) interrupt.
 * Note: The priority cannot be set for every core interrupt.
 * param IRQn Number of the interrupt for set priority
 * param priority Priority to set
 */
static __INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority) {
    if(IRQn < 0) {
        /* set Priority for Cortex-M  System Interrupts */
        SCB->SHP[((uint32_t)(IRQn) & 0xF)-4] = (
            (priority << (8 - __NVIC_PRIO_BITS)) & 0xff
        );
    } else {
        /* set Priority for device specific Interrupts  */
        NVIC->IP[(uint32_t)(IRQn)] = (
            (priority << (8 - __NVIC_PRIO_BITS)) & 0xff
        );
    }
}

/**
 * Get Interrupt Priority
 * Function reads the priority for the specified interrupt. The interrupt
 * number can be positive to specify an external (device specific)
 * interrupt, or negative to specify an internal (core) interrupt.
 * The returned priority value is automatically aligned to the implemented
 * priority bits of the microcontroller.
 * param IRQn Number of the interrupt for get priority
 * return Interrupt Priority
 */
static __INLINE uint32_t NVIC_GetPriority(IRQn_Type IRQn) {
    if(IRQn < 0) {
        /* get priority for Cortex-M  system interrupts */
        return (
            (uint32_t) (
                SCB->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - __NVIC_PRIO_BITS)
            )
        );
    } else {
        /* get priority for device specific interrupts */
        return (
            (uint32_t)(NVIC->IP[(uint32_t)(IRQn)] >> (8 - __NVIC_PRIO_BITS))
        );
    }
}

/**
 * Encode Priority
 * Function encodes the priority for an interrupt with the given priority
 * group, preemptive priority value and sub priority value.
 * In case of a conflict between priority grouping and available priority
 * bits (__NVIC_PRIO_BITS) the samllest possible priority group is set.
 * The returned priority value can be used for NVIC_SetPriority(...) function
 * param PriorityGroup Used priority group.
 * param PreemptPriority  Preemptive priority value (starting from 0)
 * param SubPriority  Sub priority value (starting from 0)
 * return Encoded priority for the interrupt
 */
static __INLINE uint32_t NVIC_EncodePriority(
    uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority
) {
    /* only values 0..7 are used */
    uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);
    uint32_t PreemptPriorityBits;
    uint32_t SubPriorityBits;
    PreemptPriorityBits = (
        (7 - PriorityGroupTmp) > __NVIC_PRIO_BITS
    ) ? __NVIC_PRIO_BITS : 7 - PriorityGroupTmp;
    SubPriorityBits = (
        (PriorityGroupTmp + __NVIC_PRIO_BITS) < 7
    ) ? 0 : PriorityGroupTmp - 7 + __NVIC_PRIO_BITS;
    return (
        (
            (
                PreemptPriority &
                ((1 << (PreemptPriorityBits)) - 1)
            ) << SubPriorityBits
        ) | ((SubPriority & ((1 << (SubPriorityBits)) - 1)))
    );
}

/**
 * Decode Priority
 * Function decodes an interrupt priority value with the given priority
 * group to preemptive priority value and sub priority value.
 * In case of a conflict between priority grouping and available
 * priority bits (__NVIC_PRIO_BITS) smallest possible priority group is set.
 * The priority value can be retrieved with NVIC_GetPriority(...) function
 * param Priority Priority value
 * param PriorityGroup Used priority group
 * param pPreemptPriority Preemptive priority value (starting from 0)
 * param pSubPriority Sub priority value (starting from 0)
 */
static __INLINE void NVIC_DecodePriority(
    uint32_t Priority, uint32_t PriorityGroup,
    uint32_t* pPreemptPriority, uint32_t* pSubPriority
) {
    /* only values 0..7 are used */
    uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);
    uint32_t PreemptPriorityBits;
    uint32_t SubPriorityBits;
    PreemptPriorityBits = (
        (7 - PriorityGroupTmp) > __NVIC_PRIO_BITS
    ) ? __NVIC_PRIO_BITS : 7 - PriorityGroupTmp;
    SubPriorityBits = (
        (PriorityGroupTmp + __NVIC_PRIO_BITS) < 7
    ) ? 0 : PriorityGroupTmp - 7 + __NVIC_PRIO_BITS;
    *pPreemptPriority = (
        (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1)
    );
    *pSubPriority = (Priority) & ((1 << (SubPriorityBits)) - 1);
}

/**
 * System Reset
 * Function initiate a system reset request to reset the MCU.
 */
static __INLINE void NVIC_SystemReset(void) {
    /**
     * Ensure all outstanding memory accesses included buffered write 
     * are completed before reset 
     */
    __DSB();
    /* Keep priority group unchanged */
    SCB->AIRCR  = (
        (0x5FA << SCB_AIRCR_VECTKEY_Pos) |
        (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
        SCB_AIRCR_SYSRESETREQ_Msk
    );
    __DSB(); /* Ensure completion of memory access */
    while(1); /* wait until reset */
}

#if (__Vendor_SysTickConfig == 0)

/**
 * System Tick Configuration
 * This function initialises the system tick timer and its interrupt and start
 * the system tick timer. Counter is in free running mode to generate
 * periodical interrupts.
 * param  ticks Number of ticks between two interrupts
 * return 0  Function succeeded
 * return 1  Function failed
 */
static __INLINE uint32_t SysTick_Config(uint32_t ticks) {
    if (ticks > SysTick_LOAD_RELOAD_Msk) {
        return (1);
    }
    /* set reload register */
    SysTick->LOAD = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;
    /* set Priority for Cortex-M0 System Interrupts */
    NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
    /* Load the SysTick Counter Value */
    SysTick->VAL = 0;
    /* Enable SysTick IRQ and SysTick Timer */
    SysTick->CTRL = (
        SysTick_CTRL_CLKSOURCE_Msk |
        SysTick_CTRL_TICKINT_Msk |
        SysTick_CTRL_ENABLE_Msk
    );
    return (0);
}

#endif

/* external variable to receive characters */
extern volatile int32_t ITM_RxBuffer;

/* value identifying ITM_RxBuffer is ready for next character */
#define ITM_RXBUFFER_EMPTY 0x5AA55AA5

/**
 * ITM Send Character
 * This function transmits a character via the ITM channel 0.
 * It just returns when no debugger is connected that has booked the output.
 * It is blocking when a debugger is connected, but the previous character
 * send is not transmitted.
 * param ch  Character to transmit
 * return Character to transmit
 */
static __INLINE uint32_t ITM_SendChar (uint32_t ch) {
    if (
        (CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk) && /* Trace enabled */
        (ITM->TCR & ITM_TCR_ITMENA_Msk) && /* ITM enabled */
        (ITM->TER & (1UL << 0)) /* ITM Port #0 enabled */
    ) {
        while (ITM->PORT[0].u32 == 0);
        ITM->PORT[0].u8 = (uint8_t) ch;
    }
    return (ch);
}

/**
 * ITM Receive Character
 * This function inputs a character via external variable ITM_RxBuffer.
 * It just returns when no debugger is connected that has booked the output.
 * It is blocking when a debugger is connected, but the previous character
 * send is not transmitted.
 * return Received character
 * return -1  No character received
 */
static __INLINE int32_t ITM_ReceiveChar (void) {
    int32_t ch = -1; /* no character available */
    if (ITM_RxBuffer != ITM_RXBUFFER_EMPTY) {
        ch = ITM_RxBuffer;
        ITM_RxBuffer = ITM_RXBUFFER_EMPTY; /* ready for next character */
    }
    return (ch);
}

/**
 * ITM Check Character
 * This function checks external variable ITM_RxBuffer whether a character
 * is available or not. It returns '1' if a character is available and '0'
 * if no character is available.
 * return 0 No character available
 * return 1 Character available
 */
static __INLINE int32_t ITM_CheckChar (void) {
    if (ITM_RxBuffer == ITM_RXBUFFER_EMPTY) {
        return (0); /* no character available */
    } else {
        return (1); /*    character available */
    }
}

#endif

#endif

#ifdef __cplusplus
    }
#endif

