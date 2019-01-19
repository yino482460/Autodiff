/*
*　作成日　2018/01/18 23:00
* 「単語」=「トークン」を定義するプログラム
*　!　パースのように構文解析を実装する必要はない
*/
#include "Autodiff.h"
#include "Token.h"

Token tokens[100];

//  2018/01/18 23:00 Vector をまだ理解できてない(泣)
Vector *tokenize(char *p){
    int i = 0;
    while (*p) {
        if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
            tokens[i].ty = *p;
            tokens[i].input = p;
            i++;
            p++;
            continue;
        }
        if (isdigit(*p)) {
            tokens[i].ty = TK_NUM;
            tokens[i].input = p;
            tokens[i].val = strtol(p, &p, 10);
            i++;
            continue;
        }
        fprintf(stderr, "トークナイズできません: %s\n", p);
        exit(1);
    }
    tokens[i].ty = TK_EOF;
    tokens[i].input = p;


};
