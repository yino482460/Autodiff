#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***  Node 2019/01/18 23:30 ***/
/* ノードのラベル */
enum {
    ND_NUM = 256,   //整数の場合におけるノードの型
};
/* ノード本体の設定 */
typedef struct Node {
    /* data */
    int Nd_Ty;           // 演算子かND_NUM つまり 考えている対象の型
    struct Node *Lhs;   // 左辺
    struct Node *Rhs;   // 右辺
    int Nd_Val;          // Nd_Tyが数字の場合のみ使う
}Node;

/* 新規ノードを作成する関数 (全てのノードに共通して生成する)*/
Node *NewNode (int Nd_Ty, Node *Lhs, Node *Rhs){
    Node *node = malloc(sizeof(Node));  //Node分のメモリを確保
    node -> Nd_Ty = Nd_Ty;  //以下新規ノードに各値をセット
    node -> Lhs = Lhs;
    node -> Rhs = Rhs;
    return node;
}
/* 新規に作成したノードに数字が含まれているときにNd_Valを追加する関数 */
Node *NewNodeNum(int Nd_Val) {
    Node *node = malloc(sizeof(Node));
    node -> Nd_Ty = ND_NUM;
    node -> Nd_Val = Nd_Val;
    return node;
}


/***  Token 2019/01/18 10:00 ***/
/* トークンが数値が四則演算記号、関数かを分類しラベルを貼る */
enum {
    TK_NUM = 256,    /* 整数トークン */
    TK_EOF = -1,     /* トークン文字列の終わりを表す */
};
/* トークン(Token)の型の設定 */
typedef struct {
    /* data */
    int TY; /* トークンの型 に対するラベル*/
    int VAL;    /* TYが数字のときその数値を代入 */
    char *input;    /* トークン文字列(エラーメッセージ用) */
}Token ;

// トークナイズした結果のトークン列はこの配列に保存する
// 100個以上のトークンは来ないものとする
Token tokens[100];

// pが指している文字列をトークンに分割してtokensに保存する関数
void tokenize(char *p) {
    int i = 0;  /* 文字列の最初に設定 */

    while (*p) {
        //空白文字をスキップ
        if ( isspace(*p) ) {
            /* isspace()は空白があれば真を返す */
            p++;    //読みとばして次に
            continue;   //ループの先頭に跳ぶ
        }
        // +か - を判定
        if ( *p == '+' || *p == '-' ) {
            tokens[i].TY = *p;  /* +, - に対応する文字コードの数値を代入 */
            tokens[i].input = p;
            i++;
            p++;
            continue;
        }
        //数字かどうかを判定
        if ( isdigit(*p)) {
            tokens[i].TY = TK_NUM;  /* 数字のときは256のラベルを設定 */
            tokens[i].input = p;
            tokens[i].VAL = strtol(p, &p, 10);
            i++;
            continue;
        }
        fprintf(stderr, "トークナイズできません: %s\n", p);
        exit(1);
    }

    tokens[i].TY = TK_EOF;
    tokens[i].input = p;
}

// エラーを報告するための関数
void error(int i) {
  fprintf(stderr, "予期しないトークンです: %s\n", tokens[i].input);
  exit(1);
}


//メイン関数
int main(int argc, char const *argv[]) {
    FILE *file;
    char fname[] = "test.txt";  //読み込むファイルの名前
    int N = 100;    //一行当たりに読み込める最大文字数
    char formula[N];    //読み込んだ数式 = Numerical formula

    //ファイルからの読み込み
    file = fopen(fname, "r");
    //例外処理
    if ( file == NULL) {
        printf("%s file not open!\n", fname );
        return -1;
    }
    /*一行丸ごと数式を読み込む　※複数の数式を読み込むならwhile文に　*/
    fgets(formula, N, file);    //ファイルから読み込んでformulaに代入
    fclose(file);
    //読み込んだかの確認
    //printf("%s", formula);

    //ファイルから読み込んだ文字列をトークナイズする
    tokenize( formula );

    //トークナイズされたかの確認
    //printf("%s\n", test );


    // 式の最初は数でなければならないので、それをチェックして
    int i = 0;
    if (tokens[0].TY != TK_NUM){  //例外処理
        error(0); }
    printf("%d\n", tokens[0].VAL);

    i = 1;
    while (tokens[i].TY != TK_EOF) {
        // +の場合
        if (tokens[i].TY == '+') {
            i++;
            //+が最初または最後のとき式が成立しない
            if (tokens[i].TY != TK_NUM) {
                error(i);
            }
            printf("%d\n", tokens[i].VAL);
            i++;
            continue;
        }
        // - の場合
        if (tokens[i].TY == '-') {
            i++;
            if (tokens[i].TY != TK_NUM) {
                error(i);
            }
            printf("%d\n", tokens[i].VAL);
            i++;
            continue;
        }

    error(i);
  }

    return 0;
}
