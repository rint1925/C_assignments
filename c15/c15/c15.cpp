// c15.cpp : �I�Z���Q�[���̃��C���v���O����

#include "stdafx.h"
#include "Setting.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//1��̃Q�[�����s��
void play(player p1, player p2) {

	p1.playerId = 1;
	p2.playerId = 2;

	int p1Score = 0;
	int	p2Score = 0;

	//�ꎞ�I�Ɏg�p
	player tmp;
	char txtBuf[1024];
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


	//�t�@�C���������ݏ���
	FILE *fp;
	errno_t error = fopen_s(&fp, "gameLog.txt", "w");



	//�v���[���[�̊e�^�[��
	int placeNums[64] = { 0 };



	while (1) {
		int placeNums[64] = { 0 };
		dispBoard(board, txtBuf); //�Ֆʂ�\��
		fputs(txtBuf, fp);

		//currentPlayer�̐΂�u���ꏊ���Ȃ��ꍇ
		if (!scanPlaced(placeNums, board, currentPlayer.playerId)) {
			sprintf_s(txtBuf, "%s����̐΂�u����}�X������܂���,�p�X���܂�\n", currentPlayer.name);
			fprintf_s(stdout, txtBuf);
			fputs(txtBuf, fp);

			//�X�ɁA������΂�u���Ȃ��ꍇ
			if (!scanPlaced(placeNums, board, opponentPlayer.playerId)) {
				break; //���[�v���o��i�Q�[���I���j
			}
			//�U��̓���ւ�
			tmp = currentPlayer;
			currentPlayer = opponentPlayer;
			opponentPlayer = tmp;

		}


		//�΂��u����ꍇ
		sprintf_s(txtBuf, "\n%s(%s)����̔Ԃł�  ", currentPlayer.name, currentPlayer.stoneSymbol);
		fprintf_s(stdout, txtBuf);
		fputs(txtBuf, fp);

		int ptr = 0;
		while (placeNums[ptr] != 0) {
			fprintf_s(stdout, "%d ", placeNums[ptr]);
			ptr++;
		}
		fprintf_s(stdout, "  �̒�����u���ꏊ��I�����Ă�������");
		int selectedPlace = getPlayerInput(board, currentPlayer); //currentPlayer�̓��͂��󂯂�
		sprintf_s(txtBuf, "%s(%s)����̓���>>>%d\n", currentPlayer.name, currentPlayer.stoneSymbol, selectedPlace);
		fputs(txtBuf, fp);
		putAndReverse(board, currentPlayer, opponentPlayer, selectedPlace / 10, selectedPlace % 10); //����̐΂𗠕Ԃ�

																									 //�U��̓���ւ�
		tmp = currentPlayer;
		currentPlayer = opponentPlayer;
		opponentPlayer = tmp;
	}


	//�X�R�A�v�Z
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

	//�I�����e�L�X�g
	sprintf_s(txtBuf, "�Q�[���I��!\n�y�ΐ팋�ʁz��=%d, ��=%d\n", p1Score, p2Score);
	fprintf_s(stdout, txtBuf);
	fputs(txtBuf, fp);
	fclose(fp);
}



int main()
{
	//�v���[���̏�����
	player p1;
	p1.stoneSymbol = "��";

	player p2;
	p2.stoneSymbol = "��";


	//���O�̎擾
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

	//���[�v
	while (1) {
		int flag;
		fprintf_s(stdout, "�I�Z���Q�[���ւ悤�����I\n���݂̐ݒ�́y��U�z%s����A�y��U�z%s����ł�\n[1]�Q�[���J�n, [�Q]��U��U���t�ɂ��ăQ�[���J�n >>>",p1.name,p2.name);
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

