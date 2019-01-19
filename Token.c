/*
*　作成日　2018/01/18 23:00
* 「単語」=「トークン」を定義するプログラム
*　!　パースのように構文解析を実装する必要はない
*/
#include "Autodiff.h"
#include "Token.h"

static Token *add_token(Vector *v, int ty, char *input) {
    Token *t = malloc(sizeof(Token));
    t->ty = ty;
    t->input = input;
    vec_push(v, t);
    return t;
}

//  2018/01/18 23:00 Vector をまだ理解できてない(泣)
Vector *tokenize(char *p){
    Vector *v = new_vec();  //関数未定義?　2018/01/18
    int i = 0;
    while (*p) {
        //空白を読み飛ばす
        if (isspace(*p)) {
            p++;
            continue;
        }
        if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
            add_token(v, *p, p);
            i++;
            p++;
            continue;
        }
        if (isdigit(*p)) {
            Token *t = add_token(v, TK_NUM, p);
            t->val = strtol(p, &p, 10);
            i++;
            continue;
        }
        fprintf(stderr, "トークナイズできません: %s\n", p);
        exit(1);
    }

    add_token(v, TK_EOF, p);
    return v;
};
