#ifndef TOKENISER_H_
#define TOKENISER_H_

#include "util.h"

typedef enum
{
	Number,
	Mult,
	Div,
	Add,
	Sub,
	LParen,
	RParen,
	//Expression,
	Identifier,
} TokType;

typedef struct sToken Token;
typedef struct sTokenArray TokenArray;

struct sToken
{
	char* data;
	TokType type;
	double num_value;
	//TokenArray* ta_value;
};

struct sTokenArray
{
	Token **array;
	int num_elements;
	int pos;
};

Token* next(TokenArray* ta);
Token* grab_next(TokenArray* ta);
Token* grab_prev(TokenArray* ta);
void reset(TokenArray* ta);
TokenArray *create_new_token_array();
void set_position(TokenArray* ta, Token *t);
bool has_x_identifiers(TokenArray *ta);
void replace_x_identifiers(TokenArray *ta, double val);
Token *copy_token(Token *t);
TokenArray *copy_token_array(TokenArray *ta);
bool is_first(TokenArray *ta, Token *t);
void reset_null_end(TokenArray *ta);
void add_to_token_array(TokenArray *ta, Token *t);
void remove_token(TokenArray *ta, Token *t);
void add_singular_token(TokenArray *ta, char c);
char *ttype_to_str(TokType t);
void print_token(Token* t);
void print_token_array(TokenArray *ta);
TokenArray *tokenise_expression(char* expression);

#endif
