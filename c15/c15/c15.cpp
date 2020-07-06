// c15.cpp : オセロゲームのメインプログラム

#include "stdafx.h"
#include "Setting.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//1回のゲームを行う
void play(player p1, player p2) {

	p1.playerId = 1;
	p2.playerId = 2;

	int p1Score = 0;
	int	p2Score = 0;

	//一時的に使用
	player tmp;
	char txtBuf[1024];
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


	//ファイル書き込み準備
	FILE *fp;
	errno_t error = fopen_s(&fp, "gameLog.txt", "w");



	//プレーヤーの各ターン
	int placeNums[64] = { 0 };



	while (1) {
		int placeNums[64] = { 0 };
		dispBoard(board, txtBuf); //盤面を表示
		fputs(txtBuf, fp);

		//currentPlayerの石を置く場所がない場合
		if (!scanPlaced(placeNums, board, currentPlayer.playerId)) {
			sprintf_s(txtBuf, "%sさんの石を置けるマスがありません,パスします\n", currentPlayer.name);
			fprintf_s(stdout, txtBuf);
			fputs(txtBuf, fp);

			//更に、相手も石を置けない場合
			if (!scanPlaced(placeNums, board, opponentPlayer.playerId)) {
				break; //ループを出る（ゲーム終了）
			}
			//攻守の入れ替え
			tmp = currentPlayer;
			currentPlayer = opponentPlayer;
			opponentPlayer = tmp;

		}


		//石が置ける場合
		sprintf_s(txtBuf, "\n%s(%s)さんの番です  ", currentPlayer.name, currentPlayer.stoneSymbol);
		fprintf_s(stdout, txtBuf);
		fputs(txtBuf, fp);

		int ptr = 0;
		while (placeNums[ptr] != 0) {
			fprintf_s(stdout, "%d ", placeNums[ptr]);
			ptr++;
		}
		fprintf_s(stdout, "  の中から置く場所を選択してください");
		int selectedPlace = getPlayerInput(board, currentPlayer); //currentPlayerの入力を受ける
		sprintf_s(txtBuf, "%s(%s)さんの入力>>>%d\n", currentPlayer.name, currentPlayer.stoneSymbol, selectedPlace);
		fputs(txtBuf, fp);
		putAndReverse(board, currentPlayer, opponentPlayer, selectedPlace / 10, selectedPlace % 10); //相手の石を裏返す

																									 //攻守の入れ替え
		tmp = currentPlayer;
		currentPlayer = opponentPlayer;
		opponentPlayer = tmp;
	}


	//スコア計算
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

	//終了時テキスト
	sprintf_s(txtBuf, "ゲーム終了!\n【対戦結果】○=%d, ●=%d\n", p1Score, p2Score);
	fprintf_s(stdout, txtBuf);
	fputs(txtBuf, fp);
	fclose(fp);
}



int main()
{
	//プレーヤの初期化
	player p1;
	p1.stoneSymbol = "○";

	player p2;
	p2.stoneSymbol = "●";


	//名前の取得
	char currentDirectory[BUFFLENGTH];
	getCurrentDirectory(currentDirectory);
	char section[BUFFLENGTH];
	sprintf_s(section, "names");
	char keyWord[BUFFLENGTH];
	sprintf_s(keyWord, "player1");
	char settingFile[BUFFLENGTH];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	char p1Name[BUFFLENGTH];
	readChar(section, keyWord, "none", p1Name, settingFile);
	p1.name = p1Name;
	sprintf_s(keyWord, "player2");
	char p2Name[BUFFLENGTH];
	readChar(section, keyWord, "none", p2Name, settingFile);
	p2.name = p2Name;

	//ループ
	while (1) {
		int flag;
		fprintf_s(stdout, "オセロゲームへようこそ！\n現在の設定は【先攻】%sさん、【後攻】%sさんです\n[1]ゲーム開始, [２]先攻後攻を逆にしてゲーム開始 >>>",p1.name,p2.name);
		scanf_s("%d", &flag);
		fprintf_s(stdout, "\n");

		if (flag == 1) {
			play(p1, p2);
		}
		else if (flag == 2) {
			play(p2, p1);
		}else {
			break;
		}

	}
	
    return 0;
}

