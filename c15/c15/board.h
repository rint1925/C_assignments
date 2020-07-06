#pragma once

typedef struct player { char *name; char *stoneSymbol; int playerId; };

//盤面を表示する関数（また、引数で与えられた変数にも同じものを書き込む）
void dispBoard(int board[10][10], char stream[1024]);

//x,yに置いたとき,playerがp,q方向に裏返し可能な石の個数を返す関数(player番号は石番号に一致)
int countReversibleStones(int board[10][10], int playerId, int x, int y, int p, int q);

//playerがx,yに石を置けるかどうか
bool isPlaced(int board[10][10], int playerId, int x, int y);

//playerにとって石が置ける場所を探して、場所番号が入った配列（引数）を書き換える。また、1つでも置けるならtrueを返す
bool scanPlaced(int placeNums[64], int board[10][10], int playerId);

//プレイヤーの入力を受け取って、11~88の値を返す
int getPlayerInput(int board[10][10], player p);

//石を置いて相手の石を裏返す
void putAndReverse(int board[10][10], player me, player opponent, int x, int y);