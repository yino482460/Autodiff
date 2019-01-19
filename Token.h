/*
*　作成日　2018/01/18 23:00
*/

#include "Autodiff.h"
// Token type　トークンの構造体
#ifndef Autodiff_Token_Struct
#define Autodiff_Token_Struct
typedef struct Token {
    int ty;      // Token type
    int val;     // Number literal
    char *input; // Token string (for error reporting)
} Token;
#endif

// トークンの型
#ifndef Autodiff_Token
#define Autodiff_Token
enum {
    TK_NUM = 256, // Number literal
    TK_EOF,       // End marker
};
#endif


// 文字列をトークンに整理して出力する関数
Vector *tokenize(char *p);
