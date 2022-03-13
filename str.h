#ifndef str_h
#define str_h

#include "constants.h"

int str_starts_with(const char *pre, const char *str);
char *str_trim(char *str);
char **str_explode(char* str, char c);
char** split(char* chaine,const char* delim,int vide, int *finalSize);
int str_array_len(char **array);
int str_count_occurrences(char *str, char search);
char *str_get_quotes_content(char *str);
void str_tolower(char *str);

#endif