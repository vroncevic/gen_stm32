/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * core_cmFunc.h
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

#ifndef __CORE_CMFUNC_H
#define __CORE_CMFUNC_H

#if defined(__CC_ARM)

#if (__ARMCC_VERSION < 400677)
    #error "Please use ARM Compiler Toolchain V4.0.677 or later!"
#endif

/**
 * Get Control Register
 * This function returns the content of the Control Register.
 * return Control Register value
 */
static __INLINE uint32_t __get_CONTROL(void) {
    register uint32_t __regControl __ASM("control");
    return(__regControl);
}

/**
 * Set Control Register
 * This function writes the given value to the Control Register.
 * param control Control Register value to set
 */
static __INLINE void __set_CONTROL(uint32_t control) {
    register uint32_t __regControl __ASM("control");
    __regControl = control;
}

/**
 * Get ISPR Register
 * This function returns the content of the ISPR Register.
 * return ISPR Register value
 */
static __INLINE uint32_t __get_IPSR(void) {
    register uint32_t __regIPSR __ASM("ipsr");
    return(__regIPSR);
}

/**
 * Get APSR Register
 * This function returns the content of the APSR Register.
 * return APSR Register value
 */
static __INLINE uint32_t __get_APSR(void) {
    register uint32_t __regAPSR __ASM("apsr");
    return(__regAPSR);
}

/**
 * Get xPSR Register
 * This function returns the content of the xPSR Register.
 * return xPSR Register value
 */
static __INLINE uint32_t __get_xPSR(void) {
    register uint32_t __regXPSR __ASM("xpsr");
    return(__regXPSR);
}

/**
 * Get Process Stack Pointer
 * This function returns the current value of the Process Stack Pointer (PSP).
 * return PSP Register value
 */
static __INLINE uint32_t __get_PSP(void) {
    register uint32_t __regProcessStackPointer __ASM("psp");
    return(__regProcessStackPointer);
}

/**
 * Set Process Stack Pointer
 * This function assigns the given value to the Process Stack Pointer (PSP).
 * param topOfProcStack  Process Stack Pointer value to set
 */
static __INLINE void __set_PSP(uint32_t topOfProcStack) {
    register uint32_t __regProcessStackPointer __ASM("psp");
    __regProcessStackPointer = topOfProcStack;
}

/**
 * Get Main Stack Pointer
 * This function returns the current value of the Main Stack Pointer (MSP).
 * return MSP Register value
 */
static __INLINE uint32_t __get_MSP(void) {
    register uint32_t __regMainStackPointer __ASM("msp");
    return(__regMainStackPointer);
}

/**
 * Set Main Stack Pointer
 * This function assigns the given value to the Main Stack Pointer (MSP).
 * param topOfMainStack  Main Stack Pointer value to set
 */
static __INLINE void __set_MSP(uint32_t topOfMainStack) {
    register uint32_t __regMainStackPointer __ASM("msp");
    __regMainStackPointer = topOfMainStack;
}

/**
 * Get Priority Mask
 * Function returns state of priority mask bit from Priority Mask Register.
 * return Priority Mask value
 */
static __INLINE uint32_t __get_PRIMASK(void) {
    register uint32_t __regPriMask __ASM("primask");
    return(__regPriMask);
}

/**
 * Set Priority Mask
 * This function assigns the given value to the Priority Mask Register.
 * param priMask  Priority Mask
 */
static __INLINE void __set_PRIMASK(uint32_t priMask) {
    register uint32_t __regPriMask __ASM("primask");
    __regPriMask = (priMask);
}

#if (__CORTEX_M >= 0x03)

/**
 * Enable FIQ
 * This function enables FIQ interrupts by clearing the F-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
#define __enable_fault_irq __enable_fiq

/**
 * Disable FIQ
 * This function disables FIQ interrupts by setting the F-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
#define __disable_fault_irq __disable_fiq

/**
 * Get Base Priority
 * This function returns the current value of the Base Priority register.
 * return Base Priority register value
 */
static __INLINE uint32_t  __get_BASEPRI(void) {
    register uint32_t __regBasePri __ASM("basepri");
    return(__regBasePri);
}

/**
 * Set Base Priority
 * This function assigns the given value to the Base Priority register.
 * param basePri Base Priority value to set
 */
static __INLINE void __set_BASEPRI(uint32_t basePri) {
    register uint32_t __regBasePri __ASM("basepri");
    __regBasePri = (basePri & 0xff);
}

/**
 * Get Fault Mask
 * This function returns the current value of the Fault Mask register.
 * return Fault Mask register value
 */
static __INLINE uint32_t __get_FAULTMASK(void) {
    register uint32_t __regFaultMask __ASM("faultmask");
    return(__regFaultMask);
}

/**
 * Set Fault Mask
 * This function assigns the given value to the Fault Mask register.
 * param faultMask  Fault Mask value to set
 */
static __INLINE void __set_FAULTMASK(uint32_t faultMask) {
    register uint32_t __regFaultMask __ASM("faultmask");
    __regFaultMask = (faultMask & (uint32_t)1);
}

#endif

#if (__CORTEX_M == 0x04)

/**
 * Get FPSCR
 * This function returns value of the Floating Point Status/Control register.
 * return Floating Point Status/Control register value
 */
static __INLINE uint32_t __get_FPSCR(void) {
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    register uint32_t __regfpscr __ASM("fpscr");
    return(__regfpscr);
#else
    return(0);
#endif
}

/**
 * Set FPSCR
 * This function assigns value to the Floating Point Status/Control register.
 * param fpscr Floating Point Status/Control value to set
 */
static __INLINE void __set_FPSCR(uint32_t fpscr) {
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    register uint32_t __regfpscr __ASM("fpscr");
    __regfpscr = (fpscr);
#endif
}

#endif

#elif defined(__ICCARM__)

#include <cmsis_iar.h>

#elif defined(__GNUC__)

#define __STATIC_INLINE __attribute__((always_inline)) static __INLINE

/**
 * Enable IRQ Interrupts
 * This function enables IRQ interrupts by clearing the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
__STATIC_INLINE void __enable_irq(void) {
    __ASM volatile ("cpsie i");
}

/**
 * Disable IRQ Interrupts
 * This function disables IRQ interrupts by setting the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
__STATIC_INLINE void __disable_irq(void) {
    __ASM volatile ("cpsid i");
}

/**
 * Get Control Register
 * This function returns the content of the Control Register.
 * return Control Register value
 */
__STATIC_INLINE uint32_t __get_CONTROL(void) {
    uint32_t result;
    __ASM volatile ("MRS %0, control" : "=r" (result));
    return(result);
}

/**
 * Set Control Register
 * This function writes the given value to the Control Register.
 * param control Control Register value to set
 */
__STATIC_INLINE void __set_CONTROL(uint32_t control) {
    __ASM volatile ("MSR control, %0" : : "r" (control));
}

/**
 * Get ISPR Register
 * This function returns the content of the ISPR Register.
 * return ISPR Register value
 */
__STATIC_INLINE uint32_t __get_IPSR(void) {
    uint32_t result;
    __ASM volatile ("MRS %0, ipsr" : "=r" (result));
    return(result);
}

/**
 * Get APSR Register
 * This function returns the content of the APSR Register.
 * return APSR Register value
 */
__STATIC_INLINE uint32_t __get_APSR(void) {
    uint32_t result;
    __ASM volatile ("MRS %0, apsr" : "=r" (result));
    return(result);
}

/**
 * Get xPSR Register
 * This function returns the content of the xPSR Register.
 * return xPSR Register value
 */
__STATIC_INLINE uint32_t __get_xPSR(void) {
    uint32_t result;
    __ASM volatile ("MRS %0, xpsr" : "=r" (result));
    return(result);
}

/**
 * Get Process Stack Pointer
 * This function returns the current value of the Process Stack Pointer (PSP).
 * return PSP Register value
 */
__STATIC_INLINE uint32_t __get_PSP(void) {
    register uint32_t result;
    __ASM volatile ("MRS %0, psp\n"  : "=r" (result));
    return(result);
}

/**
 * Set Process Stack Pointer
 * This function assigns the given value to the Process Stack Pointer (PSP).
 * param topOfProcStack  Process Stack Pointer value to set
 */
__STATIC_INLINE void __set_PSP(uint32_t topOfProcStack) {
    __ASM volatile ("MSR psp, %0\n" : : "r" (topOfProcStack));
}

/**
 * Get Main Stack Pointer
 * This function returns the current value of the Main Stack Pointer (MSP).
 * return MSP Register value
 */
__STATIC_INLINE uint32_t __get_MSP(void) {
    register uint32_t result;
    __ASM volatile ("MRS %0, msp\n" : "=r" (result));
    return(result);
}

/**
 * Set Main Stack Pointer
 * This function assigns the given value to the Main Stack Pointer (MSP).
 * param topOfMainStack  Main Stack Pointer value to set
 */
__STATIC_INLINE void __set_MSP(uint32_t topOfMainStack) {
    __ASM volatile ("MSR msp, %0\n" : : "r" (topOfMainStack));
}

/**
 * Get Priority Mask
 * This function returns the current state of the priority mask bit
 * from the Priority Mask Register.
 * return Priority Mask value
 */
__STATIC_INLINE uint32_t __get_PRIMASK(void) {
    uint32_t result;
    __ASM volatile ("MRS %0, primask" : "=r" (result));
    return(result);
}

/**
 * Set Priority Mask
 * This function assigns the given value to the Priority Mask Register.
 * param priMask  Priority Mask
 */
__STATIC_INLINE void __set_PRIMASK(uint32_t priMask) {
    __ASM volatile ("MSR primask, %0" : : "r" (priMask));
}

#if (__CORTEX_M >= 0x03)

/**
 * Enable FIQ
 * This function enables FIQ interrupts by clearing the F-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
__STATIC_INLINE void __enable_fault_irq(void) {
    __ASM volatile ("cpsie f");
}

/**
 * Disable FIQ
 * This function disables FIQ interrupts by setting the F-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
__STATIC_INLINE void __disable_fault_irq(void) {
    __ASM volatile ("cpsid f");
}

/**
 * Get Base Priority
 * This function returns the current value of the Base Priority register.
 * return Base Priority register value
 */
__STATIC_INLINE uint32_t __get_BASEPRI(void) {
    uint32_t result;
    __ASM volatile ("MRS %0, basepri_max" : "=r" (result));
    return(result);
}

/**
 * Set Base Priority
 * This function assigns the given value to the Base Priority register.
 * param basePri Base Priority value to set
 */
__STATIC_INLINE void __set_BASEPRI(uint32_t value) {
    __ASM volatile ("MSR basepri, %0" : : "r" (value));
}

/**
 * Get Fault Mask
 * This function returns the current value of the Fault Mask register.
 * return Fault Mask register value
 */
__STATIC_INLINE uint32_t __get_FAULTMASK(void) {
    uint32_t result;
    __ASM volatile ("MRS %0, faultmask" : "=r" (result));
    return(result);
}

/**
 * Set Fault Mask
 * This function assigns the given value to the Fault Mask register.
 * param faultMask Fault Mask value to set
 */
__STATIC_INLINE void __set_FAULTMASK(uint32_t faultMask) {
    __ASM volatile ("MSR faultmask, %0" : : "r" (faultMask));
}

#endif

#if (__CORTEX_M == 0x04)

/**
 * Get FPSCR
 * This function returns value of the Floating Point Status/Control register.
 * return Floating Point Status/Control register value
 */
__STATIC_INLINE uint32_t __get_FPSCR(void) {
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    uint32_t result;
    __ASM volatile ("VMRS %0, fpscr" : "=r" (result));
    return(result);
#else
    return(0);
#endif
}

/**
 * Set FPSCR
 * This function assigns value to the Floating Point Status/Control register.
 * param fpscr Floating Point Status/Control value to set
 */
__STATIC_INLINE void __set_FPSCR(uint32_t fpscr) {
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    __ASM volatile ("VMSR fpscr, %0" : : "r" (fpscr));
#endif
}

#endif

#elif defined(__TASKING__)

/**
 * The CMSIS functions have been implemented as intrinsics in the compiler.
 * Please use "carm -?i" to get an up to date list of all instrinsics,
 * Including the CMSIS ones.
 */

#endif

#endif

