#ifndef DEF_TOKENIZER_H
#define DEF_TOKENIZER_H

#include <stdio.h>

int tokenize_file(FILE *file);
int get_statement(char *statement);
int is_token_valid(char *token);

#endif