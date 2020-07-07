// player.cpp : �v���C���Ɋւ���֐����W�߂��v���O����

#include "stdafx.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�v���C���[�̓��͂��󂯎���āA11~88�̒l��Ԃ�
int getPlayerInput(int board[10][10], player p) {

	int placeNum;
	int x, y;

	//fprintf_s(stdout, "%s����̎����͂��Ă�������",p.name);
	while (1) {
		fprintf_s(stdout, " >>>");
		scanf_s("%d", &placeNum);

		if (placeNum < 11 || placeNum >88) {
			fprintf_s(stdout, "11����88�̒l����͂��Ă�������");
			continue;
		}

		x = placeNum / 10;
		y = placeNum % 10;

		if (isPlaced(board, p.playerId, x, y)) {
			return placeNum;
		}
		else {
			fprintf_s(stdout, "���̏ꏊ�ɂ͐΂�u���܂���.���̏ꏊ���w�肵�Ă�������");
			continue;
		}

	}
}