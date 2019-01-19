#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

/// util.c ///

// noreturn void error(char *fmt);

// Vector の構造体
#ifndef Autodiff_Vector_Token
#define Autodiff_Vector_Token
typedef struct {
    void **data;
    int capacity;
    int len;
} Vector;
#endif

// Vector を使う色々な関数の宣言
Vector *new_vec(void);
void vec_push(Vector *v, void *elem);

/***  token.c　***/
// トークンの型
#ifndef Autodiff_Token
#define Autodiff_Token
enum {
    TK_NUM = 256, // Number literal
    TK_EOF,       // End marker
};
#endif

// Token type　トークンの構造体
#ifndef Autodiff_Token_Struct
#define Autodiff_Token_Struct
typedef struct {
    int ty;      // Token type
    int val;     // Number literal
    char *input; // Token string (for error reporting)
} Token;
#endif

// 文字列をトークンに分割する関数
Vector *tokenize(char *p);

/***　parse.c　パーサ ***/
#ifndef Autodiff_Parse
#define Autodiff_Parse
enum {
    ND_NUM = 256,     // Number literal
};
#endif

// Node構造体の宣言
#ifndef Autodiff_Node_Struct
#define Autodiff_Node_Struct
typedef struct Node {
    int ty;           // Node type
    struct Node *lhs; // left-hand side
    struct Node *rhs; // right-hand side
    int val;          // Number literal
} Node;
#endif


Node *parse(Vector *tokens);

/*
/// ir.c /// 以下の変更は行っていない　2019/01/18

enum {
  IR_IMM,
  IR_MOV,
  IR_RETURN,
  IR_KILL,
  IR_NOP,
};

typedef struct {
  int op;
  int lhs;
  int rhs;
} IR;

Vector *gen_ir(Node *node);

/// regalloc.c

extern char *regs[];
void alloc_regs(Vector *irv);

/// codegen.c
void gen_x86(Vector *irv);
*/
