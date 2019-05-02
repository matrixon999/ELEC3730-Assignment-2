#include "parser.h"

double parse_expression1(TokenArray *ta)
{
	reset(ta);
	Token *t = NULL;
	while(t = next(ta))
	{
		if(t->type == Sub)
		{
			Token *next = grab_next(ta);
			if(next == NULL) return 0.0;

			if(next->type == Number)
			{
				if(is_first(ta, t))
				{
					next->num_value *= -1;
					remove_token(ta, t);
					continue;
				}

				Token *prev = grab_prev(ta);
				if(prev->type == LParen
				|| prev->type == Add
				|| prev->type == Sub
				|| prev->type == Mult
				|| prev->type == Div)
				{
					next->num_value *= -1;
					remove_token(ta, t);
					continue;
				}
			}
		}
	}

	return parse_expression2(ta);
}

// parentheses
double parse_expression2(TokenArray *ta)
{
	reset(ta);
	Token *t = NULL;
	while(t = next(ta))
	{
		if(t->type == LParen)
		{
			Token* start = t;
			Token* end = NULL;
			int depth = 1;

			while(t = next(ta))
			{
				if(t->type == LParen) depth++;
				if(t->type == RParen) depth--;

				if(depth == 0)
				{
					end = t;
					break;
				}
			}

			if(depth != 0)
			{
				printf(CONSOLE_RED("No closing parentheses found!\n"));
				return 0.0;
			}

			set_position(ta, start);

			// split start to end into new token array
			TokenArray *ta_new = create_new_token_array();
			Token *t_new = NULL;

			while(t_new = next(ta))
			{
				if(t_new == end)
				{
					remove_token(ta, end);
					break;
				}

				add_to_token_array(ta_new, t_new);
				remove_token(ta, t_new);
				set_position(ta, start);
			}

			start->type = Number;
			start->num_value = parse_expression1(ta_new);

			// probably need to reset original ta after dealing with everything
			reset(ta);
		}
	}

	return parse_expression3(ta);
}

//functions
double parse_expression3(TokenArray *ta)
{
	reset(ta);
	Token *t = NULL;
	while (t = next(ta))
	{
		if(t->type == Identifier)
		{
			if(strcmp(t->data, "x") == 0)
			{
				printf("Found an x, this is probably for graphing mode\n");
				return 0.0;
			}

			// literals
			if(strcmp(t->data, "Pi") == 0)
			{
				t->type = Number;
				t->num_value = 3.1415926;
				continue;
			}

			Token *right = grab_next(ta);
			if(right == NULL) return 0.0;

			// functions

			if(right != NULL && right->type == Number)
			{
				if(strcmp(t->data, "sin") == 0)
				{
					t->type = Number;
					t->num_value = sin(right->num_value);
					remove_token(ta, right);
					ta->pos -= 1;
				}
				else if(strcmp(t->data, "cos") == 0)
				{
					t->type = Number;
					t->num_value = cos(right->num_value);
					remove_token(ta, right);
					ta->pos -= 1;
				}
				else if(strcmp(t->data, "tan") == 0)
				{
					t->type = Number;
					t->num_value = tan(right->num_value);
					remove_token(ta, right);
					ta->pos -= 1;
				}
				else if(strcmp(t->data, "abs") == 0)
				{
					t->type = Number;
					t->num_value = abs(right->num_value);
					remove_token(ta, right);
					ta->pos -= 1;
				}
				else if(strcmp(t->data, "exp") == 0)
				{
					t->type = Number;
					t->num_value = exp(right->num_value);
					remove_token(ta, right);
					ta->pos -= 1;
				}
				else if(strcmp(t->data, "ln") == 0)
				{
					t->type = Number;
					t->num_value = log(right->num_value);
					remove_token(ta, right);
					ta->pos -= 1;
				}
				else if(strcmp(t->data, "sqrt") == 0)
				{
					t->type = Number;
					t->num_value = sqrt(right->num_value);
					remove_token(ta, right);
					ta->pos -= 1;
				}
				else if(strcmp(t->data, "log") == 0)
				{
					t->type = Number;
					t->num_value = log10(right->num_value);
					remove_token(ta, right);
					ta->pos -= 1;
				}
			}
			else
			{
				printf(CONSOLE_RED("Unknown Identifier: %s\n"), t->data);
				return 0.0;
			}
		}
	}

	return parse_expression4(ta);
}

// * and /
double parse_expression4(TokenArray *ta)
{
	reset(ta);
	Token *t = NULL;
	while(t = next(ta))
	{
		if(t->type == Mult)
		{
			Token* left = grab_prev(ta);
			if(left == NULL) return 0.0;
			Token* right = grab_next(ta);
			if(right == NULL) return 0.0;

			if(left->type == Number && right->type == Number)
			{
				left->type = Number;
				left->num_value = left->num_value * right->num_value;

				remove_token(ta, t);
				remove_token(ta, right);
				ta->pos -= 1;
			}
		}
		else if(t->type == Div)
		{
			Token* left = grab_prev(ta);
			if(left == NULL) return 0.0;
			Token* right = grab_next(ta);
			if(right == NULL) return 0.0;

			if(left->type == Number && right->type == Number)
			{
				left->type = Number;
				left->num_value = left->num_value / right->num_value;

				remove_token(ta, t);
				remove_token(ta, right);
				ta->pos -= 1;
			}
		}
	}

	return parse_expression5(ta);
}

// + and -
double parse_expression5(TokenArray *ta)
{
	reset(ta);
	Token *t = NULL;
	while(t = next(ta))
	{
		if(t->type == Add)
		{
			Token* left = grab_prev(ta);
			if(left == NULL) return 0.0;
			Token* right = grab_next(ta);
			if(right == NULL) return 0.0;

			if(left->type == Number && right->type == Number)
			{
				left->type = Number;
				left->num_value = left->num_value + right->num_value;

				remove_token(ta, t);
				remove_token(ta, right);
				ta->pos -= 1;
			}
		}
		else if(t->type == Sub)
		{
			Token* left = grab_prev(ta);
			if(left == NULL) return 0.0;
			Token* right = grab_next(ta);
			if(right == NULL) return 0.0;

			if(left->type == Number && right->type == Number)
			{
				left->type = Number;
				left->num_value = left->num_value - right->num_value;

				remove_token(ta, t);
				remove_token(ta, right);
				ta->pos -= 1;
			}
		}
	}

	// hopefully by this point we have only 1 token left
	if(ta->num_elements != 1)
	{
		printf("Error occurred\n");
		printf("We should only have 1 token by this point.\n");
		//print_token_array(ta);
		return 0.0;
	}
	if(ta->array[0]->type != Number)
	{
		printf("Error occurred\n");
		printf("We have 1 token, but it's not a number.\n");
		//print_token_array(ta);
		return 0.0;
	}

	return ta->array[0]->num_value;
}
