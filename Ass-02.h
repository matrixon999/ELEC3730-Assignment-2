/*        $Id: Ass-02.h 1592 2019-02-05 14:38:48Z Peter $
 *  $Revision: 1592 $
 *      $Date: 2019-02-06 01:38:48 +1100 (Wed, 06 Feb 2019) $
 *    $Author: Peter $
 */

// Assignment 2 include file

#ifndef ASS_02_H_
#define ASS_02_H_

// Standard includes
#ifdef STM32F407xx
#include "stm32f4xx_hal.h"
#include "openx07v_c_lcd.h"
#include "touch_panel.h"
#include "main.h"
#else
#include <windows.h>
#endif
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

// Assignment and version strings
#define ASS_STRING "ELEC3730-2019t1 Assignment 2"
#define VER_STRING "Ver: 01 $Rev: 1592 $"

// Assignment main
extern void
Ass_02_Main (void);

//
// REPLACE THE EXAMPLE CODE WITH YOUR CODE 
//

extern int string_parser(char *inp, char **array_of_words_p[]);

// Question 1
extern void
CommandLineParserInit (void);
extern void
CommandLineParserProcess (void);

// Question 2
extern void
CalculatorInit (void);
extern void
CalculatorProcess (void);

// Library functions
#ifdef STM32F407xx
extern uint8_t
BSP_TP_Init (void);
extern uint8_t
BSP_TP_GetDisplayPoint (Coordinate *pDisplay);
#endif

#endif /* ASS_02_H_ */
