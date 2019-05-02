//Ass-02-Q02.c


/*        $Id: Ass-02-Q02.c 1592 2019-02-05 14:38:48Z Peter $
 *  $Revision: 1592 $
 *      $Date: 2019-02-06 01:38:48 +1100 (Wed, 06 Feb 2019) $
 *    $Author: Peter $
 */

#include "Ass-02.h"

//
// REPLACE THE EXAMPLE CODE WITH YOUR CODE 
//

typedef struct{
	double x, y, width, height;
	char text;
} Button;




//static char *itemg[42] = {"0","1","2","3","4","5","6","7","8","9","AC","DEL",".","=","+","-","*","/","sqrt","pow(","ln(","sin(","cos(","tan(","(",")","exp(","abs(","graph","pi"};
static char *itemg[42] = {"graph","ln(",".","0","3","2","1","abs(","exp(","pow(","Pi","6","5","4","tan(","cos(","sin(","sqrt(","9","8","7","=",")","(","/","*","-","+","DEL","AC"};

void screen(void){
	grid.items = &itemg;
}

int draw(int item, int text_colour, int cell_colour) {

  int minWidthX = grid.Area[item][0];
  int maxWidthX = grid.Area[item][1];
  int minWidthY = grid.Area[item][2];
  int maxWidthY = grid.Area[item][3];

  int x = ((maxWidthX - minWidthX) / 2.0) + minWidthX;
  int y = ((maxWidthY - minWidthY) / 2.0) + minWidthY;

  BSP_LCD_SetFont(&Font12);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_DARKGRAY);
  BSP_LCD_DisplayStringAt(x, y,(uint8_t *)itemg[item], CENTER_MODE);

  return 0;
}

void Area(int first, int second, int value) {
  grid.Area[first][second] = value;
}


int drawSymbols() {

    for (int i = 0; i < 30; i++) {
        if (draw(i, LCD_COLOR_WHITE, LCD_COLOR_DARKGRAY) == 0) {
            Area(i, 4, i);
        }
        else {
            printf("ERROR");
        }
    }
    return 0;
}


void CalculatorInit(void){
	BSP_LCD_Init();
	BSP_LCD_DisplayOn();
	BSP_TP_Init();

	BSP_LCD_Clear(LCD_COLOR_DARKGRAY);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);


}

void drawGrid(void){
	int numVline = 7;
	int numHline = 5;

	int displayHeight = BSP_LCD_GetYSize();
	int displayWidth  = BSP_LCD_GetXSize();

	int cellWidth  = displayWidth / numVline;
	int cellHeight = displayHeight / numHline;

	uint16_t x = 0;
	uint16_t y = 0;
	uint16_t len   = 0;

	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

	y = cellHeight;

	len = numHline * cellHeight - cellHeight;


	for (int l = 0; l < numVline; l++) {
		if (l > 4) {
			y = 0;
			len   = numHline * cellHeight;
		}
		x = l * cellWidth;
		BSP_LCD_DrawVLine(x, y, len);
	}

	x = displayWidth;

	len = displayWidth;

	for (int l = 0; l < numHline; l++) {
		y = l * cellHeight;
		BSP_LCD_DrawHLine(0, y, len);
	    }

	int maxWidth = displayWidth;
	int maxHeight = displayHeight;
	int minWidth = maxWidth;
	int minHeight = maxHeight;
	int temp = 0;

	for(int i = 0; i < numHline; i++){
		maxHeight = minHeight;
		minHeight = minHeight - cellHeight;
		minWidth = displayWidth;
		for(int j = 0; j < numVline; j++){
			maxWidth = minWidth;
			minWidth = maxWidth - cellWidth;
			Area(temp, 0, minWidth);
			Area(temp, 1, maxWidth);
			Area(temp, 2, minHeight);
			Area(temp, 3, maxHeight);
			temp += 1;

		}
	}

}

typedef enum {
	Yes = 0,
	No = 1,
} TouchState;

static char* tempString;
static int init = 0;
static int count = 1;

void HandlePress(int x, int y)
{
	char *temp;
	for(int i = 0; i < 30; i++){

		if(x <= grid.Area[i][1] && x >= grid.Area[i][0] && y <= grid.Area[i][3] && y >= grid.Area[i][2]){
			//printf("Button %s pressed at: x: %d, y: %d \n", itemg[i],x ,y);

			int should_print = 1;

			if(strcmp(itemg[i], "DEL")==0){
				should_print = 0;

				BSP_LCD_DisplayStringAt(20, 20, "                            ", LEFT_MODE);
				init = 0;

				tempString[strlen(tempString)] = '\0';
			}
			else if(strcmp(itemg[i], "=")==0){
				should_print = 0;

				BSP_LCD_DisplayStringAt(20, 20, "                            ", LEFT_MODE);
				init = 0;

				// tokenise here to check if has an x terms
				TokenArray *token_array = tokenise_expression(tempString);
				// if there are x's. Don't calculate, and let the user know to press the graph button
				if(has_x_identifiers(token_array))
				{
					printf(CONSOLE_RED("This equation has x terms. To create a graph, press the graph button!\n"));
				}
				else
				{
					double result = EquationParserSTM(tempString);
					char res[20];
					snprintf(res, 20,  "%lf", result);
					BSP_LCD_DisplayStringAt(20, 20, res, LEFT_MODE);
				}

				// if crashing at this point. remove this line. should be fine though.
				free(token_array);
			}
			else if(strcmp(itemg[i], "AC")==0){
				should_print = 0;
				BSP_LCD_DisplayStringAt(20, 20, "                            ", LEFT_MODE);
				init = 0;
			}
			else if(strcmp(itemg[i], "graph") == 0) {
				int y_Points[SCREEN_WIDTH] = CalculateGraph(tempString);

				// These are the y points for the x's 0 to SCREEN_WIDTH.
				// SCREEN_WIDTH is a define just above the CalculateGraph function in Ass-02.h
			}

			if(should_print) {
				if(strlen(tempString) >= 28)
				{
					return;
				}
				temp = itemg[i];
				tempString = realloc(tempString, strlen(temp) + strlen(tempString) + 1);
				strcat(tempString, temp);
				BSP_LCD_DisplayStringAt(20, 20, tempString, LEFT_MODE);
				return;
			}
		}

	}
}

void CalculatorProcess(void){

	if(init == 0)
	{
		if(tempString != NULL)
		{
			free(tempString);
		}
		tempString = malloc(2);
		strcpy(tempString, "");
		init = 1;
	}

	while(count){
		HAL_Delay(200);
		drawGrid();
		drawSymbols();
		count = 0;
	}

	static int last_state = No;
	int cur_state = No;

	double accum = 0;
	int sensitivity = 50;
	for(int i = 0; i < sensitivity; i++)
	{
		int state_tmp = BSP_TP_GetDisplayPoint (&display);
		accum += (double)state_tmp;
	}
	accum /= sensitivity;

	cur_state = accum < 0.5 ? Yes : No;

	if(cur_state == No && last_state == Yes) last_state = No;
	else if(cur_state == Yes  && last_state == No)
	{
		last_state = Yes;
		HandlePress(display.x, display.y);
	}

}
