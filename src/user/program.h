#ifndef DEF_USER_PROGRAM
#define DEF_USER_PROGRAM

#include <stdbool.h>
#include "../constants.h"
#include "../tokens.h"

typedef struct
{
    arg_type_t argType;
    int argInt;
    arg_sign_t argSign;
    char argStr[MAX_TOKEN_SIZE];
} LineArg;
typedef struct
{
    int lineNumber;
    int statement;
    int argsCount;
    LineArg args[MAX_LINE_ARGS_NUMBER];
} LineTokens;
extern LineTokens Lines[MAX_LINE_NUMBER];

typedef struct
{
    char name[MAX_TOKEN_SIZE];
    int lineNumber;
} DiploLabel;
// extern DiploLabel Labels[MAX_LABEL_NUMBER];

typedef struct
{
    int lines;
    int labelsCount;
    DiploLabel labels[MAX_LABEL_NUMBER];
    unsigned char array[DIPLO_ARRAY_SIZE];
    int pointer;
    struct {
        bool eq;
        bool notEq;
        bool greater;
        bool greaterEq;
        bool less;
        bool lessEq;
    } lastComp;
} program;
extern program Program;


// typedef struct
// {
//     char raw[MAX_LINE_SIZE];
//     char *trimmed;
//     int number;
//     struct
//     {
//         struct
//         {
//             char **content;
//             int length;
//         } space;
//     } exploded;

//     char tokens[MAX_TOKEN_NUMBER][MAX_TOKEN_SIZE];
// } line;

// typedef struct
// {
//     char lines[MAX_LINE_NUMBER][MAX_LINE_SIZE];
//     int linesNumber;
//     unsigned char array[DIPLO_ARRAY_SIZE];
//     int pointer;
//     int loopDepth;
// } program;

// typedef struct
// {
//     char lines[MAX_LINE_NUMBER][MAX_TOKEN_NUMBER][MAX_TOKEN_SIZE];
// } tokens;

// extern program Program;
// extern line CurrentLine;
// extern tokens Tokens;

#endif