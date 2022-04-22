#ifndef DEF_TOKENS_H
#define DEF_TOKENS_H

enum STATEMENTS {
    STATEMENT_NULL,
    STATEMENT_OUT,
    STATEMENT_GET,
    STATEMENT_INSERT,
    STATEMENT_INSERTL,
    STATEMENT_POINTER,
    STATEMENT_EXIT,
    STATEMENT_COMP,
    STATEMENT_JUMP,
    STATEMENT_JE,      // JumpEq
    STATEMENT_JNE,     // JumpNotEq
    STATEMENT_JG,      // JumpGreater
    STATEMENT_JGE,     // JumpGreaterEq
    STATEMENT_JL,      // JumpLess
    STATEMENT_JLE,     // JumpLessEq
    STATEMENT_LABEL
};

static const char *STATEMENTS_STR[] = {
    "",
    "out",
    "get",
    "insert",
    "insertl",
    "pointer",
    "exit",
    "comp",
    "jump",
    "jumpeq",
    "jumpnoteq",
    "jumpgreater",
    "jumpgreatereq",
    "jumpless",
    "jumplesseq",
    "label"
};

typedef enum
{
    SIGN_PLUS = '+',
    SIGN_MINUS = '-',
    SIGN_MULTIPLY = '*',
    SIGN_DIVIDE = '/',
    SIGN_MODULO = '%'
} arg_sign_t;

typedef enum {
    ARG_TYPE_INT,
    ARG_TYPE_STR
} arg_type_t;


#endif