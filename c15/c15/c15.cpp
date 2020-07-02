// c15.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFLENGTH 1024

typedef struct player { char *name; char *stoneSymbol; int playerId;};

//�Ֆʂ�\������֐�
void dispBoard(int board[10][10]){
	int i, j; //�C���f�b�N�X
	char str[BUFFLENGTH] = " 1 2 3 4 5 6 7 8"; //�o�͗p
	for (i = 0; i < 8; i++) {
		char tmp[BUFFLENGTH];
		sprintf_s(tmp, "\n%d", i+1);

		for (j = 0; j < 8; j++) {
			switch (board[i+1][j+1]) {
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
	fprintf_s(stdout, str);
}


//x,y�ɒu�����Ƃ�,player��p,q�����ɗ��Ԃ��\�Ȑ΂̌���Ԃ��֐�(player�ԍ��͐Δԍ��Ɉ�v)
int countReversibleStones(int board[10][10],int playerId, int x, int y, int p, int q) {
	int opponent = 3 - playerId; //����̔ԍ��Ȃ̂�,1�̏ꍇ2,2�̏ꍇ1

	int cnt;

	//���ɐ΂��u����Ă���ꍇ
	if (board[x][y] != 0) {
		return 0;
	}

	//�G�̐΂��������J��Ԃ��i�[�_��-1�ƂȂ肻���ŏI���j
	for(cnt = 1; board[x + p*cnt][y + q*cnt] == opponent; cnt++){}

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



//�v���C���[�̓��͂��󂯎���āA11~88�̒l��Ԃ�
int getPlayerInput(int board[10][10], player p) {
	
	int placeNum;
	int x, y;

	//fprintf_s(stdout, "%s����̎����͂��Ă�������",p.name);
	while (1) {
		fprintf_s(stdout,">>>");
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


//1��̃Q�[�����s��
void play(player p1, player p2) {
	
	p1.playerId = 1;
	p2.playerId = 2;

	int p1Score = 0;
	int	p2Score = 0;

	player tmp; //�ꎞ�I�Ɏg�p
	int i, j;

	//�ŏ��ɐ΂�u���v���[���[��,���̑���
	player currentPlayer = p1; //�R�s�[
	player opponentPlayer = p2;
	
	//�Ֆʂ�������
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

	//�v���[���[�̊e�^�[��

	int placeNums[64] = { 0 };

	while (1) {
		int placeNums[64] = { 0 };
		dispBoard(board); //�Ֆʂ�\��

		//currentPlayer�̐΂�u���ꏊ���Ȃ��ꍇ
		if (!scanPlaced(placeNums,board,currentPlayer.playerId)){
			fprintf_s(stdout, "%s����̐΂�u����}�X������܂���,�p�X���܂�\n", currentPlayer.name);

			//�X�ɁA������΂�u���Ȃ��ꍇ
			if (!scanPlaced(placeNums, board, opponentPlayer.playerId)) {
				break; //���[�v���o��i�Q�[���I���j
			}
			//�U��̓���ւ�
			tmp = currentPlayer;
			currentPlayer = opponentPlayer;
			opponentPlayer = tmp;
			
		}


		//
		fprintf_s(stdout, "%s(%s)����̔Ԃł� [ ", currentPlayer.name,currentPlayer.stoneSymbol);
		int ptr = 0;
		while (placeNums[ptr] != 0) {
			fprintf_s(stdout, "%d ", placeNums[ptr]);
			ptr++;
		}
		fprintf_s(stdout, "] �̒�����u���ꏊ��I�����Ă�������");
		int selectedPlace = getPlayerInput(board, currentPlayer); //currentPlayer�̓��͂��󂯂�
		putAndReverse(board, currentPlayer, opponentPlayer, selectedPlace / 10, selectedPlace % 10); //����̐΂𗠕Ԃ�
		
		//�U��̓���ւ�
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
	
	fprintf_s(stdout, "�Q�[���I��!\n�y�ΐ팋�ʁz��=%d, ��=%d",p1Score,p2Score);

}



int main()
{
	//�v���[���̖��O���Q�b�g
	player p1;
	p1.name = "player1";
	p1.stoneSymbol = "��";
	

	player p2;
	p2.name = "player2";
	p2.stoneSymbol = "��";
	
	
	play(p1,p2);
	
    return 0;
}

