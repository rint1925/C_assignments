// player.cpp : プレイヤに関する関数を集めたプログラム

#include "stdafx.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//プレイヤーの入力を受け取って、11~88の値を返す
int getPlayerInput(int board[10][10], player p) {

	int placeNum;
	int x, y;

	//fprintf_s(stdout, "%sさんの手を入力してください",p.name);
	while (1) {
		fprintf_s(stdout, " >>>");
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