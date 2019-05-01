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

// These are defines for changing the colours of the output text
#define CONSOLE_RED(str)     "\x1b[31m" str "\x1b[0m"
#define CONSOLE_GREEN(str)   "\x1b[32m" str "\x1b[0m"
#define CONSOLE_YELLOW(str)  "\x1b[33m" str "\x1b[0m"
#define CONSOLE_BLUE(str)    "\x1b[34m" str "\x1b[0m"
#define CONSOLE_MAGENTA(str) "\x1b[35m" str "\x1b[0m"
#define CONSOLE_CYAN(str)    "\x1b[36m" str "\x1b[0m"
#define CONSOLE_RESET   "\x1b[0m"

// static variable to keep track of debug status even outside of looping
static int debug_enabled = 0;
static int equation_mode = 0;

// function takes string of numbers and adds them
double add(uint8_t num_args, char **args)
{
	double result = 0.0;

	if(debug_enabled) printf(CONSOLE_BLUE("Adding "));

	// loops over each 'word'
	for(int i = 0; i < num_args; i++)
	{
		// tries to parse 'word' as number
		double val;
		int error = sscanf(args[i], "%lf", &val);
		if(error != 1)
		{
			printf(CONSOLE_RED("\nError parsing %s. Not a valid numeric input\n"), args[i]);
			return 0.0;
		}
		if(debug_enabled) printf(CONSOLE_BLUE("%lf "), val);
		// adds it to running result
		result += val;
	}

	if(debug_enabled) printf(CONSOLE_BLUE("\n"));

	// returns result
	return result;
}

// function takes string of numbers, but only substracts the seconds from the first
double sub(uint8_t num_args, char **args)
{
	if(num_args > 2)
	{
		printf(CONSOLE_YELLOW("More than 2 arguments given, ignoring all but the first 2.\n"));
	}

	double v1, v2;
	int error = sscanf(args[0], "%lf", &v1);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[0]);
		return 0.0;
	}
	error = sscanf(args[1], "%lf", &v2);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[1]);
		return 0.0;
	}

	if(debug_enabled) printf(CONSOLE_BLUE("Subtracting %lf from %lf\n"), v2, v1);

	return v1 - v2;
}

// takes string of numbers and multiplies them together
double mul(uint8_t num_args, char **args)
{
	double result = 1.0;

	for(int i = 0; i < num_args; i++)
	{
		double val;
		int error = sscanf(args[i], "%lf", &val);
		if(error != 1)
		{
			printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[i]);
			return 0.0;
		}
		result *= val;
	}

	return result;
}

// function takes string of numbers, but only divides the first by the second
double divi(uint8_t num_args, char **args)
{
	if(num_args > 2)
	{
		printf(CONSOLE_YELLOW("More than 2 arguments given, ignoring all but the first 2.\n"));
	}

	double v1, v2;
	int error = sscanf(args[0], "%lf", &v1);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[0]);
		return 0.0;
	}
	error = sscanf(args[1], "%lf", &v2);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[1]);
		return 0.0;
	}

	if(debug_enabled) printf(CONSOLE_BLUE("Dividing %lf by %lf\n"), v1, v2);

	return v1 / v2;
}

// takes string of numbers, returns square root of first
double square_root(uint8_t num_args, char **args)
{
	if(num_args > 1)
	{
		printf(CONSOLE_YELLOW("More than 1 argument given, ignoring all but the first.\n"));
	}
	double v;
	int error = sscanf(args[0], "%lf", &v);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[0]);
		return 0.0;
	}

	if(debug_enabled) printf(CONSOLE_BLUE("Square root of %lf\n"), v);

	return sqrt(v);
}

double absval(uint8_t num_args, char **args)
{
	if(num_args > 1)
	{
		printf(CONSOLE_YELLOW("More than 1 argument given, ignoring all but the first.\n"));
	}

	double v;
	int error = sscanf(args[0], "%lf", &v);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[0]);
		return 0.0;
	}

	if(debug_enabled) printf(CONSOLE_BLUE("Absolute value of %lf\n"), v);

	return fabs(v);
}


double sinval(uint8_t num_args, char **args)
{
	if(num_args > 1)
	{
		printf(CONSOLE_YELLOW("More than 1 argument given, ignoring all but the first.\n"));
	}

	double v;
	int error = sscanf(args[0], "%lf", &v);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[0]);
		return 0.0;
	}

	if(debug_enabled) printf(CONSOLE_BLUE("Sin of %lf\n"), v);

	return sin(v);
}

double cosval(uint8_t num_args, char **args)
{
	if(num_args > 1)
	{
		printf(CONSOLE_YELLOW("More than 1 argument given, ignoring all but the first.\n"));
	}

	double v;
	int error = sscanf(args[0], "%lf", &v);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[0]);
		return 0.0;
	}

	if(debug_enabled) printf(CONSOLE_BLUE("Cos of %lf\n"), v);

	return cos(v);
}

double tanval(uint8_t num_args, char **args)
{
	if(num_args > 1)
	{
		printf(CONSOLE_YELLOW("More than 1 argument given, ignoring all but the first.\n"));
	}

	double v;
	int error = sscanf(args[0], "%lf", &v);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[0]);
		return 0.0;
	}

	if(debug_enabled) printf(CONSOLE_BLUE("Tan of %lf\n"), v);

	return tan(v);
}

double powval(uint8_t num_args, char **args)
{
	if(num_args > 2)
	{
		printf(CONSOLE_YELLOW("More than 2 arguments given, ignoring all but the first 2.\n"));
	}

	double v1, v2;
	int error = sscanf(args[0], "%lf", &v1);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[0]);
		return 0.0;
	}
	error = sscanf(args[1], "%lf", &v2);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[1]);
		return 0.0;
	}

	if(debug_enabled) printf(CONSOLE_BLUE("Multiplying %lf to the power of %lf\n"), v1, v2);

	return pow(v1, v2);
}

double expval(uint8_t num_args, char **args)
{
	if(num_args > 1)
	{
		printf(CONSOLE_YELLOW("More than 1 argument given, ignoring all but the first.\n"));
	}

	double v;
	int error = sscanf(args[0], "%lf", &v);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[0]);
		return 0.0;
	}

	if(debug_enabled) printf(CONSOLE_BLUE("Exponential of %lf\n"), v);

	return exp(v);
}

double lnval(uint8_t num_args, char **args)
{
	if(num_args > 1)
	{
		printf(CONSOLE_YELLOW("More than 1 argument given, ignoring all but the first.\n"));
	}

	double v;
	int error = sscanf(args[0], "%lf", &v);
	if(error != 1)
	{
		printf(CONSOLE_RED("Error parsing %s. Not a valid numeric input\n"), args[0]);
		return 0.0;
	}

	if(debug_enabled) printf(CONSOLE_BLUE("Natural log of %lf\n"), v);

	return log(v);
}

// struct to hold information about mathematical functions
typedef struct {
	char *function_name;
	char *friendly_name;
	double (*function_pointer)(uint8_t num_args, char **args);
	char *help_string;
} command;

// array of implemented maths functions
const command Commands[] = {
		{"add", "Addition", &add, "add <num_1> .. <num_N>"},
		{"sub", "Subtraction", &sub, "sub <num_1> <num_2>"},
		{"mul", "Multiplication", &mul, "mul <num_1> .. <num_N>"},
		{"div", "Division", &divi, "divi <num_1> <num_2>"},
		{"sqr", "Square root", &square_root, "sqr <num_1>"},
		{"abs", "Absolute value", &absval, "abs <num_1>"},
		{"sin", "Sin", &sinval, "sin <num_1>"},
		{"cos", "Cos", &cosval, "cos <num_1>"},
		{"tan", "Tan", &tanval, "tan <num_1>"},
		{"pow", "Power", &powval, "pow <num_1> <num_2>"},
		{"exp", "Exponential", &expval, "exp <num_1>"},
		{"ln", "Natural log", &lnval, "ln <num_1>"},
};

// function to print all help details
void print_help()
{
	if(debug_enabled) printf(CONSOLE_BLUE("Printing help menu\n"));
	printf(CONSOLE_GREEN("For more information on a specific command, type 'help <command>.\n"));
	printf(CONSOLE_GREEN("Available commands:\n"));
	for(int i = 0; i < sizeof(Commands) / sizeof(command); i++)
	{
		printf(CONSOLE_YELLOW("%s: %s\n"), Commands[i].friendly_name, Commands[i].help_string);
	}
	printf(CONSOLE_YELLOW("Debug: debug {on/off}\n"));
	printf(CONSOLE_YELLOW("Equation: equation {on/off}\n"));
	printf(CONSOLE_YELLOW("Exit: exit\n"));
}

void RegularParser(char *str)
{
	// separates input into words
	char **words;
	int word_count = string_parser(str, &words);

	// number of commands, used for looping over them
	int num_of_commands = sizeof(Commands) / sizeof(command);

	// handle math functions, loop over each one
	for(int i = 0; i < num_of_commands; i++)
	{
		// if the name matches
		if(strcmp(words[0], Commands[i].function_name) == 0)
		{
			// execute the function with given arguments
			double result = Commands[i].function_pointer(word_count - 1, &words[1]);
			// print result and return
			printf("Result : %lf\n", result);
			return;
		}
	}

	// if 'help' input
	if(strcmp(words[0], "help") == 0)
	{
		// if no arguments given, print help menu
		if(word_count == 1) print_help();
		// if arguments given
		else
		{
			// fund matching argument
			for(int i = 0; i < num_of_commands; i++)
			{
				if(strcmp(words[1], Commands[i].function_name) == 0)
				{
					// print the help string for that command
					printf(CONSOLE_YELLOW("%s: %s\n"), Commands[i].friendly_name, Commands[i].help_string);
					return;
				}
			}

			// print info for those functions not in math array
			if(strcmp(words[1], "debug") == 0) printf(CONSOLE_YELLOW("Debug: debug {on/off}\n"));
			if(strcmp(words[1], "equation") == 0) printf(CONSOLE_YELLOW("Equation: equation {on/off}\n"));
			else if(strcmp(words[1], "exit") == 0) printf(CONSOLE_YELLOW("Exit: exit\n"));
		}
	}
	// if 'debug' input
	else if(strcmp(words[0], "debug") == 0)
	{
		// if just debug, print status
		if(word_count == 1)
		{
			if(debug_enabled) printf(CONSOLE_BLUE("Displaying debug status.\n"));
			char* debug_result = debug_enabled == 0 ? "false" : "true";
			printf("Debug enabled : %s\n", debug_result);
		}
		// if argument == 'on', enable debugging mode
		else if(strcmp(words[1], "on") == 0)
		{
			if(debug_enabled) printf(CONSOLE_BLUE("Debug mode enabled.\n"));
			debug_enabled = 1;
			printf("Debug messages will be displayed.\n");
		}
		// if argument == 'off', disable debugging mode
		else if(strcmp(words[1], "off") == 0)
		{
			if(debug_enabled) printf(CONSOLE_BLUE("Debug mode disabled.\n"));
			debug_enabled = 0;
			printf("Debug messages will not be displayed.\n");
		}
		else
		{
			printf(CONSOLE_RED("Unknown argument '%s' given.\n"), words[1]);
		}
	}
	// for equation mode
	else if(strcmp(words[0], "equation") == 0)
	{
		// if just equation, print status
		if(word_count == 1)
		{
			if(debug_enabled) printf(CONSOLE_BLUE("Displaying equation mode status.\n"));
			char* equation_result = equation_mode == 0 ? "false" : "true";
			printf("Equation Mode enabled : %s\n", equation_result);
		}
		// if argument == 'on', enable equation mode
		else if(strcmp(words[1], "on") == 0)
		{
			if(debug_enabled) printf(CONSOLE_BLUE("Equation mode enabled.\n"));
			equation_mode = 1;
			printf("Equation mode now enabled.\n");
		}
		// if argument == 'off', disable equation mode
		else if(strcmp(words[1], "off") == 0)
		{
			if(debug_enabled) printf(CONSOLE_BLUE("Equation mode disabled.\n"));
			equation_mode = 0;
			printf("Equation mode now disabled.\n");
		}
		else
		{
			printf(CONSOLE_RED("Unknown argument '%s' given.\n"), words[1]);
		}
	}
	// for exiting
	else if(strcmp(words[0], "exit") == 0)
	{
		if(debug_enabled) printf(CONSOLE_BLUE("Exiting\n"));
		exit(0);
	}
	else
	{
		printf(CONSOLE_RED("Unknown command '%s'. Type 'Help' for instructions on how to use this program.\n"), words[0]);
	}
}

double EquationParserSTM(char *equation)
{
	TokenArray *token_array = tokenise_expression(equation);
	double result = parse_expression1(token_array);
	return result;
}

void EquationModeParser(char *equation)
{
	if(strcmp(equation, "equation off") == 0)
	{
		printf("equation mode off\n");
		equation_mode = 0;
		return;
	}
	if(strcmp(equation, "equation on") == 0)
	{
		printf("Equation mode already enabled\n");
		return;
	}

	TokenArray *token_array = tokenise_expression(equation);
	print_token_array(token_array);

	if(has_x_identifiers(token_array))
	{
		int screen_width = 100;
		for(int x = 0; x < screen_width; x++)
		{
			TokenArray *copy = copy_token_array(token_array);
			replace_x_identifiers(copy, x);
			double y = parse_expression1(copy);
			printf("x: %lf, y: %lf\n", (float)x, y);
		}
	}
	else
	{
		double result = parse_expression1(token_array);
		printf("%lf\n\n", truncate_double(result));
	}

	// this might delete data in the structs
	free(equation);

	reset(token_array);
}

static char *in_string;
static int in_initialized = 0;
void CommandLineParserProcess(void)
{
#ifdef STM32F407xx
	if(in_initialized == 0)
	{
		if(in_string != NULL)
		{
			free(in_string);
		}
		in_string = malloc(2);
		strcpy(in_string, "");
		in_initialized = 1;
	}

	uint8_t c;
	if (HAL_UART_Receive (&huart2, &c, 1, 0x0) == HAL_OK)
	{
		if ((c < 32) | (c > 126))
		{
			if(c == 127) {
				printf("%c", (char)127);
				in_string[strlen(in_string)-1] = '\0';
			}
			else if(c == 13) {
				printf("%c", (char)13);
				if(equation_mode == 1)
				{
					EquationModeParser(in_string);
				}
				else
				{
					RegularParser(in_string);
				}
				in_initialized = 0;
			}
		}
		else
		{
			in_string = realloc(in_string, 1 + strlen(in_string) + 1);
			strcat(in_string, &c);
			printf("%c", c);
		}
	}

#else
	// receive input from user
	char str[256];
	fflush(stdin);
	scanf("%[^\n]s", str);

	if(equation_mode == 1)
	{
		EquationModeParser(str);
	}
	else
	{
		RegularParser(str);
	}
#endif
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
/*void
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
}*/
