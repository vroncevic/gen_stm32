/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/* 
 * arm_math.h
 * 
 * Public header file for CMSIS DSP Library.
 * 
 * Version V1.0.10
 * Target Processor Cortex-M4/Cortex-M3/Cortex-M0
 * 
 * Copyright (C) 2010 ARM Limited. All rights reserved.
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
 * 
 * CMSIS DSP Software Library
 * 
 * Introduction
 * 
 * This user manual describes the CMSIS DSP software library, a suite of
 * common signal processing functions for use on Cortex-M processor based
 * devices.
 *
 * The library is divided into a number of modules, each module covering a
 * specific category:
 * 
 * - Basic math functions
 * - Fast math functions
 * - Complex math functions
 * - Filters
 * - Matrix functions
 * - Transforms
 * - Motor control functions
 * - Statistical functions
 * - Support functions
 * - Interpolation functions
 *
 * The library has separate functions for operating on 8-bit integers,
 * 16-bit integers, 32-bit integer and 32-bit floating-point values.
 * 
 * Processor Support
 * 
 * The library is completely written in C and is fully CMSIS compliant.
 * High performance is achieved through maximum use of Cortex-M4 intrinsics.
 * 
 * The supplied library source code also builds and runs on the Cortex-M3
 * and Cortex-M0 processor, with the DSP intrinsics being emulated through
 * software.
 * 
 * Toolchain Support
 * 
 * The library has been developed and tested with MDK-ARM version 4.21.
 * The library is being tested in GCC and IAR toolchains and updates on this
 * activity will be made available shortly.
 * 
 * Using the Library
 * 
 * The library installer contains prebuilt versions of the libraries in the
 * Lib folder.
 * - arm_cortexM4lf_math.lib (LE and Floating Point Unit on Cortex-M4)
 * - arm_cortexM4bf_math.lib (BE and Floating Point Unit on Cortex-M4)
 * - arm_cortexM4l_math.lib (LE on Cortex-M4)
 * - arm_cortexM4b_math.lib (BE on Cortex-M4)
 * - arm_cortexM3l_math.lib (LE on Cortex-M3)
 * - arm_cortexM3b_math.lib (BE on Cortex-M3)
 * - arm_cortexM0l_math.lib (LE on Cortex-M0)
 * - arm_cortexM0b_math.lib (BE on Cortex-M3)
 * 
 * The library functions are declared in the public file arm_math.h which is
 * placed in the Include folder.
 * Simply include this file and link the appropriate library in the 
 * application and begin calling the library functions.
 * The Library supports single public header file arm_math.h for
 * Cortex-M4/M3/M0 with LE and BE. Same header file will be used for floating
 * point unit(FPU) variants.
 * Defines the appropriate pre processor MACRO ARM_MATH_CM4 or  ARM_MATH_CM3 or
 * ARM_MATH_CM0 depending on the target processor in the application.
 * 
 * Fast Math Functions
 * 
 * This set of functions provides a fast approximation to sine, cosine, and
 * square root. As compared to most of the other functions in the CMSIS math
 * library, the fast math functions operate on individual values and not
 * arrays. There are separate functions for Q15, Q31, and floating-point data.
 * 
 * Complex Math Functions
 * 
 * This set of functions operates on complex data vectors.
 * The data in the complex arrays is stored in an interleaved fashion
 * (real, imag, real, imag, ...).
 * In the API functions, the number of samples in a complex array refers
 * to the number of complex values; the array contains twice this number of
 * real values.
 * 
 * Matrix Functions
 * 
 * This set of functions provides basic matrix math operations.
 * The functions operate on matrix data structures.  For example,
 * the type
 * definition for the floating-point matrix structure is shown
 * below:
 * 
 *     typedef struct {
 *         uint16_t numRows;     // number of rows of the matrix.
 *         uint16_t numCols;     // number of columns of the matrix.
 *         float32_t *pData;     // points to the data of the matrix.
 *     } arm_matrix_instance_f32;
 * 
 * There are similar definitions for Q15 and Q31 data types.
 * 
 * The structure specifies the size of the matrix and then points to
 * an array of data.  The array is of size numRows X numCols
 * and the values are arranged in row order.  That is, the
 * matrix element (i, j) is stored at:
 * 
 *     pData[i*numCols + j]
 * 
 * Init Functions
 * 
 * There is an associated initialization function for each type of matrix
 * data structure. The initialization function sets the values of the internal
 * structure fields.
 * Refer to the function arm_mat_init_f32(), arm_mat_init_q31()
 * and arm_mat_init_q15() for floating-point, Q31 and Q15 types, respectively.
 * 
 * Use of the initialization function is optional. However, if initialization
 * function is used then the instance structure cannot be placed into a const
 * data section.
 * To place the instance structure in a const data
 * section, manually initialize the data structure.  For example:
 * 
 * arm_matrix_instance_f32 S = {nRows, nColumns, pData};
 * arm_matrix_instance_q31 S = {nRows, nColumns, pData};
 * arm_matrix_instance_q15 S = {nRows, nColumns, pData};
 * 
 * where nRows specifies the number of rows, nColumns specifies the number of
 * columns, and pData points to the data array.
 * 
 * Size Checking
 * 
 * By default all of the matrix functions perform size checking on input and
 * output matrices.  For example, matrix addition function verifies that the
 * two input matrices and output matrix all have the same number of rows and
 * columns. If the size check fails the functions return:
 * 
 *     ARM_MATH_SIZE_MISMATCH
 * 
 * Otherwise the functions return
 * 
 *     ARM_MATH_SUCCESS
 * 
 * There is some overhead associated with this matrix size checking.
 * The matrix size checking is enabled via the #define ARM_MATH_MATRIX_CHECK
 * within the library project settings. By default this macro is defined
 * and size checking is enabled. By changing the project settings and
 * undefining this macro size checking is eliminated and the functions
 * run a bit faster.  With size checking disabled the functions always
 * return ARM_MATH_SUCCESS.
 */

#ifndef _ARM_MATH_H
#define _ARM_MATH_H

#define __CMSIS_GENERIC

#if defined (ARM_MATH_CM4)
    #include "core_cm4.h"
#elif defined (ARM_MATH_CM3)
    #include "core_cm3.h"
#elif defined (ARM_MATH_CM0)
    #include "core_cm0.h"
#else
    #include "ARMCM4.h"
    #warning "Defines either ARM_MATH_CM4 OR ARM_MATH_CM3."
    #warning "By Default building on ARM_MATH_CM4."
#endif

#undef __CMSIS_GENERIC

#include "string.h"
#include "math.h"

#ifdef __cplusplus
    extern "C" {
#endif

/**
 * Macros required for reciprocal calculation in Normalized LMS
 */
#define DELTA_Q31 (0x100)
#define DELTA_Q15 0x5
#define INDEX_MASK 0x0000003F
#define PI 3.14159265358979f

/**
 * Macros required for SINE and COSINE Fast math approximations
 */
#define TABLE_SIZE 256
#define TABLE_SPACING_Q31 0x800000
#define TABLE_SPACING_Q15 0x80

/**
 * Macros required for SINE and COSINE Controller functions
 */
#define INPUT_SPACING 0xB60B61

/**
 * Error status returned by some functions in the library.
 * No error 0
 * One or more arguments are incorrect -1
 * Length of data buffer is incorrect -2
 * Size of matrices is not compatible with the operation -3
 * Not-a-number (NaN) or infinity is generated -4
 * Generated by matrix inversion if the input matrix is singular and
 * cannot be inverted -5
 * Test Failed -6
 */
typedef enum {
    ARM_MATH_SUCCESS = 0,
    ARM_MATH_ARGUMENT_ERROR = -1,
    ARM_MATH_LENGTH_ERROR = -2,
    ARM_MATH_SIZE_MISMATCH = -3,
    ARM_MATH_NANINF = -4,
    ARM_MATH_SINGULAR = -5,
    ARM_MATH_TEST_FAILURE = -6
} arm_status;

/**
 * 8-bit fractional data type in 1.7 format.
 */
typedef int8_t q7_t;

/**
 * 16-bit fractional data type in 1.15 format.
 */
typedef int16_t q15_t;

/**
 * 32-bit fractional data type in 1.31 format.
 */
typedef int32_t q31_t;

/**
 * 64-bit fractional data type in 1.63 format.
 */
typedef int64_t q63_t;

/**
 * 32-bit floating-point type definition.
 */
typedef float float32_t;

/**
 * 64-bit floating-point type definition.
 */
typedef double float64_t;

/**
 * definition to read/write two 16 bit values.
 */
#define __SIMD32(addr) (*(int32_t **) & (addr))

#if defined (ARM_MATH_CM3) || defined (ARM_MATH_CM0)
    /**
     * definition to pack two 16 bit values.
     */
    #define __PKHBT(ARG1, ARG2, ARG3) ( \
        (((int32_t)(ARG1) <<  0) & (int32_t)0x0000FFFF) | \
        (((int32_t)(ARG2) << ARG3) & (int32_t)0xFFFF0000) \
    )
#endif

/**
 * definition to pack four 8 bit values.
 */
#ifndef ARM_MATH_BIG_ENDIAN
    #define __PACKq7(v0,v1,v2,v3) (\
        (((int32_t)(v0) <<  0) & (int32_t)0x000000FF) | \
        (((int32_t)(v1) <<  8) & (int32_t)0x0000FF00) | \
        (((int32_t)(v2) << 16) & (int32_t)0x00FF0000) | \
        (((int32_t)(v3) << 24) & (int32_t)0xFF000000) \
    )
#else
    #define __PACKq7(v0,v1,v2,v3) (\
        (((int32_t)(v3) <<  0) & (int32_t)0x000000FF) | \
        (((int32_t)(v2) <<  8) & (int32_t)0x0000FF00) | \
        (((int32_t)(v1) << 16) & (int32_t)0x00FF0000) | \
        (((int32_t)(v0) << 24) & (int32_t)0xFF000000) \
    )
#endif

/**
 * Clips Q63 to Q31 values.
 */
static __INLINE q31_t clip_q63_to_q31(q63_t x) {
    return (
        (q31_t) (x >> 32) != ((q31_t) x >> 31)
    ) ? ((0x7FFFFFFF ^ ((q31_t) (x >> 63)))) : (q31_t) x;
}

/**
 * Clips Q63 to Q15 values.
 */
static __INLINE q15_t clip_q63_to_q15(q63_t x) {
    return (
        (q31_t) (x >> 32) != ((q31_t) x >> 31)
    ) ? ((0x7FFF ^ ((q15_t) (x >> 63)))) : (q15_t) (x >> 15);
}

/**
 * Clips Q31 to Q7 values.
 */
static __INLINE q7_t clip_q31_to_q7(q31_t x) {
    return (
        (q31_t) (x >> 24) != ((q31_t) x >> 23)
    ) ? ((0x7F ^ ((q7_t) (x >> 31)))) : (q7_t) x;
}

/**
 * Clips Q31 to Q15 values.
 */
static __INLINE q15_t clip_q31_to_q15(q31_t x) {
    return (
        (q31_t) (x >> 16) != ((q31_t) x >> 15)
    ) ? ((0x7FFF ^ ((q15_t) (x >> 31)))) : (q15_t) x;
}

/**
 * Multiplies 32 X 64 and returns 32 bit result in 2.30 format.
 */
static __INLINE q63_t mult32x64(q63_t x, q31_t y) {
    return (
        (((q63_t) (x & 0x00000000FFFFFFFF) * y) >> 32) +
        (((q63_t) (x >> 32) * y))
    );
}

#if defined(ARM_MATH_CM0) && defined(__CC_ARM)
    #define __CLZ __clz
#endif

#if defined(ARM_MATH_CM0) && ( \
    (defined(__ICCARM__)) || (defined(__GNUC__)) || defined(__TASKING__) \
)
    static __INLINE  uint32_t __CLZ(q31_t data);
    static __INLINE uint32_t __CLZ(q31_t data) {
        uint32_t count = 0;
        uint32_t mask = 0x80000000;

        while((data & mask) ==  0) {
            count += 1u;
            mask = mask >> 1u;
        }
        return(count);
    }
#endif

/**
 * Function to Calculates 1/in(reciprocal) value of Q31 Data type.
 */
static __INLINE uint32_t arm_recip_q31(
    q31_t in, q31_t* dst, q31_t* pRecipTable
) {
    uint32_t out, tempVal;
    uint32_t index, i;
    uint32_t signBits;

    if(in > 0) {
        signBits = __CLZ(in) - 1;
    } else {
        signBits = __CLZ(-in) - 1;
    }
    /* Convert input sample to 1.31 format */
    in = in << signBits;
    /* calculation of index for initial approximated Val */
    index = (uint32_t) (in >> 24u);
    index = (index & INDEX_MASK);
    /* 1.31 with exp 1 */
    out = pRecipTable[index];
    /* calculation of reciprocal value */
    /* running approximation for two iterations */
    for (i = 0u; i < 2u; i++) {
        tempVal = (q31_t) (((q63_t) in * out) >> 31u);
        tempVal = 0x7FFFFFFF - tempVal;
        /*      1.31 with exp 1 */
        /* out = (q31_t) (((q63_t) out * tempVal) >> 30u); */
        out = (q31_t) clip_q63_to_q31(((q63_t) out * tempVal) >> 30u);
    }
    /* write output */
    *dst = out;
    /* return num of signbits of out = 1/in value */
    return (signBits + 1u);
}

/**
 * Function to Calculates 1/in(reciprocal) value of Q15 Data type.
 */
static __INLINE uint32_t arm_recip_q15(
    q15_t in, q15_t * dst, q15_t * pRecipTable
) {
    uint32_t out = 0, tempVal = 0;
    uint32_t index = 0, i = 0;
    uint32_t signBits = 0;

    if(in > 0) {
        signBits = __CLZ(in) - 17;
    } else {
        signBits = __CLZ(-in) - 17;
    }
    /* Convert input sample to 1.15 format */
    in = in << signBits;
    /* calculation of index for initial approximated Val */
    index = in >> 8;
    index = (index & INDEX_MASK);
    /*      1.15 with exp 1  */
    out = pRecipTable[index];
    /* calculation of reciprocal value */
    /* running approximation for two iterations */
    for (i = 0; i < 2; i++) {
        tempVal = (q15_t) (((q31_t) in * out) >> 15);
        tempVal = 0x7FFF - tempVal;
        /*      1.15 with exp 1 */
        out = (q15_t) (((q31_t) out * tempVal) >> 14);
    }
    /* write output */
    *dst = out;
    /* return num of signbits of out = 1/in value */
    return (signBits + 1);
}

/**
 * C custom defined intrinisic function for only M0 processors
 */
#if defined(ARM_MATH_CM0)
    static __INLINE q31_t __SSAT(q31_t x, uint32_t y) {
        int32_t posMax, negMin;
        uint32_t i;
        posMax = 1;

        for (i = 0; i < (y - 1); i++) {
            posMax = posMax * 2;
        }
        if(x > 0) {
            posMax = (posMax - 1);
            if(x > posMax) {
                x = posMax;
            }
        } else {
            negMin = -posMax;
            if(x < negMin) {
                x = negMin;
            }
        }
        return (x);
    }
#endif

/**
 * C custom defined intrinsic function for M3 and M0 processors
 */
#if defined(ARM_MATH_CM3) || defined(ARM_MATH_CM0)
    /**
     * C custom defined QADD8 for M3 and M0 processors
     */
    static __INLINE q31_t __QADD8(q31_t x, q31_t y) {
        q31_t sum;
        q7_t r, s, t, u;

        r = (char) x;
        s = (char) y;
        r = __SSAT((q31_t) (r + s), 8);
        s = __SSAT(((q31_t) (((x << 16) >> 24) + ((y << 16) >> 24))), 8);
        t = __SSAT(((q31_t) (((x << 8) >> 24) + ((y << 8) >> 24))), 8);
        u = __SSAT(((q31_t) ((x >> 24) + (y >> 24))), 8);
        sum = (((q31_t) u << 24) & 0xFF000000) |
              (((q31_t) t << 16) & 0x00FF0000) |
              (((q31_t) s << 8) & 0x0000FF00) |
              (r & 0x000000FF);
        return sum;
    }

    /**
     * C custom defined QSUB8 for M3 and M0 processors
     */
    static __INLINE q31_t __QSUB8(q31_t x, q31_t y) {
        q31_t sum;
        q31_t r, s, t, u;

        r = (char) x;
        s = (char) y;
        r = __SSAT((r - s), 8);
        s = __SSAT(((q31_t) (((x << 16) >> 24) - ((y << 16) >> 24))), 8) << 8;
        t = __SSAT(((q31_t) (((x << 8) >> 24) - ((y << 8) >> 24))), 8) << 16;
        u = __SSAT(((q31_t) ((x >> 24) - (y >> 24))), 8) << 24;
        sum = (u & 0xFF000000) | (t & 0x00FF0000) |
              (s & 0x0000FF00) | (r & 0x000000FF);
        return sum;
    }

    /**
     * C custom defined QADD16 for M3 and M0 processors
     */
    static __INLINE q31_t __QADD16(q31_t x, q31_t y) {
        q31_t sum;
        q31_t r, s;

        r = (short) x;
        s = (short) y;
        r = __SSAT(r + s, 16);
        s = __SSAT(((q31_t) ((x >> 16) + (y >> 16))), 16) << 16;
        sum = (s & 0xFFFF0000) | (r & 0x0000FFFF);
        return sum;
    }

    /**
     * C custom defined SHADD16 for M3 and M0 processors
     */
    static __INLINE q31_t __SHADD16(q31_t x, q31_t y) {
        q31_t sum;
        q31_t r, s;

        r = (short) x;
        s = (short) y;
        r = ((r >> 1) + (s >> 1));
        s = ((q31_t) ((x >> 17) + (y >> 17))) << 16;
        sum = (s & 0xFFFF0000) | (r & 0x0000FFFF);
        return sum;
    }

    /**
     * C custom defined QSUB16 for M3 and M0 processors
     */
    static __INLINE q31_t __QSUB16(q31_t x, q31_t y) {
        q31_t sum;
        q31_t r, s;

        r = (short) x;
        s = (short) y;
        r = __SSAT(r - s, 16);
        s = __SSAT(((q31_t) ((x >> 16) - (y >> 16))), 16) << 16;
        sum = (s & 0xFFFF0000) | (r & 0x0000FFFF);
        return sum;
    }

    /**
     * C custom defined SHSUB16 for M3 and M0 processors
     */
    static __INLINE q31_t __SHSUB16(q31_t x, q31_t y) {
        q31_t diff;
        q31_t r, s;

        r = (short) x;
        s = (short) y;
        r = ((r >> 1) - (s >> 1));
        s = (((x >> 17) - (y >> 17)) << 16);
        diff = (s & 0xFFFF0000) | (r & 0x0000FFFF);
        return diff;
    }

    /**
     * C custom defined QASX for M3 and M0 processors
     */
    static __INLINE q31_t __QASX(q31_t x, q31_t y) {
        q31_t sum = 0;

        sum = (
                  (
                      sum +
                      clip_q31_to_q15(
                          (q31_t) ((short) (x >> 16) + (short) y)
                      )
                  ) << 16
              ) +
                  clip_q31_to_q15(
                      (q31_t) ((short) x - (short) (y >> 16))
              );
        return sum;
    }

    /**
     * C custom defined SHASX for M3 and M0 processors
     */
    static __INLINE q31_t __SHASX(q31_t x, q31_t y) {
        q31_t sum;
        q31_t r, s;

        r = (short) x;
        s = (short) y;
        r = ((r >> 1) - (y >> 17));
        s = (((x >> 17) + (s >> 1)) << 16);
        sum = (s & 0xFFFF0000) | (r & 0x0000FFFF);
        return sum;
    }

    /**
     * C custom defined QSAX for M3 and M0 processors
     */
    static __INLINE q31_t __QSAX(q31_t x, q31_t y) {
        q31_t sum = 0;

        sum = (
                  (
                      sum +
                      clip_q31_to_q15(
                          (q31_t) ((short) (x >> 16) - (short) y)
                      )
                  ) << 16
              ) +
              clip_q31_to_q15((q31_t) ((short) x + (short) (y >> 16)));
        return sum;
    }

    /**
     * C custom defined SHSAX for M3 and M0 processors
     */
    static __INLINE q31_t __SHSAX(q31_t x, q31_t y) {
        q31_t sum;
        q31_t r, s;

        r = (short) x;
        s = (short) y;
        r = ((r >> 1) + (y >> 17));
        s = (((x >> 17) - (s >> 1)) << 16);
        sum = (s & 0xFFFF0000) | (r & 0x0000FFFF);
        return sum;
    }

    /**
     * C custom defined SMUSDX for M3 and M0 processors
     */
    static __INLINE q31_t __SMUSDX(q31_t x, q31_t y) {
        return (
            (q31_t) (
                ((short) x * (short) (y >> 16)) -
                ((short) (x >> 16) * (short) y)
            )
        );
    }

    /**
     * C custom defined SMUADX for M3 and M0 processors
     */
    static __INLINE q31_t __SMUADX(q31_t x, q31_t y) {
        return (
            (q31_t) (
                ((short) x * (short) (y >> 16)) +
                ((short) (x >> 16) * (short) y)
            )
        );
    }

    /**
     * C custom defined QADD for M3 and M0 processors
     */
    static __INLINE q31_t __QADD(q31_t x, q31_t y) {
        return clip_q63_to_q31((q63_t) x + y);
    }

    /**
     * C custom defined QSUB for M3 and M0 processors
     */
    static __INLINE q31_t __QSUB(q31_t x, q31_t y) {
        return clip_q63_to_q31((q63_t) x - y);
    }

    /**
     * C custom defined SMLAD for M3 and M0 processors
     */
    static __INLINE q31_t __SMLAD(q31_t x, q31_t y, q31_t sum) {
        return (
            sum +
            ((short) (x >> 16) * (short) (y >> 16)) +
            ((short) x * (short) y)
        );
    }

    /**
     * C custom defined SMLADX for M3 and M0 processors
     */
    static __INLINE q31_t __SMLADX(q31_t x, q31_t y, q31_t sum) {
        return (
            sum +
            ((short) (x >> 16) * (short) (y)) +
            ((short) x * (short) (y >> 16))
        );
    }

    /**
     * C custom defined SMLSDX for M3 and M0 processors
     */
    static __INLINE q31_t __SMLSDX(q31_t x, q31_t y, q31_t sum) {
        return (
            sum -
            ((short) (x >> 16) * (short) (y)) +
            ((short) x * (short) (y >> 16))
        );
    }

    /**
     * C custom defined SMLALD for M3 and M0 processors
     */
    static __INLINE q63_t __SMLALD(q31_t x, q31_t y, q63_t sum) {
        return (
            sum +
            ((short) (x >> 16) * (short) (y >> 16)) +
            ((short) x * (short) y)
        );
    }

    /**
     * C custom defined SMLALDX for M3 and M0 processors
     */
    static __INLINE q63_t __SMLALDX(q31_t x, q31_t y, q63_t sum) {
        return (
            (sum + ((short) (x >> 16) * (short) y)) +
            ((short) x * (short) (y >> 16))
        );
    }

    /**
     * C custom defined SMUAD for M3 and M0 processors
     */
    static __INLINE q31_t __SMUAD(q31_t x, q31_t y) {
        return (
            ((x >> 16) * (y >> 16)) +
            (((x << 16) >> 16) * ((y << 16) >> 16))
        );
    }

    /**
     * C custom defined SMUSD for M3 and M0 processors
     */
    static __INLINE q31_t __SMUSD(q31_t x, q31_t y) {
        return (
            -((x >> 16) * (y >> 16)) + (((x << 16) >> 16) * ((y << 16) >> 16))
        );
    }
#endif

/**
 * Instance structure for the Q7 FIR filter.
 */
typedef struct {
    /* Number of filter coefficients in the filter. */
    uint16_t numTaps;
    /**
     * Points to the state variable array. The array is of length
     * numTaps+blockSize-1.
     */
    q7_t* pState;
    /* Points to the coefficient array. The array is of length numTaps.*/
    q7_t* pCoeffs;
} arm_fir_instance_q7;

/**
 * Instance structure for the Q15 FIR filter.
 */
typedef struct {
    /* Number of filter coefficients in the filter. */
    uint16_t numTaps;
    /**
     * Points to the state variable array. The array is of length
     * numTaps+blockSize-1.
     */
    q15_t* pState;
    /* Points to the coefficient array. The array is of length numTaps.*/
    q15_t* pCoeffs;
} arm_fir_instance_q15;

/**
 * Instance structure for the Q31 FIR filter.
 */
typedef struct {
    /* Number of filter coefficients in the filter. */
    uint16_t numTaps;
    /**
     * Points to the state variable array. The array is of
     * length numTaps+blockSize-1.
     */
    q31_t* pState;
    /* Points to the coefficient array. The array is of length numTaps. */
    q31_t* pCoeffs;
} arm_fir_instance_q31;

/**
 * Instance structure for the floating-point FIR filter.
 */
typedef struct {
    /* Number of filter coefficients in the filter. */
    uint16_t numTaps;
    /**
     * Points to the state variable array. The array is of length
     * numTaps+blockSize-1.
     */
    float32_t* pState;
    /* Points to the coefficient array. The array is of length numTaps. */
    float32_t* pCoeffs;
} arm_fir_instance_f32;

/**
 * Processing function for the Q7 FIR filter.
 * param *S points to an instance of the Q7 FIR filter structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_fir_q7(
    const arm_fir_instance_q7* S, q7_t* pSrc,
    q7_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q7 FIR filter.
 * param *S points to an instance of the Q7 FIR structure.
 * param numTaps  Number of filter coefficients in the filter.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * param blockSize number of samples that are processed.
 * return none
 */
void arm_fir_init_q7(
    arm_fir_instance_q7* S, uint16_t numTaps,
    q7_t* pCoeffs, q7_t* pState,
    uint32_t blockSize
);

/**
 * Processing function for the Q15 FIR filter.
 * param *S points to an instance of the Q15 FIR structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_fir_q15(
    const arm_fir_instance_q15* S, q15_t* pSrc,
    q15_t* pDst, uint32_t blockSize
);

/**
 * Processing function for the fast Q15 FIR filter for Cortex-M3 and Cortex-M4.
 * param *S points to an instance of the Q15 FIR filter structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_fir_fast_q15(
    const arm_fir_instance_q15* S, q15_t* pSrc,
    q15_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q15 FIR filter.
 * param *S points to an instance of the Q15 FIR filter structure.
 * param numTaps  Number of filter coefficients in the filter.
 * Must be even and greater than or equal to 4.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * param blockSize number of samples that are processed at a time.
 * return The function returns ARM_MATH_SUCCESS if initialization was
 * successful or ARM_MATH_ARGUMENT_ERROR if
 * numTaps is not a supported value.
 */
arm_status arm_fir_init_q15(
    arm_fir_instance_q15* S, uint16_t numTaps,
    q15_t* pCoeffs, q15_t* pState, uint32_t blockSize
);

/**
 * Processing function for the Q31 FIR filter.
 * param *S points to an instance of the Q31 FIR filter structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_fir_q31(
    const arm_fir_instance_q31* S, q31_t* pSrc,
    q31_t* pDst, uint32_t blockSize
);

/**
 * Processing function for the fast Q31 FIR filter for Cortex-M3 and Cortex-M4.
 * param *S points to an instance of the Q31 FIR structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_fir_fast_q31(
    const arm_fir_instance_q31* S, q31_t* pSrc,
    q31_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q31 FIR filter.
 * param *S points to an instance of the Q31 FIR structure.
 * param numTaps  Number of filter coefficients in the filter.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * param blockSize number of samples that are processed at a time.
 * return none.
 */
void arm_fir_init_q31(
    arm_fir_instance_q31* S, uint16_t numTaps,
    q31_t* pCoeffs, q31_t* pState, uint32_t blockSize
);

/**
 * Processing function for the floating-point FIR filter.
 * param *S points to an instance of the floating-point FIR structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_fir_f32(
    const arm_fir_instance_f32* S, float32_t* pSrc,
    float32_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the floating-point FIR filter.
 * param *S points to an instance of the floating-point FIR filter structure.
 * param numTaps  Number of filter coefficients in the filter.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * param blockSize number of samples that are processed at a time.
 * return none.
 */
void arm_fir_init_f32(
    arm_fir_instance_f32* S, uint16_t numTaps, float32_t* pCoeffs,
    float32_t* pState, uint32_t blockSize
);

/**
 * Instance structure for the Q15 Biquad cascade filter.
 */
typedef struct {
    /**
     * Number of 2nd order stages in the filter.
     * Overall order is 2*numStages.
     */
    int8_t numStages;
    /**
     * Points to the array of state coefficients.
     * The array is of length 4*numStages.
     */
    q15_t* pState;
    /**
     * Points to the array of coefficients.
     * The array is of length 5*numStages.
     */
    q15_t* pCoeffs;
    /* Additional shift, in bits, applied to each output sample. */
    int8_t postShift;
} arm_biquad_casd_df1_inst_q15;

/**
 * Instance structure for the Q31 Biquad cascade filter.
 */
typedef struct {
    /**
     * Number of 2nd order stages in the filter.
     * Overall order is 2*numStages.
     */
    uint32_t numStages;
    /**
     * Points to the array of state coefficients.
     * The array is of length 4*numStages.
     */
    q31_t* pState;
    /**
     * Points to the array of coefficients.
     * The array is of length 5*numStages.
     */
    q31_t* pCoeffs;
    /* Additional shift, in bits, applied to each output sample. */
    uint8_t postShift;
} arm_biquad_casd_df1_inst_q31;

/**
 * Instance structure for the floating-point Biquad cascade filter.
 */
typedef struct {
    /**
     * Number of 2nd order stages in the filter.
     * Overall order is 2*numStages.
     */
    uint32_t numStages;
    /**
     * Points to the array of state coefficients.
     * The array is of length 4*numStages.
     */
    float32_t* pState;
    /** 
     * Points to the array of coefficients.
     * The array is of length 5*numStages.
     */
    float32_t* pCoeffs;
} arm_biquad_casd_df1_inst_f32;

/**
 * Processing function for the Q15 Biquad cascade filter.
 * param *S points to an instance of the Q15 Biquad cascade structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_biquad_cascade_df1_q15(
    const arm_biquad_casd_df1_inst_q15* S, q15_t* pSrc,
    q15_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q15 Biquad cascade filter.
 * param *S points to an instance of the Q15 Biquad cascade structure.
 * param numStages number of 2nd order stages in the filter.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * param postShift Shift to be applied to the output.
 * Varies according to the coefficients format
 * return none
 */
void arm_biquad_cascade_df1_init_q15(
    arm_biquad_casd_df1_inst_q15* S, uint8_t numStages,
    q15_t* pCoeffs, q15_t* pState, int8_t postShift
);

/**
 * Fast but less precise processing function for the Q15 Biquad cascade
 * filter for Cortex-M3 and Cortex-M4.
 * param *S points to an instance of the Q15 Biquad cascade structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_biquad_cascade_df1_fast_q15(
    const arm_biquad_casd_df1_inst_q15* S, q15_t* pSrc,
    q15_t* pDst, uint32_t blockSize
);

/**
 * Processing function for the Q31 Biquad cascade filter
 * param *S points to an instance of the Q31 Biquad cascade structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_biquad_cascade_df1_q31(
    const arm_biquad_casd_df1_inst_q31* S, q31_t* pSrc,
    q31_t* pDst, uint32_t blockSize
);

/**
 * Fast but less precise processing function for the Q31 Biquad cascade
 * filter for Cortex-M3 and Cortex-M4.
 * param *S points to an instance of the Q31 Biquad cascade structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_biquad_cascade_df1_fast_q31(
    const arm_biquad_casd_df1_inst_q31* S, q31_t* pSrc,
    q31_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q31 Biquad cascade filter.
 * param *S points to an instance of the Q31 Biquad cascade structure.
 * param numStages number of 2nd order stages in the filter.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * param postShift Shift to be applied to the output.
 * Varies according to the coefficients format
 * return none
 */
void arm_biquad_cascade_df1_init_q31(
    arm_biquad_casd_df1_inst_q31* S, uint8_t numStages,
    q31_t* pCoeffs, q31_t* pState, int8_t postShift
);

/**
 * Processing function for the floating-point Biquad cascade filter.
 * param *S points to an instance of floating-point Biquad cascade structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize  number of samples to process.
 * return none.
 */
void arm_biquad_cascade_df1_f32(
    const arm_biquad_casd_df1_inst_f32* S, float32_t* pSrc,
    float32_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the floating-point Biquad cascade filter.
 * param *S points to an instance of floating-point Biquad cascade structure.
 * param numStages number of 2nd order stages in the filter.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * return none
 */
void arm_biquad_cascade_df1_init_f32(
    arm_biquad_casd_df1_inst_f32* S, uint8_t numStages,
    float32_t* pCoeffs, float32_t* pState
);

/**
 * Instance structure for the floating-point matrix structure.
 */
typedef struct {
    uint16_t numRows; /* number of rows of the matrix. */
    uint16_t numCols; /* number of columns of the matrix. */
    float32_t* pData; /* points to the data of the matrix.*/
} arm_matrix_instance_f32;

/**
 * Instance structure for the Q15 matrix structure.
 */
typedef struct {
    uint16_t numRows; /* number of rows of the matrix. */
    uint16_t numCols; /* number of columns of the matrix. */
    q15_t* pData; /* points to the data of the matrix.*/
} arm_matrix_instance_q15;

/**
 * Instance structure for the Q31 matrix structure.
 */
typedef struct {
    uint16_t numRows; /* number of rows of the matrix. */
    uint16_t numCols; /* number of columns of the matrix. */
    q31_t* pData; /* points to the data of the matrix. */
} arm_matrix_instance_q31;

/**
 * Floating-point matrix addition.
 * param *pSrcA points to the first input matrix structure
 * param *pSrcB points to the second input matrix structure
 * param *pDst points to output matrix structure
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_add_f32(
    const arm_matrix_instance_f32* pSrcA,
    const arm_matrix_instance_f32* pSrcB,
    arm_matrix_instance_f32* pDst
);

/**
 * Q15 matrix addition.
 * param *pSrcA points to the first input matrix structure
 * param *pSrcB points to the second input matrix structure
 * param *pDst points to output matrix structure
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_add_q15(
    const arm_matrix_instance_q15* pSrcA,
    const arm_matrix_instance_q15* pSrcB,
    arm_matrix_instance_q15* pDst
);

/**
 * Q31 matrix addition.
 * param *pSrcA points to the first input matrix structure
 * param *pSrcB points to the second input matrix structure
 * param *pDst points to output matrix structure
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_add_q31(
    const arm_matrix_instance_q31* pSrcA,
    const arm_matrix_instance_q31* pSrcB,
    arm_matrix_instance_q31* pDst
);

/**
 * Floating-point matrix transpose.
 * param *pSrc points to the input matrix
 * param *pDst points to the output matrix
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_trans_f32(
    const arm_matrix_instance_f32* pSrc, arm_matrix_instance_f32* pDst
);

/**
 * Q15 matrix transpose.
 * param *pSrc points to the input matrix
 * param *pDst points to the output matrix
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_trans_q15(
    const arm_matrix_instance_q15* pSrc, arm_matrix_instance_q15* pDst
);

/**
 * Q31 matrix transpose.
 * param *pSrc points to the input matrix
 * param *pDst points to the output matrix
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_trans_q31(
    const arm_matrix_instance_q31* pSrc, arm_matrix_instance_q31* pDst
);

/**
 * Floating-point matrix multiplication
 * param *pSrcA points to the first input matrix structure
 * param *pSrcB points to the second input matrix structure
 * param *pDst points to output matrix structure
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_mult_f32(
    const arm_matrix_instance_f32* pSrcA,
    const arm_matrix_instance_f32* pSrcB,
    arm_matrix_instance_f32* pDst
);

/**
 * Q15 matrix multiplication
 * param *pSrcA points to the first input matrix structure
 * param *pSrcB points to the second input matrix structure
 * param *pDst points to output matrix structure
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_mult_q15(
    const arm_matrix_instance_q15* pSrcA,
    const arm_matrix_instance_q15* pSrcB,
    arm_matrix_instance_q15* pDst,
    q15_t* pState
);

/**
 * Q15 matrix multiplication (fast variant) for Cortex-M3 and Cortex-M4
 * param *pSrcA  points to the first input matrix structure
 * param *pSrcB  points to the second input matrix structure
 * param *pDst   points to output matrix structure
 * param *pState points to the array for storing intermediate results
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_mult_fast_q15(
    const arm_matrix_instance_q15* pSrcA,
    const arm_matrix_instance_q15* pSrcB,
    arm_matrix_instance_q15* pDst,
    q15_t* pState
);

/**
 * Q31 matrix multiplication
 * param *pSrcA points to the first input matrix structure
 * param *pSrcB points to the second input matrix structure
 * param *pDst points to output matrix structure
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_mult_q31(
    const arm_matrix_instance_q31* pSrcA,
    const arm_matrix_instance_q31* pSrcB,
    arm_matrix_instance_q31* pDst
);

/**
 * Q31 matrix multiplication (fast variant) for Cortex-M3 and Cortex-M4
 * param *pSrcA points to the first input matrix structure
 * param *pSrcB points to the second input matrix structure
 * param *pDst points to output matrix structure
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_mult_fast_q31(
    const arm_matrix_instance_q31* pSrcA,
    const arm_matrix_instance_q31* pSrcB,
    arm_matrix_instance_q31* pDst
);

/**
 * Floating-point matrix subtraction
 * param *pSrcA points to the first input matrix structure
 * param *pSrcB points to the second input matrix structure
 * param *pDst points to output matrix structure
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_sub_f32(
    const arm_matrix_instance_f32* pSrcA,
    const arm_matrix_instance_f32* pSrcB,
    arm_matrix_instance_f32* pDst
);

/**
 * Q15 matrix subtraction
 * param *pSrcA points to the first input matrix structure
 * param *pSrcB points to the second input matrix structure
 * param *pDst points to output matrix structure
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_sub_q15(
    const arm_matrix_instance_q15* pSrcA,
    const arm_matrix_instance_q15* pSrcB,
    arm_matrix_instance_q15* pDst
);

/**
 * Q31 matrix subtraction
 * param *pSrcA points to the first input matrix structure
 * param *pSrcB points to the second input matrix structure
 * param *pDst points to output matrix structure
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_sub_q31(
    const arm_matrix_instance_q31* pSrcA,
    const arm_matrix_instance_q31* pSrcB,
    arm_matrix_instance_q31* pDst
);

/**
 * Floating-point matrix scaling.
 * param *pSrc points to the input matrix
 * param scale scale factor
 * param *pDst points to the output matrix
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_scale_f32(
    const arm_matrix_instance_f32* pSrc, float32_t scale,
    arm_matrix_instance_f32* pDst
);

/**
 * Q15 matrix scaling.
 * param *pSrc points to input matrix
 * param scaleFract fractional portion of the scale factor
 * param shift number of bits to shift the result by
 * param *pDst points to output matrix
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_scale_q15(
    const arm_matrix_instance_q15* pSrc, q15_t scaleFract,
    int32_t shift, arm_matrix_instance_q15* pDst
);

/**
 * Q31 matrix scaling.
 * param *pSrc points to input matrix
 * param scaleFract fractional portion of the scale factor
 * param shift number of bits to shift the result by
 * param *pDst points to output matrix structure
 * return The function returns either ARM_MATH_SIZE_MISMATCH
 * or ARM_MATH_SUCCESS based on the outcome of size checking.
 */
arm_status arm_mat_scale_q31(
    const arm_matrix_instance_q31* pSrc, q31_t scaleFract,
    int32_t shift, arm_matrix_instance_q31* pDst
);

/**
 * Q31 matrix initialization.
 * param *S points to an instance of the floating-point matrix structure.
 * param nRows number of rows in the matrix.
 * param nColumns number of columns in the matrix.
 * param *pData points to the matrix data array.
 * return none
 */
void arm_mat_init_q31(
    arm_matrix_instance_q31* S, uint16_t nRows,
    uint16_t nColumns, q31_t* pData
);

/**
 * Q15 matrix initialization.
 * param *S points to an instance of the floating-point matrix structure.
 * param nRows number of rows in the matrix.
 * param nColumns number of columns in the matrix.
 * param *pData points to the matrix data array.
 * return none
 */
void arm_mat_init_q15(
    arm_matrix_instance_q15* S, uint16_t nRows,
    uint16_t nColumns, q15_t* pData
);

/**
 * Floating-point matrix initialization.
 * param *S points to an instance of the floating-point matrix structure.
 * param nRows number of rows in the matrix.
 * param nColumns number of columns in the matrix.
 * param *pData points to the matrix data array.
 * return none
 */
void arm_mat_init_f32(
    arm_matrix_instance_f32* S, uint16_t nRows,
    uint16_t nColumns, float32_t* pData
);

/**
 * Instance structure for the Q15 PID Control.
 */
typedef struct {
    q15_t A0; /* The derived gain, A0 = Kp + Ki + Kd . */
#ifdef ARM_MATH_CM0  
    q15_t A1;
    q15_t A2; 
#else       
    q31_t A1; /* The derived gain A1 = -Kp - 2Kd | Kd.*/
#endif 
    q15_t state[3]; /**< The state array of length 3. */
    q15_t Kp; /* The proportional gain. */
    q15_t Ki; /* The integral gain. */
    q15_t Kd; /* The derivative gain. */
} arm_pid_instance_q15;

/**
 * Instance structure for the Q31 PID Control.
 */
typedef struct {
    q31_t A0; /* The derived gain, A0 = Kp + Ki + Kd . */
    q31_t A1; /* The derived gain, A1 = -Kp - 2Kd. */
    q31_t A2; /* The derived gain, A2 = Kd . */
    q31_t state[3]; /* The state array of length 3. */
    q31_t Kp; /* The proportional gain. */
    q31_t Ki; /* The integral gain. */
    q31_t Kd; /* The derivative gain. */
} arm_pid_instance_q31;

/**
 * Instance structure for the floating-point PID Control.
 */
typedef struct {
    float32_t A0; /* The derived gain, A0 = Kp + Ki + Kd . */
    float32_t A1; /* The derived gain, A1 = -Kp - 2Kd. */
    float32_t A2; /* The derived gain, A2 = Kd . */
    float32_t state[3]; /* The state array of length 3. */
    float32_t Kp; /* The proportional gain. */
    float32_t Ki; /* The integral gain. */
    float32_t Kd; /* The derivative gain. */
} arm_pid_instance_f32;

/**
 * Initialization function for the floating-point PID Control.
 * param *S points to an instance of the PID structure.
 * param resetStateFlag flag to reset the state. 0 = no change
 * in state 1 = reset the state.
 * return none.
 */
void arm_pid_init_f32(arm_pid_instance_f32* S, int32_t resetStateFlag);

/**
 * Reset function for the floating-point PID Control.
 * param *S is an instance of the floating-point PID Control structure
 * return none
 */
void arm_pid_reset_f32(arm_pid_instance_f32* S);

/**
 * Initialization function for the Q31 PID Control.
 * param *S points to an instance of the Q15 PID structure.
 * param resetStateFlag flag to reset the state. 0 = no change
 * in state 1 = reset the state.
 * return none.
 */
void arm_pid_init_q31(arm_pid_instance_q31* S, int32_t resetStateFlag);

/**
 * Reset function for the Q31 PID Control.
 * param *S points to an instance of the Q31 PID Control structure
 * return none
 */
void arm_pid_reset_q31(arm_pid_instance_q31* S);

/**
 * Initialization function for the Q15 PID Control.
 * param *S points to an instance of the Q15 PID structure.
 * param resetStateFlag flag to reset the state. 0 = no change
 * in state 1 = reset the state.
 * return none.
 */
void arm_pid_init_q15(arm_pid_instance_q15* S, int32_t resetStateFlag);

/**
 *  Reset function for the Q15 PID Control.
 * param *S points to an instance of the q15 PID Control structure
 * return none
 */
void arm_pid_reset_q15(arm_pid_instance_q15* S);

/**
 * Instance structure for the floating-point Linear Interpolate function.
 */
typedef struct {
    uint32_t nValues;
    float32_t x1;
    float32_t xSpacing;
    float32_t* pYData; /* pointer to the table of Y values */
} arm_linear_interp_instance_f32;

/**
 * Instance structure for the floating-point bilinear interpolation function.
 */
typedef struct {
    uint16_t numRows;/* number of rows in the data table. */
    uint16_t numCols;/* number of columns in the data table. */
    float32_t* pData;/* points to the data table. */
} arm_bilinear_interp_instance_f32;

/**
 * Instance structure for the Q31 bilinear interpolation function.
 */
typedef struct {
    uint16_t numRows; /* number of rows in the data table. */
    uint16_t numCols; /* number of columns in the data table. */
    q31_t* pData; /* points to the data table. */
} arm_bilinear_interp_instance_q31;

/**
 * Instance structure for the Q15 bilinear interpolation function.
 */
typedef struct {
    uint16_t numRows; /* number of rows in the data table. */
    uint16_t numCols; /* number of columns in the data table. */
    q15_t* pData; /* points to the data table. */
} arm_bilinear_interp_instance_q15;

/**
 * Instance structure for the Q15 bilinear interpolation function.
 */
typedef struct {
    uint16_t numRows; /* number of rows in the data table. */
    uint16_t numCols; /* number of columns in the data table. */
    q7_t* pData; /* points to the data table. */
} arm_bilinear_interp_instance_q7;

/**
 * Q7 vector multiplication.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst  points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_mult_q7(q7_t* pSrcA, q7_t* pSrcB, q7_t* pDst, uint32_t blockSize);

/**
 * Q15 vector multiplication.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst  points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_mult_q15(q15_t* pSrcA, q15_t* pSrcB, q15_t* pDst, uint32_t blockSize);

/**
 * Q31 vector multiplication.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_mult_q31(q31_t* pSrcA, q31_t* pSrcB, q31_t* pDst, uint32_t blockSize);

/**
 * Floating-point vector multiplication.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_mult_f32(
    float32_t* pSrcA, float32_t* pSrcB, float32_t* pDst, uint32_t blockSize
);

/**
 * Instance structure for the Q15 CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen; /* length of the FFT. */
    /**
     * Flag that selects forward (ifftFlag=0) or
     * inverse (ifftFlag=1) transform.
     */
    uint8_t ifftFlag;
    /**
     * Flag that enables (bitReverseFlag=1) or disables
     * (bitReverseFlag=0) bit reversal of output.
     */
    uint8_t bitReverseFlag;
    q15_t* pTwiddle; /* points to the twiddle factor table. */
    uint16_t* pBitRevTable; /* points to the bit reversal table. */
    /**
     * Twiddle coefficient modifier that supports different size FFTs
     * with the same twiddle factor table.
     */
    uint16_t twidCoefModifier;
    /** Bit reversal modifier that supports different size FFTs
     * with the same bit reversal table.
     */
    uint16_t bitRevFactor;
} arm_cfft_radix4_instance_q15;

/**
 * Instance structure for the Q31 CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen; /* length of the FFT. */
    /**
     * Flag that selects forward (ifftFlag=0) or inverse
     * (ifftFlag=1) transform.
     */
    uint8_t ifftFlag;
    /**
     * Flag that enables (bitReverseFlag=1) or disables
     * (bitReverseFlag=0) bit reversal of output.
     */
    uint8_t bitReverseFlag;
    q31_t* pTwiddle; /* Points to the twiddle factor table. */
    uint16_t* pBitRevTable; /* Points to the bit reversal table. */
    /**
     * Twiddle coefficient modifier that supports different size FFTs
     * with the same twiddle factor table.
     */
    uint16_t twidCoefModifier;
    /**
     * Bit reversal modifier that supports different size FFTs
     * with the same bit reversal table.
     */
    uint16_t bitRevFactor;
} arm_cfft_radix4_instance_q31;

/**
 * Instance structure for the floating-point CFFT/CIFFT function.
 */
typedef struct {
    uint16_t fftLen; /* Length of the FFT. */
    /**
     * Flag that selects forward (ifftFlag=0) or
     * inverse (ifftFlag=1) transform.
     */
    uint8_t ifftFlag;
    /**
     * Flag that enables (bitReverseFlag=1) or disables
     * (bitReverseFlag=0) bit reversal of output.
     */
    uint8_t bitReverseFlag;
    float32_t* pTwiddle; /* points to the twiddle factor table. */
    uint16_t* pBitRevTable; /* points to the bit reversal table. */
    /**
     * Twiddle coefficient modifier that supports different size FFTs
     * with the same twiddle factor table.
     */
    uint16_t twidCoefModifier;
    /**
     * Bit reversal modifier that supports different size FFTs
     * with the same bit reversal table.
     */
    uint16_t bitRevFactor;
    float32_t onebyfftLen; /* value of 1/fftLen. */
} arm_cfft_radix4_instance_f32;

/**
 * Processing function for the Q15 CFFT/CIFFT.
 * param *S points to an instance of the Q15 CFFT/CIFFT structure.
 * param *pSrc points to the complex data buffer. Processing occurs in-place.
 * return none.
 */
void arm_cfft_radix4_q15(const arm_cfft_radix4_instance_q15* S, q15_t* pSrc);

/**
 * Initialization function for the Q15 CFFT/CIFFT.
 * param *S points to an instance of the Q15 CFFT/CIFFT structure.
 * param fftLen length of the FFT.
 * param ifftFlag flag that selects forward (ifftFlag=0) or
 * inverse (ifftFlag=1) transform.
 * param bitReverseFlag flag that enables (bitReverseFlag=1) or
 * disables (bitReverseFlag=0) bit reversal of output.
 * return arm_status function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_ARGUMENT_ERROR if fftLen is not a supported value.
 */
arm_status arm_cfft_radix4_init_q15(
    arm_cfft_radix4_instance_q15* S, uint16_t fftLen,
    uint8_t ifftFlag, uint8_t bitReverseFlag
);

/**
 * Processing function for the Q31 CFFT/CIFFT.
 * param *S points to an instance of the Q31 CFFT/CIFFT structure.
 * param *pSrc points to the complex data buffer. Processing occurs in-place.
 * return none.
 */
void arm_cfft_radix4_q31(const arm_cfft_radix4_instance_q31* S, q31_t* pSrc);

/**
 * Initialization function for the Q31 CFFT/CIFFT.
 * param *S points to an instance of the Q31 CFFT/CIFFT structure.
 * param fftLen length of the FFT.
 * param ifftFlag flag that selects forward (ifftFlag=0) or
 * inverse (ifftFlag=1) transform.
 * param bitReverseFlag flag that enables (bitReverseFlag=1) or disables
 * (bitReverseFlag=0) bit reversal of output.
 * return arm_status function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_ARGUMENT_ERROR if fftLen is not a supported value.
 */
arm_status arm_cfft_radix4_init_q31(
    arm_cfft_radix4_instance_q31* S, uint16_t fftLen,
    uint8_t ifftFlag, uint8_t bitReverseFlag
);

/**
 * Processing function for the floating-point CFFT/CIFFT.
 * param *S points to an instance of the floating-point CFFT/CIFFT structure.
 * param *pSrc points to the complex data buffer. Processing occurs in-place.
 * return none.
 */
void arm_cfft_radix4_f32(
    const arm_cfft_radix4_instance_f32* S, float32_t* pSrc
);

/**
 * Initialization function for the floating-point CFFT/CIFFT.
 * param *S points to an instance of the floating-point CFFT/CIFFT structure.
 * param fftLen length of the FFT.
 * param ifftFlag flag that selects forward (ifftFlag=0) or
 * inverse (ifftFlag=1) transform.
 * param bitReverseFlag flag that enables (bitReverseFlag=1) or disables
 * (bitReverseFlag=0) bit reversal of output.
 * return The function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_ARGUMENT_ERROR if fftLen is not a supported value.
 */
arm_status arm_cfft_radix4_init_f32(
    arm_cfft_radix4_instance_f32* S, uint16_t fftLen,
    uint8_t ifftFlag, uint8_t bitReverseFlag
);

/**
 * Core function for the floating-point CFFT butterfly process.
 * param *pSrc points to the in-place buffer of floating-point data type.
 * param fftLen length of the FFT.
 * param *pCoef points to the twiddle coefficient buffer.
 * param twidCoefModifier twiddle coefficient modifier that supports
 * different size FFTs with the same twiddle factor table.
 * return none.
 */
void arm_radix4_butterfly_f32(
    float32_t* pSrc, uint16_t fftLen,
    float32_t* pCoef, uint16_t twidCoefModifier
);

/**
 * Core function for the floating-point CIFFT butterfly process.
 * param *pSrc points to the in-place buffer of floating-point data type.
 * param fftLen length of the FFT.
 * param *pCoef points to twiddle coefficient buffer.
 * param twidCoefModifier twiddle coefficient modifier that supports
 * different size FFTs with the same twiddle factor table.
 * param onebyfftLen value of 1/fftLen.
 * return none.
 */
void arm_radix4_butterfly_inverse_f32(
    float32_t* pSrc, uint16_t fftLen, float32_t* pCoef,
    uint16_t twidCoefModifier, float32_t onebyfftLen
);

/**
 * In-place bit reversal function.
 * param *pSrc points to the in-place buffer of floating-point data type.
 * param fftSize length of the FFT.
 * param bitRevFactor bit reversal modifier that supports different
 * size FFTs with the same bit reversal table.
 * param *pBitRevTab points to the bit reversal table.
 * return none.
 */
void arm_bitreversal_f32(
    float32_t* pSrc, uint16_t fftSize,
    uint16_t bitRevFactor, uint16_t* pBitRevTab
);

/**
 * Core function for the Q31 CFFT butterfly process.
 * param *pSrc points to the in-place buffer of Q31 data type.
 * param fftLen length of the FFT.
 * param *pCoef points to twiddle coefficient buffer.
 * param twidCoefModifier twiddle coefficient modifier that supports
 * different size FFTs with the same twiddle factor table.
 * return none.
 */
void arm_radix4_butterfly_q31(
    q31_t* pSrc, uint32_t fftLen, q31_t* pCoef, uint32_t twidCoefModifier
);

/**
 * Core function for the Q31 CIFFT butterfly process.
 * param *pSrc points to the in-place buffer of Q31 data type.
 * param fftLen length of the FFT.
 * param *pCoef points to twiddle coefficient buffer.
 * param twidCoefModifier twiddle coefficient modifier that supports
 * different size FFTs with the same twiddle factor table.
 * return none.
 */
void arm_radix4_butterfly_inverse_q31(
    q31_t* pSrc, uint32_t fftLen, q31_t* pCoef, uint32_t twidCoefModifier
);

/**
 * In-place bit reversal function.
 * param *pSrc points to the in-place buffer of Q31 data type.
 * param fftLen length of the FFT.
 * param bitRevFactor bit reversal modifier that supports different
 * size FFTs with the same bit reversal table
 * param *pBitRevTab points to bit reversal table.
 * return none.
 */
void arm_bitreversal_q31(
    q31_t* pSrc, uint32_t fftLen, uint16_t bitRevFactor, uint16_t* pBitRevTab
);

/**
 * Core function for the Q15 CFFT butterfly process.
 * param *pSrc16 points to the in-place buffer of Q15 data type.
 * param fftLen length of the FFT.
 * param *pCoef16 points to twiddle coefficient buffer.
 * param twidCoefModifier twiddle coefficient modifier that supports
 * different size FFTs with the same twiddle factor table.
 * return none.
 */
void arm_radix4_butterfly_q15(
    q15_t* pSrc16, uint32_t fftLen, q15_t* pCoef16, uint32_t twidCoefModifier
);

/**
 * Core function for the Q15 CIFFT butterfly process.
 * param *pSrc16 points to the in-place buffer of Q15 data type.
 * param fftLen length of the FFT.
 * param *pCoef16 points to twiddle coefficient buffer.
 * param twidCoefModifier twiddle coefficient modifier that supports
 * different size FFTs with the same twiddle factor table.
 * return none.
 */
void arm_radix4_butterfly_inverse_q15(
    q15_t* pSrc16, uint32_t fftLen, q15_t* pCoef16, uint32_t twidCoefModifier
);

/**
 * In-place bit reversal function.
 * param *pSrc points to the in-place buffer of Q15 data type.
 * param fftLen length of the FFT.
 * param bitRevFactor bit reversal modifier that supports different
 * size FFTs with the same bit reversal table
 * param *pBitRevTab points to bit reversal table.
 * return none.
 */
void arm_bitreversal_q15(
    q15_t* pSrc, uint32_t fftLen, uint16_t bitRevFactor, uint16_t* pBitRevTab
);

/**
 * Instance structure for the Q15 RFFT/RIFFT function.
 */
typedef struct {
    uint32_t fftLenReal; /* Length of the real FFT. */
    uint32_t fftLenBy2; /* Length of the complex FFT. */
    /**
     * Flag that selects forward (ifftFlagR=0) or
     * inverse (ifftFlagR=1) transform.
     */
    uint8_t  ifftFlagR;
    /**
     * Flag that enables (bitReverseFlagR=1) or disables
     * (bitReverseFlagR=0) bit reversal of output.
     */
    uint8_t  bitReverseFlagR;
    /**
     * Twiddle coefficient modifier that supports different size FFTs
     * with the same twiddle factor table.
     */
    uint32_t twidCoefRModifier;
    q15_t* pTwiddleAReal; /* Points to the real twiddle factor table. */
    q15_t* pTwiddleBReal; /* Points to the imag twiddle factor table. */
    arm_cfft_radix4_instance_q15 *pCfft;/* Points to complex FFT instance. */
} arm_rfft_instance_q15;

/**
 * Instance structure for the Q31 RFFT/RIFFT function.
 */
typedef struct {
    uint32_t fftLenReal; /* Length of the real FFT. */
    uint32_t fftLenBy2; /* Length of the complex FFT. */
    /**
     * Flag that selects forward (ifftFlagR=0) or
     * inverse (ifftFlagR=1) transform.
     */
    uint8_t ifftFlagR;
    /**
     * Flag that enables (bitReverseFlagR=1) or disables
     * (bitReverseFlagR=0) bit reversal of output.
     */
    uint8_t bitReverseFlagR;
    /**
     * Twiddle coefficient modifier that supports different size FFTs
     * with the same twiddle factor table.
     */
    uint32_t twidCoefRModifier;
    q31_t* pTwiddleAReal; /* Points to the real twiddle factor table. */
    q31_t* pTwiddleBReal; /* Points to the imag twiddle factor table. */
    arm_cfft_radix4_instance_q31* pCfft; /* Points to complex FFT instance. */
} arm_rfft_instance_q31;

/**
 * Instance structure for the floating-point RFFT/RIFFT function.
 */
typedef struct {
    uint32_t fftLenReal; /* Length of the real FFT. */
    uint16_t fftLenBy2; /* Length of the complex FFT. */
    /**
     * Flag that selects forward (ifftFlagR=0) or
     * inverse (ifftFlagR=1) transform.
     */
    uint8_t ifftFlagR;
    /**
     * Flag that enables (bitReverseFlagR=1) or disables
     * (bitReverseFlagR=0) bit reversal of output.
     */
    uint8_t bitReverseFlagR;
    /**
     * Twiddle coefficient modifier that supports different size FFTs
     * with the same twiddle factor table.
     */
    uint32_t twidCoefRModifier;
    float32_t* pTwiddleAReal; /* Points to real twiddle factor table. */
    float32_t* pTwiddleBReal; /* Points to imag twiddle factor table. */
    arm_cfft_radix4_instance_f32* pCfft; /* Points to complex FFT instance. */
} arm_rfft_instance_f32;

/**
 * Processing function for the Q15 RFFT/RIFFT.
 * param *S points to an instance of the Q15 RFFT/RIFFT structure.
 * param *pSrc points to the input buffer.
 * param *pDst points to the output buffer.
 * return none.
 */
void arm_rfft_q15(const arm_rfft_instance_q15* S, q15_t* pSrc, q15_t* pDst);

/**
 * Initialization function for the Q15 RFFT/RIFFT.
 * param *S points to an instance of the Q15 RFFT/RIFFT structure.
 * param *S_CFFT points to an instance of the Q15 CFFT/CIFFT structure.
 * param fftLenReal length of the FFT.
 * param ifftFlagR flag that selects forward (ifftFlagR=0) or
 * inverse (ifftFlagR=1) transform.
 * param bitReverseFlag flag that enables (bitReverseFlag=1) or
 * disables (bitReverseFlag=0) bit reversal of output.
 * returnThe function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_ARGUMENT_ERROR if fftLenReal is not
 * a supported value.
 */
arm_status arm_rfft_init_q15(
    arm_rfft_instance_q15* S, arm_cfft_radix4_instance_q15* S_CFFT,
    uint32_t fftLenReal, uint32_t ifftFlagR, uint32_t bitReverseFlag
);

/**
 * Processing function for the Q31 RFFT/RIFFT.
 * param *S points to an instance of the Q31 RFFT/RIFFT structure.
 * param *pSrc points to the input buffer.
 * param *pDst points to the output buffer.
 * return none.
 */
void arm_rfft_q31(const arm_rfft_instance_q31* S, q31_t* pSrc, q31_t* pDst);

/**
 * Initialization function for the Q31 RFFT/RIFFT.
 * param *S points to an instance of the Q31 RFFT/RIFFT structure.
 * param *S_CFFT points to an instance of the Q31 CFFT/CIFFT structure.
 * param fftLenReal length of the FFT.
 * param ifftFlagR flag that selects forward (ifftFlagR=0) or
 * inverse (ifftFlagR=1) transform.
 * param bitReverseFlag flag that enables (bitReverseFlag=1) or disables
 * (bitReverseFlag=0) bit reversal of output.
 * return The function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_ARGUMENT_ERROR if fftLenReal is not supported value.
 */
arm_status arm_rfft_init_q31(
    arm_rfft_instance_q31* S, arm_cfft_radix4_instance_q31* S_CFFT,
    uint32_t fftLenReal, uint32_t ifftFlagR, uint32_t bitReverseFlag
);

/**
 * Initialization function for the floating-point RFFT/RIFFT.
 * param *S points to an instance of the floating-point RFFT/RIFFT structure.
 * param *S_CFFT points to an instance of floating-point CFFT/CIFFT structure.
 * param fftLenReal length of the FFT.
 * param ifftFlagR flag that selects forward (ifftFlagR=0)
 * or inverse (ifftFlagR=1) transform.
 * param bitReverseFlag flag that enables (bitReverseFlag=1) or
 * disables (bitReverseFlag=0) bit reversal of output.
 * return function returns ARM_MATH_SUCCESS if initialization is successful
 * or ARM_MATH_ARGUMENT_ERROR if fftLenReal is not a supported value.
 */
arm_status arm_rfft_init_f32(
    arm_rfft_instance_f32* S, arm_cfft_radix4_instance_f32* S_CFFT,
    uint32_t fftLenReal, uint32_t ifftFlagR, uint32_t bitReverseFlag
);

/**
 * Processing function for the floating-point RFFT/RIFFT.
 * param *S points to an instance of the floating-point RFFT/RIFFT structure.
 * param *pSrc points to the input buffer.
 * param *pDst points to the output buffer.
 * return none.
 */
void arm_rfft_f32(
    const arm_rfft_instance_f32* S, float32_t* pSrc, float32_t* pDst
);

/**
 * Instance structure for the floating-point DCT4/IDCT4 function.
 */
typedef struct {
    uint16_t N; /* Length of the DCT4. */
    uint16_t Nby2; /* Half of the length of the DCT4. */
    float32_t normalize; /* Normalizing factor. */
    float32_t* pTwiddle; /* Points to the twiddle factor table. */
    float32_t* pCosFactor; /* Points to the cosFactor table. */
    arm_rfft_instance_f32* pRfft; /* Points to the real FFT instance. */
    arm_cfft_radix4_instance_f32* pCfft; /* Points to complex FFT instance. */
} arm_dct4_instance_f32;

/**
 * Initialization function for the floating-point DCT4/IDCT4.
 * param *S points to an instance of floating-point DCT4/IDCT4 structure.
 * param *S_RFFT points to an instance of floating-point RFFT/RIFFT structure.
 * param *S_CFFT points to an instance of floating-point CFFT/CIFFT structure.
 * param N length of the DCT4.
 * param Nby2 half of the length of the DCT4.
 * param normalize normalizing factor.
 * return arm_status function returns ARM_MATH_SUCCESS if initialization
 * is successful or ARM_MATH_ARGUMENT_ERROR if fftLenReal is not a supported
 * transform length.
 */
arm_status arm_dct4_init_f32(
    arm_dct4_instance_f32* S, arm_rfft_instance_f32* S_RFFT,
    arm_cfft_radix4_instance_f32* S_CFFT, uint16_t N,
    uint16_t Nby2, float32_t normalize
);

/**
 * Processing function for the floating-point DCT4/IDCT4.
 * param *S points to an instance of the floating-point DCT4/IDCT4 structure.
 * param *pState points to state buffer.
 * param *pInlineBuffer points to the in-place input and output buffer.
 * return none.
 */
void arm_dct4_f32(
    const arm_dct4_instance_f32* S,
    float32_t* pState,
    float32_t* pInlineBuffer
);

/**
 * Instance structure for the Q31 DCT4/IDCT4 function.
 */
typedef struct {
    uint16_t N; /* Length of the DCT4. */
    uint16_t Nby2; /* Half of the length of the DCT4. */
    q31_t normalize; /* Normalizing factor. */
    q31_t* pTwiddle; /* Points to the twiddle factor table. */
    q31_t* pCosFactor; /* Points to the cosFactor table. */
    arm_rfft_instance_q31* pRfft; /* Points to the real FFT instance. */
    arm_cfft_radix4_instance_q31* pCfft; /* Points to complex FFT instance. */
} arm_dct4_instance_q31;

/**
 * Initialization function for the Q31 DCT4/IDCT4.
 * param *S points to an instance of Q31 DCT4/IDCT4 structure.
 * param *S_RFFT points to an instance of Q31 RFFT/RIFFT structure
 * param *S_CFFT points to an instance of Q31 CFFT/CIFFT structure
 * param N length of the DCT4.
 * param Nby2 half of the length of the DCT4.
 * param normalize normalizing factor.
 * return arm_status function returns ARM_MATH_SUCCESS if initialization
 * is successful or ARM_MATH_ARGUMENT_ERROR if N is not a supported
 * transform length.
 */
arm_status arm_dct4_init_q31(
    arm_dct4_instance_q31* S, arm_rfft_instance_q31* S_RFFT,
    arm_cfft_radix4_instance_q31* S_CFFT, uint16_t N,
    uint16_t Nby2, q31_t normalize
);

/**
 * Processing function for the Q31 DCT4/IDCT4.
 * param *S points to an instance of the Q31 DCT4 structure.
 * param *pState points to state buffer.
 * param *pInlineBuffer points to the in-place input and output buffer.
 * return none.
 */
void arm_dct4_q31(
    const arm_dct4_instance_q31* S, q31_t* pState, q31_t* pInlineBuffer
);

/**
 * Instance structure for the Q15 DCT4/IDCT4 function.
 */
typedef struct {
    uint16_t N; /* Length of the DCT4. */
    uint16_t Nby2; /* Half of the length of the DCT4. */
    q15_t normalize; /* Normalizing factor. */
    q15_t* pTwiddle; /* Points to the twiddle factor table. */
    q15_t* pCosFactor; /* Points to the cosFactor table. */
    arm_rfft_instance_q15* pRfft; /* Points to the real FFT instance. */
    arm_cfft_radix4_instance_q15* pCfft; /* Points to complex FFT instance. */
} arm_dct4_instance_q15;

/**
 * Initialization function for the Q15 DCT4/IDCT4.
 * param *S points to an instance of Q15 DCT4/IDCT4 structure.
 * param *S_RFFT points to an instance of Q15 RFFT/RIFFT structure.
 * param *S_CFFT points to an instance of Q15 CFFT/CIFFT structure.
 * param N length of the DCT4.
 * param Nby2 half of the length of the DCT4.
 * param normalize  normalizing factor.
 * return arm_status function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_ARGUMENT_ERROR if N is not a supported
 * transform length.
 */
arm_status arm_dct4_init_q15(
    arm_dct4_instance_q15* S, arm_rfft_instance_q15* S_RFFT,
    arm_cfft_radix4_instance_q15* S_CFFT, uint16_t N,
    uint16_t Nby2, q15_t normalize
);

/**
 * Processing function for the Q15 DCT4/IDCT4.
 * param *S points to an instance of the Q15 DCT4 structure.
 * param *pState points to state buffer.
 * param *pInlineBuffer points to the in-place input and output buffer.
 * return none.
 */
void arm_dct4_q15(
    const arm_dct4_instance_q15* S, q15_t* pState, q15_t* pInlineBuffer
);

/**
 * Floating-point vector addition.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_add_f32(
    float32_t* pSrcA, float32_t* pSrcB, float32_t* pDst, uint32_t blockSize
);

/**
 * Q7 vector addition.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_add_q7(q7_t* pSrcA, q7_t* pSrcB, q7_t* pDst, uint32_t blockSize);

/**
 * Q15 vector addition.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_add_q15(q15_t* pSrcA, q15_t* pSrcB, q15_t* pDst, uint32_t blockSize);

/**
 * Q31 vector addition.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_add_q31(q31_t* pSrcA, q31_t* pSrcB, q31_t* pDst, uint32_t blockSize);

/**
 * Floating-point vector subtraction.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_sub_f32(
    float32_t* pSrcA, float32_t* pSrcB, float32_t* pDst, uint32_t blockSize
);

/**
 * Q7 vector subtraction.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_sub_q7(q7_t* pSrcA, q7_t* pSrcB, q7_t* pDst, uint32_t blockSize);

/**
 * Q15 vector subtraction.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_sub_q15(q15_t* pSrcA, q15_t* pSrcB, q15_t* pDst, uint32_t blockSize);

/**
 * Q31 vector subtraction.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_sub_q31(q31_t* pSrcA, q31_t* pSrcB, q31_t* pDst, uint32_t blockSize);

/**
 * Multiplies a floating-point vector by a scalar.
 * param *pSrc points to the input vector
 * param scale scale factor to be applied
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_scale_f32(
    float32_t* pSrc, float32_t scale, float32_t* pDst, uint32_t blockSize
);

/**
 * Multiplies a Q7 vector by a scalar.
 * param *pSrc points to the input vector
 * param scaleFract fractional portion of the scale value
 * param shift number of bits to shift the result by
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_scale_q7(
    q7_t* pSrc, q7_t scaleFract, int8_t shift, q7_t* pDst, uint32_t blockSize
);

/**
 * Multiplies a Q15 vector by a scalar.
 * param *pSrc points to the input vector
 * param scaleFract fractional portion of the scale value
 * param shift number of bits to shift the result by
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_scale_q15(
    q15_t* pSrc, q15_t scaleFract, int8_t shift,
    q15_t* pDst, uint32_t blockSize
);

/**
 * Multiplies a Q31 vector by a scalar.
 * param *pSrc points to the input vector
 * param scaleFract fractional portion of the scale value
 * param shift number of bits to shift the result by
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_scale_q31(
    q31_t* pSrc, q31_t scaleFract, int8_t shift,
    q31_t* pDst, uint32_t blockSize
);

/**
 * Q7 vector absolute value.
 * param *pSrc points to the input buffer
 * param *pDst points to the output buffer
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_abs_q7(q7_t* pSrc, q7_t* pDst, uint32_t blockSize);

/**
 * Floating-point vector absolute value.
 * param *pSrc points to the input buffer
 * param *pDst points to the output buffer
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_abs_f32(float32_t* pSrc, float32_t* pDst, uint32_t blockSize);

/**
 * Q15 vector absolute value.
 * param *pSrc points to the input buffer
 * param *pDst points to the output buffer
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_abs_q15(q15_t* pSrc, q15_t* pDst, uint32_t blockSize);

/**
 * Q31 vector absolute value.
 * param *pSrc points to the input buffer
 * param *pDst points to the output buffer
 * param blockSize number of samples in each vector
 * return none.
 */
void arm_abs_q31(q31_t* pSrc, q31_t* pDst, uint32_t blockSize);

/**
 * Dot product of floating-point vectors.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param blockSize number of samples in each vector
 * param *result output result returned here
 * return none.
 */
void arm_dot_prod_f32(
    float32_t* pSrcA, float32_t* pSrcB, uint32_t blockSize, float32_t* result
);

/**
 * Dot product of Q7 vectors.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param blockSize number of samples in each vector
 * param *result output result returned here
 * return none.
 */
void arm_dot_prod_q7(
    q7_t* pSrcA, q7_t* pSrcB, uint32_t blockSize, q31_t* result
);

/**
 * Dot product of Q15 vectors.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param blockSize number of samples in each vector
 * param *result output result returned here
 * return none.
 */
void arm_dot_prod_q15(
    q15_t* pSrcA, q15_t* pSrcB, uint32_t blockSize, q63_t* result
);

/**
 * Dot product of Q31 vectors.
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param blockSize number of samples in each vector
 * param *result output result returned here
 * return none.
 */
void arm_dot_prod_q31(
    q31_t* pSrcA, q31_t* pSrcB, uint32_t blockSize, q63_t* result
);

/**
 * Shifts the elements of a Q7 vector a specified number of bits.
 * param *pSrc points to the input vector
 * param shiftBits number of bits to shift. A positive value shifts left;
 * a negative value shifts right.
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_shift_q7(
    q7_t* pSrc, int8_t shiftBits, q7_t* pDst, uint32_t blockSize
);

/**
 * Shifts the elements of a Q15 vector a specified number of bits.
 * param *pSrc points to the input vector
 * param shiftBits number of bits to shift. A positive value shifts left;
 * a negative value shifts right.
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_shift_q15(
    q15_t* pSrc, int8_t shiftBits, q15_t* pDst, uint32_t blockSize
);

/**
 * Shifts the elements of a Q31 vector a specified number of bits.
 * param *pSrc points to the input vector
 * param shiftBits number of bits to shift. A positive value shifts left;
 * a negative value shifts right.
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_shift_q31(
    q31_t* pSrc, int8_t shiftBits, q31_t* pDst, uint32_t blockSize
);

/**
 * Adds a constant offset to a floating-point vector.
 * param *pSrc points to the input vector
 * param offset is the offset to be added
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_offset_f32(
    float32_t* pSrc, float32_t offset, float32_t* pDst, uint32_t blockSize
);

/**
 * Adds a constant offset to a Q7 vector.
 * param *pSrc points to the input vector
 * param offset is the offset to be added
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_offset_q7(q7_t* pSrc, q7_t offset, q7_t* pDst, uint32_t blockSize);

/**
 * Adds a constant offset to a Q15 vector.
 * param *pSrc points to the input vector
 * param offset is the offset to be added
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_offset_q15(
    q15_t* pSrc, q15_t offset, q15_t* pDst, uint32_t blockSize
);

/**
 * Adds a constant offset to a Q31 vector.
 * param *pSrc points to the input vector
 * param offset is the offset to be added
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_offset_q31(
    q31_t* pSrc, q31_t offset, q31_t* pDst, uint32_t blockSize
);

/**
 * Negates the elements of a floating-point vector.
 * param *pSrc points to the input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_negate_f32(float32_t* pSrc, float32_t* pDst, uint32_t blockSize);

/**
 * Negates the elements of a Q7 vector.
 * param *pSrc points to the input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_negate_q7(q7_t* pSrc, q7_t* pDst, uint32_t blockSize);

/**
 * Negates the elements of a Q15 vector.
 * param *pSrc points to the input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_negate_q15(q15_t* pSrc, q15_t* pDst, uint32_t blockSize);

/**
 * Negates the elements of a Q31 vector.
 * param *pSrc points to the input vector
 * param *pDst points to the output vector
 * param blockSize number of samples in the vector
 * return none.
 */
void arm_negate_q31(q31_t* pSrc, q31_t* pDst, uint32_t blockSize);
/**
 * Copies the elements of a floating-point vector. 
 * param *pSrc input pointer
 * param *pDst output pointer
 * param blockSize number of samples to process
 * return none.
 */
void arm_copy_f32(float32_t* pSrc, float32_t* pDst, uint32_t blockSize);

/**
 * Copies the elements of a Q7 vector. 
 * param *pSrc input pointer
 * param *pDst output pointer
 * param blockSize number of samples to process
 * return none.
 */
void arm_copy_q7(q7_t* pSrc, q7_t* pDst, uint32_t blockSize);

/**
 * Copies the elements of a Q15 vector. 
 * param *pSrc input pointer
 * param *pDst output pointer
 * param blockSize number of samples to process
 * return none.
 */
void arm_copy_q15(q15_t* pSrc, q15_t* pDst, uint32_t blockSize);

/**
 * Copies the elements of a Q31 vector. 
 * param *pSrc input pointer
 * param *pDst output pointer
 * param blockSize number of samples to process
 * return none.
 */
void arm_copy_q31(q31_t* pSrc, q31_t* pDst, uint32_t blockSize);

/**
 * Fills a constant value into a floating-point vector. 
 * param value input value to be filled
 * param *pDst output pointer
 * param blockSize number of samples to process
 * return none.
 */
void arm_fill_f32(float32_t value, float32_t* pDst, uint32_t blockSize);

/**
 * Fills a constant value into a Q7 vector. 
 * param value input value to be filled
 * param *pDst output pointer
 * param blockSize number of samples to process
 * return none.
 */
void arm_fill_q7(q7_t value, q7_t* pDst, uint32_t blockSize);

/**
 * Fills a constant value into a Q15 vector. 
 * param value input value to be filled
 * param *pDst output pointer
 * param blockSize number of samples to process
 * return none.
 */
void arm_fill_q15(q15_t value, q15_t* pDst, uint32_t blockSize);

/**
 * Fills a constant value into a Q31 vector. 
 * param value input value to be filled
 * param *pDst output pointer
 * param blockSize number of samples to process
 * return none.
 */
void arm_fill_q31(q31_t value, q31_t* pDst, uint32_t blockSize);

/**
 * Convolution of floating-point sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the location where the output result is written.
 * Length srcALen+srcBLen-1.
 * return none.
 */
void arm_conv_f32(
    float32_t* pSrcA, uint32_t srcALen, float32_t* pSrcB,
    uint32_t srcBLen, float32_t* pDst
);

/**
 * Convolution of Q15 sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the location where the output result is written.
 * Length srcALen+srcBLen-1.
 * return none.
 */
void arm_conv_q15(
    q15_t* pSrcA, uint32_t srcALen, q15_t* pSrcB,
    uint32_t srcBLen, q15_t* pDst
);

/**
 * Convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data  Length srcALen+srcBLen-1.
 * return none.
 */
void arm_conv_fast_q15(
    q15_t* pSrcA, uint32_t srcALen, q15_t* pSrcB,
    uint32_t srcBLen, q15_t* pDst
);

/**
 * Convolution of Q31 sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data  Length srcALen+srcBLen-1.
 * return none.
 */
void arm_conv_q31(
    q31_t* pSrcA, uint32_t srcALen, q31_t* pSrcB,
    uint32_t srcBLen, q31_t* pDst
);

/**
 * Convolution of Q31 sequences (fast version) for Cortex-M3 and Cortex-M4
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data  Length srcALen+srcBLen-1.
 * return none.
 */
void arm_conv_fast_q31(
    q31_t* pSrcA, uint32_t srcALen, q31_t* pSrcB,
    uint32_t srcBLen, q31_t* pDst
);

/**
 * Convolution of Q7 sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data  Length srcALen+srcBLen-1.
 * return none.
 */
void arm_conv_q7(
    q7_t* pSrcA, uint32_t srcALen, q7_t* pSrcB,
    uint32_t srcBLen, q7_t* pDst
);

/**
 * Partial convolution of floating-point sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data
 * param firstIndex is the first output sample to start with.
 * param numPoints is the number of output points to be computed.
 * return  Returns either ARM_MATH_SUCCESS if the function completed
 * correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not
 * in the range [0 srcALen+srcBLen-2].
 */
arm_status arm_conv_partial_f32(
    float32_t* pSrcA, uint32_t srcALen, float32_t* pSrcB, uint32_t srcBLen,
    float32_t* pDst, uint32_t firstIndex, uint32_t numPoints
);

/**
 * Partial convolution of Q15 sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data
 * param firstIndex is the first output sample to start with.
 * param numPoints is the number of output points to be computed.
 * return  Returns either ARM_MATH_SUCCESS if the function completed
 * correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in
 * the range [0 srcALen+srcBLen-2].
 */
arm_status arm_conv_partial_q15(
    q15_t* pSrcA, uint32_t srcALen, q15_t* pSrcB, uint32_t srcBLen,
    q15_t* pDst, uint32_t firstIndex, uint32_t numPoints
);

/**
 * Partial convolution of Q15 sequences (fast) for Cortex-M3 and Cortex-M4
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data
 * param firstIndex is the first output sample to start with.
 * param numPoints is the number of output points to be computed.
 * return  Returns either ARM_MATH_SUCCESS if the function completed
 * correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not
 * in the range [0 srcALen+srcBLen-2].
 */
arm_status arm_conv_partial_fast_q15(
    q15_t* pSrcA, uint32_t srcALen, q15_t* pSrcB, uint32_t srcBLen,
    q15_t* pDst, uint32_t firstIndex, uint32_t numPoints
);

/**
 * Partial convolution of Q31 sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data
 * param firstIndex is the first output sample to start with.
 * param numPoints is the number of output points to be computed.
 * return Returns either ARM_MATH_SUCCESS if the function completed
 * correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not
 * in the range [0 srcALen+srcBLen-2].
 */
arm_status arm_conv_partial_q31(
    q31_t* pSrcA, uint32_t srcALen, q31_t* pSrcB, uint32_t srcBLen,
    q31_t* pDst, uint32_t firstIndex, uint32_t numPoints
);

/**
 * Partial convolution of Q31 sequences (fast) for Cortex-M3 and Cortex-M4
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data
 * param firstIndex is the first output sample to start with.
 * param numPoints is the number of output points to be computed.
 * return  Returns either ARM_MATH_SUCCESS if the function completed
 * correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in
 * the range [0 srcALen+srcBLen-2].
 */
arm_status arm_conv_partial_fast_q31(
    q31_t* pSrcA, uint32_t srcALen, q31_t* pSrcB, uint32_t srcBLen,
    q31_t* pDst, uint32_t firstIndex, uint32_t numPoints
);

/**
 * Partial convolution of Q7 sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data
 * param firstIndex is the first output sample to start with.
 * param numPoints is the number of output points to be computed.
 * return Returns either ARM_MATH_SUCCESS if the function completed
 * correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not
 * in the range [0 srcALen+srcBLen-2].
 */
arm_status arm_conv_partial_q7(
    q7_t* pSrcA, uint32_t srcALen, q7_t* pSrcB, uint32_t srcBLen,
    q7_t* pDst, uint32_t firstIndex, uint32_t numPoints
);

/**
 * Instance structure for the Q15 FIR decimator.
 */
typedef struct {
    uint8_t M; /* Decimation factor. */
    uint16_t numTaps; /* Number of coefficients in the filter. */
    /* Points to the coefficient array. The array is of length numTaps.*/
    q15_t* pCoeffs;
    /* Points to state variable array (length numTaps+blockSize-1). */
    q15_t* pState;
} arm_fir_decimate_instance_q15;

/**
 * Instance structure for the Q31 FIR decimator.
 */
typedef struct {
    uint8_t M; /* Decimation factor. */
    uint16_t numTaps; /* Number of coefficients in the filter. */
    /* Points to the coefficient array. The array is of length numTaps.*/
    q31_t* pCoeffs;
    /* Points to state variable array (length numTaps+blockSize-1) . */
    q31_t* pState;
} arm_fir_decimate_instance_q31;

/**
 * Instance structure for the floating-point FIR decimator.
 */
typedef struct {
    uint8_t M; /* Decimation factor. */
    uint16_t numTaps; /* Number of coefficients in the filter. */
    /* Points to the coefficient array. The array is of length numTaps.*/
    float32_t* pCoeffs;
    /* Points to state variable array (length numTaps+blockSize-1). */
    float32_t* pState;
} arm_fir_decimate_instance_f32;

/**
 * Processing function for the floating-point FIR decimator.
 * param *S points to an instance of floating-point FIR decimator structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param blockSize number of input samples to process per call.
 * return none
 */
void arm_fir_decimate_f32(
    const arm_fir_decimate_instance_f32* S, float32_t* pSrc,
    float32_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the floating-point FIR decimator.
 * param *S points to an instance of floating-point FIR decimator structure.
 * param numTaps  number of coefficients in the filter.
 * param M  decimation factor.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * param blockSize number of input samples to process per call.
 * return The function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_LENGTH_ERROR if blockSize is not a multiple of M.
 */
arm_status arm_fir_decimate_init_f32(
    arm_fir_decimate_instance_f32* S, uint16_t numTaps, uint8_t M,
    float32_t* pCoeffs, float32_t* pState, uint32_t blockSize
);

/**
 * Processing function for the Q15 FIR decimator.
 * param *S points to an instance of the Q15 FIR decimator structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param blockSize number of input samples to process per call.
 * return none
 */
void arm_fir_decimate_q15(
    const arm_fir_decimate_instance_q15* S, q15_t* pSrc,
    q15_t* pDst, uint32_t blockSize
);

/**
 * Processing function for Q15 FIR decimator (fast) for Cortex-M3/Cortex-M4.
 * param *S points to an instance of the Q15 FIR decimator structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param blockSize number of input samples to process per call.
 * return none
 */
void arm_fir_decimate_fast_q15(
    const arm_fir_decimate_instance_q15* S, q15_t* pSrc,
    q15_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q15 FIR decimator.
 * param *S points to an instance of the Q15 FIR decimator structure.
 * param numTaps  number of coefficients in the filter.
 * param M  decimation factor.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * param blockSize number of input samples to process per call.
 * return The function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_LENGTH_ERROR if blockSize is not a multiple of M.
 */
arm_status arm_fir_decimate_init_q15(
    arm_fir_decimate_instance_q15* S, uint16_t numTaps, uint8_t M,
    q15_t* pCoeffs, q15_t* pState, uint32_t blockSize
);

/**
 * Processing function for the Q31 FIR decimator.
 * param *S points to an instance of the Q31 FIR decimator structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param blockSize number of input samples to process per call.
 * return none
 */
void arm_fir_decimate_q31(
    const arm_fir_decimate_instance_q31* S, q31_t* pSrc,
    q31_t* pDst, uint32_t blockSize
);

/**
 * Processing function for Q31 FIR decimator (fast) for Cortex-M3/Cortex-M4.
 * param *S points to an instance of the Q31 FIR decimator structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param blockSize number of input samples to process per call.
 * return none
 */
void arm_fir_decimate_fast_q31(
    arm_fir_decimate_instance_q31* S, q31_t* pSrc,
    q31_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q31 FIR decimator.
 * param *S points to an instance of the Q31 FIR decimator structure.
 * param numTaps  number of coefficients in the filter.
 * param M  decimation factor.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * param blockSize number of input samples to process per call.
 * return The function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_LENGTH_ERROR if blockSize is not a multiple of M.
 */
arm_status arm_fir_decimate_init_q31(
    arm_fir_decimate_instance_q31* S, uint16_t numTaps, uint8_t M,
    q31_t* pCoeffs, q31_t* pState, uint32_t blockSize
);

/**
 * Instance structure for the Q15 FIR interpolator.
 */
typedef struct {
    uint8_t L; /* Upsample factor. */
    uint16_t phaseLength; /* Length of each polyphase filter component. */
    /* Points to the coefficient array (length L*phaseLength). */
    q15_t* pCoeffs;
    /* Points to the state variable array (length blockSize+phaseLength-1). */
    q15_t* pState;
} arm_fir_interpolate_instance_q15;

/**
 * Instance structure for the Q31 FIR interpolator.
 */
typedef struct {
    uint8_t L; /* Upsample factor. */
    uint16_t phaseLength; /* Length of each polyphase filter component. */
    /* Points to the coefficient array (length L*phaseLength). */
    q31_t* pCoeffs;
    /* Points to the state variable array (length blockSize+phaseLength-1). */
    q31_t* pState;
} arm_fir_interpolate_instance_q31;

/**
 * Instance structure for the floating-point FIR interpolator.
 */
typedef struct {
    uint8_t L; /* Upsample factor. */
    uint16_t phaseLength; /* Length of each polyphase filter component. */
    /* Points to the coefficient array (length L*phaseLength). */
    float32_t* pCoeffs;
    /* Points to the state variable array (length phaseLength+numTaps-1). */
    float32_t* pState;
} arm_fir_interpolate_instance_f32;

/**
 * Processing function for the Q15 FIR interpolator.
 * param *S points to an instance of the Q15 FIR interpolator structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of input samples to process per call.
 * return none.
 */
void arm_fir_interpolate_q15(
    const arm_fir_interpolate_instance_q15* S, q15_t* pSrc,
    q15_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q15 FIR interpolator.
 * param *S points to an instance of the Q15 FIR interpolator structure.
 * param L upsample factor.
 * param numTaps number of filter coefficients in the filter.
 * param *pCoeffs points to the filter coefficient buffer.
 * param *pState points to the state buffer.
 * param blockSize number of input samples to process per call.
 * return The function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_LENGTH_ERROR if
 * the filter length numTaps is not a multiple of the interpolation factor L.
 */
arm_status arm_fir_interpolate_init_q15(
    arm_fir_interpolate_instance_q15* S, uint8_t L, uint16_t numTaps,
    q15_t* pCoeffs, q15_t* pState, uint32_t blockSize
);

/**
 * Processing function for the Q31 FIR interpolator.
 * param *S points to an instance of the Q15 FIR interpolator structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of input samples to process per call.
 * return none.
 */
void arm_fir_interpolate_q31(
    const arm_fir_interpolate_instance_q31* S, q31_t* pSrc,
    q31_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q31 FIR interpolator.
 * param *S points to an instance of the Q31 FIR interpolator structure.
 * param L upsample factor.
 * param numTaps number of filter coefficients in the filter.
 * param *pCoeffs points to the filter coefficient buffer.
 * param *pState points to the state buffer.
 * param blockSize number of input samples to process per call.
 * return The function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_LENGTH_ERROR if the filter length numTaps
 * is not a multiple of the interpolation factor L.
 */
arm_status arm_fir_interpolate_init_q31(
    arm_fir_interpolate_instance_q31* S, uint8_t L, uint16_t numTaps,
    q31_t* pCoeffs, q31_t* pState, uint32_t blockSize
);

/**
 * Processing function for the floating-point FIR interpolator.
 * param *S points to an instance of floating-point FIR interpolator structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of input samples to process per call.
 * return none.
 */
void arm_fir_interpolate_f32(
    const arm_fir_interpolate_instance_f32* S, float32_t* pSrc,
    float32_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the floating-point FIR interpolator.
 * param *S points to an instance of floating-point FIR interpolator structure.
 * param L upsample factor.
 * param numTaps number of filter coefficients in the filter.
 * param *pCoeffs points to the filter coefficient buffer.
 * param *pState points to the state buffer.
 * param blockSize number of input samples to process per call.
 * return The function returns ARM_MATH_SUCCESS if initialization is
 * successful or ARM_MATH_LENGTH_ERROR if the filter length numTaps is not
 * a multiple of the interpolation factor L.
 */
arm_status arm_fir_interpolate_init_f32(
    arm_fir_interpolate_instance_f32* S, uint8_t L, uint16_t numTaps,
    float32_t* pCoeffs, float32_t* pState, uint32_t blockSize
);

/**
 * Instance structure for the high precision Q31 Biquad cascade filter.
 */
typedef struct {
    /**
     * Number of 2nd order stages in the filter.
     * Overall order is 2*numStages.
     */
    uint8_t numStages;
    /** Points to the array (length 4*numStages) of state coefficients. */
    q63_t* pState;
    /** Points to the array (length 5*numStages) of coefficients. */
    q31_t* pCoeffs;
    /* Additional shift, in bits, applied to each output sample. */
    uint8_t postShift;
} arm_biquad_cas_df1_32x64_ins_q31;

/**
 * param *S points to an instance of high precision Q31 Biquad
 * cascade filter structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param blockSize number of samples to process.
 * return none.
 */
void arm_biquad_cas_df1_32x64_q31(
    const arm_biquad_cas_df1_32x64_ins_q31* S, q31_t* pSrc,
    q31_t* pDst, uint32_t blockSize
);

/**
 * param *S points to an instance of the high precision Q31 Biquad
 * cascade filter structure.
 * param numStages number of 2nd order stages in the filter.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * param postShift shift to be applied to the output.
 * Varies according to the coefficients format
 * return none
 */
void arm_biquad_cas_df1_32x64_init_q31(
    arm_biquad_cas_df1_32x64_ins_q31* S, uint8_t numStages,
    q31_t* pCoeffs, q63_t* pState, uint8_t postShift
);

/**
 * Instance structure for the floating-point transposed direct
 * form II Biquad cascade filter.
 */
typedef struct {
    /**
     * Number of 2nd order stages in the filter.
     * Overall order is 2*numStages.
     */
    uint8_t numStages;
    /**
     * Points to the array of state coefficients.
     * The array is of length 2*numStages.
     */
    float32_t* pState;
    /**
     * Points to the array of coefficients.
     * The array is of length 5*numStages.
     */
    float32_t* pCoeffs;
} arm_biquad_cascade_df2T_instance_f32;

/**
 * Processing function for the floating-point transposed direct
 * form II Biquad cascade filter.
 * param *S points to an instance of the filter data structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param blockSize number of samples to process.
 * return none.
 */
void arm_biquad_cascade_df2T_f32(
    const arm_biquad_cascade_df2T_instance_f32* S,
    float32_t* pSrc, float32_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the floating-point transposed
 * direct form II Biquad cascade filter.
 * param *S points to an instance of the filter data structure.
 * param numStages number of 2nd order stages in the filter.
 * param *pCoeffs points to the filter coefficients.
 * param *pState points to the state buffer.
 * return none
 */
void arm_biquad_cascade_df2T_init_f32(
    arm_biquad_cascade_df2T_instance_f32* S, uint8_t numStages,
    float32_t* pCoeffs, float32_t* pState
);

/**
 * Instance structure for the Q15 FIR lattice filter.
 */
typedef struct {
    uint16_t numStages; /* Number of filter stages. */
    /**
     * Points to the state variable array.
     * The array is of length numStages.
     */
    q15_t* pState;
    /**
     * Points to the coefficient array.
     * The array is of length numStages.
     */
    q15_t* pCoeffs;
} arm_fir_lattice_instance_q15;

/**
 * Instance structure for the Q31 FIR lattice filter.
 */
typedef struct {
    uint16_t numStages; /* Number of filter stages. */
    /**
     * Points to the state variable array.
     * The array is of length numStages.
     */
    q31_t* pState;
    /* Points to the coefficient array. The array is of length numStages. */
    q31_t* pCoeffs;
} arm_fir_lattice_instance_q31;

/**
 * Instance structure for the floating-point FIR lattice filter.
 */
typedef struct {
    uint16_t numStages; /* Number of filter stages. */
    /* Points to the state variable array. The array is of length numStages. */
    float32_t* pState;
    /* Points to the coefficient array. The array is of length numStages. */
    float32_t* pCoeffs;
} arm_fir_lattice_instance_f32;

/**
 * Initialization function for the Q15 FIR lattice filter.
 * param *S points to an instance of the Q15 FIR lattice structure.
 * param numStages  number of filter stages.
 * param *pCoeffs points to coefficient buffer. Array is of length numStages.
 * param *pState points to state buffer. Array is of length numStages.
 * return none.
 */
void arm_fir_lattice_init_q15(
    arm_fir_lattice_instance_q15* S, uint16_t numStages,
    q15_t* pCoeffs, q15_t* pState
);

/**
 * Processing function for the Q15 FIR lattice filter.
 * param *S points to an instance of the Q15 FIR lattice structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_fir_lattice_q15(
    const arm_fir_lattice_instance_q15* S, q15_t* pSrc,
    q15_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q31 FIR lattice filter.
 * param *S points to an instance of the Q31 FIR lattice structure.
 * param numStages number of filter stages.
 * param *pCoeffs points to coefficient buffer. Array is of length numStages.
 * param *pState points to state buffer. Array is of length numStages.
 * return none.
 */
void arm_fir_lattice_init_q31(
    arm_fir_lattice_instance_q31* S, uint16_t numStages,
    q31_t* pCoeffs, q31_t* pState
);

/**
 * Processing function for the Q31 FIR lattice filter.
 * param *S points to an instance of the Q31 FIR lattice structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param blockSize number of samples to process.
 * return none.
 */
void arm_fir_lattice_q31(
    const arm_fir_lattice_instance_q31* S, q31_t* pSrc,
    q31_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the floating-point FIR lattice filter.
 * param *S points to an instance of the floating-point FIR lattice structure.
 * param numStages  number of filter stages.
 * param *pCoeffs points to coefficient buffer. Array is of length numStages.
 * param *pState points to state buffer. Array is of length numStages.
 * return none.
 */
void arm_fir_lattice_init_f32(
    arm_fir_lattice_instance_f32* S, uint16_t numStages,
    float32_t* pCoeffs, float32_t* pState
);

/**
 * Processing function for the floating-point FIR lattice filter.
 * param *S points to an instance of the floating-point FIR lattice structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param blockSize number of samples to process.
 * return none.
 */
void arm_fir_lattice_f32(
    const arm_fir_lattice_instance_f32* S, float32_t* pSrc,
    float32_t* pDst, uint32_t blockSize
);

/**
 * Instance structure for the Q15 IIR lattice filter.
 */
typedef struct {
    uint16_t numStages; /* Number of stages in the filter. */
    /**
     * Points to the state variable array.
     * The array is of length numStages+blockSize.
     */
    q15_t* pState;
    /**
     * Points to the reflection coefficient array.
     * The array is of length numStages.
     */
    q15_t* pkCoeffs;
    /**
     * Points to the ladder coefficient array.
     * The array is of length numStages+1.
     */
    q15_t* pvCoeffs;
} arm_iir_lattice_instance_q15;

/**
 * Instance structure for the Q31 IIR lattice filter.
 */
typedef struct {
    uint16_t numStages; /* Number of stages in the filter. */
    /**
     * Points to the state variable array.
     * The array is of length numStages+blockSize.
     */
    q31_t* pState;
    /**
     * Points to the reflection coefficient array.
     * The array is of length numStages.
     */
    q31_t* pkCoeffs;
    /**
     * Points to the ladder coefficient array.
     * The array is of length numStages+1.
     */
    q31_t* pvCoeffs;
} arm_iir_lattice_instance_q31;

/**
 * Instance structure for the floating-point IIR lattice filter.
 */
typedef struct {
    uint16_t numStages; /* Number of stages in the filter. */
    /**
     * Points to the state variable array.
     * The array is of length numStages+blockSize.
     */
    float32_t* pState;
    /**
     * Points to the reflection coefficient array.
     * The array is of length numStages.
     */
    float32_t* pkCoeffs;
    /**
     * Points to the ladder coefficient array.
     * The array is of length numStages+1.
     */
    float32_t* pvCoeffs;
} arm_iir_lattice_instance_f32;

/**
 * Processing function for the floating-point IIR lattice filter.
 * param *S points to an instance of the floating-point IIR lattice structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_iir_lattice_f32(
    const arm_iir_lattice_instance_f32* S, float32_t* pSrc,
    float32_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the floating-point IIR lattice filter.
 * param *S points to an instance of the floating-point IIR lattice structure.
 * param numStages number of stages in the filter.
 * param *pkCoeffs points to the reflection coefficient buffer.
 * The array is of length numStages.
 * param *pvCoeffs points to the ladder coefficient buffer.
 * The array is of length numStages+1.
 * param *pState points to the state buffer.
 * The array is of length numStages+blockSize-1.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_iir_lattice_init_f32(
    arm_iir_lattice_instance_f32* S, uint16_t numStages, float32_t* pkCoeffs,
    float32_t* pvCoeffs, float32_t* pState, uint32_t blockSize
);

/**
 * Processing function for the Q31 IIR lattice filter.
 * param *S points to an instance of the Q31 IIR lattice structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_iir_lattice_q31(
    const arm_iir_lattice_instance_q31* S, q31_t* pSrc,
    q31_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q31 IIR lattice filter.
 * param *S points to an instance of the Q31 IIR lattice structure.
 * param numStages number of stages in the filter.
 * param *pkCoeffs points to the reflection coefficient buffer.
 * The array is of length numStages.
 * param *pvCoeffs points to the ladder coefficient buffer.
 * The array is of length numStages+1.
 * param *pState points to the state buffer.
 * The array is of length numStages+blockSize.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_iir_lattice_init_q31(
    arm_iir_lattice_instance_q31* S, uint16_t numStages, q31_t* pkCoeffs,
    q31_t* pvCoeffs, q31_t* pState, uint32_t blockSize
);

/**
 * Processing function for the Q15 IIR lattice filter.
 * param *S points to an instance of the Q15 IIR lattice structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_iir_lattice_q15(
    const arm_iir_lattice_instance_q15* S, q15_t* pSrc,
    q15_t* pDst, uint32_t blockSize
);

/**
 * Initialization function for the Q15 IIR lattice filter.
 * param *S points to an instance of the fixed-point Q15 IIR lattice structure.
 * param numStages  number of stages in the filter.
 * param *pkCoeffs points to reflection coefficient buffer.
 * The array is of length numStages.
 * param *pvCoeffs points to ladder coefficient buffer.
 * The array is of length numStages+1.
 * param *pState points to state buffer. The array is of length
 * numStages+blockSize.
 * param blockSize number of samples to process per call.
 * return none.
 */
void arm_iir_lattice_init_q15(
    arm_iir_lattice_instance_q15* S, uint16_t numStages, q15_t* pkCoeffs,
    q15_t* pvCoeffs, q15_t* pState, uint32_t blockSize
);

/**
 * Instance structure for the floating-point LMS filter.
 */
typedef struct {
    uint16_t numTaps;  /* Number of coefficients in the filter. */
    /**
     * Points to the state variable array.
     * The array is of length numTaps+blockSize-1.
     */
    float32_t* pState;
    /**
     * Points to the coefficient array. The array is of length numTaps.
     */
    float32_t* pCoeffs;
    float32_t mu; /* Step size that controls filter coefficient updates. */
} arm_lms_instance_f32;

/**
 * Processing function for floating-point LMS filter.
 * param *S points to an instance of the floating-point LMS filter structure.
 * param *pSrc points to the block of input data.
 * param *pRef points to the block of reference data.
 * param *pOut points to the block of output data.
 * param *pErr points to the block of error data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_lms_f32(
    const arm_lms_instance_f32* S, float32_t* pSrc, float32_t* pRef,
    float32_t* pOut, float32_t* pErr, uint32_t blockSize
);

/**
 * Initialization function for floating-point LMS filter.
 * param *S points to an instance of the floating-point LMS filter structure.
 * param numTaps  number of filter coefficients.
 * param *pCoeffs points to the coefficient buffer.
 * param *pState points to state buffer.
 * param mu step size that controls filter coefficient updates.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_lms_init_f32(
    arm_lms_instance_f32* S, uint16_t numTaps, float32_t* pCoeffs,
    float32_t* pState, float32_t mu, uint32_t blockSize
);

/**
 * Instance structure for the Q15 LMS filter.
 */
typedef struct {
    uint16_t numTaps; /* Number of coefficients in the filter. */
    /**
     * Points to the state variable array. The array is of length
     * numTaps+blockSize-1.
     */
    q15_t* pState;
    /* Points to the coefficient array. The array is of length numTaps. */
    q15_t* pCoeffs;
    q15_t mu; /* Step size that controls filter coefficient updates. */
    uint32_t postShift;/* Bit shift applied to coefficients. */
} arm_lms_instance_q15;

/**
 * Initialization function for the Q15 LMS filter.
 * param *S points to an instance of the Q15 LMS filter structure.
 * param numTaps  number of filter coefficients.
 * param *pCoeffs points to the coefficient buffer.
 * param *pState points to the state buffer.
 * param mu step size that controls filter coefficient updates.
 * param blockSize number of samples to process.
 * param postShift bit shift applied to coefficients.
 * return none.
 */
void arm_lms_init_q15(
    arm_lms_instance_q15* S, uint16_t numTaps, q15_t* pCoeffs,
    q15_t* pState, q15_t mu, uint32_t blockSize, uint32_t postShift
);

/**
 * Processing function for Q15 LMS filter.
 * param *S points to an instance of the Q15 LMS filter structure.
 * param *pSrc points to the block of input data.
 * param *pRef points to the block of reference data.
 * param *pOut points to the block of output data.
 * param *pErr points to the block of error data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_lms_q15(
    const arm_lms_instance_q15* S, q15_t* pSrc, q15_t* pRef,
    q15_t* pOut, q15_t* pErr, uint32_t blockSize
);

/**
 * Instance structure for the Q31 LMS filter.
 */
typedef struct {
    uint16_t numTaps; /* Number of coefficients in the filter. */
    /**
     * Points to the state variable array.
     * The array is of length numTaps+blockSize-1.
     */
    q31_t* pState;
    /* Points to the coefficient array. The array is of length numTaps. */
    q31_t* pCoeffs;
    q31_t mu; /* Step size that controls filter coefficient updates. */
    uint32_t postShift; /* Bit shift applied to coefficients. */
} arm_lms_instance_q31;

/**
 * Processing function for Q31 LMS filter.
 * param *S points to an instance of the Q15 LMS filter structure.
 * param *pSrc points to the block of input data.
 * param *pRef points to the block of reference data.
 * param *pOut points to the block of output data.
 * param *pErr points to the block of error data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_lms_q31(
    const arm_lms_instance_q31* S, q31_t* pSrc, q31_t* pRef,
    q31_t* pOut, q31_t* pErr, uint32_t blockSize
);

/**
 * Initialization function for Q31 LMS filter.
 * param *S points to an instance of the Q31 LMS filter structure.
 * param numTaps  number of filter coefficients.
 * param *pCoeffs points to coefficient buffer.
 * param *pState points to state buffer.
 * param mu step size that controls filter coefficient updates.
 * param blockSize number of samples to process.
 * param postShift bit shift applied to coefficients.
 * return none.
 */
void arm_lms_init_q31(
    arm_lms_instance_q31* S, uint16_t numTaps, q31_t* pCoeffs, q31_t* pState,
    q31_t mu, uint32_t blockSize, uint32_t postShift
);

/**
 * Instance structure for the floating-point normalized LMS filter.
 */
typedef struct {
    uint16_t  numTaps; /* Number of coefficients in the filter. */
    /**
     * Points to the state variable array.
     * The array is of length numTaps+blockSize-1.
     */
    float32_t* pState;
    /* Points to the coefficient array. The array is of length numTaps. */
    float32_t* pCoeffs;
    float32_t mu; /* Step size that control filter coefficient updates. */
    float32_t energy; /* Saves previous frame energy. */
    float32_t x0; /* Saves previous input sample. */
} arm_lms_norm_instance_f32;

/**
 * Processing function for floating-point normalized LMS filter.
 * param *S points to an instance of the floating-point normalized
 * LMS filter structure.
 * param *pSrc points to the block of input data.
 * param *pRef points to the block of reference data.
 * param *pOut points to the block of output data.
 * param *pErr points to the block of error data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_lms_norm_f32(
    arm_lms_norm_instance_f32* S, float32_t* pSrc, float32_t* pRef,
    float32_t* pOut, float32_t* pErr, uint32_t blockSize
);

/**
 * Initialization function for floating-point normalized LMS filter.
 * param *S points to an instance of the floating-point LMS filter structure.
 * param numTaps  number of filter coefficients.
 * param *pCoeffs points to coefficient buffer.
 * param *pState points to state buffer.
 * param mu step size that controls filter coefficient updates.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_lms_norm_init_f32(
     arm_lms_norm_instance_f32* S, uint16_t numTaps, float32_t* pCoeffs,
     float32_t* pState, float32_t mu, uint32_t blockSize
);

/**
 * Instance structure for the Q31 normalized LMS filter.
 */
typedef struct {
    uint16_t numTaps; /* Number of coefficients in the filter. */
    /**
     * Points to the state variable array.
     * The array is of length numTaps+blockSize-1.
     */
    q31_t* pState;
    /**
     * Points to the coefficient array.
     * The array is of length numTaps.
     */
    q31_t* pCoeffs;
    q31_t mu; /* Step size that controls filter coefficient updates. */
    uint8_t postShift; /* Bit shift applied to coefficients. */
    q31_t* recipTable; /* Points to the reciprocal initial value table. */
    q31_t energy; /* Saves previous frame energy. */
    q31_t x0; /* Saves previous input sample. */
} arm_lms_norm_instance_q31;

/**
 * Processing function for Q31 normalized LMS filter.
 * param *S points to an instance of the Q31 normalized LMS filter structure.
 * param *pSrc points to the block of input data.
 * param *pRef points to the block of reference data.
 * param *pOut points to the block of output data.
 * param *pErr points to the block of error data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_lms_norm_q31(
    arm_lms_norm_instance_q31* S, q31_t* pSrc, q31_t* pRef,
    q31_t* pOut, q31_t* pErr, uint32_t blockSize
);

/**
 * Initialization function for Q31 normalized LMS filter.
 * param *S points to an instance of the Q31 normalized LMS filter structure.
 * param numTaps  number of filter coefficients.
 * param *pCoeffs points to coefficient buffer.
 * param *pState points to state buffer.
 * param mu step size that controls filter coefficient updates.
 * param blockSize number of samples to process.
 * param postShift bit shift applied to coefficients.
 * return none.
 */
void arm_lms_norm_init_q31(
    arm_lms_norm_instance_q31* S, uint16_t numTaps, q31_t* pCoeffs,
    q31_t* pState, q31_t mu, uint32_t blockSize, uint8_t postShift
);

/**
 * Instance structure for the Q15 normalized LMS filter.
 */
typedef struct {
    uint16_t numTaps; /* Number of coefficients in the filter. */
    /**
     * Points to the state variable array.
     * The array is of length numTaps+blockSize-1.
     */
    q15_t* pState;
    /* Points to the coefficient array. The array is of length numTaps. */
    q15_t* pCoeffs;
    q15_t mu; /* Step size that controls filter coefficient updates. */
    uint8_t postShift; /* Bit shift applied to coefficients. */
    q15_t* recipTable; /* Points to the reciprocal initial value table. */
    q15_t energy; /* Saves previous frame energy. */
    q15_t x0; /* Saves previous input sample. */
} arm_lms_norm_instance_q15;

/**
 * Processing function for Q15 normalized LMS filter.
 * param *S points to an instance of the Q15 normalized LMS filter structure.
 * param *pSrc points to the block of input data.
 * param *pRef points to the block of reference data.
 * param *pOut points to the block of output data.
 * param *pErr points to the block of error data.
 * param blockSize number of samples to process.
 * return none.
 */
void arm_lms_norm_q15(
    arm_lms_norm_instance_q15* S, q15_t* pSrc, q15_t* pRef,
    q15_t* pOut, q15_t* pErr, uint32_t blockSize
);

/**
 * Initialization function for Q15 normalized LMS filter.
 * param *S points to an instance of the Q15 normalized LMS filter structure.
 * param numTaps  number of filter coefficients.
 * param *pCoeffs points to coefficient buffer.
 * param *pState points to state buffer.
 * param mu step size that controls filter coefficient updates.
 * param blockSize number of samples to process.
 * param postShift bit shift applied to coefficients.
 * return none.
 */
void arm_lms_norm_init_q15(
    arm_lms_norm_instance_q15* S, uint16_t numTaps, q15_t* pCoeffs,
    q15_t* pState, q15_t mu, uint32_t blockSize, uint8_t postShift
);

/**
 * Correlation of floating-point sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data 
 * length 2 * max(srcALen, srcBLen) - 1.
 * return none.
 */
void arm_correlate_f32(
    float32_t* pSrcA, uint32_t srcALen, float32_t* pSrcB,
    uint32_t srcBLen, float32_t* pDst
);

/**
 * Correlation of Q15 sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data
 * length 2 * max(srcALen, srcBLen) - 1.
 * return none.
 */
void arm_correlate_q15(
    q15_t* pSrcA, uint32_t srcALen, q15_t* pSrcB, uint32_t srcBLen, q15_t* pDst
);

/**
 * Correlation of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data
 * length 2 * max(srcALen, srcBLen) - 1.
 * return none.
 */
void arm_correlate_fast_q15(
    q15_t* pSrcA, uint32_t srcALen, q15_t* pSrcB,
    uint32_t srcBLen, q15_t* pDst
);

/**
 * Correlation of Q31 sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data
 * length 2 * max(srcALen, srcBLen) - 1.
 * return none.
 */
void arm_correlate_q31(
    q31_t* pSrcA, uint32_t srcALen, q31_t* pSrcB, uint32_t srcBLen, q31_t* pDst
);

/**
 * Correlation of Q31 sequences (fast version) for Cortex-M3 and Cortex-M4
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data
 * length 2 * max(srcALen, srcBLen) - 1.
 * return none.
 */
void arm_correlate_fast_q31(
    q31_t* pSrcA, uint32_t srcALen, q31_t* pSrcB, uint32_t srcBLen, q31_t* pDst
);

/**
 * Correlation of Q7 sequences.
 * param *pSrcA points to the first input sequence.
 * param srcALen length of the first input sequence.
 * param *pSrcB points to the second input sequence.
 * param srcBLen length of the second input sequence.
 * param *pDst points to the block of output data
 * length 2 * max(srcALen, srcBLen) - 1.
 * return none.
 */
void arm_correlate_q7(
    q7_t* pSrcA, uint32_t srcALen, q7_t* pSrcB, uint32_t srcBLen, q7_t* pDst
);

/**
 * Instance structure for the floating-point sparse FIR filter.
 */
typedef struct {
    uint16_t numTaps; /* Number of coefficients in the filter. */
    /* State buffer index. Points to the oldest sample in the state buffer. */
    uint16_t stateIndex;
    /**
     * Points to the state buffer array.
     * The array is of length maxDelay+blockSize-1.
     */
    float32_t* pState;
    /* Points to the coefficient array. Array is of length numTaps.*/
    float32_t* pCoeffs;
    uint16_t maxDelay; /* Maximum offset specified by the pTapDelay array. */
    /* Points to the array of delay values. Array is of length numTaps. */
    int32_t* pTapDelay;
} arm_fir_sparse_instance_f32;

/**
 * Instance structure for the Q31 sparse FIR filter.
 */
typedef struct {
    uint16_t numTaps; /* Number of coefficients in the filter. */
    /* State buffer index. Points to the oldest sample in the state buffer. */
    uint16_t stateIndex;
    /**
     * Points to the state buffer array.
     * Array is of length maxDelay+blockSize-1.
     */
    q31_t* pState;
    /* Points to the coefficient array. The array is of length numTaps.*/
    q31_t* pCoeffs;
    uint16_t maxDelay;/* Maximum offset specified by the pTapDelay array. */
    /* Points to the array of delay values. Array is of length numTaps. */
    int32_t* pTapDelay;
} arm_fir_sparse_instance_q31;

/**
 * Instance structure for the Q15 sparse FIR filter.
 */
typedef struct {
    uint16_t numTaps; /**< number of coefficients in the filter. */
    /* State buffer index. Points to the oldest sample in the state buffer. */
    uint16_t stateIndex;
    /**
     * Points to the state buffer array.
     * The array is of length maxDelay+blockSize-1.
     */
    q15_t* pState;
    /**
     * Points to the coefficient array.
     * The array is of length numTaps.
     */
    q15_t* pCoeffs;
    uint16_t maxDelay; /* Maximum offset specified by the pTapDelay array. */
    /* Points to the array of delay values. Array is of length numTaps. */
    int32_t* pTapDelay;
} arm_fir_sparse_instance_q15;

/**
 * Instance structure for the Q7 sparse FIR filter.
 */
typedef struct {
    uint16_t numTaps; /* Number of coefficients in the filter. */
    /* State buffer index. Points to the oldest sample in the state buffer. */
    uint16_t stateIndex;
    /* Points to the state buffer array (length maxDelay+blockSize-1). */
    q7_t* pState;
    /* Points to the coefficient array. The array is of length numTaps.*/
    q7_t* pCoeffs;
    uint16_t maxDelay; /* Maximum offset specified by the pTapDelay array. */
    /* Points to the array of delay values. Array is of length numTaps. */
    int32_t* pTapDelay;
} arm_fir_sparse_instance_q7;

/**
 * Processing function for the floating-point sparse FIR filter.
 * param *S points to an instance of the floating-point sparse FIR structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param *pScratchIn points to a temporary buffer of size blockSize.
 * param blockSize number of input samples to process per call.
 * return none.
 */
void arm_fir_sparse_f32(
    arm_fir_sparse_instance_f32* S, float32_t* pSrc, float32_t* pDst,
    float32_t* pScratchIn, uint32_t blockSize
);

/**
 * Initialization function for the floating-point sparse FIR filter.
 * param *S points to an instance of the floating-point sparse FIR structure.
 * param numTaps number of nonzero coefficients in the filter.
 * param *pCoeffs points to the array of filter coefficients.
 * param *pState points to the state buffer.
 * param *pTapDelay points to the array of offset times.
 * param maxDelay maximum offset time supported.
 * param blockSize  number of samples that will be processed per block.
 * return none
 */
void arm_fir_sparse_init_f32(
    arm_fir_sparse_instance_f32* S, uint16_t numTaps, float32_t* pCoeffs,
    float32_t* pState, int32_t* pTapDelay, uint16_t maxDelay,
    uint32_t blockSize
);

/**
 * Processing function for the Q31 sparse FIR filter.
 * param *S points to an instance of the Q31 sparse FIR structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param *pScratchIn points to a temporary buffer of size blockSize.
 * param blockSize number of input samples to process per call.
 * return none.
 */
void arm_fir_sparse_q31(
    arm_fir_sparse_instance_q31* S, q31_t* pSrc, q31_t* pDst,
    q31_t* pScratchIn, uint32_t blockSize
);

/**
 * Initialization function for the Q31 sparse FIR filter.
 * param *S points to an instance of the Q31 sparse FIR structure.
 * param numTaps number of nonzero coefficients in the filter.
 * param *pCoeffs points to the array of filter coefficients.
 * param *pState points to the state buffer.
 * param *pTapDelay points to the array of offset times.
 * param maxDelay maximum offset time supported.
 * param blockSize number of samples that will be processed per block.
 * return none
 */
void arm_fir_sparse_init_q31(
    arm_fir_sparse_instance_q31* S, uint16_t numTaps, q31_t* pCoeffs,
    q31_t* pState, int32_t * pTapDelay, uint16_t maxDelay, uint32_t blockSize
);

/**
 * Processing function for the Q15 sparse FIR filter.
 * param *S points to an instance of the Q15 sparse FIR structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param *pScratchIn points to a temporary buffer of size blockSize.
 * param *pScratchOut points to a temporary buffer of size blockSize.
 * param blockSize number of input samples to process per call.
 * return none.
 */
void arm_fir_sparse_q15(
    arm_fir_sparse_instance_q15* S, q15_t* pSrc, q15_t* pDst,
    q15_t * pScratchIn, q31_t* pScratchOut, uint32_t blockSize
);

/**
 * Initialization function for the Q15 sparse FIR filter.
 * param *S points to an instance of the Q15 sparse FIR structure.
 * param numTaps number of nonzero coefficients in the filter.
 * param *pCoeffs points to the array of filter coefficients.
 * param *pState points to the state buffer.
 * param *pTapDelay points to the array of offset times.
 * param maxDelay maximum offset time supported.
 * param blockSize number of samples that will be processed per block.
 * return none
 */
void arm_fir_sparse_init_q15(
    arm_fir_sparse_instance_q15* S, uint16_t numTaps, q15_t* pCoeffs,
    q15_t* pState, int32_t* pTapDelay, uint16_t maxDelay, uint32_t blockSize
);

/**
 * Processing function for the Q7 sparse FIR filter.
 * param *S points to an instance of the Q7 sparse FIR structure.
 * param *pSrc points to the block of input data.
 * param *pDst points to the block of output data
 * param *pScratchIn points to a temporary buffer of size blockSize.
 * param *pScratchOut points to a temporary buffer of size blockSize.
 * param blockSize number of input samples to process per call.
 * return none.
 */
void arm_fir_sparse_q7(
    arm_fir_sparse_instance_q7* S, q7_t* pSrc, q7_t* pDst,
    q7_t * pScratchIn, q31_t* pScratchOut, uint32_t blockSize
);

/**
 * Initialization function for the Q7 sparse FIR filter.
 * param *S points to an instance of the Q7 sparse FIR structure.
 * param numTaps number of nonzero coefficients in the filter.
 * param *pCoeffs points to the array of filter coefficients.
 * param *pState points to the state buffer.
 * param *pTapDelay points to the array of offset times.
 * param maxDelay maximum offset time supported.
 * param blockSize number of samples that will be processed per block.
 * return none
 */
void arm_fir_sparse_init_q7(
    arm_fir_sparse_instance_q7* S, uint16_t numTaps, q7_t* pCoeffs,
    q7_t* pState, int32_t* pTapDelay, uint16_t maxDelay, uint32_t blockSize
);

/**
 * Floating-point sin_cos function.
 * param theta input value in degrees 
 * param *pSinVal points to the processed sine output.
 * param *pCosVal points to the processed cos output.
 * return none.
 */
void arm_sin_cos_f32(float32_t theta, float32_t* pSinVal, float32_t* pCcosVal);

/**
 * Q31 sin_cos function.
 * param theta scaled input value in degrees 
 * param *pSinVal points to the processed sine output.
 * param *pCosVal points to the processed cosine output.
 * return none.
 */
void arm_sin_cos_q31(q31_t theta, q31_t* pSinVal, q31_t* pCosVal);

/**
 * Floating-point complex conjugate.
 * param *pSrc points to the input vector
 * param *pDst points to the output vector
 * param numSamples number of complex samples in each vector
 * return none.
 */
void arm_cmplx_conj_f32(float32_t* pSrc, float32_t* pDst, uint32_t numSamples);

/**
 * Q31 complex conjugate.
 * param *pSrc points to the input vector
 * param *pDst points to the output vector
 * param numSamples number of complex samples in each vector
 * return none.
 */
void arm_cmplx_conj_q31(q31_t* pSrc, q31_t* pDst, uint32_t numSamples);

/**
 * Q15 complex conjugate.
 * param *pSrc points to the input vector
 * param *pDst points to the output vector
 * param numSamples number of complex samples in each vector
 * return none.
 */
void arm_cmplx_conj_q15(q15_t* pSrc, q15_t* pDst, uint32_t numSamples);

/**
 * Floating-point complex magnitude squared
 * param *pSrc points to the complex input vector
 * param *pDst points to the real output vector
 * param numSamples number of complex samples in the input vector
 * return none.
 */
void arm_cmplx_mag_squared_f32(
    float32_t* pSrc, float32_t* pDst, uint32_t numSamples
);

/**
 * Q31 complex magnitude squared
 * param *pSrc points to the complex input vector
 * param *pDst points to the real output vector
 * param numSamples number of complex samples in the input vector
 * return none.
 */
void arm_cmplx_mag_squared_q31(q31_t* pSrc, q31_t* pDst, uint32_t numSamples);

/**
 * Q15 complex magnitude squared
 * param *pSrc points to the complex input vector
 * param *pDst points to the real output vector
 * param numSamples number of complex samples in the input vector
 * return none.
 */
void arm_cmplx_mag_squared_q15(q15_t* pSrc, q15_t* pDst, uint32_t numSamples);

/**
 * PID Motor Control
 *
 * A Proportional Integral Derivative (PID) controller is a generic feedback
 * control loop mechanism widely used in industrial control systems.
 * A PID controller is the most commonly used type of feedback controller.
 *
 * This set of functions implements (PID) controllers
 * for Q15, Q31, and floating-point data types.  Functions operate on a single
 * sample of data and each call to the function returns a single processed
 * value.S points to an instance of the PID control data structure. in
 * is the input sample value. The functions return the output value.
 *
 * par Algorithm:
 * 
 *    y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
 *    A0 = Kp + Ki + Kd
 *    A1 = (-Kp ) - (2 * Kd )
 *    A2 = Kd  </pre>
 *
 * par
 * where c Kp is proportional constant, c Ki is Integral constant and c Kd is
 * Derivative constant
 *
 * par
 * The PID controller calculates an "error" value as the difference between
 * the measured output and the reference input.
 * The controller attempts to minimize the error by adjusting the process
 * control inputs. The proportional value determines the reaction to the
 * current error, the integral value determines the reaction based on the
 * sum of recent errors, and the derivative value determines the reaction
 * based on the rate at which the error has been changing.
 *
 * par Instance Structure 
 * The Gains A0, A1, A2 and state variables for a PID controller are stored
 * together in an instance data structure. A separate instance structure must
 * be defined for each PID Controller. There are separate instance structure
 * declarations for each of the 3 supported data types.
 * 
 * par Reset Functions 
 * There is also an associated reset function for each data type which clears
 * the state array.
 *
 * par Initialization Functions 
 * There is also an associated initialization function for each data type. 
 * The initialization function performs the following operations: 
 * - Initializes the Gains A0, A1, A2 from Kp,Ki, Kd gains.
 * - Zeros out the values in the state buffer.   
 * 
 * par 
 * Instance structure cannot be placed into a const data section and it is
 * recommended to use the initialization function. 
 *
 * par Fixed-Point Behavior
 * Care must be taken when using the fixed-point versions of the PID
 * Controller functions. 
 * In particular, the overflow and saturation behavior of the accumulator
 * used in each function must be considered. 
 * Refer to the function specific documentation below for usage guidelines. 
 */

/**
 * Process function for the floating-point PID Control.
 * param *S is an instance of the floating-point PID Control structure
 * param in input sample to process
 * return out processed output sample.
 */
static __INLINE float32_t arm_pid_f32(arm_pid_instance_f32* S, float32_t in) {
    float32_t out;
    /* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
    out = (S->A0 * in) +
          (S->A1 * S->state[0]) +
          (S->A2 * S->state[1]) +
          (S->state[2]);
    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;
    /* return to application */
    return (out);
}

/**
 * Process function for the Q31 PID Control.
 * param *S points to an instance of the Q31 PID Control structure
 * param in input sample to process
 * return out processed output sample.
 *
 * Scaling and Overflow Behavior:
 * par 
 * The function is implemented using an internal 64-bit accumulator. 
 * The accumulator has a 2.62 format and maintains full precision of the
 * intermediate multiplication results but provides only a single guard bit. 
 * Thus, if the accumulator result overflows it wraps around rather than clip. 
 * In order to avoid overflows completely the input signal must be scaled down
 * by 2 bits as there are four additions. 
 * After all multiply-accumulates are performed, the 2.62 accumulator is
 * truncated to 1.32 format and then saturated to 1.31 format. 
 */
static __INLINE q31_t arm_pid_q31(arm_pid_instance_q31* S, q31_t in) {
    q63_t acc;
    q31_t out;

    /* acc = A0 * x[n]  */
    acc = (q63_t) S->A0 * in;
    /* acc += A1 * x[n-1] */
    acc += (q63_t) S->A1 * S->state[0];
    /* acc += A2 * x[n-2]  */
    acc += (q63_t) S->A2 * S->state[1];
    /* convert output to 1.31 format to add y[n-1] */
    out = (q31_t) (acc >> 31u);
    /* out += y[n-1] */
    out += S->state[2];
    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;
    /* return to application */
    return (out);
}

/**
 * Process function for the Q15 PID Control.
 * param *S points to an instance of the Q15 PID Control structure
 * param in input sample to process
 * return out processed output sample.
 *
 * Scaling and Overflow Behavior:
 * par 
 * The function is implemented using a 64-bit internal accumulator. 
 * Both Gains and state variables are represented in 1.15 format and
 * multiplications yield a 2.30 result. 
 * The 2.30 intermediate results are accumulated in a 64-bit accumulator in
 * 34.30 format. 
 * There is no risk of internal overflow with this approach and the full
 * precision of intermediate multiplications is preserved. 
 * After all additions have been performed, the accumulator is truncated to
 * 34.15 format by discarding low 15 bits. 
 * Lastly, the accumulator is saturated to yield a result in 1.15 format.
 */
static __INLINE q15_t arm_pid_q15(arm_pid_instance_q15* S, q15_t in) {
    q63_t acc;
    q15_t out;
    /* Implementation of PID controller */
#ifdef ARM_MATH_CM0
    /* acc = A0 * x[n]  */
    acc = ((q31_t) S->A0 )* in ;
#else
    /* acc = A0 * x[n]  */
    acc = (q31_t) __SMUAD(S->A0, in);
#endif
#ifdef ARM_MATH_CM0
    /* acc += A1 * x[n-1] + A2 * x[n-2]  */
    acc += (q31_t) S->A1  *  S->state[0] ;
    acc += (q31_t) S->A2  *  S->state[1] ;
#else
    /* acc += A1 * x[n-1] + A2 * x[n-2]  */
    acc = __SMLALD(S->A1, (q31_t)__SIMD32(S->state), acc);
#endif
    /* acc += y[n-1] */
    acc += (q31_t) S->state[2] << 15;
    /* saturate the output */
    out = (q15_t) (__SSAT((acc >> 15), 16));
    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;
    /* return to application */
    return (out);
}

/**
 * Floating-point matrix inverse.
 * param *src points to instance of input floating-point matrix structure.
 * param *dst points to instance of output floating-point matrix structure.
 * return Function returns ARM_MATH_SIZE_MISMATCH, if dimensions do not match.
 * If the input matrix is singular (does not have an inverse), then the
 * algorithm terminates and returns error status ARM_MATH_SINGULAR.
 */
arm_status arm_mat_inverse_f32(
    const arm_matrix_instance_f32* src, arm_matrix_instance_f32* dst
);

/**
 *
 * Floating-point Clarke transform
 * param Ia input three-phase coordinate a
 * param Ib input three-phase coordinate b
 * param *pIalpha points to output two-phase orthogonal vector axis alpha
 * param *pIbeta points to output two-phase orthogonal vector axis beta
 * return none.
 */
static __INLINE void arm_clarke_f32(
    float32_t Ia, float32_t Ib, float32_t* pIalpha, float32_t* pIbeta
) {
    /* Calculate pIalpha using the equation, pIalpha = Ia */
    *pIalpha = Ia;
    /**
     * Calculate pIbeta using the equation,
     * pIbeta = (1/sqrt(3)) * Ia + (2/sqrt(3)) * Ib
     */
    *pIbeta = (
        (float32_t) 0.57735026919 * Ia + (float32_t) 1.15470053838 * Ib
    );
}

/**
 * Clarke transform for Q31 version
 * param Ia input three-phase coordinate a
 * param Ib input three-phase coordinate b
 * param *pIalpha points to output two-phase orthogonal vector axis alpha
 * param *pIbeta points to output two-phase orthogonal vector axis beta
 * return none.
 *
 * Scaling and Overflow Behavior:
 * par
 * The function is implemented using an internal 32-bit accumulator.
 * The accumulator maintains 1.31 format by truncating lower 31 bits of the
 * intermediate multiplication in 2.62 format.
 * There is saturation on the addition, hence there is no risk of overflow.
 */
static __INLINE void arm_clarke_q31(
    q31_t Ia, q31_t Ib, q31_t* pIalpha, q31_t* pIbeta
) {
    /* Temporary variables used to store intermediate results */
    q31_t product1, product2;
    /* Calculating pIalpha from Ia by equation pIalpha = Ia */
    *pIalpha = Ia;
    /* Intermediate product is calculated by (1/(sqrt(3)) * Ia) */
    product1 = (q31_t) (((q63_t) Ia * 0x24F34E8B) >> 30);
    /* Intermediate product is calculated by (2/sqrt(3) * Ib) */
    product2 = (q31_t) (((q63_t) Ib * 0x49E69D16) >> 30);
    /* pIbeta is calculated by adding the intermediate products */
    *pIbeta = __QADD(product1, product2);
}

/**
 * Converts the elements of the Q7 vector to Q31 vector.
 * param *pSrc input pointer
 * param *pDst output pointer
 * param blockSize number of samples to process
 * return none.
 */
void arm_q7_to_q31(q7_t* pSrc, q31_t* pDst, uint32_t blockSize);

/**
 * Floating-point Inverse Clarke transform
 * param Ialpha input two-phase orthogonal vector axis alpha
 * param Ibeta input two-phase orthogonal vector axis beta
 * param *pIa points to output three-phase coordinate a
 * param *pIb points to output three-phase coordinate b
 * return none.
 */
static __INLINE void arm_inv_clarke_f32(
    float32_t Ialpha, float32_t Ibeta, float32_t* pIa, float32_t* pIb
) {
    /* Calculating pIa from Ialpha by equation pIa = Ialpha */
    *pIa = Ialpha;
    /** Calculating pIb from Ialpha and Ibeta by equation
     * pIb = -(1/2) * Ialpha + (sqrt(3)/2) * Ibeta
     */
    *pIb = -0.5 * Ialpha + (float32_t) 0.8660254039 *Ibeta;
}

/**
 * Inverse Clarke transform for Q31 version 
 * param Ialpha input two-phase orthogonal vector axis alpha
 * param Ibeta input two-phase orthogonal vector axis beta
 * param *pIa points to output three-phase coordinate a
 * param *pIb points to output three-phase coordinate b
 * return none.
 *
 * Scaling and Overflow Behavior:
 * par
 * The function is implemented using an internal 32-bit accumulator.
 * The accumulator maintains 1.31 format by truncating lower 31 bits of the
 * intermediate multiplication in 2.62 format.
 * There is saturation on the subtraction, hence there is no risk of overflow.
 */
static __INLINE void arm_inv_clarke_q31(
    q31_t Ialpha, q31_t Ibeta, q31_t* pIa, q31_t* pIb
) {
    /* Temporary variables used to store intermediate results */
    q31_t product1, product2;
    /* Calculating pIa from Ialpha by equation pIa = Ialpha */
    *pIa = Ialpha;
    /* Intermediate product is calculated by (1/(2*sqrt(3)) * Ia) */
    product1 = (q31_t) (((q63_t) (Ialpha) * (0x40000000)) >> 31);
    /* Intermediate product is calculated by (1/sqrt(3) * pIb) */
    product2 = (q31_t) (((q63_t) (Ibeta) * (0x6ED9EBA1)) >> 31);
    /* pIb is calculated by subtracting the products */
    *pIb = __QSUB(product2, product1);
}

/**
 * Converts the elements of the Q7 vector to Q15 vector.
 * param *pSrc input pointer
 * param *pDst output pointer
 * param blockSize number of samples to process
 * return none.
 */
void arm_q7_to_q15(q7_t* pSrc, q15_t* pDst, uint32_t blockSize);

/**
 * Floating-point Park transform
 * param Ialpha input two-phase vector coordinate alpha
 * param Ibeta input two-phase vector coordinate beta
 * param *pId points to outputrotor reference frame d
 * param *pIq points to outputrotor reference frame q
 * param sinVal sine value of rotation angle theta
 * param cosVal cosine value of rotation angle theta
 * return none.
 * The function implements the forward Park transform.
 */
static __INLINE void arm_park_f32(
    float32_t Ialpha, float32_t Ibeta, float32_t* pId,
    float32_t* pIq, float32_t sinVal, float32_t cosVal
) {
    /* Calculate pId = Ialpha * cosVal + Ibeta * sinVal */
    *pId = Ialpha * cosVal + Ibeta * sinVal;
    /* Calculate  pIq = - Ialpha * sinVal + Ibeta * cosVal */
    *pIq = -Ialpha * sinVal + Ibeta * cosVal;
}

/**
 * Park transform for Q31 version 
 * param Ialpha input two-phase vector coordinate alpha
 * param Ibeta input two-phase vector coordinate beta
 * param *pId points to output rotor reference frame d
 * param *pIq points to output rotor reference frame q
 * param sinVal sine value of rotation angle theta
 * param cosVal cosine value of rotation angle theta
 * return none.
 *
 *Scaling and Overflow Behavior:
 * par
 * The function is implemented using an internal 32-bit accumulator.
 * The accumulator maintains 1.31 format by truncating lower 31 bits of the
 * intermediate multiplication in 2.62 format.
 * There is saturation on the addition and subtraction, hence there is no
 * risk of overflow.
 */
static __INLINE void arm_park_q31(
    q31_t Ialpha, q31_t Ibeta, q31_t* pId,
    q31_t* pIq, q31_t sinVal, q31_t cosVal
) {
    q31_t product1, product2;
    q31_t product3, product4;

    /* Intermediate product is calculated by (Ialpha * cosVal) */
    product1 = (q31_t) (((q63_t) (Ialpha) * (cosVal)) >> 31);
    /* Intermediate product is calculated by (Ibeta * sinVal) */
    product2 = (q31_t) (((q63_t) (Ibeta) * (sinVal)) >> 31);
    /* Intermediate product is calculated by (Ialpha * sinVal) */
    product3 = (q31_t) (((q63_t) (Ialpha) * (sinVal)) >> 31);
    /* Intermediate product is calculated by (Ibeta * cosVal) */
    product4 = (q31_t) (((q63_t) (Ibeta) * (cosVal)) >> 31);
    /* Calculate pId by adding the two intermediate products 1 and 2 */
    *pId = __QADD(product1, product2);
    /* Calculate pIq by subtracting the two intermediate products 3 from 4 */
    *pIq = __QSUB(product4, product3);
}

/**
 * Converts the elements of the Q7 vector to floating-point vector.
 * param *pSrc is input pointer
 * param *pDst is output pointer
 * param blockSize is the number of samples to process
 * return none.
 */
  void arm_q7_to_float(q7_t* pSrc, float32_t* pDst, uint32_t blockSize);

/**
 * Floating-point Inverse Park transform
 * param Id input coordinate of rotor reference frame d
 * param Iq input coordinate of rotor reference frame q
 * param *pIalpha points to output two-phase orthogonal vector axis alpha
 * param *pIbeta points to output two-phase orthogonal vector axis beta
 * param sinVal sine value of rotation angle theta
 * param cosVal cosine value of rotation angle theta
 * return none.
 */
static __INLINE void arm_inv_park_f32(
    float32_t Id, float32_t Iq, float32_t* pIalpha,
    float32_t* pIbeta, float32_t sinVal, float32_t cosVal
) {
    /* Calculate pIalpha = Id * cosVal - Iq * sinVal */
    *pIalpha = Id * cosVal - Iq * sinVal;
    /* Calculate pIbeta = Id * sinVal + Iq * cosVal */
    *pIbeta = Id * sinVal + Iq * cosVal;
}

/**
 * Inverse Park transform forQ31 version 
 * param Id input coordinate of rotor reference frame d
 * param Iq input coordinate of rotor reference frame q
 * param *pIalpha points to output two-phase orthogonal vector axis alpha
 * param *pIbeta points to output two-phase orthogonal vector axis beta
 * param sinVal sine value of rotation angle theta
 * param cosVal cosine value of rotation angle theta
 * return none.
 *
 * Scaling and Overflow Behavior:
 * par
 * The function is implemented using an internal 32-bit accumulator.
 * The accumulator maintains 1.31 format by truncating lower 31 bits of the
 * intermediate multiplication in 2.62 format.
 * There is saturation on the addition, hence there is no risk of overflow.
 */
static __INLINE void arm_inv_park_q31(
    q31_t Id, q31_t Iq, q31_t* pIalpha,
    q31_t* pIbeta, q31_t sinVal, q31_t cosVal
) {
    q31_t product1, product2;
    q31_t product3, product4;

    /* Intermediate product is calculated by (Id * cosVal) */
    product1 = (q31_t) (((q63_t) (Id) * (cosVal)) >> 31);
    /* Intermediate product is calculated by (Iq * sinVal) */
    product2 = (q31_t) (((q63_t) (Iq) * (sinVal)) >> 31);
    /* Intermediate product is calculated by (Id * sinVal) */
    product3 = (q31_t) (((q63_t) (Id) * (sinVal)) >> 31);
    /* Intermediate product is calculated by (Iq * cosVal) */
    product4 = (q31_t) (((q63_t) (Iq) * (cosVal)) >> 31);
    /* Calculate pIalpha by using the two intermediate products 1 and 2 */
    *pIalpha = __QSUB(product1, product2);
    /* Calculate pIbeta by using the two intermediate products 3 and 4 */
    *pIbeta = __QADD(product4, product3);
}

/**
 * Converts the elements of the Q31 vector to floating-point vector.
 * param *pSrc is input pointer
 * param *pDst is output pointer
 * param blockSize is the number of samples to process
 * return none.
 */
void arm_q31_to_float(q31_t* pSrc, float32_t* pDst, uint32_t blockSize);

/**
 * Process function for the floating-point Linear Interpolation Function.
 * param *S is an instance of the floating-point Linear Interpolation structure
 * param x input sample to process
 * return y processed output sample.
 *
 */
static __INLINE float32_t arm_linear_interp_f32(
    arm_linear_interp_instance_f32* S, float32_t x
) {
    float32_t y;
    float32_t x0, x1;/* Nearest input values */
    float32_t y0, y1;  /* Nearest output values */
    float32_t xSpacing = S->xSpacing;/* spacing between input values */
    int32_t i;  /* Index variable */
    float32_t *pYData = S->pYData;    /* pointer to output table */

    /* Calculation of index */
    i =   (x - S->x1) / xSpacing;
    if(i < 0) {
        /**
         * Iniatilize output for below specified range as
         * least output value of table
         */
        y = pYData[0];
    } else if(i >= S->nValues) {
        /**
         * Iniatilize output for above specified range as
         * last output value of table
         */
        y = pYData[S->nValues-1];
    } else {
        /* Calculation of nearest input values */
        x0 = S->x1 + i * xSpacing;
        x1 = S->x1 + (i +1) * xSpacing;
        /* Read of nearest output values */
        y0 = pYData[i];
        y1 = pYData[i + 1];
        /* Calculation of output */
        y = y0 + (x - x0) * ((y1 - y0)/(x1-x0));
    }
    /* returns output value */
    return (y);
}

/**
 *
 * Process function for the Q31 Linear Interpolation Function.
 * param *pYData  pointer to Q31 Linear Interpolation table
 * param x input sample to process
 * param nValues number of table values
 * return y processed output sample.
 *
 * par
 * Input sample x is in 12.20 format which contains 12 bits for table
 * index and 20 bits for fractional part.
 * This function can support maximum of table size 2^12.
 *
 */
static __INLINE q31_t arm_linear_interp_q31(
    q31_t*pYData, q31_t x, uint32_t nValues
) {
    q31_t y; /* output */
    q31_t y0, y1; /* Nearest output values */
    q31_t fract; /* fractional part */
    int32_t index; /* Index to read nearest output values */

    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    index = ((x & 0xFFF00000) >> 20);
    if(index >= (nValues - 1)) {
        return(pYData[nValues - 1]);
    } else if(index < 0) {
        return(pYData[0]);
    } else {
        /* 20 bits for the fractional part */
        /* shift left by 11 to keep fract in 1.31 format */
        fract = (x & 0x000FFFFF) << 11;
        /* Read two nearest output values from the index in 1.31(q31) format */
        y0 = pYData[index];
        y1 = pYData[index + 1u];
        /* Calculation of y0 * (1-fract) and y is in 2.30 format */
        y = ((q31_t) ((q63_t) y0 * (0x7FFFFFFF - fract) >> 32));
        /* Calculation of y0 * (1-fract) + y1 *fract and y is in 2.30 format */
        y += ((q31_t) (((q63_t) y1 * fract) >> 32));
        /* Convert y to 1.31 format */
        return (y << 1u);
    }
}

/**
 *
 * Process function for the Q15 Linear Interpolation Function.
 * param *pYData  pointer to Q15 Linear Interpolation table
 * param x input sample to process
 * param nValues number of table values
 * return y processed output sample.
 *
 * par
 * Input sample x is in 12.20 format which contains 12 bits for table index
 * and 20 bits for fractional part.
 * This function can support maximum of table size 2^12. 
 *
 */
static __INLINE q15_t arm_linear_interp_q15(
    q15_t* pYData, q31_t x, uint32_t nValues
) {
    q63_t y; /* output */
    q15_t y0, y1; /* Nearest output values */
    q31_t fract; /* fractional part */
    int32_t index; /* Index to read nearest output values */ 

    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    index = ((x & 0xFFF00000) >> 20u);
    if(index >= (nValues - 1)) {
        return(pYData[nValues - 1]);
    } else if(index < 0) {
        return(pYData[0]);
    } else {
        /* 20 bits for the fractional part */
        /* fract is in 12.20 format */
        fract = (x & 0x000FFFFF);
        /* Read two nearest output values from the index */
        y0 = pYData[index];
        y1 = pYData[index + 1u];
        /* Calculation of y0 * (1-fract) and y is in 13.35 format */
        y = ((q63_t) y0 * (0xFFFFF - fract));
        /**
         * Calculation of (y0 * (1-fract) + y1 * fract)
         * and y is in 13.35 format
         */
        y += ((q63_t) y1 * (fract));
        /* convert y to 1.15 format */
        return (y >> 20);
    }
}

/**
 * Process function for the Q7 Linear Interpolation Function.
 * param *pYData  pointer to Q7 Linear Interpolation table
 * param x input sample to process
 * param nValues number of table values
 * return y processed output sample.
 *
 * par
 * Input sample x is in 12.20 format which contains 12 bits for table
 * index and 20 bits for fractional part.
 * This function can support maximum of table size 2^12.
 */
static __INLINE q7_t arm_linear_interp_q7(
    q7_t *pYData, q31_t x, uint32_t nValues
) {
    q31_t y; /* output */
    q7_t y0, y1; /* Nearest output values */
    q31_t fract; /* fractional part */
    int32_t index; /* Index to read nearest output values */

    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    index = ((x & 0xFFF00000) >> 20u);
    if(index >= (nValues - 1)) {
        return(pYData[nValues - 1]);
    } else if(index < 0) {
        return(pYData[0]);
    } else {
        /* 20 bits for the fractional part */
        /* fract is in 12.20 format */
        fract = (x & 0x000FFFFF);
        /* Read 2 nearest output values from index and are in 1.7(q7) format */
        y0 = pYData[index];
        y1 = pYData[index + 1u];
        /* Calculation of y0 * (1-fract ) and y is in 13.27(q27) format */
        y = ((y0 * (0xFFFFF - fract)));
        /**
         * Calculation of y1 * fract + y0 * (1-fract)
         * and y is in 13.27(q27) format
         */
        y += (y1 * fract);
        /* convert y to 1.7(q7) format */
        return (y >> 20u);
    }
}

/**
 * Fast approximation to trigonometric sine function for floating-point data.
 * param x input value in radians.
 * return  sin(x).
 */
float32_t arm_sin_f32(float32_t x);

/**
 * Fast approximation to the trigonometric sine function for Q31 data.
 * param x Scaled input value in radians.
 * return  sin(x).
 */
q31_t arm_sin_q31(q31_t x);

/**
 * Fast approximation to the trigonometric sine function for Q15 data.
 * param x Scaled input value in radians.
 * return  sin(x).
 */
q15_t arm_sin_q15(q15_t x);

/**
 * Fast approximation to trigonometric cosine function for floating-point data.
 * param x input value in radians.
 * return  cos(x).
 */
float32_t arm_cos_f32(float32_t x);

/**
 * Fast approximation to the trigonometric cosine function for Q31 data.
 * param x Scaled input value in radians.
 * return  cos(x).
 */
q31_t arm_cos_q31(q31_t x);

/**
 * Fast approximation to the trigonometric cosine function for Q15 data.
 * param x Scaled input value in radians.
 * return  cos(x).
 */
q15_t arm_cos_q15(q15_t x);

/**
 *
 * Computes the square root of a number.
 * There are separate functions for Q15, Q31, and floating-point data types.  
 * The square root function is computed using the Newton-Raphson algorithm.
 * This is an iterative algorithm of the form:
 * 
 *      x1 = x0 - f(x0)/f'(x0)
 * 
 * where x1 is the current estimate,
 * x0 is the previous estimate and
 * f'(x0) is the derivative of f() evaluated at x0.
 * For the square root function, the algorithm reduces to:
 * 
 *     x0 = in/2                         [initial guess]
 *     x1 = 1/2 * ( x0 + in / x0)        [each iteration]
 */

/**
 * Floating-point square root function.
 * param in input value.
 * param *pOut square root of input value.
 * return The function returns ARM_MATH_SUCCESS if input value is positive
 * value or ARM_MATH_ARGUMENT_ERROR if in is negative value and returns
 * zero output for negative values.
 */
static __INLINE arm_status  arm_sqrt_f32(float32_t in, float32_t *pOut) {
    if(in > 0) {
#if (__FPU_USED == 1) && defined ( __CC_ARM   )
        *pOut = __sqrtf(in);
#else
        *pOut = sqrtf(in);
#endif
        return (ARM_MATH_SUCCESS);
    } else {
        *pOut = 0.0f;
        return (ARM_MATH_ARGUMENT_ERROR);
    }
}

/**
 * Q31 square root function.
 * param in input value. The range of the input value is [0 +1)
 * or 0x00000000 to 0x7FFFFFFF.
 * param *pOut square root of input value.
 * return The function returns ARM_MATH_SUCCESS if input value is positive
 * value or ARM_MATH_ARGUMENT_ERROR if
 * in is negative value and returns zero output for negative values.
 */
arm_status arm_sqrt_q31(q31_t in, q31_t*pOut);

/**
 * Q15 square root function.
 * param in input value. The range of the input value is [0 +1)
 * or 0x0000 to 0x7FFF.
 * param *pOut  square root of input value.
 * return The function returns ARM_MATH_SUCCESS if input value is
 * positive value or ARM_MATH_ARGUMENT_ERROR if
 * in is negative value and returns zero output for negative values.
 */
arm_status arm_sqrt_q15(q15_t in, q15_t *pOut);

/**
 * floating-point Circular write function.
 */
static __INLINE void arm_circularWrite_f32(
    int32_t* circBuffer, int32_t L, uint16_t* writeOffset, int32_t bufferInc,
    const int32_t* src, int32_t srcInc, uint32_t blockSize
) {
    uint32_t i = 0u;
    int32_t wOffset;

    /**
     * Copy the value of Index pointer that points
     * to the current location where the input samples to be copied 
     */
    wOffset = *writeOffset;
    /* Loop over the blockSize */
    i = blockSize;
    while(i > 0u) {
        /* copy the input sample to the circular buffer */
        circBuffer[wOffset] = *src;
        /* Update the input pointer */
        src += srcInc;
        /**
         * Circularly update wOffset.
         * Watch out for positive and negative value
         */
        wOffset += bufferInc;
        if (wOffset >= L) wOffset -= L;
        /* Decrement the loop counter */
        i--;
    }
    /* Update the index pointer */
    *writeOffset = wOffset;
}

/**
 * floating-point Circular Read function.
 */
static __INLINE void arm_circularRead_f32(
    int32_t* circBuffer, int32_t L, int32_t* readOffset, int32_t bufferInc,
    int32_t* dst, int32_t* dst_base, int32_t dst_length, int32_t dstInc,
    uint32_t blockSize
) {
    uint32_t i = 0u;
    int32_t rOffset, dst_end;

    /**
     * Copy the value of Index pointer that points to the current location
     * from where the input samples to be read
     */
    rOffset = *readOffset;
    dst_end = (int32_t) (dst_base + dst_length);
    /* Loop over the blockSize */
    i = blockSize;
    while(i > 0u) {
        /* copy the sample from circular buffer to the destination buffer */
        *dst = circBuffer[rOffset];
        /* Update the input pointer */
        dst += dstInc;
        if (dst == (int32_t *) dst_end) {
            dst = dst_base;
        }
        /**
         * Circularly update rOffset.
         * Watch out for positive and negative value.
         */
        rOffset += bufferInc;
        if (rOffset >= L) {
            rOffset -= L;
        }
        /* Decrement the loop counter */
        i--;
    }
    /* Update the index pointer */
    *readOffset = rOffset;
}

/**
 * Q15 Circular write function.
 */
static __INLINE void arm_circularWrite_q15(
    q15_t* circBuffer, int32_t L, uint16_t* writeOffset, int32_t bufferInc,
    const q15_t* src, int32_t srcInc, uint32_t blockSize
) {
    uint32_t i = 0u;
    int32_t wOffset;

    /**
     * Copy the value of Index pointer that points
     * to the current location where the input samples to be copied 
     */
    wOffset = *writeOffset;
    /* Loop over the blockSize */
    i = blockSize;
    while(i > 0u) {
        /* copy the input sample to the circular buffer */
        circBuffer[wOffset] = *src;
        /* Update the input pointer */
        src += srcInc;
        /**
         * Circularly update wOffset.
         * Watch out for positive and negative value.
         */
        wOffset += bufferInc;
        if (wOffset >= L) wOffset -= L;
        /* Decrement the loop counter */
        i--;
    }
    /* Update the index pointer */
    *writeOffset = wOffset;
}

/**
 * Q15 Circular Read function.
 */
static __INLINE void arm_circularRead_q15(
    q15_t* circBuffer, int32_t L, int32_t* readOffset, int32_t bufferInc,
    q15_t* dst, q15_t* dst_base, int32_t dst_length, int32_t dstInc,
    uint32_t blockSize
) {
    uint32_t i = 0;
    int32_t rOffset, dst_end;

    /**
     * Copy the value of Index pointer that points to the current location
     * from where the input samples to be read.
     */
    rOffset = *readOffset;
    dst_end = (int32_t) (dst_base + dst_length);
    /* Loop over the blockSize */
    i = blockSize;
    while (i > 0u) {
        /* copy sample from the circular buffer to the destination buffer */
        *dst = circBuffer[rOffset];
        /* Update the input pointer */
        dst += dstInc;
        if (dst == (q15_t *) dst_end) {
            dst = dst_base;
        }
        /**
         * Circularly update wOffset.
         * Watch out for positive and negative value.
         */
        rOffset += bufferInc;
        if(rOffset >= L) {
            rOffset -= L;
        }
        /* Decrement the loop counter */
        i--;
    }
    /* Update the index pointer */
    *readOffset = rOffset;
}

/**
 * Q7 Circular write function.
 */
static __INLINE void arm_circularWrite_q7(
    q7_t* circBuffer, int32_t L, uint16_t* writeOffset, int32_t bufferInc,
    const q7_t* src, int32_t srcInc, uint32_t blockSize
) {
    uint32_t i = 0u;
    int32_t wOffset;

    /**
     * Copy the value of Index pointer that points to the current location
     * where the input samples to be copied.
     */
    wOffset = *writeOffset;
    /* Loop over the blockSize */
    i = blockSize;
    while (i > 0u) {
        /* copy the input sample to the circular buffer */
        circBuffer[wOffset] = *src;
        /* Update the input pointer */
        src += srcInc;
        /**
         * Circularly update wOffset.
         * Watch out for positive and negative value.
         */
        wOffset += bufferInc;
        if (wOffset >= L) wOffset -= L;
        /* Decrement the loop counter */
        i--;
    }
    /* Update the index pointer */
    *writeOffset = wOffset;
}

/**
 * Q7 Circular Read function.
 */
static __INLINE void arm_circularRead_q7(
    q7_t* circBuffer, int32_t L, int32_t* readOffset, int32_t bufferInc,
    q7_t* dst, q7_t* dst_base, int32_t dst_length, int32_t dstInc,
    uint32_t blockSize
) {
    uint32_t i = 0;
    int32_t rOffset, dst_end;

    /**
     * Copy the value of Index pointer that points to the current
     * location from where the input samples to be read.
     */
    rOffset = *readOffset;
    dst_end = (int32_t) (dst_base + dst_length);
    /* Loop over the blockSize */
    i = blockSize;
    while (i > 0u) {
        /* copy the sample from circular buffer to the destination buffer */
        *dst = circBuffer[rOffset];
        /* Update the input pointer */
        dst += dstInc;
        if (dst == (q7_t *) dst_end) {
            dst = dst_base;
        }
        /**
         * Circularly update rOffset.
         * Watch out for positive and negative value.
         */
        rOffset += bufferInc;
        if (rOffset >= L) {
            rOffset -= L;
        }
        /* Decrement the loop counter */
        i--;
    }
    /* Update the index pointer */
    *readOffset = rOffset;
}

/**
 * Sum of the squares of the elements of a Q31 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_power_q31(q31_t* pSrc, uint32_t blockSize, q63_t* pResult);

/**
 * Sum of the squares of the elements of a floating-point vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_power_f32(float32_t* pSrc, uint32_t blockSize, float32_t* pResult);

/**
 * Sum of the squares of the elements of a Q15 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_power_q15(q15_t* pSrc, uint32_t blockSize, q63_t* pResult);

/**
 * Sum of the squares of the elements of a Q7 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_power_q7(q7_t* pSrc, uint32_t blockSize, q31_t* pResult);

/**
 * Mean value of a Q7 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_mean_q7(q7_t* pSrc, uint32_t blockSize, q7_t* pResult);

/**
 * Mean value of a Q15 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_mean_q15(q15_t* pSrc, uint32_t blockSize, q15_t* pResult);

/**
 * Mean value of a Q31 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_mean_q31(q31_t* pSrc, uint32_t blockSize, q31_t* pResult);

/**
 * Mean value of a floating-point vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_mean_f32(float32_t* pSrc, uint32_t blockSize, float32_t* pResult);

/**
 * Variance of the elements of a floating-point vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_var_f32(float32_t* pSrc, uint32_t blockSize, float32_t* pResult);

/**
 * Variance of the elements of a Q31 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_var_q31(q31_t* pSrc, uint32_t blockSize, q63_t* pResult);

/**
 * Variance of the elements of a Q15 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_var_q15(q15_t* pSrc, uint32_t blockSize, q31_t* pResult);

/**
 * Root Mean Square of the elements of a floating-point vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_rms_f32(float32_t* pSrc, uint32_t blockSize, float32_t* pResult);

/**
 * Root Mean Square of the elements of a Q31 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_rms_q31(q31_t* pSrc, uint32_t blockSize, q31_t* pResult);

/**
 * Root Mean Square of the elements of a Q15 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_rms_q15(q15_t* pSrc, uint32_t blockSize, q15_t* pResult);

/**
 * Standard deviation of the elements of a floating-point vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_std_f32(float32_t* pSrc, uint32_t blockSize, float32_t* pResult);

/**
 * Standard deviation of the elements of a Q31 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_std_q31(q31_t* pSrc, uint32_t blockSize, q31_t* pResult);

/**
 * Standard deviation of the elements of a Q15 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output value.
 * return none.
 */
void arm_std_q15(q15_t* pSrc, uint32_t blockSize, q15_t* pResult);

/**
 * Floating-point complex magnitude
 * param *pSrc points to the complex input vector
 * param *pDst points to the real output vector
 * param numSamples number of complex samples in the input vector
 * return none.
 */
void arm_cmplx_mag_f32(float32_t* pSrc, float32_t* pDst, uint32_t numSamples);

/**
 * Q31 complex magnitude
 * param *pSrc points to the complex input vector
 * param *pDst points to the real output vector
 * param numSamples number of complex samples in the input vector
 * return none.
 */
void arm_cmplx_mag_q31(q31_t* pSrc, q31_t* pDst, uint32_t numSamples);

/**
 * Q15 complex magnitude
 * param *pSrc points to the complex input vector
 * param *pDst points to the real output vector
 * param numSamples number of complex samples in the input vector
 * return none.
 */
void arm_cmplx_mag_q15(q15_t* pSrc, q15_t* pDst, uint32_t numSamples);

/**
 * Q15 complex dot product
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param numSamples number of complex samples in each vector
 * param *realResult real part of the result returned here
 * param *imagResult imaginary part of the result returned here
 * return none.
 */
void arm_cmplx_dot_prod_q15(
    q15_t* pSrcA, q15_t* pSrcB, uint32_t numSamples,
    q31_t* realResult, q31_t* imagResult
);

/**
 * Q31 complex dot product
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param numSamples number of complex samples in each vector
 * param *realResult real part of the result returned here
 * param *imagResult imaginary part of the result returned here
 * return none.
 */
void arm_cmplx_dot_prod_q31(
    q31_t* pSrcA, q31_t* pSrcB, uint32_t numSamples,
    q63_t* realResult, q63_t* imagResult
);

/**
 * Floating-point complex dot product
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param numSamples number of complex samples in each vector
 * param *realResult real part of the result returned here
 * param *imagResult imaginary part of the result returned here
 * return none.
 */
void arm_cmplx_dot_prod_f32(
    float32_t* pSrcA, float32_t* pSrcB, uint32_t numSamples,
    float32_t* realResult, float32_t* imagResult
);

/**
 * Q15 complex-by-real multiplication
 * param *pSrcCmplx points to the complex input vector
 * param *pSrcReal points to the real input vector
 * param *pCmplxDst points to the complex output vector
 * param numSamples number of samples in each vector
 * return none.
 */
void arm_cmplx_mult_real_q15(
    q15_t* pSrcCmplx, q15_t* pSrcReal, q15_t* pCmplxDst, uint32_t numSamples
);

/**
 * Q31 complex-by-real multiplication
 * param *pSrcCmplx points to the complex input vector
 * param *pSrcReal points to the real input vector
 * param *pCmplxDst points to the complex output vector
 * param numSamples number of samples in each vector
 * return none.
 */
void arm_cmplx_mult_real_q31(
    q31_t* pSrcCmplx, q31_t* pSrcReal, q31_t* pCmplxDst, uint32_t numSamples
);

/**
 * Floating-point complex-by-real multiplication
 * param *pSrcCmplx points to the complex input vector
 * param *pSrcReal points to the real input vector
 * param *pCmplxDst points to the complex output vector
 * param numSamples number of samples in each vector
 * return none.
 */
void arm_cmplx_mult_real_f32(
    float32_t* pSrcCmplx, float32_t* pSrcReal,
    float32_t* pCmplxDst, uint32_t numSamples
);

/**
 * Minimum value of a Q7 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *result is output pointer
 * param index is the array index of the minimum value in the input buffer.
 * return none.
 */
void arm_min_q7(
    q7_t* pSrc, uint32_t blockSize, q7_t* result, uint32_t* index
);

/**
 * Minimum value of a Q15 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output pointer
 * param *pIndex is the array index of the minimum value in the input buffer.
 * return none.
 */
void arm_min_q15(
    q15_t* pSrc, uint32_t blockSize, q15_t* pResult, uint32_t* pIndex
);

/**
 * Minimum value of a Q31 vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output pointer
 * param *pIndex is the array index of the minimum value in the input buffer.
 * return none.
 */
void arm_min_q31(
    q31_t* pSrc, uint32_t blockSize, q31_t* pResult, uint32_t* pIndex
);

/**
 * Minimum value of a floating-point vector.
 * param *pSrc is input pointer
 * param blockSize is the number of samples to process
 * param *pResult is output pointer
 * param *pIndex is the array index of the minimum value in the input buffer.
 * return none.
 */
void arm_min_f32(
    float32_t* pSrc, uint32_t blockSize, float32_t* pResult, uint32_t* pIndex
);

/**
 * Maximum value of a Q7 vector.
 * param *pSrc points to the input buffer
 * param blockSize length of the input vector
 * param *pResult maximum value returned here
 * param *pIndex index of maximum value returned here
 * return none.
 */
void arm_max_q7(
    q7_t* pSrc, uint32_t blockSize, q7_t* pResult, uint32_t* pIndex
);

/**
 * Maximum value of a Q15 vector.
 * param *pSrc points to the input buffer
 * param blockSize length of the input vector
 * param *pResult maximum value returned here
 * param *pIndex index of maximum value returned here
 * return none.
 */
void arm_max_q15(
    q15_t* pSrc, uint32_t blockSize, q15_t* pResult, uint32_t* pIndex
);

/**
 * Maximum value of a Q31 vector.
 * param *pSrc points to the input buffer
 * param blockSize length of the input vector
 * param *pResult maximum value returned here
 * param *pIndex index of maximum value returned here
 * return none.
 */
void arm_max_q31(
    q31_t* pSrc, uint32_t blockSize, q31_t* pResult, uint32_t* pIndex
);

/**
 * Maximum value of a floating-point vector.
 * param *pSrc points to the input buffer
 * param blockSize length of the input vector
 * param *pResult maximum value returned here
 * param *pIndex index of maximum value returned here
 * return none.
 */
void arm_max_f32(
   float32_t* pSrc, uint32_t blockSize, float32_t* pResult, uint32_t* pIndex
);

/**
 * Q15 complex-by-complex multiplication
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst  points to the output vector
 * param numSamples number of complex samples in each vector
 * return none.
 */
void arm_cmplx_mult_cmplx_q15(
    q15_t* pSrcA, q15_t* pSrcB, q15_t* pDst, uint32_t numSamples
);

/**
 *  Q31 complex-by-complex multiplication
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst  points to the output vector
 * param numSamples number of complex samples in each vector
 * return none.
 */
void arm_cmplx_mult_cmplx_q31(
    q31_t* pSrcA, q31_t* pSrcB, q31_t* pDst, uint32_t numSamples
);

/**
 * Floating-point complex-by-complex multiplication
 * param *pSrcA points to the first input vector
 * param *pSrcB points to the second input vector
 * param *pDst  points to the output vector
 * param numSamples number of complex samples in each vector
 * return none.
 */
void arm_cmplx_mult_cmplx_f32(
    float32_t* pSrcA, float32_t* pSrcB, float32_t* pDst, uint32_t numSamples
);

/**
 * Converts the elements of the floating-point vector to Q31 vector. 
 * param *pSrc points to the floating-point input vector 
 * param *pDst points to the Q31 output vector
 * param blockSize length of the input vector 
 * return none. 
 */
void arm_float_to_q31(float32_t* pSrc, q31_t* pDst, uint32_t blockSize);

/**
 * Converts the elements of the floating-point vector to Q15 vector. 
 * param *pSrc points to the floating-point input vector 
 * param *pDst points to the Q15 output vector
 * param blockSize length of the input vector 
 * return   none
 */
void arm_float_to_q15(float32_t* pSrc, q15_t* pDst, uint32_t blockSize);

/**
 * Converts the elements of the floating-point vector to Q7 vector. 
 * param *pSrc points to the floating-point input vector 
 * param *pDst points to the Q7 output vector
 * param blockSize length of the input vector 
 * return   none
 */
void arm_float_to_q7(float32_t* pSrc, q7_t* pDst, uint32_t blockSize);

/**
 * Converts the elements of the Q31 vector to Q15 vector.
 * param *pSrc is input pointer
 * param *pDst is output pointer
 * param blockSize is the number of samples to process
 * return none.
 */
void arm_q31_to_q15(q31_t* pSrc, q15_t* pDst, uint32_t blockSize);

/**
 * Converts the elements of the Q31 vector to Q7 vector.
 * param *pSrc is input pointer
 * param *pDst is output pointer
 * param blockSize is the number of samples to process
 * return none.
 */
void arm_q31_to_q7(q31_t* pSrc, q7_t* pDst, uint32_t blockSize);

/**
 * Converts the elements of the Q15 vector to floating-point vector.
 * param *pSrc is input pointer
 * param *pDst is output pointer
 * param blockSize is the number of samples to process
 * return none.
 */
void arm_q15_to_float(q15_t* pSrc, float32_t* pDst, uint32_t blockSize);

/**
 * Converts the elements of the Q15 vector to Q31 vector.
 * param *pSrc is input pointer
 * param *pDst is output pointer
 * param blockSize is the number of samples to process
 * return none.
 */
void arm_q15_to_q31(q15_t* pSrc, q31_t* pDst, uint32_t blockSize);

/**
 * Converts the elements of the Q15 vector to Q7 vector.
 * param *pSrc is input pointer
 * param *pDst is output pointer
 * param blockSize is the number of samples to process
 * return none.
 */
void arm_q15_to_q7(q15_t* pSrc, q7_t* pDst, uint32_t blockSize);

/**
 * Floating-point bilinear interpolation.
 * param *S points to an instance of the interpolation structure.
 * param X interpolation coordinate.
 * param Y interpolation coordinate.
 * return out interpolated value.
 */
static __INLINE float32_t arm_bilinear_interp_f32(
    const arm_bilinear_interp_instance_f32* S, float32_t X, float32_t Y
) {
    float32_t out;
    float32_t f00, f01, f10, f11;
    float32_t *pData = S->pData;
    int32_t xIndex, yIndex, index;
    float32_t xdiff, ydiff;
    float32_t b1, b2, b3, b4;
    xIndex = (int32_t) X;
    yIndex = (int32_t) Y;

    /* Care taken for table outside boundary */
    /* Returns zero output when values are outside table boundary */
    if (
        xIndex < 0 || xIndex > (S->numRows-1) ||
        yIndex < 0  || yIndex > ( S->numCols-1)
    ) {
        return(0);
    }
    /* Calculation of index for two nearest points in X-direction */
    index = (xIndex - 1) + (yIndex-1) *  S->numCols ;
    /* Read two nearest points in X-direction */
    f00 = pData[index];
    f01 = pData[index + 1];
    /* Calculation of index for two nearest points in Y-direction */
    index = (xIndex-1) + (yIndex) * S->numCols;
    /* Read two nearest points in Y-direction */
    f10 = pData[index];
    f11 = pData[index + 1];
    /* Calculation of intermediate values */
    b1 = f00;
    b2 = f01 - f00;
    b3 = f10 - f00;
    b4 = f00 - f01 - f10 + f11;
    /* Calculation of fractional part in X */
    xdiff = X - xIndex;
    /* Calculation of fractional part in Y */
    ydiff = Y - yIndex;
    /* Calculation of bi-linear interpolated output */
     out = b1 + b2 * xdiff + b3 * ydiff + b4 * xdiff * ydiff;
   /* return to application */
    return (out);
}

/**
 * Q31 bilinear interpolation.
 * param *S points to an instance of the interpolation structure.
 * param X interpolation coordinate in 12.20 format.
 * param Y interpolation coordinate in 12.20 format.
 * return out interpolated value.
 */
static __INLINE q31_t arm_bilinear_interp_q31(
    arm_bilinear_interp_instance_q31* S, q31_t X, q31_t Y
) {
    q31_t out; /* Temporary output */
    q31_t acc = 0; /* output */
    q31_t xfract, yfract; /* X, Y fractional parts */
    q31_t x1, x2, y1, y2; /* Nearest output values */
    int32_t rI, cI; /* Row and column indices */
    q31_t*pYData = S->pData; /* pointer to output table values */
    uint32_t nCols = S->numCols; /* num of rows */

    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    rI = ((X & 0xFFF00000) >> 20u);
    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    cI = ((Y & 0xFFF00000) >> 20u);
    /* Care taken for table outside boundary */
    /* Returns zero output when values are outside table boundary */
    if (rI < 0 || rI > (S->numRows-1) || cI < 0  || cI > ( S->numCols-1)) {
        return(0);
    }
    /* 20 bits for the fractional part */
    /* shift left xfract by 11 to keep 1.31 format */
    xfract = (X & 0x000FFFFF) << 11u;
    /* Read two nearest output values from the index */
    x1 = pYData[(rI) + nCols * (cI)];
    x2 = pYData[(rI) + nCols * (cI) + 1u];
    /* 20 bits for the fractional part */
    /* shift left yfract by 11 to keep 1.31 format */
    yfract = (Y & 0x000FFFFF) << 11u;
    /* Read two nearest output values from the index */
    y1 = pYData[(rI) + nCols * (cI + 1)];
    y2 = pYData[(rI) + nCols * (cI + 1) + 1u];
    /* Calculation x1*(1-xfract)*(1-yfract) and acc is in 3.29(q29) format */
    out = ((q31_t) (((q63_t) x1 * (0x7FFFFFFF - xfract)) >> 32));
    acc = ((q31_t) (((q63_t) out * (0x7FFFFFFF - yfract)) >> 32));
    /* x2 * (xfract) * (1-yfract)  in 3.29(q29) and adding to acc */
    out = ((q31_t) ((q63_t) x2 * (0x7FFFFFFF - yfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (xfract) >> 32));
    /* y1 * (1 - xfract) * (yfract)  in 3.29(q29) and adding to acc */
    out = ((q31_t) ((q63_t) y1 * (0x7FFFFFFF - xfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (yfract) >> 32));
    /* y2 * (xfract) * (yfract)  in 3.29(q29) and adding to acc */
    out = ((q31_t) ((q63_t) y2 * (xfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (yfract) >> 32));
    /* Convert acc to 1.31(q31) format */
    return (acc << 2u);
}

/**
 * Q15 bilinear interpolation.
 * param *S points to an instance of the interpolation structure.
 * param X interpolation coordinate in 12.20 format.
 * param Y interpolation coordinate in 12.20 format.
 * return out interpolated value.
 */
static __INLINE q15_t arm_bilinear_interp_q15(
    arm_bilinear_interp_instance_q15* S, q31_t X, q31_t Y
) {
    q63_t acc = 0; /* output */
    q31_t out; /* Temporary output */
    q15_t x1, x2, y1, y2; /* Nearest output values */
    q31_t xfract, yfract; /* X, Y fractional parts */
    int32_t rI, cI; /* Row and column indices */
    q15_t *pYData = S->pData; /* pointer to output table values */
    uint32_t nCols = S->numCols; /* num of rows */

    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    rI = ((X & 0xFFF00000) >> 20);
    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    cI = ((Y & 0xFFF00000) >> 20);
    /* Care taken for table outside boundary */
    /* Returns zero output when values are outside table boundary */
    if (rI < 0 || rI > (S->numRows-1) || cI < 0  || cI > ( S->numCols-1)) {
        return(0);
    }
    /* 20 bits for the fractional part */
    /* xfract should be in 12.20 format */
    xfract = (X & 0x000FFFFF);
    /* Read two nearest output values from the index */
    x1 = pYData[(rI) + nCols * (cI)];
    x2 = pYData[(rI) + nCols * (cI) + 1u];
    /* 20 bits for the fractional part */
    /* yfract should be in 12.20 format */
    yfract = (Y & 0x000FFFFF);
    /* Read two nearest output values from the index */
    y1 = pYData[(rI) + nCols * (cI + 1)];
    y2 = pYData[(rI) + nCols * (cI + 1) + 1u];
    /* Calculation x1 * (1-xfract ) * (1-yfract) and acc is in 13.51 format */
    /* x1 is in 1.15(q15), xfract in 12.20 format and out is in 13.35 format */
    /* convert 13.35 to 13.31 by right shifting  and out is in 1.31 */
    out = (q31_t) (((q63_t) x1 * (0xFFFFF - xfract)) >> 4u);
    acc = ((q63_t) out * (0xFFFFF - yfract));
    /* x2 * (xfract) * (1-yfract)  in 1.51 and adding to acc */
    out = (q31_t) (((q63_t) x2 * (0xFFFFF - yfract)) >> 4u);
    acc += ((q63_t) out * (xfract));
    /* y1 * (1 - xfract) * (yfract)  in 1.51 and adding to acc */
    out = (q31_t) (((q63_t) y1 * (0xFFFFF - xfract)) >> 4u);
    acc += ((q63_t) out * (yfract));
    /* y2 * (xfract) * (yfract)  in 1.51 and adding to acc */
    out = (q31_t) (((q63_t) y2 * (xfract)) >> 4u);
    acc += ((q63_t) out * (yfract));
    /* acc is in 13.51 format and down shift acc by 36 times */
    /* Convert out to 1.15 format */
    return (acc >> 36);
}

/**
  * Q7 bilinear interpolation.
  * param *S points to an instance of the interpolation structure.
  * param X interpolation coordinate in 12.20 format.
  * param Y interpolation coordinate in 12.20 format.
  * return out interpolated value.
  */
static __INLINE q7_t arm_bilinear_interp_q7(
    arm_bilinear_interp_instance_q7* S, q31_t X, q31_t Y
) {
    q63_t acc = 0; /* output */
    q31_t out; /* Temporary output */
    q31_t xfract, yfract; /* X, Y fractional parts */
    q7_t x1, x2, y1, y2; /* Nearest output values */
    int32_t rI, cI; /* Row and column indices */
    q7_t *pYData = S->pData; /* pointer to output table values */
    uint32_t nCols = S->numCols; /* num of rows */

    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    rI = ((X & 0xFFF00000) >> 20);
    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    cI = ((Y & 0xFFF00000) >> 20);
    /* Care taken for table outside boundary */
    /* Returns zero output when values are outside table boundary */
    if(rI < 0 || rI > (S->numRows-1) || cI < 0  || cI > ( S->numCols-1)) {
        return(0);
    }
    /* 20 bits for the fractional part */
    /* xfract should be in 12.20 format */
    xfract = (X & 0x000FFFFF);
    /* Read two nearest output values from the index */
    x1 = pYData[(rI) + nCols * (cI)];
    x2 = pYData[(rI) + nCols * (cI) + 1u];
    /* 20 bits for the fractional part */
    /* yfract should be in 12.20 format */
    yfract = (Y & 0x000FFFFF);
    /* Read two nearest output values from the index */
    y1 = pYData[(rI) + nCols * (cI + 1)];
    y2 = pYData[(rI) + nCols * (cI + 1) + 1u];
    /* Calculation of x1*(1-xfract)*(1-yfract) and acc is in 16.47 format */
    out = ((x1 * (0xFFFFF - xfract)));
    acc = (((q63_t) out * (0xFFFFF - yfract)));
    /* x2 * (xfract) * (1-yfract)  in 2.22 and adding to acc */
    out = ((x2 * (0xFFFFF - yfract)));
    acc += (((q63_t) out * (xfract)));
    /* y1 * (1 - xfract) * (yfract)  in 2.22 and adding to acc */
    out = ((y1 * (0xFFFFF - xfract)));
    acc += (((q63_t) out * (yfract)));
    /* y2 * (xfract) * (yfract)  in 2.22 and adding to acc */
    out = ((y2 * (yfract)));
    acc += (((q63_t) out * (xfract)));
    /* acc in 16.47 format and down shift by 40 to convert to 1.7 format */
    return (acc >> 40);
}

#ifdef __cplusplus
    }
#endif

#endif

