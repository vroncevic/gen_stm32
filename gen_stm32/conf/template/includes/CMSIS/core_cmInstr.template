/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * core_cmInstr.h
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

#ifndef __CORE_CMINSTR_H
#define __CORE_CMINSTR_H

#if defined(__CC_ARM)

#if (__ARMCC_VERSION < 400677)
    #error "Please use ARM Compiler Toolchain V4.0.677 or later!"
#endif

/**
 * No Operation, this instruction can be used for code alignment purposes.
 */
#define __NOP __nop

/**
  * Wait For Interrupt is a hint instruction that suspends execution
  * until one of a number of events occurs.
 */
#define __WFI __wfi

/**
  * Wait For Event is a hint instruction that permits the processor to enter
  * a low-power state until one of a number of events occurs.
 */
#define __WFE __wfe

/**
 * Send Event it causes an event to be signaled to the CPU.
 */
#define __SEV __sev

/**
 * Instruction Synchronization Barrier flushes the pipeline in the processor,
 * so that all instructions following the ISB are fetched from cache or
 * memory, after the instruction has been completed.
 */
#define __ISB() __isb(0xF)

/**
 * This function acts as a special kind of Data Memory Barrier. It completes
 * when all explicit memory accesses before this instruction complete.
 */
#define __DSB() __dsb(0xF)

/**
 * This function ensures the apparent order of the explicit memory operations
 * before and after the instruction, without ensuring their completion.
 */
#define __DMB() __dmb(0xF)

/**
 * Reverse byte order (32 bit)
 * This function reverses the byte order in integer value
 * param value to reverse
 * return reversed value
 */
#define __REV __rev

/**
 * Reverse byte order (16 bit)
 * This function reverses the byte order in two unsigned short values
 * param value to reverse
 * return reserved value
 */
static __INLINE __ASM uint32_t __REV16(uint32_t value) {
    rev16 r0, r0
    bx lr
}

/**
 * Reverse byte order in signed short value
 * This function reverses the byte order in a signed short value with sign
 * extension to integer
 * param value to reverse
 * return reserved value
 */
static __INLINE __ASM int32_t __REVSH(int32_t value) {
    revsh r0, r0
    bx lr
}

#if (__CORTEX_M >= 0x03)

/**
 * Reverse bit order of value
 * This function reverses the bit order of the given value.
 * param value to reverse
 * return reserved value
 */
#define __RBIT __rbit

/**
 * LDR Exclusive (8 bit)
 * This function performs a exclusive LDR command for 8 bit value.
 * param ptr to data
 * return value of type uint8_t at (*ptr)
 */
#define __LDREXB(ptr) ((uint8_t) __ldrex(ptr))

/**
 * LDR Exclusive (16 bit)
 * This function performs a exclusive LDR command for 16 bit values.
 * param ptr to data
 * return value of type uint16_t at (*ptr)
 */
#define __LDREXH(ptr) ((uint16_t) __ldrex(ptr))

/**
 * LDR Exclusive (32 bit)
 * This function performs a exclusive LDR command for 32 bit values.
 * param ptr to data
 * return value of type uint32_t at (*ptr)
 */
#define __LDREXW(ptr) ((uint32_t) __ldrex(ptr))

/**
 * STR Exclusive (8 bit)
 * This function performs a exclusive STR command for 8 bit values.
 * param  value to store
 * param ptr to location
 * return 0  Function succeeded
 * return 1  Function failed
 */
#define __STREXB(value, ptr) __strex(value, ptr)

/**
 * STR Exclusive (16 bit)
 * This function performs a exclusive STR command for 16 bit values.
 * param  value to store
 * param ptr to location
 * return 0  Function succeeded
 * return 1  Function failed
 */
#define __STREXH(value, ptr) __strex(value, ptr)

/**
 * STR Exclusive (32 bit)
 * This function performs a exclusive STR command for 32 bit values.
 * param  value to store
 * param ptr to location
 * return 0  Function succeeded
 * return 1  Function failed
 */
#define __STREXW(value, ptr) __strex(value, ptr)

/**
 * Remove the exclusive lock
 * This function removes the exclusive lock which is created by LDREX.
 */
#define __CLREX __clrex

/**
 * Signed Saturate
 * This function saturates a signed value.
 * param value to be saturated
 * param sat bit position to saturate to (1..32)
 * return saturated value
 */
#define __SSAT __ssat

/**
 * Unsigned Saturate
 * This function saturates an unsigned value.
 * param value to be saturated
 * param sat bit position to saturate to (0..31)
 * return saturated value
 */
#define __USAT __usat

/**
 * Count leading zeros
 * This function counts the number of leading zeros of a data value.
 * param value to count the leading zeros
 * return number of leading zeros in value
 */
#define __CLZ __clz

#endif

#elif defined (__ICCARM__)

#include <cmsis_iar.h>

#elif defined (__GNUC__)

#define __STATIC_INLINE __attribute__((always_inline)) static __INLINE

/**
 * No Operation
 * This instruction can be used for code alignment purposes.
 */
__STATIC_INLINE void __NOP(void) {
    __ASM volatile ("nop");
}

/**
 * Wait For Interrupt
 * Is a hint instruction that suspends execution until one of a number
 * of events occurs.
 */
__STATIC_INLINE void __WFI(void) {
    __ASM volatile ("wfi");
}

/**
 * Wait For Event
 * Is a hint instruction that permits the processor to enter
 * a low-power state until one of a number of events occurs.
 */
__STATIC_INLINE void __WFE(void) {
    __ASM volatile ("wfe");
}

/**
 * Send Event is a hint instruction.
 * It causes an event to be signaled to the CPU.
 */
__STATIC_INLINE void __SEV(void) {
    __ASM volatile ("sev");
}

/**
 * Instruction Synchronization Barrier
 * Flushes the pipeline in the processor, so that all instructions following
 * the ISB are fetched from cache or memory, after the instruction has been
 * completed.
 */
__STATIC_INLINE void __ISB(void) {
    __ASM volatile ("isb");
}

/**
 * Data Synchronization Barrier
 * This function acts as a special kind of Data Memory Barrier.
 * It completes when all explicit memory accesses before this
  * instruction complete.
 */
__STATIC_INLINE void __DSB(void) {
    __ASM volatile ("dsb");
}

/**
 * Data Memory Barrier
 * Function ensures the apparent order of the explicit memory operations
 * before and after the instruction, without ensuring their completion.
 */
__STATIC_INLINE void __DMB(void) {
    __ASM volatile ("dmb");
}

/**
 * Reverse byte order (32 bit)
 * This function reverses the byte order in integer value.
 * param value to reverse
 * return reserved value
 */
__STATIC_INLINE uint32_t __REV(uint32_t value) {
    uint32_t result;
    __ASM volatile ("rev %0, %1" : "=r" (result) : "r" (value));
    return(result);
}

/**
 * Reverse byte order (16 bit)
 * This function reverses the byte order in two unsigned short values.
 * param value to reverse
 * return reserved value
 */
__STATIC_INLINE uint32_t __REV16(uint32_t value) {
    uint32_t result;
    __ASM volatile ("rev16 %0, %1" : "=r" (result) : "r" (value));
    return(result);
}

/**
 * Reverse byte order in signed short value
 * This function reverses the byte order in a signed short value with
 * sign extension to integer.
 * param value to reverse
 * return reserved value
 */
__STATIC_INLINE int32_t __REVSH(int32_t value) {
    uint32_t result;
    __ASM volatile ("revsh %0, %1" : "=r" (result) : "r" (value));
    return(result);
}

#if (__CORTEX_M >= 0x03)

/**
 * Reverse bit order of value
 * This function reverses the bit order of the given value.
 * param value to reverse
 * return reserved value
 */
__STATIC_INLINE uint32_t __RBIT(uint32_t value) {
    uint32_t result;
     __ASM volatile ("rbit %0, %1" : "=r" (result) : "r" (value));
     return(result);
}

/**
 * LDR Exclusive (8 bit)
 * This function performs a exclusive LDR command for 8 bit value.
 * param ptr to data
 * return value of type uint8_t at (*ptr)
 */
__STATIC_INLINE uint8_t __LDREXB(volatile uint8_t *addr) {
    uint8_t result;
    __ASM volatile ("ldrexb %0, [%1]" : "=r" (result) : "r" (addr));
    return(result);
}

/**
 * LDR Exclusive (16 bit)
 * This function performs a exclusive LDR command for 16 bit values.
 * param ptr to data
 * return value of type uint16_t at (*ptr)
 */
__STATIC_INLINE uint16_t __LDREXH(volatile uint16_t *addr) {
    uint16_t result;
    __ASM volatile ("ldrexh %0, [%1]" : "=r" (result) : "r" (addr));
    return(result);
}

/**
 * LDR Exclusive (32 bit)
 * This function performs a exclusive LDR command for 32 bit values.
 * param ptr to data
 * return value of type uint32_t at (*ptr)
 */
__STATIC_INLINE uint32_t __LDREXW(volatile uint32_t *addr) {
    uint32_t result;
    __ASM volatile ("ldrex %0, [%1]" : "=r" (result) : "r" (addr));
    return(result);
}

/**
 * STR Exclusive (8 bit)
 * This function performs a exclusive STR command for 8 bit values.
 * param  value to store
 * param ptr to location
 * return 0  Function succeeded
 * return 1  Function failed
 */
__STATIC_INLINE uint32_t __STREXB(uint8_t value, volatile uint8_t *addr) {
    uint32_t result;
    __ASM volatile (
        "strexb %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value)
    );
    return(result);
}

/**
 * STR Exclusive (16 bit)
 * This function performs a exclusive STR command for 16 bit values.
 * param value  Value to store
 * param ptr to location
 * return 0 Function succeeded
 * return 1 Function failed
 */
__STATIC_INLINE uint32_t __STREXH(uint16_t value, volatile uint16_t *addr) {
    uint32_t result;
    __ASM volatile (
        "strexh %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value)
    );
    return(result);
}

/**
 * STR Exclusive (32 bit)
 * This function performs a exclusive STR command for 32 bit values.
 * param value to store
 * param ptr to location
 * return 0 Function succeeded
 * return 1 Function failed
 */
__STATIC_INLINE uint32_t __STREXW(uint32_t value, volatile uint32_t *addr) {
    uint32_t result;
    __ASM volatile (
        "strex %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value)
    );
    return(result);
}

/**
 * Remove the exclusive lock
 * This function removes the exclusive lock which is created by LDREX.
 */
__STATIC_INLINE void __CLREX(void) {
    __ASM volatile ("clrex");
}

/**
 * Signed Saturate
 * This function saturates a signed value.
 * param value to be saturated
 * param sat bit position to saturate to (1..32)
 * return saturated value
 */
#define __SSAT(ARG1,ARG2) ({ \
    uint32_t __RES, __ARG1 = (ARG1); \
    __ASM ("ssat %0, %1, %2" : "=r" (__RES) :  "I" (ARG2), "r" (__ARG1)); \
    __RES; \
})

/**
 * Unsigned Saturate
 * This function saturates an unsigned value.
 * param value to be saturated
 * param sat bit position to saturate to (0..31)
 * return saturated value
 */
#define __USAT(ARG1,ARG2) ({ \
    uint32_t __RES, __ARG1 = (ARG1); \
    __ASM ("usat %0, %1, %2" : "=r" (__RES) :  "I" (ARG2), "r" (__ARG1)); \
    __RES; \
})

/**
 * Count leading zeros
 * This function counts the number of leading zeros of a data value
 * param  value  Value to count the leading zeros
 * return number of leading zeros in value
 */
__STATIC_INLINE uint8_t __CLZ(uint32_t value) {
    uint8_t result;
    __ASM volatile("clz %0, %1" : "=r" (result) : "r" (value));
    return(result);
}

#endif

#elif defined(__TASKING__)

/**
 * The CMSIS functions have been implemented as intrinsics in the compiler.
 * Please use "carm -?i" to get an up to date list of all intrinsics,
 * Including the CMSIS ones.
 */

#endif

#endif

