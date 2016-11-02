/* Copyright 2016, XXXX
 *
 *  * All rights reserved.
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

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
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

#include "03_blinking.h"       /* <= own header */
#include "stdint.h"


/*==================[macros and definitions]=================================*/
#define CONST_TIMER 300000

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void Corre_Izquierda(uint8_t *led_prendido)
{
			switch (*led_prendido)
				{
				case LED_3:
					*led_prendido=LED_2;
					break;
				case LED_2:
					*led_prendido=LED_1;
					break;
				case LED_1:
					*led_prendido=LED_R;
					break;
				case LED_R:
					*led_prendido=LED_G;
					break;
				case LED_G:
					*led_prendido=LED_B;
					break;
				case LED_B:
					*led_prendido=LED_3;
					break;
				default: break;
				}
}
uint8_t Corre_Derecha(uint8_t led_prendido)
{
			switch (led_prendido)
				{
				case LED_3:
					return(LED_B);
				case LED_B:
					return(LED_G);
				case LED_G:
					return(LED_R);
				case LED_R:
					return(LED_1);
				case LED_1:
					return(LED_2);
				case LED_2:
					return(LED_3);
				default: break;
				}
}
/*==================[external functions definition]==========================*/
void Delay (uint8_t c){
uint64_t i;
for (i=CONST_TIMER * c;i!=0;i--);
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



int main(void)
{
	uint8_t led_prendido=LED_3, tecla, frecuencia=1;
   /* inicializaciones */
	InitLeds();
	Init_Switches();
	while(1)
	{
		do
		{
		ToggleLed(led_prendido);
		Delay(frecuencia);
		tecla=Read_Switches();
		}while(tecla==0);
		ApagarLed(led_prendido);
	switch(tecla)
		{
		case TEC3:
			Corre_Izquierda(&led_prendido);
			break;
		case TEC4:
			led_prendido=Corre_Derecha(led_prendido);
			break;
		case TEC2:
			frecuencia++;
			break;
		case TEC1:
			if (frecuencia>1)
				frecuencia--;
			else
				frecuencia=1;
			break;
		default: break;
		}
	ToggleLed(led_prendido);
	Delay(frecuencia);
	};
    
	return 0;


}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

