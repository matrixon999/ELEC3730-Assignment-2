#include "tokeniser.h"

Token* next(TokenArray* ta)
{
	Token *t = ta->array[ta->pos++];
	if(t == NULL) return NULL;
	return t;
}

Token* grab_next(TokenArray* ta)
{
	return ta->array[ta->pos];
}

Token* grab_prev(TokenArray* ta)
{
	return ta->array[ta->pos - 2];
}

void reset(TokenArray* ta)
{
	ta->pos = 0;
}

TokenArray *create_new_token_array()
{
	TokenArray *token_array = malloc(sizeof(TokenArray));
	token_array->array = malloc(sizeof(Token));
	token_array->num_elements = 0;
	reset_null_end(token_array);
	reset(token_array);

	return token_array;
}

void set_position(TokenArray* ta, Token *t)
{
	reset(ta);
	Token *pos = NULL;
	while(pos = next(ta))
	{
		if(pos == t) return;
	}

	printf("Couldn't find that token in token array\n");
}

bool has_x_identifiers(TokenArray *ta)
{
	reset(ta);
	Token *pos = NULL;
	while(pos = next(ta))
	{
		if(pos->type == Identifier && strcmp(pos->data, "x") == 0)
		{
			return true;
		}
	}

	return false;
}

void replace_x_identifiers(TokenArray *ta, double val)
{
	reset(ta);
	Token *pos = NULL;
	while(pos = next(ta))
	{
		if(pos->type == Identifier && strcmp(pos->data, "x") == 0)
		{
			pos->type = Number;
			pos->num_value = val;
		}
	}
}

Token *copy_token(Token *t)
{
	Token *copy = malloc(sizeof(Token));
	copy->type = t->type;

	if(t->type == Number) copy->num_value = t->num_value;
	else
	{
		copy->data = malloc(strlen(t->data) + 1);
		strcpy(copy->data, t->data);
	}

	return copy;
}

TokenArray *copy_token_array(TokenArray *ta)
{
	TokenArray *copy = create_new_token_array();
	for(int i = 0; i < ta->num_elements; i++)
	{
		Token *new_token = copy_token(ta->array[i]);
		add_to_token_array(copy, new_token);
	}

	return copy;
}

bool is_first(TokenArray *ta, Token *t)
{
	return ta->array[0] == t;
}

void reset_null_end(TokenArray *ta)
{
	ta->array[ta->num_elements] = NULL;
	memset(&ta->array[ta->num_elements], 0, sizeof(Token));
}

void add_to_token_array(TokenArray *ta, Token *t)
{
	// inc num_elements
	ta->num_elements++;
	// reallocate memory to hold number of elements + 1 for null
	ta->array = realloc(ta->array, (ta->num_elements + 1) * sizeof(Token));
	// set last element in array to the new token
	ta->array[ta->num_elements - 1] = t;
	// make sure null object is at end
	reset_null_end(ta);
}

void remove_token(TokenArray *ta, Token *t)
{
	for(int i = 0; i < ta->num_elements; i++)
	{
		if(ta->array[i] == t)
		{
			int num_to_copy = ta->num_elements - i + 1;
			memmove(&ta->array[i], &ta->array[i+1], num_to_copy * sizeof(Token));
			ta->num_elements--;
			reset_null_end(ta);
			return;
		}
	}

	printf("Removed nothing\n");
}

void add_singular_token(TokenArray *ta, char c)
{
	Token *t = malloc(sizeof(Token));
	t->data = malloc(2);
	strcpy(t->data, &c);
	t->data[1] = '\0';
	switch(c)
	{
		case '+': t->type = Add; break;
		case '-': t->type = Sub; break;
		case '*': t->type = Mult; break;
		case '/': t->type = Div; break;
		case '(': t->type = LParen; break;
		case ')': t->type = RParen; break;
	}

	add_to_token_array(ta, t);
}

char *ttype_to_str(TokType t)
{
	switch(t)
	{
		case Number: return "Number";
		case Mult: return "Mult";
		case Div: return "Div";
		case Add: return "Add";
		case Sub: return "Sub";
		case LParen: return "LParen";
		case RParen: return "RParen";
		//case Expression: return "Expression";
		case Identifier: return "Identifier";
	}

	return "Unknown";
}

void print_token(Token* t)
{
	if(t->type == Number)
	{
		printf("Token: %p - %s : %lf\n", t, ttype_to_str(t->type), t->num_value);
	}
	else
	{
		printf("Token: %p - %s : %s\n", t, ttype_to_str(t->type), t->data);
	}
}

void print_token_array(TokenArray *ta)
{
	printf("--\n");
	for(int i = 0; i < ta->num_elements; i++)
	{
		if(ta->pos-1 == i) printf("-> ");
		print_token(ta->array[i]);
	}
	printf("--\n\n");
}

TokenArray *tokenise_expression(char* expression)
{
	TokenArray *token_array = create_new_token_array();

	//printf("Size of expression: %d\n", strlen(expression));

	for(int i = 0; i < strlen(expression); i++)
	{
		char c = expression[i];

		// handle whitespace
		if (is_whitespace(c)) continue;

		// handle numbers
		if (is_numeric(c) || c == '.')
		{
			char *tmp = malloc(1);
			strcpy(tmp, "");
			while (is_numeric(expression[i]) || expression[i] == '.')
			{
				add_to_string(tmp, expression[i++]);
			}
			i--;

			Token *token = malloc(sizeof(Token));
			token->num_value = to_double(tmp);
			token->type = Number;
			add_to_token_array(token_array, token);
			continue;
		}

		// handle identifiers
		if (is_alpha(c))
		{
			char *tmp = malloc(1);
			strcpy(tmp, "");
			while (is_alpha(expression[i]))
			{
				add_to_string(tmp, expression[i++]);
			}
			i--;

			Token *token = malloc(sizeof(Token));
			token->data = tmp;
			token->type = Identifier;
			add_to_token_array(token_array, token);
			continue;
		}

		// handle single character tokens
		switch(c)
		{
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			case ')':
			{
				add_singular_token(token_array, c);
				continue;
			} break;
		}

		printf("What in the fuck is this? -> %c\n", c);
		//exit(0);
	}

	return token_array;
}
