/* Copyright 2016, XXXXXXXXX  
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/
/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
 ** @{ */
/*
 * Initials     Name
 * ---------------------------
 *
 */
/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */
/*==================[inclusions]=============================================*/

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
#include "led.h"

/*==================[macros and definitions]=================================*/

#define LED0_R_PORT 2
#define LED0_R_PIN 0
#define LED0_R_GPIO_PORT 5
#define LED0_R_GPIO_BIT 0

#define LED0_G_PORT 2
#define LED0_G_PIN 1
#define LED0_G_GPIO_PORT 5
#define LED0_G_GPIO_BIT 1

#define LED0_B_PORT 2
#define LED0_B_PIN 2
#define LED0_B_GPIO_PORT 5
#define LED0_B_GPIO_BIT 2

#define LED1_PORT 2
#define LED1_PIN 10
#define LED1_GPIO_PORT 0
#define LED1_GPIO_BIT 14

#define LED2_PORT 2
#define LED2_PIN 11
#define LED2_GPIO_PORT 1
#define LED2_GPIO_BIT 11

#define LED3_PORT 2
#define LED3_PIN 12
#define LED3_GPIO_PORT 1
#define LED3_GPIO_BIT 12

#define OUTPUT_DIRECTION 1
#define INPUT_DIRECTION 0
/*==================[internal data declaration]==============================*/
/*==================[internal functions declaration]=========================*/
/*==================[internal data definition]===============================*/
/*==================[external data definition]===============================*/
/*==================[internal functions definition]==========================*/
/*==================[external functions definition]==========================*/
void InitLeds (void)
{
	Chip_GPIO_Init(LPC_GPIO_PORT);

	Chip_SCU_PinMux(LED0_R_PORT,LED0_R_PIN,MD_PUP,FUNC4); /* mapea P2 0 en GPIO5[0], LED0R y habilita el pull up*/
	Chip_SCU_PinMux(LED0_G_PORT,LED0_G_PIN,MD_PUP,FUNC4);
	Chip_SCU_PinMux(LED0_B_PORT,LED0_B_PIN,MD_PUP,FUNC4);
	Chip_SCU_PinMux(LED1_PORT,LED1_PIN,MD_PUP,FUNC0);
	Chip_SCU_PinMux(LED2_PORT,LED2_PIN,MD_PUP,FUNC0);
	Chip_SCU_PinMux(LED3_PORT,LED3_PIN,MD_PUP,FUNC0);

	Chip_GPIO_SetDir(LPC_GPIO_PORT,LED0_R_GPIO_PORT,1<<LED0_R_GPIO_BIT,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,LED0_G_GPIO_PORT,1<<LED0_G_GPIO_BIT,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,LED0_B_GPIO_PORT,1<<LED0_B_GPIO_BIT,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,LED1_GPIO_PORT,1<<LED1_GPIO_BIT,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,LED2_GPIO_PORT,1<<LED2_GPIO_BIT,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,LED3_GPIO_PORT,1<<LED3_GPIO_BIT,OUTPUT_DIRECTION);

	ApagarLed(LED_R);
	ApagarLed(LED_G);
	ApagarLed(LED_B);
	ApagarLed(LED_1);
	ApagarLed(LED_2);
	ApagarLed(LED_3);

	}
void EncenderLed(uint8_t led)
{
	switch (led)
	{
		case LED_R:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED0_R_GPIO_PORT, LED0_R_GPIO_BIT);
			break;
		case LED_G:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED0_G_GPIO_PORT, LED0_G_GPIO_BIT);
			break;
		case LED_B:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED0_B_GPIO_PORT, LED0_B_GPIO_BIT);
			break;
		case LED_1:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED1_GPIO_PORT, LED1_GPIO_BIT);
			break;
		case LED_2:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED2_GPIO_PORT, LED2_GPIO_BIT);
			break;
		case LED_3:
			Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, LED3_GPIO_PORT, LED3_GPIO_BIT);
			break;
		default: break;
	}
	}
void ApagarLed(uint8_t led)
{
	switch (led)
		{
			case LED_R:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED0_R_GPIO_PORT, LED0_R_GPIO_BIT);
				break;
			case LED_G:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED0_G_GPIO_PORT, LED0_G_GPIO_BIT);
				break;
			case LED_B:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED0_B_GPIO_PORT, LED0_B_GPIO_BIT);
				break;
			case LED_1:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED1_GPIO_PORT, LED1_GPIO_BIT);
				break;
			case LED_2:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED2_GPIO_PORT, LED2_GPIO_BIT);
				break;
			case LED_3:
				Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, LED3_GPIO_PORT, LED3_GPIO_BIT);
				break;
			default: break;
		}
	}
void ToggleLed (uint8_t led)
{
	switch (led)
		{
			case LED_R:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED0_R_GPIO_PORT, LED0_R_GPIO_BIT);
				break;
			case LED_G:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED0_G_GPIO_PORT, LED0_G_GPIO_BIT);
				break;
			case LED_B:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED0_B_GPIO_PORT, LED0_B_GPIO_BIT);
				break;
			case LED_1:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED1_GPIO_PORT, LED1_GPIO_BIT);
				break;
			case LED_2:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED2_GPIO_PORT, LED2_GPIO_BIT);
				break;
			case LED_3:
				Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED3_GPIO_PORT, LED3_GPIO_BIT);
				break;
			default: break;
		}
}
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */

/*==================[end of file]============================================*/

