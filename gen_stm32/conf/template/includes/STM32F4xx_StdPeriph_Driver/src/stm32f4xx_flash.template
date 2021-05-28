/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_flash.c
 * 
 * This file provides firmware functions to manage following
 * functionalities of FLASH peripheral:
 *     - FLASH Interface configuration
 *     - FLASH Memory Programming
 *     - Option Bytes Programming
 *     - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_flash is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_flash is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_flash.h"
#include "stm32f4xx_conf.h"

#define SECTOR_MASK ((uint32_t) 0xFFFFFF07)

/**
 * Sets code latency value.
 * param FLASH_Latency: specifies FLASH Latency value.
 *   This parameter can be one of following values:
 *       arg FLASH_Latency_0: FLASH Zero Latency cycle
 *       arg FLASH_Latency_1: FLASH One Latency cycle
 *       arg FLASH_Latency_2: FLASH Two Latency cycles
 *       arg FLASH_Latency_3: FLASH Three Latency cycles
 *       arg FLASH_Latency_4: FLASH Four Latency cycles 
 *       arg FLASH_Latency_5: FLASH Five Latency cycles 
 *       arg FLASH_Latency_6: FLASH Six Latency cycles
 *       arg FLASH_Latency_7: FLASH Seven Latency cycles
 * retval None
 */
void FLASH_SetLatency(uint32_t FLASH_Latency) {
    assert_param(IS_FLASH_LATENCY(FLASH_Latency));
    /* Perform Byte access to FLASH_ACR[8:0] to set Latency value */
    *(__IO uint8_t *) ACR_BYTE0_ADDRESS = (uint8_t) FLASH_Latency;
}

/**
 * Enables or disables Prefetch Buffer.
 * param NewState: new state of Prefetch Buffer.
 *   This parameter  can be: ENABLE or DISABLE.
 * retval None
 */
void FLASH_PrefetchBufferCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    /* Enable or disable Prefetch Buffer */
    if (NewState != DISABLE) {
        FLASH->ACR |= FLASH_ACR_PRFTEN;
    } else {
        FLASH->ACR &= (~FLASH_ACR_PRFTEN);
    }
}

/**
 * Enables or disables Instruction Cache feature.
 * param NewState: new state of Instruction Cache.
 *   This parameter  can be: ENABLE or DISABLE.
 * retval None
 */
void FLASH_InstructionCacheCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        FLASH->ACR |= FLASH_ACR_ICEN;
    } else {
        FLASH->ACR &= (~FLASH_ACR_ICEN);
    }
}

/**
 * Enables or disables Data Cache feature.
 * param NewState: new state of Data Cache.
 *   This parameter  can be: ENABLE or DISABLE.
 * retval None
 */
void FLASH_DataCacheCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        FLASH->ACR |= FLASH_ACR_DCEN;
    } else {
        FLASH->ACR &= (~FLASH_ACR_DCEN);
    }
}

/**
 * Resets Instruction Cache.
 * This function must be used only when Instruction Cache is disabled.
 * param None
 * retval None
 */
void FLASH_InstructionCacheReset(void) {
    FLASH->ACR |= FLASH_ACR_ICRST;
}

/**
 * Resets Data Cache.
 * This function must be used only when Data Cache is disabled.
 * param None
 * retval None
 */
void FLASH_DataCacheReset(void) {
    FLASH->ACR |= FLASH_ACR_DCRST;
}

/**
 * Unlocks FLASH control register access
 * param None
 * retval None
 */
void FLASH_Unlock(void) {
    if ((FLASH->CR & FLASH_CR_LOCK) != RESET) {
        /* Authorize FLASH Registers access */
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

/**
 * Locks FLASH control register access
 * param None
 * retval None
 */
void FLASH_Lock(void) {
    /* Set LOCK Bit to lock FLASH Registers access */
    FLASH->CR |= FLASH_CR_LOCK;
}

/**
 * Erases a specified FLASH Sector.
 * param FLASH_Sector: The Sector number to be erased.
 *   This parameter can be a value between FLASH_Sector_0 and FLASH_Sector_11
 * param VoltageRange: The device voltage range which defines
 *       erase parallelism.
 *   This parameter can be one of following values:
 *       arg VoltageRange_1: when device voltage range is 1.8V to 2.1V,
 *            operation will be done by byte (8-bit) 
 *       arg VoltageRange_2: when device voltage range is 2.1V to 2.7V,
 *            operation will be done by half word (16-bit)
 *       arg VoltageRange_3: when device voltage range is 2.7V to 3.6V,
 *            operation will be done by word (32-bit)
 *       arg VoltageRange_4: when device voltage range is 2.7V to 3.6V +
 *           External Vpp, operation will be done by double word (64-bit)
 * retval FLASH Status: The returned value can be: FLASH_BUSY,
 * FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_ERROR_OPERATION
 or FLASH_COMPLETE.
 */
FLASH_Status FLASH_EraseSector(uint32_t FLASH_Sector, uint8_t VoltageRange) {
    uint32_t tmp_psize = 0x0;
    FLASH_Status status = FLASH_COMPLETE;

    assert_param(IS_FLASH_SECTOR(FLASH_Sector));
    assert_param(IS_VOLTAGERANGE(VoltageRange));
    if (VoltageRange == VoltageRange_1) {
        tmp_psize = FLASH_PSIZE_BYTE;
    } else if (VoltageRange == VoltageRange_2) {
        tmp_psize = FLASH_PSIZE_HALF_WORD;
    } else if (VoltageRange == VoltageRange_3) {
        tmp_psize = FLASH_PSIZE_WORD;
    } else {
        tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
    }
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();
    if (status == FLASH_COMPLETE) {
        /* if previous operation is completed, proceed to erase sector */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= tmp_psize;
        FLASH->CR &= SECTOR_MASK;
        FLASH->CR |= FLASH_CR_SER | FLASH_Sector;
        FLASH->CR |= FLASH_CR_STRT;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation();
        /* if erase operation is completed, disable SER Bit */
        FLASH->CR &= (~FLASH_CR_SER);
        FLASH->CR &= SECTOR_MASK; 
    }
    return status; /* Return Erase Status */
}

/**
 * Erases all FLASH Sectors.
 * param VoltageRange: The device voltage range which defines
 *       erase parallelism.
 *   This parameter can be one of following values:
 *       arg VoltageRange_1: when device voltage range is 1.8V to 2.1V, 
 *           operation will be done by byte (8-bit) 
 *       arg VoltageRange_2: when device voltage range is 2.1V to 2.7V,
 *           operation will be done by half word (16-bit)
 *       arg VoltageRange_3: when device voltage range is 2.7V to 3.6V,
 *           operation will be done by word (32-bit)
 *       arg VoltageRange_4: when device voltage range is 2.7V to 3.6V +
 *           External Vpp, operation will be done by double word (64-bit)
 * retval FLASH Status: The returned value can be: FLASH_BUSY,
 * FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_ERROR_OPERATION
 * or FLASH_COMPLETE.
 */
FLASH_Status FLASH_EraseAllSectors(uint8_t VoltageRange) {
    uint32_t tmp_psize = 0x0;
    FLASH_Status status = FLASH_COMPLETE;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();
    assert_param(IS_VOLTAGERANGE(VoltageRange));
    if(VoltageRange == VoltageRange_1) {
        tmp_psize = FLASH_PSIZE_BYTE;
    } else if (VoltageRange == VoltageRange_2) {
        tmp_psize = FLASH_PSIZE_HALF_WORD;
    } else if (VoltageRange == VoltageRange_3) {
        tmp_psize = FLASH_PSIZE_WORD;
    } else {
        tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
    } if (status == FLASH_COMPLETE) {
        /* if previous operation is completed, proceed to erase all sectors */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= tmp_psize;
        FLASH->CR |= FLASH_CR_MER;
        FLASH->CR |= FLASH_CR_STRT;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation();
        /* if erase operation is completed, disable MER Bit */
        FLASH->CR &= (~FLASH_CR_MER);
    }
    return status; /* Return Erase Status */
}

/**
 * Programs a double word (64-bit) at a specified address.
 * This function must be used when device voltage range is from
 * 2.7V to 3.6V and an External Vpp is present.
 * param Address: specifies address to be programmed.
 * param Data: specifies data to be programmed.
 * retval FLASH Status: The returned value can be: FLASH_BUSY,
 * FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_ERROR_OPERATION
 * or FLASH_COMPLETE.
 */
FLASH_Status FLASH_ProgramDoubleWord(uint32_t Address, uint64_t Data) {
    FLASH_Status status = FLASH_COMPLETE;

    assert_param(IS_FLASH_ADDRESS(Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();
    if (status == FLASH_COMPLETE) {
        /* if previous operation is completed, proceed to program new data */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= FLASH_PSIZE_DOUBLE_WORD;
        FLASH->CR |= FLASH_CR_PG;
        *(__IO uint64_t*) Address = Data;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation();
        /* if program operation is completed, disable PG Bit */
        FLASH->CR &= (~FLASH_CR_PG);
    }
    return status; /* Return Program Status */
}

/**
 * Programs a word (32-bit) at a specified address.
 * param Address: specifies address to be programmed.
 *   This parameter can be any address in Program memory zone or in OTP zone.
 * This function must be used when device voltage range is from 2.7V to 3.6V.
 * param Data: specifies data to be programmed.
 * retval FLASH Status: The returned value can be: FLASH_BUSY,
 * FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_ERROR_OPERATION
 * or FLASH_COMPLETE.
 */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data) {
    FLASH_Status status = FLASH_COMPLETE;

    assert_param(IS_FLASH_ADDRESS(Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();
    if (status == FLASH_COMPLETE) {
        /* if previous operation is completed, proceed to program new data */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= FLASH_PSIZE_WORD;
        FLASH->CR |= FLASH_CR_PG;
        *(__IO uint32_t*) Address = Data;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation();
        /* if program operation is completed, disable PG Bit */
        FLASH->CR &= (~FLASH_CR_PG);
    }
    return status; /* Return Program Status */
}

/**
 * Programs a half word (16-bit) at a specified address.
 * This function must be used when device voltage range is from 2.1V to 3.6V.
 * param Address: specifies address to be programmed.
 *   This parameter can be any address in Program memory zone or in OTP zone.
 * param Data: specifies data to be programmed.
 * retval FLASH Status: The returned value can be: FLASH_BUSY,
 * FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_ERROR_OPERATION
 * or FLASH_COMPLETE.
 */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data) {
    FLASH_Status status = FLASH_COMPLETE;

    assert_param(IS_FLASH_ADDRESS(Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();
    if (status == FLASH_COMPLETE) {
        /* if previous operation is completed, proceed to program new data */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= FLASH_PSIZE_HALF_WORD;
        FLASH->CR |= FLASH_CR_PG;
        *(__IO uint16_t*) Address = Data;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation();
        /* if program operation is completed, disable PG Bit */
        FLASH->CR &= (~FLASH_CR_PG);
    }
    return status; /* Return Program Status */
}

/**
 * Programs a byte (8-bit) at a specified address.
 * This function can be used within all device supply voltage ranges.
 * param Address: specifies address to be programmed.
 *   This parameter can be any address in Program memory zone or in OTP zone.
 * param Data: specifies data to be programmed.
 * retval FLASH Status: The returned value can be: FLASH_BUSY,
 * FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_ERROR_OPERATION
 * or FLASH_COMPLETE.
 */
FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data) {
    FLASH_Status status = FLASH_COMPLETE;

    assert_param(IS_FLASH_ADDRESS(Address));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();
    if (status == FLASH_COMPLETE) {
        /* if previous operation is completed, proceed to program new data */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= FLASH_PSIZE_BYTE;
        FLASH->CR |= FLASH_CR_PG;
        *(__IO uint8_t*) Address = Data;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation();
        /* if program operation is completed, disable PG Bit */
        FLASH->CR &= (~FLASH_CR_PG);
    }
    return status; /* Return Program Status */
}

/**
 * Unlocks FLASH Option Control Registers access.
 * param None
 * retval None
 */
void FLASH_OB_Unlock(void) {
    if ((FLASH->OPTCR & FLASH_OPTCR_OPTLOCK) != RESET) {
        /* Authorizes Option Byte register programming */
        FLASH->OPTKEYR = FLASH_OPT_KEY1;
        FLASH->OPTKEYR = FLASH_OPT_KEY2;
    }
}

/**
 * Locks FLASH Option Control Registers access.
 * param None
 * retval None
 */
void FLASH_OB_Lock(void) {
    /* Set OPTLOCK Bit to lock FLASH Option Byte Registers access */
    FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK;
}

/**
 * Enables or disables write protection of desired sectors
 * param OB_WRP: specifies sector(s) to be write protected or unprotected.
 *   This parameter can be one of following values:
 *       arg OB_WRP: A value between OB_WRP_Sector0 and OB_WRP_Sector11
 *       arg OB_WRP_Sector_All
 * param Newstate: new state of Write Protection.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void FLASH_OB_WRPConfig(uint32_t OB_WRP, FunctionalState NewState) {
    FLASH_Status status = FLASH_COMPLETE;

    assert_param(IS_OB_WRP(OB_WRP));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    status = FLASH_WaitForLastOperation();
    if (status == FLASH_COMPLETE) {
        if (NewState != DISABLE) {
            *(__IO uint16_t*) OPTCR_BYTE2_ADDRESS &= (~OB_WRP);
        } else {
            *(__IO uint16_t*) OPTCR_BYTE2_ADDRESS |= (uint16_t) OB_WRP;
        }
    }
}

/**
 * Sets read protection level.
 * param OB_RDP: specifies read protection level.
 *   This parameter can be one of following values:
 *       arg OB_RDP_Level_0: No protection
 *       arg OB_RDP_Level_1: Read protection of memory
 *       arg OB_RDP_Level_2: Full chip protection
 * 
 * !!!Warning!!! When enabling OB_RDP level 2 it's no more
 * possible to go back to level 1 or 0
 * 
 * retval None
 */
void FLASH_OB_RDPConfig(uint8_t OB_RDP) {
    FLASH_Status status = FLASH_COMPLETE;

    assert_param(IS_OB_RDP(OB_RDP));
    status = FLASH_WaitForLastOperation();
    if (status == FLASH_COMPLETE) {
        *(__IO uint8_t*) OPTCR_BYTE1_ADDRESS = OB_RDP;
    }
}

/**
 * Programs FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
 * param OB_IWDG: Selects IWDG mode
 *   This parameter can be one of following values:
 *       arg OB_IWDG_SW: Software IWDG selected
 *       arg OB_IWDG_HW: Hardware IWDG selected
 * param OB_STOP: Reset event when entering STOP mode.
 *   This parameter can be one of following values:
 *       arg OB_STOP_NoRST: No reset generated when entering in STOP
 *       arg OB_STOP_RST: Reset generated when entering in STOP
 * param OB_STDBY: Reset event when entering Standby mode.
 *   This parameter can be one of following values:
 *       arg OB_STDBY_NoRST: No reset generated when entering in STANDBY
 *       arg OB_STDBY_RST: Reset generated when entering in STANDBY
 * retval None
 */
void FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY) {
    uint8_t optiontmp = 0xFF;
    FLASH_Status status = FLASH_COMPLETE; 

    assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
    assert_param(IS_OB_STOP_SOURCE(OB_STOP));
    assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();
    if (status == FLASH_COMPLETE) {
        /* Mask OPTLOCK, OPTSTRT and BOR_LEV bits */
        optiontmp =  (uint8_t) (
            (*(__IO uint8_t *) OPTCR_BYTE0_ADDRESS) & (uint8_t) 0x0F
        );
        /* Update User Option Byte */
        *(__IO uint8_t *) OPTCR_BYTE0_ADDRESS = OB_IWDG | (uint8_t) (
            OB_STDBY | (uint8_t)(OB_STOP | ((uint8_t)optiontmp))
        );
    }
}

/**
 * Sets BOR Level.
 * param OB_BOR: specifies Option Bytes BOR Reset Level.
 *   This parameter can be one of following values:
 *       arg OB_BOR_LEVEL3: Supply voltage ranges from 2.7 to 3.6 V
 *       arg OB_BOR_LEVEL2: Supply voltage ranges from 2.4 to 2.7 V
 *       arg OB_BOR_LEVEL1: Supply voltage ranges from 2.1 to 2.4 V
 *       arg OB_BOR_OFF: Supply voltage ranges from 1.62 to 2.1 V
 * retval None
 */
void FLASH_OB_BORConfig(uint8_t OB_BOR) {
    assert_param(IS_OB_BOR(OB_BOR));
    /* Set BOR Level */
    *(__IO uint8_t *) OPTCR_BYTE0_ADDRESS &= (~FLASH_OPTCR_BOR_LEV);
    *(__IO uint8_t *) OPTCR_BYTE0_ADDRESS |= OB_BOR;
}

/**
 * Launch option byte loading.
 * param None
 * retval FLASH Status: The returned value can be: FLASH_BUSY,
 * FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_ERROR_OPERATION
 * or FLASH_COMPLETE.
 */
FLASH_Status FLASH_OB_Launch(void) {
    FLASH_Status status = FLASH_COMPLETE;

    /* Set OPTSTRT bit in OPTCR register */
    *(__IO uint8_t *) OPTCR_BYTE0_ADDRESS |= FLASH_OPTCR_OPTSTRT;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();
    return status;
}

/**
 * Returns FLASH User Option Bytes values.
 * param None
 * retval The FLASH User Option Bytes values: IWDG_SW(Bit0), RST_STOP(Bit1)
 * and RST_STDBY(Bit2).
 */
uint8_t FLASH_OB_GetUser(void) {
    return (uint8_t) (FLASH->OPTCR >> 5); /* Return User Option Byte */
}

/**
 * Returns FLASH Write Protection Option Bytes value.
 * param None
 * retval The FLASH Write Protection  Option Bytes value
 */
uint16_t FLASH_OB_GetWRP(void) {
    /* Return FLASH write protection Register value */
    return (*(__IO uint16_t *) (OPTCR_BYTE2_ADDRESS));
}

/**
 * Returns FLASH Read Protection level.
 * param None
 * retval FLASH ReadOut Protection Status:
 *     - SET, when OB_RDP_Level_1 or OB_RDP_Level_2 is set
 *     - RESET, when OB_RDP_Level_0 is set
 */
FlagStatus FLASH_OB_GetRDP(void) {
    FlagStatus readstatus = RESET;
    if ((*(__IO uint8_t*) (OPTCR_BYTE1_ADDRESS) != (uint8_t) OB_RDP_Level_0)) {
        readstatus = SET;
    } else {
        readstatus = RESET;
    }
    return readstatus;
}

/**
 * Returns FLASH BOR level.
 * param None
 * retval The FLASH BOR level:
 *     - OB_BOR_LEVEL3: Supply voltage ranges from 2.7 to 3.6 V
 *     - OB_BOR_LEVEL2: Supply voltage ranges from 2.4 to 2.7 V
 *     - OB_BOR_LEVEL1: Supply voltage ranges from 2.1 to 2.4 V
 *     - OB_BOR_OFF : Supply voltage ranges from 1.62 to 2.1 V
 */
uint8_t FLASH_OB_GetBOR(void) {
    /* Return FLASH BOR level */
    return (uint8_t) (
        *(__IO uint8_t *) (OPTCR_BYTE0_ADDRESS) & (uint8_t) 0x0C
    );
}

/**
 * Enables or disables specified FLASH interrupts.
 * param FLASH_IT: specifies FLASH interrupt sources to be enabled or disabled.
 *   This parameter can be any combination of following values:
 *       arg FLASH_IT_ERR: FLASH Error Interrupt
 *       arg FLASH_IT_EOP: FLASH end of operation Interrupt
 * retval None 
 */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState) {
    assert_param(IS_FLASH_IT(FLASH_IT)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        FLASH->CR |= FLASH_IT; /* Enable interrupt sources */
    } else {
        FLASH->CR &= ~(uint32_t) FLASH_IT; /* Disable interrupt sources */
    }
}

/**
 * Checks whether specified FLASH flag is set or not.
 * param FLASH_FLAG: specifies FLASH flag to check.
 *   This parameter can be one of following values:
 *       arg FLASH_FLAG_EOP: FLASH End of Operation flag
 *       arg FLASH_FLAG_OPERR: FLASH operation Error flag
 *       arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
 *       arg FLASH_FLAG_PGAERR: FLASH Programming Alignment error flag
 *       arg FLASH_FLAG_PGPERR: FLASH Programming Parallelism error flag
 *       arg FLASH_FLAG_PGSERR: FLASH Programming Sequence error flag
 *       arg FLASH_FLAG_BSY: FLASH Busy flag
 * retval The new state of FLASH_FLAG (SET or RESET).
 */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG) {
    FlagStatus bitstatus = RESET;

    assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));
    if ((FLASH->SR & FLASH_FLAG) != (uint32_t) RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus; /* Return new state of FLASH_FLAG (SET or RESET) */
}

/**
 * Clears FLASH's pending flags.
 * param FLASH_FLAG: specifies FLASH flags to clear.
 *   This parameter can be any combination of following values:
 *       arg FLASH_FLAG_EOP: FLASH End of Operation flag
 *       arg FLASH_FLAG_OPERR: FLASH operation Error flag
 *       arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
 *       arg FLASH_FLAG_PGAERR: FLASH Programming Alignment error flag
 *       arg FLASH_FLAG_PGPERR: FLASH Programming Parallelism error flag
 *       arg FLASH_FLAG_PGSERR: FLASH Programming Sequence error flag
 * retval None
 */
void FLASH_ClearFlag(uint32_t FLASH_FLAG) {
    assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));
    FLASH->SR = FLASH_FLAG; /* Clear flags */
}

/**
 * Returns FLASH Status.
 * param None
 * retval FLASH Status: The returned value can be: FLASH_BUSY,
 * FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_ERROR_OPERATION
 * or FLASH_COMPLETE.
 */
FLASH_Status FLASH_GetStatus(void) {
    FLASH_Status flashstatus = FLASH_COMPLETE;

    if ((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) {
        flashstatus = FLASH_BUSY;
    } else {
        if ((FLASH->SR & FLASH_FLAG_WRPERR) != (uint32_t) 0x00) {
            flashstatus = FLASH_ERROR_WRP;
        } else {
            if ((FLASH->SR & (uint32_t) 0xEF) != (uint32_t) 0x00) {
                flashstatus = FLASH_ERROR_PROGRAM;
            } else {
                if ((FLASH->SR & FLASH_FLAG_OPERR) != (uint32_t) 0x00) {
                    flashstatus = FLASH_ERROR_OPERATION;
                } else {
                    flashstatus = FLASH_COMPLETE;
                }
            }
        }
    }
    return flashstatus; /* Return FLASH Status */
}

/**
 * Waits for a FLASH operation to complete.
 * param None
 * retval FLASH Status: The returned value can be: FLASH_BUSY,
 * FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or
 * FLASH_COMPLETE.
 */
FLASH_Status FLASH_WaitForLastOperation(void) {
    __IO FLASH_Status status = FLASH_COMPLETE;

    status = FLASH_GetStatus();
    /**
     * Wait for FLASH operation to complete by polling on BUSY flag
     * to be reset. Even if FLASH operation fails, BUSY flag will
     * be reset and an errorflag will be set.
     */
    while(status == FLASH_BUSY) {
        status = FLASH_GetStatus();
    }
    return status; /* Return operation status */
}

