/*        $Id: Ass-02-Q02.c 1592 2019-02-05 14:38:48Z Peter $
 *  $Revision: 1592 $
 *      $Date: 2019-02-06 01:38:48 +1100 (Wed, 06 Feb 2019) $
 *    $Author: Peter $
 */

#include "Ass-02.h"

//
// REPLACE THE EXAMPLE CODE WITH YOUR CODE 
//

typedef struct
{
	double x, y, width, height;
	char text;
} Button;

void DrawButton(Button btn)
{
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(btn.x, btn.y, btn.width, btn.height);

	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

	// top line
	BSP_LCD_DrawHLine(btn.x, btn.y, btn.width);
	// bottom line
	BSP_LCD_DrawHLine(btn.x, btn.y + btn.height, btn.width);
	// left line
	BSP_LCD_DrawVLine(btn.x, btn.y, btn.height);
	// right line
	BSP_LCD_DrawVLine(btn.x + btn.width, btn.y, btn.height);

	BSP_LCD_SetFont (&Font24);
	BSP_LCD_DisplayChar(btn.x - (Font24.Width / 2) + (btn.width / 2), btn.y - (Font24.Height / 2) + (btn.height / 2), btn.text);
}

void DrawTextScreen()
{
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(0, 0, , btn.height);
}

void CalculatorInit(void)
{
	BSP_LCD_Init();
	BSP_LCD_DisplayOn();
	BSP_TP_Init();

	BSP_LCD_Clear(LCD_COLOR_DARKGRAY);

	/*Button btn = { 10.0, 10.0, 100.0, 75.0, '+' };
	DrawButton(btn);*/

	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			Button btn_tmp = { 50 * x, 50 * y, 49, 49, (char)('a' + x + y) };
			DrawButton(btn_tmp);
		}
	}
}

void
CalculatorInit2 (void)
{
  // STEPIEN: Assume horizontal display

  // Initialize and turn on LCD and calibrate the touch panel
  BSP_LCD_Init ();
  BSP_LCD_DisplayOn ();
  BSP_TP_Init ();

  // Display welcome message
  BSP_LCD_Clear (LCD_COLOR_WHITE);
  BSP_LCD_SetFont (&Font12);
  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
  BSP_LCD_DisplayStringAtLine (0, (uint8_t*) ASS_STRING);
  BSP_LCD_DisplayStringAtLine (1, (uint8_t*) VER_STRING);
  BSP_LCD_DisplayStringAtLine (2, (uint8_t*) "Calculator Example");

  // Create colour choices
  BSP_LCD_SetTextColor (LCD_COLOR_RED);
  BSP_LCD_FillRect (5, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_BLUE);
  BSP_LCD_FillRect (40, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_GREEN);
  BSP_LCD_FillRect (75, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
  BSP_LCD_FillRect (110, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_MAGENTA);
  BSP_LCD_FillRect (145, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_ORANGE);
  BSP_LCD_FillRect (180, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_CYAN);
  BSP_LCD_FillRect (215, 200, 30, 30);
  BSP_LCD_SetTextColor (LCD_COLOR_YELLOW);
  BSP_LCD_FillRect (250, 200, 30, 30);

  BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
  BSP_LCD_SetFont (&Font24);
  BSP_LCD_DisplayChar (290, 205, 'C');
  BSP_LCD_DrawHLine (0, 196, 320);

  BSP_LCD_DrawVLine (1, 198, 35);
  BSP_LCD_DrawVLine (37, 198, 35);
  BSP_LCD_DrawVLine (72, 198, 35);
  BSP_LCD_DrawVLine (107, 198, 35);
  BSP_LCD_DrawVLine (142, 198, 35);

  BSP_LCD_DrawVLine (177, 198, 35);
  BSP_LCD_DrawVLine (212, 198, 35);
  BSP_LCD_DrawVLine (247, 198, 35);
  BSP_LCD_DrawVLine (282, 198, 35);
  BSP_LCD_DrawVLine (317, 198, 35);

  BSP_LCD_DrawHLine (1, 232, 320);
}

typedef enum {
	Yes = 0,
	No = 1,
} TouchState;

void HandlePress(int x, int y)
{

}

void CalculatorProcess(void)
{
	// keep track of current and last state
	static int last_state = No;
	int cur_state = No;

	// get touch value 'sensitivity' times
	// average the values
	// this accounts for the bounce in the touch response
	double accum = 0;
	int sensitivity = 50;
	for(int i = 0; i < sensitivity; i++)
	{
		int state_tmp = BSP_TP_GetDisplayPoint (&display);
		accum += (double)state_tmp;
	}
	accum /= sensitivity;

	// if it was yes more often, then yes, else no
	cur_state = accum < 0.5 ? Yes : No;

	if(cur_state == No && last_state == Yes) last_state = No;
	else if(cur_state == Yes  && last_state == No)
	{
		last_state = Yes;
		printf("Press\n");
		//handle a press

		HandlePress(display.x, display.y);
	}
}

void
CalculatorProcess2 (void)
{
  // STEPIEN: Assume horizontal display

  uint16_t linenum = 0;

  if (BSP_TP_GetDisplayPoint (&display) == 0)
  {
    if (((display.y < 190) && (display.y >= 38)))
    {
      if ((display.x >= 318) || (display.x < 2))
      {
      }
      else
      {
        BSP_LCD_FillCircle (display.x, display.y, 2);
        printf ("TOUCH:  Got (%3d,%3d)\n", display.x, display.y);
      }
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 180)
        && (display.x <= 210))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_ORANGE);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 215)
        && (display.x <= 245))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_CYAN);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 250)
        && (display.x <= 280))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_YELLOW);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 5)
        && (display.x <= 35))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_RED);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 40)
        && (display.x <= 70))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_BLUE);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 75)
        && (display.x <= 105))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_GREEN);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 110)
        && (display.x <= 140))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 145)
        && (display.x <= 175))
    {
      BSP_LCD_SetTextColor (LCD_COLOR_MAGENTA);
    }
    else if ((display.y <= 230) && (display.y >= 190) && (display.x >= 285)
        && (display.x <= 315))
    {
      BSP_LCD_SetFont (&Font12);
      for (linenum = 3; linenum < 16; linenum++)
      {
        BSP_LCD_ClearStringLine (linenum);
      }
    }
    else
    {
    }
  }
}
