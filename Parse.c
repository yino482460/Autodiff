/*
*　2019 01/18　12:45　パーサを作成開始
*/

#include "Autodiff.h"

static Vector *tokens;
static int pos;

/* 新しいノードを作成する関数 */
static Node *new_node(int op, Node *lhs, Node *rhs) {
    Node *node = malloc(sizeof(Node));
    node->ty = op;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

/* トークンが数字のとき新しいノードに数字を追加する関数 */
static Node *new_node_num(int val) {
    Node *node = malloc(sizeof(Node));
    node->ty = ND_NUM;
    node->val = val;
    return node;
}

static Node *number() {
    Token *t = tokens->data[pos];
    if (t->ty != TK_NUM) {
        perror("number expected, Token");
    }
    pos++;
    return new_node_num(t->val);
}

static Node *expr() {
    Node *lhs = number();
    for (;;) {
        Token *t = tokens->data[pos];
        int op = t->ty;
        if (op != '+' && op != '-') {
            break;
        }
        pos++;
        lhs = new_node(op, lhs, number());
  }

  Token *t = tokens->data[pos];
  if (t->ty != TK_EOF) {
      perror("stray token");
  }
    return lhs;
}

Node *parse(Vector *v) {
    tokens = v;
    pos = 0;
    return expr();
}
