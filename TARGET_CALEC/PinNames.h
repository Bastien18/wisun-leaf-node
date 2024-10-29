/***************************************************************************//**
 * @file PinNames.h
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

/* MBED TARGET LIST: TB_SENSE_12 */

#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "CommonPinNames.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFR32_CUSTOM_BOARD

typedef enum {
    EFM32_STANDARD_PIN_DEFINITIONS,

    ENABLE_VCOM = PA11,

    RF_CSD = PC4,   // (old RF_7_0A : PC3)
    RF_VDET = PC7,
    RF_NCTRL_BAND = PC8,
    RF_CTRL_BAND = PC9,
    RF_CTX = PB0,
    RF_CPS = PA0,

    GPIO0_EXT        = PC0,
    GPIO1_EXT        = PC1,
    GPIO2_EXT        = PC2,
    GPIO3_EXT        = PC3,
    GPIO4_EXT        = PD4,
    GPIO5_EXT        = PD3,
    GPIO6_EXT        = PD2,
    GPIO7_EXT        = PD0,

    /* Board Controller UART (USB)*/
    CONSOLE_TX       = GPIO1_EXT,
    CONSOLE_RX       = GPIO7_EXT,

    ISM_UART_TX       = PA5,
    ISM_UART_RX       = PA6,

    /* Board Controller */
#if defined(MBED_CONF_TARGET_STDIO_UART_TX)
    STDIO_UART_TX   = MBED_CONF_TARGET_STDIO_UART_TX,
#else
    STDIO_UART_TX   = CONSOLE_TX,
#endif
#if defined(MBED_CONF_TARGET_STDIO_UART_RX)
    STDIO_UART_RX   = MBED_CONF_TARGET_STDIO_UART_RX,
#else
    STDIO_UART_RX   = CONSOLE_RX
#endif
} PinName;

#ifdef __cplusplus
}
#endif

#endif
