#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

// Program
#define DIPLO_VERSION "1.0.0"

#define INPUT_FNAME_MAX_LENGTH   512
#define CONFIG_FLAGS_MAX_LENGTH  20
#define MAX_LINE_SIZE            1024
#define MAX_LINE_NUMBER          32768
#define MAX_TOKEN_SIZE           200
#define MAX_TOKEN_NUMBER         100
#define MAX_LINE_ARGS_NUMBER     100
#define MAX_LABEL_NUMBER         512
#define MAX_ERR_SIZE             1024
#define DIPLO_ARRAY_SIZE         65536

#define EXECUTION_DEBUG 0

// Error messages
#define MSG_FATAL_ERROR "Fatal:"

// Error codes (16 bits)
// Error types:
// - 0001: Various
// - 0010: Statement
// - 0011: Argument

//                    (10 bits) error detail + (6 bits) error type + (1 bit) program halted
//                                 ++++++++++******-
#define ERR_UNKNOWN              0b00000000010000011
#define ERR_LOOP_DEPTH           0b00000000100000011
#define ERR_UNKNOWN_STATEMENT    0b00000000010000101
#define ERR_EXPECTED_ARGUMENT    0b00000000010001001
#define ERR_INVALID_ARGUMENT     0b00000000100001001
#define ERR_UNKNOWN_VARIABLE     0b00000000010010001
#define ERR_UNKNOWN_LABEL        0b00000000010100001


#define BETA_KEY                 "key/b0ec34ef212ab5b1057606331ffd868b"

#endif