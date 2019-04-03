/*        $Id: Ass-02-Lib.c 1592 2019-02-05 14:38:48Z Peter $
 *  $Revision: 1592 $
 *      $Date: 2019-02-06 01:38:48 +1100 (Wed, 06 Feb 2019) $
 *    $Author: Peter $
 */

#include "Ass-02.h"

//
// PLACE YOUR COMMON CODE HERE 
//

/*int string_parser(char *inp, char **array_of_words_p[]) {
  // copy string to a local variable for manipulation
    char* str = malloc(sizeof(inp));
    strcpy(str, inp);

    // start off with just a pointer
    char** array_of_words = malloc(0);

    // delimiter is just a single space
    char* delim = " ";

    // first call to strtok
    char* tok = strtok(str, delim);

    int string_count = 0;

    // if tok isn't NULL, we have a string
    while(tok != 0)
    {
      string_count++;
      // reallocate memory to allow for another char* to be added.
      array_of_words = realloc(array_of_words, sizeof(char*) * string_count);

      // allocate tok in new_string on the heap
      char* new_string = malloc(sizeof(strlen(tok)));
      // copy the string to the new allocating
      strcpy(new_string, tok);
      // add new_string to the array of words
      array_of_words[string_count-1] = new_string;

      tok = strtok(NULL, delim);
    }

    // assign input pointer
    *array_of_words_p = array_of_words;

    return string_count;
}*/

int string_parser(char *inp, char **array_of_words_p[])
{

   int string_length = 0, letterCount = 0, wordCount = 0;
   for (int i = 0; inp[i] != '\0'; i++){
     string_length++;
   }

   char *wordArray = (char*)malloc(sizeof(char) * string_length);
   int elements = 0;
   for (int i = 0; inp[i] != '\0'; i++){
     if (inp[i] != 8){
       wordArray[elements] = inp[i];
       elements++;
     }
     else if (elements > 0){
       elements--;
     }

   }
   wordArray[elements] = '\0';



   for (int i = 0; inp[i] != '\0'; i++){
     if ((i > 0 && inp[i] == ' ' && inp[i-1] != ' ')
           || (inp[i+1] == '\0' && inp[i] != ' ')){
       wordCount++;
     }
   }

   *array_of_words_p = (char**)malloc(sizeof(char*) * wordCount);
   wordCount = 0;

   for (int i = 0; wordArray[i] != '\0'; i++){
     if ((i > 0 && wordArray[i] == ' ' && wordArray[i-1] != ' ') || (wordArray[i+1] == '\0' && wordArray[i] != ' ')){
       if (wordArray[i+1] == '\0'){
         letterCount++;
       }
       (*array_of_words_p)[wordCount] = (char*)malloc(sizeof(char)*(letterCount+1));

       letterCount = 0;
       wordCount++;
     }
     if (i > 0 && wordArray[i] == ' ' && wordArray[i-1] == ' '){
       continue;
     }
     else {
       letterCount++;
     }
   }

   wordCount = 0;
   letterCount = 0;


   for (int i = 0; wordArray[i] != '\0'; i++){
     if ((i > 0 && wordArray[i] == ' ' && wordArray[i-1] != ' ') || (wordArray[i+1] == '\0' && wordArray[i] != ' ')){
       if (wordArray[i+1] == '\0'){
         (*array_of_words_p)[wordCount][letterCount] = wordArray[i];
         letterCount++;
       }
       (*array_of_words_p)[wordCount][letterCount] = '\0';

       wordCount++;
       letterCount = 0;
     }
     else if (wordArray[i] == ' '){
       continue;
     }
     else{

       (*array_of_words_p)[wordCount][letterCount] = wordArray[i];
       letterCount++;
     }
   }
   free(wordArray);

   return wordCount;
 printf("This code has been commented out, explained at the top of the source code!");
 return 0;
}



// STEPIEN: Added two touch panel functions to make the interface more
//          consistent with the LCD BSP.

#ifdef STM32F407xx
uint8_t
BSP_TP_Init (void)
{
  // Initialise the interface and calibrate
  TP_Init (); // This is an empty function since done by STM32CubeMX
  TouchPanel_Calibrate ();

  return 0;
}

uint8_t
BSP_TP_GetDisplayPoint (Coordinate *pDisplay)
{
  Coordinate *pScreen;

  pScreen = Read_Ads7846 ();
  if (pScreen == NULL)
  {
    return 1; // Error reading the touch panel
  }
  if (getDisplayPoint (pDisplay, pScreen, &matrix) == DISABLE)
  {
    return 1; // Error in LCD
  }
  return 0;
}
#endif
