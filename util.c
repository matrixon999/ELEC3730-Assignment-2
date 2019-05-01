#include "util.h"

void add_to_string(char *str, char c)
{
	size_t len = strlen(str);
	str = realloc(str, len + 1);

	str[len] = c;
	str[len + 1] = '\0';
}

void concatenate_strings(char *str, char *str2)
{
	size_t len1 = strlen(str);
	size_t len2 = strlen(str2);
	str = realloc(str, len1 + len2 + 1);
	strcat(str, str2);
}

bool is_alpha(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool is_numeric(char c)
{
	return c >= '0' && c <= '9';
}

bool is_whitespace(char c)
{
	return c == ' ' || c == '\r' || c == '\n';
}

double to_double(char *str)
{
	double x;
	int result = sscanf(str, "%lf", &x);
	/*if(result < 0)
	{
		printf("to_double failed to parse: %s\n", str);
		return 0.0;
	}*/
	return x;
}

char *to_string(double val)
{
	char out[20];
	int result = snprintf(out, 20, "%lf", val);
	if(result < 0)
	{
		printf("to_string failed\n");
		return "";
	}

	char *out2 = malloc(strlen(out) + 1);
	strcpy(out2, out);

	return out2;
}

char *truncate_double(double val)
{
	int count = 0;
	char *str = to_string(val);
	for(int i = strlen(str)-1; i > 0; --i)
	{
		if(str[i] == '0') count++;
		else if(str[i] == '.') {
			count++;
			break;
		}
		else break;
	}

	str[strlen(str) - count] = '\0';
	return str;
}
