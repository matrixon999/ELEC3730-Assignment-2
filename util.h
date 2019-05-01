#ifndef UTIL_H_
#define UTIL_H_

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
