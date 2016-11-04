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
 ** This is a mini example of the CIAA Firmware.
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
 */
/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */
/*==================[inclusions]=============================================*/
#include "08_ProyectoFinal.h"       /* <= own header */
#include "stdint.h"
/*==================[macros and definitions]=================================*/
/*==================[internal data declaration]==============================*/
/*==================[internal functions declaration]=========================*/
/*==================[internal data definition]===============================*/
/*==================[external data definition]===============================*/
/*==================[internal functions definition]==========================*/
/*==================[external functions definition]==========================*/
/** \brief Main function
 * This is the main entry point of the software.
 * \returns 0
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
#define CONST_TIMER 3000000
#define CANT_TECLAS 16
const 	uint16_t senial[] = {512,544,576,608,639,670,700,730,759,786,813,838,862,885,907,926,944,961,975,988,999,1008,1015,1020,1023,1024,1023,1020,1015,1008,999,988,975,961,944,926,907,885,862,838,813,786,759,730,700,670,639,608,576,544,512,480,448,416,385,354,324,294,265,238,211,186,162,139,117,98,80,63,49,36,25,16,9,4,1,0,1,4,9,16,25,36,49,63,80,98,117,139,162,186,211,238,265,294,324,354,385,416,448,480};
float amplitud=1;
uint8_t Frecuencia=100;
uint8_t ContFrec=10;

void Generar_sonido(void)
{
static uint8_t i=0;
uint16_t dato;
ContFrec--;
if (ContFrec==0)
	{
	ContFrec=Frecuencia;
	dato=amplitud*senial[i];
	update_DAC_value(dato);
	i++;
	if(i==100)
		{
		i=0;
		EncenderLed(LED_R);
	  	}
	}
}

void Delay2 (void)
{
uint32_t m;
for (m=0;m<CONST_TIMER;m++){}
}

void armar_clave(char tecla, char *clave)
{
	static uint8_t k=0,i;
if (tecla==42)
	{
	clave[k]='\0';
	k=0;
	}
else
	{
	clave[k]=tecla;
	k++;
	}
}

uint8_t verificar_clave(char *clave)
{
	char *numero;
	uint8_t i=0, clavenumerica;
	while(clave[i+1]!='\0')
		{
		//for (i=0; i<strlen(clave);i++)
		numero[i]=clave[i+1];
		i++;
		}
	clavenumerica=Itoa(numero,10);
	for (i=0;i<100;i++)
		{
		if (clavenumerica==senial[i])
			sendString_UART_USB_EDUCIAA("EXITOOOO!!!\n\r",25);
		}
}

void enciende_luces(char valor)
{
	switch (valor)
	{
		case 'A':
    			EncenderLed(LED_1);
    			ApagarLed(LED_2);
    			ApagarLed(LED_3);
    			break;
		case 'B':
	    		EncenderLed(LED_2);
	    		ApagarLed(LED_1);
	    		ApagarLed(LED_3);
	    		break;
		case 'C':
	    		EncenderLed(LED_3);
	    		ApagarLed(LED_1);
	    		ApagarLed(LED_2);
	    		break;
		default:
				EncenderLed(LED_1);
				EncenderLed(LED_3);
				EncenderLed(LED_2);
				break;
    }

}
int main(void)
{
	uint8_t j=0;
	char teclado4x4[16][2]={{'1','\0'},{'2','\0'},{'3','\0'},{'A','\0'},{'4','\0'},{'5','\0'},{'6','\0'},{'B','\0'},{'7','\0'},{'8','\0'},{'9','\0'},{'C','\0'},{'*','\0'},{'0','\0'},{'#','\0'},{'D','\0'}};
	char *clave;
	/* inicializaciones */
	InitLeds();
	initGPIO_keyboard_EDUCIAA();
	init_UART_FTDI_EDUCIAA();
	init_DAC_EDUCIAA();
	sendString_UART_USB_EDUCIAA("PROBANDO\n\r",10);
   /*acá va mi programa principal */
   while (j<=CANT_TECLAS)
    {
	   ApagarLed(LED_R);
    	if(getKeyStatusECB(j)==1)
    		{
    		for(k=0;k<275;k++)
    			Generar_sonido();
    		armar_clave(teclado4x4[j-1][0],clave);
    		Delay2();
    		if(teclado4x4[j-1][0]==42)
    			{
    			enciende_luces(clave[0]);
    			sendString_UART_USB_EDUCIAA(clave,25);
    			sendString_UART_USB_EDUCIAA("\n\r",2);
    			verificar_clave(clave);
    			clave[0]='\0';
    			}
    		}
    	if(j==CANT_TECLAS)
    		j=0;
    	j++;
    };
	return 0;
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
