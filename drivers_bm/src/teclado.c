/* Copyright 2016, Leandro D. Medus
 * lmedus@bioingenieria.edu.ar
 * Faculty of Engineering
 * National University of Entre Ríos
 * Argentina
 *
 * All rights reserved.
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

/** \brief Bare Metal driver for a keyboard connected to the EDU-CIAA NXP board.
 **
 **
 **
 **/

/** \addtogroup EDU-CIAA_Course
 ** @{ */
/** \addtogroup Sources_LDM Leandro D. Medus Sources
 ** @{ */
/** \addtogroup Baremetal_App Bare Metal application source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *	LM			Leandro Medus
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160422 v0.4 Base version of the keyboard driver.
 */

/*==================[inclusions]=============================================*/
//#include "teclas.h"
#include "teclado.h"

/*==================[macros and definitions]=================================*/
#define N_ROW	4
#define N_COL	3


#define F0_MUX_GROUP 	4
#define F0_MUX_PIN 		0
#define F0_GPIO_PORT	2
#define F0_GPIO_PIN 	0

#define F1_MUX_GROUP 	4
#define F1_MUX_PIN 		1
#define F1_GPIO_PORT 	2
#define F1_GPIO_PIN 	1

#define F2_MUX_GROUP	4
#define F2_MUX_PIN		2
#define F2_GPIO_PORT	2
#define F2_GPIO_PIN		2

#define F3_MUX_GROUP	4
#define F3_MUX_PIN		3
#define F3_GPIO_PORT	2
#define F3_GPIO_PIN		3

#define C0_MUX_GROUP	1
#define C0_MUX_PIN		5
#define C0_GPIO_PORT	1
#define C0_GPIO_PIN		8

#define C1_MUX_GROUP	7
#define C1_MUX_PIN		4
#define C1_GPIO_PORT	3
#define C1_GPIO_PIN		12

#define C2_MUX_GROUP	7
#define C2_MUX_PIN		5
#define C2_GPIO_PORT	3
#define C2_GPIO_PIN		13

#define C3_MUX_GROUP	6
#define C3_MUX_PIN		12
#define C3_GPIO_PORT	2
#define C3_GPIO_PIN		8


#define OUTPUT_DIRECTION 	1
#define INPUT_DIRECTION 	0
#define TECLA_PRESIONADA 	1
#define SONIDO 	1
/*==================[internal data declaration]==============================*/
/** */
uint8_t layout_keys_row_port[N_ROW] = {F0_GPIO_PORT, F1_GPIO_PORT, F2_GPIO_PORT, F3_GPIO_PORT};
uint8_t layout_keys_row_pin[N_ROW] 	= {F0_GPIO_PIN, F1_GPIO_PIN, F2_GPIO_PIN, F3_GPIO_PIN};
uint8_t layout_keys_col_port[N_COL] = {C0_GPIO_PORT, C1_GPIO_PORT, C2_GPIO_PORT};
uint8_t layout_keys_col_pin[N_COL] 	= {C0_GPIO_PIN, C1_GPIO_PIN, C2_GPIO_PIN};


/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/** \brief Initialize method for the keyboard connected to the EDU-CIAA board */
void initGPIO_keyboard_EDUCIAA(void)
{
	/** \details
	 * This function initialize the seven GPIOs present in the EDU-CIAA board,
	 * to control the keyboard.
	 *
	 * \param none
	 * \return none
	 * */

	/* Configuración del GPIO*/
	Chip_GPIO_Init(LPC_GPIO_PORT);

	/* Mapeo de pines Pulsadores */
	Chip_SCU_PinMux(F0_MUX_GROUP,F0_MUX_PIN,0,FUNC0);
	Chip_SCU_PinMux(F1_MUX_GROUP,F1_MUX_PIN,0,FUNC0);
	Chip_SCU_PinMux(F2_MUX_GROUP,F2_MUX_PIN,0,FUNC0);
	Chip_SCU_PinMux(F3_MUX_GROUP,F3_MUX_PIN,0,FUNC0);

	Chip_SCU_PinMux(C0_MUX_GROUP,C0_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux(C1_MUX_GROUP,C1_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux(C2_MUX_GROUP,C2_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux(C3_MUX_GROUP,C3_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);


	/* Configuración como entrada para los pulsadores */
	Chip_GPIO_SetDir(LPC_GPIO_PORT, F0_GPIO_PORT,1<<F0_GPIO_PIN,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, F1_GPIO_PORT,1<<F1_GPIO_PIN,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, F2_GPIO_PORT,1<<F2_GPIO_PIN,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, F3_GPIO_PORT,1<<F3_GPIO_PIN,OUTPUT_DIRECTION);

	Chip_GPIO_SetDir(LPC_GPIO_PORT, C0_GPIO_PORT,1<<C0_GPIO_PIN,INPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, C1_GPIO_PORT,1<<C1_GPIO_PIN,INPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, C2_GPIO_PORT,1<<C2_GPIO_PIN,INPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, C3_GPIO_PORT,1<<C3_GPIO_PIN,INPUT_DIRECTION);


	//return TRUE;
}

/** \brief Scan method to search a specific key pressed in the keyboard */
uint8_t scanKeyboardRusticECB(void)
{
	/** \details
	 * Scan method to search a specific key pressed in the keyboard.
	 *
	 * \param none
	 *
	 * \return uint8_t result : if 1, the specific key searched is pressed.
	 * */

	/** Value of the key pressed or 0 if it does not find anything */
	uint8_t result = 0;

	//Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,F0_GPIO_PORT,F0_GPIO_PIN);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,F0_GPIO_PORT,F0_GPIO_PIN);

	//Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,F1_GPIO_PORT,F1_GPIO_PIN);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,F1_GPIO_PORT,F1_GPIO_PIN);

	//Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,F2_GPIO_PORT,F2_GPIO_PIN);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,F2_GPIO_PORT,F2_GPIO_PIN);

	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,F3_GPIO_PORT,F3_GPIO_PIN);
	//Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,F3_GPIO_PORT,F3_GPIO_PIN);

	if (!(	//Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,C0_GPIO_PORT,C0_GPIO_PIN)
			//&
			//Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,C1_GPIO_PORT,C1_GPIO_PIN)
			//&
			Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,C2_GPIO_PORT,C2_GPIO_PIN)
			) )
	{
		result = 1;

	}
	return result;
}

/** \brief Scan method to determine if a specific key is pressed in the keyboard */
uint8_t getKeyStatusECB(uint8_t key)
{
	/** \details
	 * Scan method to determine if a specific key pressed in the keyboard.
	 * \param key: number of the key to be tested. Value goes from 1 to 12.
	 * \return uint8_t result : if 1, the specific key searched is pressed.
	 * */

	/** Scan Keyboard Result */
	uint16_t scanResult = 0;
	/** Value of the key pressed or 0 if it does not find anything */
	uint8_t result = 0;

	scanResult = scanKeyboarECB();

	if (scanResult & (1<< key))
		result = 1;

	return result;
}


/** \brief Scan method to search if one or more keys are pressed in the keyboard */
uint16_t scanKeyboarECB(void)
{
	/** \details
	 *	Scan method to search if one or more keys are pressed in the keyboard, it uses
	 *	generic parameters to achieve the goal.
	 *
	 * \param none
	 *
	 * \return uint16_t result : a 16 bit word representing in each position, the status
	 * of a key in the keyboard. Value = 1: key pressed. It is important to emphasize that
	 * key names goes from 1 to 12.
	 * */

	/** Value of the key pressed or 0 if it does not find anything */
	uint16_t result = 0;
	/** Counter for rows */
	uint8_t row;
	/** Counter for columns */
	uint8_t col;

	/** -------- basic scan method ---------- */

	for(row = 0; row < N_ROW; row++)
	{
		if(row == 0) Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,F0_GPIO_PORT,F0_GPIO_PIN);
		else Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,F0_GPIO_PORT,F0_GPIO_PIN);

		if(row == 1) Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,F1_GPIO_PORT,F1_GPIO_PIN);
		else Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,F1_GPIO_PORT,F1_GPIO_PIN);

		if(row == 2) Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,F2_GPIO_PORT,F2_GPIO_PIN);
		else Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,F2_GPIO_PORT,F2_GPIO_PIN);

		if(row == 3) Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,F3_GPIO_PORT,F3_GPIO_PIN);
		else Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,F3_GPIO_PORT,F3_GPIO_PIN);

		if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,C0_GPIO_PORT,C0_GPIO_PIN))
				result |= 1 << (N_ROW * row + 1);

		if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,C1_GPIO_PORT,C1_GPIO_PIN))
				result |= 1 << (N_ROW * row + 2);

		if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,C2_GPIO_PORT,C2_GPIO_PIN))
				result |= 1 << (N_ROW * row + 3);

		if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,C3_GPIO_PORT,C3_GPIO_PIN))
						result |= 1 << (N_ROW * row + 4);
	}

	return result;
}

void Delay (uint8_t debounce)
{
uint32_t m;
//debounce = demora del delay
for (m=0;m<debounce;m++){}
}


uint8_t ScanSwitchPlus(uint8_t debounce, uint8_t beep)
{
uint8_t tecla;
if (scanKeyboarECB()== TECLA_PRESIONADA)
{
	tecla = scanKeyboarECB();
	if(beep == SONIDO)
		update_DAC_value(1);
	Delay(debounce);
		update_DAC_value(1);
	if(tecla ==scanKeyboarECB())
	{
		return tecla;
	}
}
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/


/*
 * Para los pulsadores
 * Chip_GPIO_ReadValue()
 * Chip_GPIO_ReadPortBit()
 * */
