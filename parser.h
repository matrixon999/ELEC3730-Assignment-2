#ifndef PARSER_H_
#define PARSER_H_

#include "util.h"
#include "tokeniser.h"

double parse_expression1(TokenArray *ta); // unary
double parse_expression2(TokenArray *ta); // parentheses
double parse_expression3(TokenArray *ta); // functions
double parse_expression4(TokenArray *ta); // * and /
double parse_expression5(TokenArray *ta); // + and -

#endif
