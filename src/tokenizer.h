#ifndef DEF_TOKENIZER_H
#define DEF_TOKENIZER_H

#include <stdio.h>
#include "tokens.h"

int tokenize_file(FILE *file);
statement_t get_statement(char *statement);

#endif