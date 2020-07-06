#include "stdafx.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




//�Ֆʂ�\������֐��i�܂��A�����ŗ^����ꂽ�ϐ��ɂ��������̂��������ށj
void dispBoard(int board[10][10], char stream[1024]) {
	int i, j; //�C���f�b�N�X
	char str[1024] = " 1 2 3 4 5 6 7 8"; //�o�͗p
	for (i = 0; i < 8; i++) {
		char tmp[1024];
		sprintf_s(tmp, "\n%d", i + 1);

		for (j = 0; j < 8; j++) {
			switch (board[i + 1][j + 1]) {
			case 0:
				strcat_s(tmp, "�E"); //tmp��"�E"������
				break;

			case 1:
				strcat_s(tmp, "��");
				break;

			case 2:
				strcat_s(tmp, "��");
				break;
			}
		}
		strcat_s(str, tmp); //"\n1�E�E�E�E�E�E�E�E"�̌`��8�񌋍�
	}
	strcat_s(str, "\n"); //�Ō�ɉ��s
	fprintf_s(stdout, str); //�\��
	strcpy_s(stream, 1024, str); //��������R�s�[

}


//x,y�ɒu�����Ƃ�,player��p,q�����ɗ��Ԃ��\�Ȑ΂̌���Ԃ��֐�(player�ԍ��͐Δԍ��Ɉ�v)
int countReversibleStones(int board[10][10], int playerId, int x, int y, int p, int q) {
	int opponent = 3 - playerId; //����̔ԍ��Ȃ̂�,1�̏ꍇ2,2�̏ꍇ1

	int cnt;

	//���ɐ΂��u����Ă���ꍇ
	if (board[x][y] != 0) {
		return 0;
	}

	//�G�̐΂��������J��Ԃ��i�[�_��-1�ƂȂ肻���ŏI���j
	for (cnt = 1; board[x + p*cnt][y + q*cnt] == opponent; cnt++) {}

	//�[�������̐΂ł���ꍇ
	if (board[x + p*cnt][y + q*cnt] == playerId) {
		return cnt - 1;

	}
	//�[�������̐΂łȂ��i-1�́j�ꍇ
	else {
		return 0;
	}
}


//player��x,y�ɐ΂�u���邩�ǂ���
bool isPlaced(int board[10][10], int playerId, int x, int y) {
	bool result = false;
	int i, j;

	//����8�����𒲂ׂ�
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (i == 0 && j == 0) continue;
			if (countReversibleStones(board, playerId, x, y, i, j) > 0) result = true;
		}
	}

	return result;
}



//player�ɂƂ��Đ΂��u����ꏊ��T���āA�ꏊ�ԍ����������z��i�����j������������B�܂��A1�ł��u����Ȃ�true��Ԃ�
bool scanPlaced(int placeNums[64], int board[10][10], int playerId) {
	int ptr = 0;
	int i, j;
	bool result = false;
	for (i = 1; i < 9; i++) {
		for (j = 1; j < 9; j++) {
			if (isPlaced(board, playerId, i, j)) {
				placeNums[ptr] = 10 * i + j;
				ptr += 1;
				if (!result) result = true;
			}
		}
	}

	return result;
}



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


//�΂�u���đ���̐΂𗠕Ԃ�
void putAndReverse(int board[10][10], player me, player opponent, int x, int y) {
	int i, j, k, num;

	//����8�����ɂ��Ď��s
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (i == 0 && j == 0) continue;
			num = countReversibleStones(board, me.playerId, x, y, i, j);

			//i,j������num�񕪗��Ԃ�
			for (k = 1; k <= num; k++) {
				board[x + i*k][y + j*k] = me.playerId; //����̐΂𗠕Ԃ�
			}
		}
	}
	board[x][y] = me.playerId;  //�����̐΂�u��

}





