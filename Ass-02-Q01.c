/*        $Id: Ass-02-Q01.c 1592 2019-02-05 14:38:48Z Peter $
 *  $Revision: 1592 $
 *      $Date: 2019-02-06 01:38:48 +1100 (Wed, 06 Feb 2019) $
 *    $Author: Peter $
 */

#include "Ass-02.h"
#ifdef STM32F407xx
#include "usart.h"
#endif

//
// REPLACE THE EXAMPLE CODE WITH YOUR CODE
//

/*
 * to add
 * sin
 * cos
 * tan
 * sinh
 * cosh
 * tanh
 * ln
 * log
 * exp
 * pow
 * ceil
 * floor
 * abs
 * mod
 *
 */

static int debug_enabled = 0;

double add(char **values, int count)
{
	double result = 0.0;

	for(int i = 0; i < count; i++)
	{
		double val;
		int error = sscanf(values[i], "%lf", &val);
		if(error != 1)
		{
			printf("Error parsing %s. Not a valid numeric input\n", values[i]);
			return 0.0;
		}
		result += val;
	}

	return result;
}

double sub(char **values)
{
	double v1, v2;
	int error = sscanf(values[0], "%lf", &v1);
	if(error != 1)
	{
		printf("Error parsing %s. Not a valid numeric input\n", values[0]);
		return 0.0;
	}
	error = sscanf(values[1], "%lf", &v2);
	if(error != 1)
	{
		printf("Error parsing %s. Not a valid numeric input\n", values[1]);
		return 0.0;
	}

	return v1 - v2;
}

double mul(char **values, int count)
{
	double result = 1.0;

	for(int i = 0; i < count; i++)
	{
		double val;
		int error = sscanf(values[i], "%lf", &val);
		if(error != 1)
		{
			printf("Error parsing %s. Not a valid numeric input\n", values[i]);
			return 0.0;
		}
		result *= val;
	}

	return result;
}

double divi(char **values)
{
	double v1, v2;
	int error = sscanf(values[0], "%lf", &v1);
	if(error != 1)
	{
		printf("Error parsing %s. Not a valid numeric input\n", values[0]);
		return 0.0;
	}
	error = sscanf(values[1], "%lf", &v2);
	if(error != 1)
	{
		printf("Error parsing %s. Not a valid numeric input\n", values[1]);
		return 0.0;
	}

	return v1 / v2;
}

double square_root(char* val)
{
	double v;
	int error = sscanf(val, "%lf", &v);
	if(error != 1)
	{
		printf("Error parsing %s. Not a valid numeric input\n", val);
		return 0.0;
	}

	return sqrt(v);
}

void print_help()
{
	printf("NOT IMPLEMENTED\n");
}

void CommandLineParserProcess(void)
{
	char str[128];
	fflush(stdin);
	scanf("%[^\n]s", str);

	char **words;
	int word_count = string_parser(str, &words);

	if(strcmp(words[0], "add") == 0)
	{
		printf("Result : %lf\n", add(&words[1], word_count-1));
	}
	else if(strcmp(words[0], "sub") == 0)
	{
		printf("Result : %lf\n", sub(&words[1]));
	}
	else if(strcmp(words[0], "mul") == 0)
	{
		printf("Result : %lf\n", mul(&words[1], word_count-1));
	}
	else if(strcmp(words[0], "div") == 0)
	{
		printf("Result : %lf\n", divi(&words[1]));
	}
	else if(strcmp(words[0], "sqrt") == 0)
	{
		if(word_count > 2)
		{
			printf("More than the 1 required arguments were given. The rest will be ignored");
		}

		printf("Result : %lf\n", square_root(words[1]));
	}
	else if(strcmp(words[0], "debug") == 0)
	{
		if(word_count == 1)
		{
			char* debug_result = debug_enabled == 0 ? "false" : "true";
			printf("Debug enabled : %s", debug_result);
		}
		else if(strcmp(words[1], "on") == 0)
		{
			debug_enabled = 1;
			printf("Debug messages will be displayed.\n");
		}
		else if(strcmp(words[1], "off") == 0)
		{
			debug_enabled = 0;
			printf("Debug messages will not be displayed.\n");
		}
		else
		{
			printf("Unknown argument '%s' given.\n", words[1]);
		}
	}
	else if(strcmp(words[0], "help") == 0)
	{
		if(word_count == 1)
		{
			print_help();
		}
		else if(strcmp(words[1], "add") == 0)
		{
			printf("add <num 1> .. <num N> : Prints the result of the sum of all given numbers.\n");
		}
		else if(strcmp(words[1], "sub") == 0)
		{
			printf("sub <num 1> <num 2> : Prints the result of of num1 - num2.\n");
		}
		else if(strcmp(words[1], "mul") == 0)
		{
			printf("mul <num 1> .. <num N> : Prints the result of the product of all given numbers.\n");
		}
		else if(strcmp(words[1], "div") == 0)
		{
			printf("div <num 1> <num 2> : Prints the result of of num1 / num2.\n");
		}
		else if(strcmp(words[1], "help") == 0)
		{
			printf("help [command] : Prints help information for command.\n");
		}
		else if(strcmp(words[1], "debug") == 0)
		{
			printf("debug on/off : Enables or Disables debugging messages in terminal.\n");
		}
		else if(strcmp(words[1], "exit") == 0)
		{
			printf("exit : Exits the program.\n");
		}
		else
		{
			printf("Unknown command '%s'\n", words[1]);
		}
	}
	else if(strcmp(words[0], "exit") == 0)
	{
		exit(0);
	}
	else
	{
		printf("Unknown command. Type 'Help' for instructions on how to use this program.\n");
	}
}

void
CommandLineParserInit (void)
{
  // Print welcome message
  // printf("\014");
  printf ("\n");
  printf ("%s\n", ASS_STRING);
  printf ("%s\n", VER_STRING);
  printf ("Command Line Parser Example\n");
}

// Check for input and echo back
void
CommandLineParserProcess1 (void)
{
#ifdef STM32F407xx
  uint8_t c;
  // STEPIEN: Can't use getchar() here since need to continue if no character to read
  if (HAL_UART_Receive (&huart2, &c, 1, 0x0) == HAL_OK)
  {
    printf ("\nSERIAL: Got ");
    if ((c < 32) | (c > 126))
    {
      printf ("ASCII %d\n", c);
    }
    else
    {
      printf ("character '%c'\n", c);
    }
    HAL_GPIO_TogglePin (GPIOD, LD4_Pin); // Toggle LED4

    // STEPIEN: The following is some test code that can be removed
    //
    /*{
      int c1, c2;
      char si[] = "1234";
      int i;
      char sf1[] = "Testing";
      char sf2[] = "1.234";
      float f1 = 1.11;
      float f2 = 2.22;

      sscanf (si, "%d", &i);
      printf ("TEST: Input int string   : '%s'\n", si);
      printf ("TEST: Input int value    : %d\n", i);
      c1 = sscanf (sf1, "%f", &f1);
      c2 = sscanf (sf2, "%f", &f2);
      printf ("TEST: Input float string : '%s'\n", sf1);
      printf ("TEST: Input float value  : %f\n", f1);
      printf ("TEST: sscanf() returns   : %d\n", c1);
      printf ("TEST: Input float string : '%s'\n", sf2);
      printf ("TEST: Input float value  : %f\n", f2);
      printf ("TEST: sscanf() returns   : %d\n", c2);
    }*/
  }
#else
  int c;

  c = getchar();
  if (c<0)
  {
    printf("INFO: Exiting program.\n");
    exit(0);
  }
  printf("SERIAL: Got ");
  if ((c<32) | (c>126))
  {
    printf("ASCII %d\n", c);
  }
  else
  {
    printf("character '%c'\n", c);
  }
#endif
}
