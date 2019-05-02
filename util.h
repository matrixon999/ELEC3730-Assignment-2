#ifndef UTIL_H_
#define UTIL_H_

// These are defines for changing the colours of the output text
#define CONSOLE_RED(str)     "\x1b[31m" str "\x1b[0m"
#define CONSOLE_GREEN(str)   "\x1b[32m" str "\x1b[0m"
#define CONSOLE_YELLOW(str)  "\x1b[33m" str "\x1b[0m"
#define CONSOLE_BLUE(str)    "\x1b[34m" str "\x1b[0m"
#define CONSOLE_MAGENTA(str) "\x1b[35m" str "\x1b[0m"
#define CONSOLE_CYAN(str)    "\x1b[36m" str "\x1b[0m"
#define CONSOLE_RESET   "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
//#include <math.h>

void add_to_string(char *str, char c);
void concatenate_strings(char *str, char *str2);
bool is_alpha(char c);
bool is_numeric(char c);
bool is_whitespace(char c);
double to_double(char *str);
char *to_string(double val);
extern char *truncate_double(double val);

#endif
