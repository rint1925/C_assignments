// c15.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFLENGTH 1024

typedef struct player { char *name; char *stoneSymbol; int playerId;};

//盤面を表示する関数
void dispBoard(int board[10][10]){
	int i, j; //インデックス
	char str[BUFFLENGTH] = " 1 2 3 4 5 6 7 8"; //出力用
	for (i = 0; i < 8; i++) {
		char tmp[BUFFLENGTH];
		sprintf_s(tmp, "\n%d", i+1);

		for (j = 0; j < 8; j++) {
			switch (board[i+1][j+1]) {
				case 0:
					strcat_s(tmp, "・"); //tmpと"・"を結合
					break;

				case 1:
					strcat_s(tmp, "○");
					break;

				case 2:
					strcat_s(tmp, "●");
					break;
			}	
		}
		strcat_s(str, tmp); //"\n1・・・・・・・・"の形を8回結合
	}
	strcat_s(str, "\n"); //最後に改行
	fprintf_s(stdout, str);
}


//x,yに置いたとき,playerがp,q方向に裏返し可能な石の個数を返す関数(player番号は石番号に一致)
int countReversibleStones(int board[10][10],int playerId, int x, int y, int p, int q) {
	int opponent = 3 - playerId; //相手の番号なので,1の場合2,2の場合1

	int cnt;

	//既に石が置かれている場合
	if (board[x][y] != 0) {
		return 0;
	}

	//敵の石がある限り繰り返す（端点は-1となりそこで終わる）
	for(cnt = 1; board[x + p*cnt][y + q*cnt] == opponent; cnt++){}

	//端が自分の石である場合
	if (board[x + p*cnt][y + q*cnt] == playerId) {
		return cnt - 1;
	
	}
	//端が自分の石でない（-1の）場合
	else {
		return 0;
	}
}


//playerがx,yに石を置けるかどうか
bool isPlaced(int board[10][10], int playerId, int x, int y) {
	bool result = false;
	int i, j;

	//周囲8方向を調べる
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (i == 0 && j == 0) continue;
			if (countReversibleStones(board, playerId, x, y, i, j) > 0) result = true;
		}
	}

	return result;
}



//playerにとって石が置ける場所を探して、場所番号が入った配列（引数）を書き換える。また、1つでも置けるならtrueを返す
bool scanPlaced(int placeNums[64],int board[10][10], int playerId) {
	int ptr = 0;
	int i, j;
	bool result = false;
	for (i = 1; i < 9; i++) {
		for (j = 1; j < 9; j++) {
			if (isPlaced(board, playerId, i, j)) {
				placeNums[ptr] = 10*i+j;
				ptr += 1;
				if(!result) result = true;
			}
		}
	}

	return result;
}



//プレイヤーの入力を受け取って、11~88の値を返す
int getPlayerInput(int board[10][10], player p) {
	
	int placeNum;
	int x, y;

	//fprintf_s(stdout, "%sさんの手を入力してください",p.name);
	while (1) {
		fprintf_s(stdout,">>>");
		scanf_s("%d", &placeNum);

		if (placeNum < 11 || placeNum >88) {
			fprintf_s(stdout, "11から88の値を入力してください");
			continue;
		}

		x = placeNum / 10;
		y = placeNum % 10;

		if (isPlaced(board, p.playerId, x, y)) {
			return placeNum;
		}
		else {
			fprintf_s(stdout, "この場所には石を置けません.他の場所を指定してください");
			continue;
		}
	}
}


//石を置いて相手の石を裏返す
void putAndReverse(int board[10][10], player me, player opponent, int x, int y) {
	int i, j, k, num;

	//周囲8方向について実行
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (i == 0 && j == 0) continue;
			num = countReversibleStones(board, me.playerId, x, y, i, j);

			//i,j方向にnum回分裏返す
			for (k = 1; k <= num; k++) {
				board[x + i*k][y + j*k] = me.playerId; //相手の石を裏返す
			}
		}
	}
	board[x][y] = me.playerId;  //自分の石を置く

}


//1回のゲームを行う
void play(player p1, player p2) {
	
	p1.playerId = 1;
	p2.playerId = 2;

	int p1Score = 0;
	int	p2Score = 0;

	player tmp; //一時的に使用
	int i, j;

	//最初に石を置くプレーヤーと,その相手
	player currentPlayer = p1; //コピー
	player opponentPlayer = p2;
	
	//盤面を初期化
	int board[10][10] = {
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1 },
		{ -1,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0, -1 },
		{ -1,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,2,1,0,0,0,-1 },
		{ -1,0,0,0,1,2,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,-1 },
		{ -1,0,0,0,0,0,0,0,0,-1 },
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1 }
	};

	//プレーヤーの各ターン

	int placeNums[64] = { 0 };

	while (1) {
		int placeNums[64] = { 0 };
		dispBoard(board); //盤面を表示

		//currentPlayerの石を置く場所がない場合
		if (!scanPlaced(placeNums,board,currentPlayer.playerId)){
			fprintf_s(stdout, "%sさんの石を置けるマスがありません,パスします\n", currentPlayer.name);

			//更に、相手も石を置けない場合
			if (!scanPlaced(placeNums, board, opponentPlayer.playerId)) {
				break; //ループを出る（ゲーム終了）
			}
			//攻守の入れ替え
			tmp = currentPlayer;
			currentPlayer = opponentPlayer;
			opponentPlayer = tmp;
			
		}


		//
		fprintf_s(stdout, "%s(%s)さんの番です [ ", currentPlayer.name,currentPlayer.stoneSymbol);
		int ptr = 0;
		while (placeNums[ptr] != 0) {
			fprintf_s(stdout, "%d ", placeNums[ptr]);
			ptr++;
		}
		fprintf_s(stdout, "] の中から置く場所を選択してください");
		int selectedPlace = getPlayerInput(board, currentPlayer); //currentPlayerの入力を受ける
		putAndReverse(board, currentPlayer, opponentPlayer, selectedPlace / 10, selectedPlace % 10); //相手の石を裏返す
		
		//攻守の入れ替え
		tmp = currentPlayer;
		currentPlayer = opponentPlayer;
		opponentPlayer = tmp;
	}

	for (i = 1; i < 9; i++) {
		for (j = 1; j < 9; j++) {
			if (board[i][j] == 1) {
				p1Score += 1;
			}
			else if (board[i][j] == 2) {
				p2Score += 1;
			}
		}
	}
	
	fprintf_s(stdout, "ゲーム終了!\n【対戦結果】○=%d, ●=%d",p1Score,p2Score);

}



int main()
{
	//プレーヤの名前をゲット
	player p1;
	p1.name = "player1";
	p1.stoneSymbol = "○";
	

	player p2;
	p2.name = "player2";
	p2.stoneSymbol = "●";
	
	
	play(p1,p2);
	
    return 0;
}

