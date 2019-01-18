#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* トークンが数値が四則演算記号、関数かを分類しラベルを貼る */
enum {
    TK_NUM = 256,    /* 整数トークン */
    TK_EOF,     /* トークン文字列の終わりを表す */

};
/* トークン(Token)の型の設定 */
typedef struct {
    /* data */
    int TY; /* トークンの型 に対するラベル*/
    int VAL;    /* TYがTK_NUMのときその数値を代入 */
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
  fprintf(stderr, "予期しないトークンです: %s\n",
          tokens[i].input);
  exit(1);
}

//メイン関数
int main(int argc, char const *argv[]) {
    FILE *file;
    char fname[] = "test.txt";  //読み込むファイルの名前
    int N = 100;    //一行当たりに読み込める最大文字数
    char str[N];    //読み込んだ文字列

    file = fopen(fname, "r");
    if ( file == NULL) {
        printf("%s file not open!\n", fname );
        return -1;
    }
    while(fgets(str, N, file) != NULL) {
		printf("%s", str);
	}
    fclose(file);
    
    return 0;
}
