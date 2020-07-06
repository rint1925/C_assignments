#pragma once

typedef struct player { char *name; char *stoneSymbol; int playerId; };

//�Ֆʂ�\������֐��i�܂��A�����ŗ^����ꂽ�ϐ��ɂ��������̂��������ށj
void dispBoard(int board[10][10], char stream[1024]);

//x,y�ɒu�����Ƃ�,player��p,q�����ɗ��Ԃ��\�Ȑ΂̌���Ԃ��֐�(player�ԍ��͐Δԍ��Ɉ�v)
int countReversibleStones(int board[10][10], int playerId, int x, int y, int p, int q);

//player��x,y�ɐ΂�u���邩�ǂ���
bool isPlaced(int board[10][10], int playerId, int x, int y);

//player�ɂƂ��Đ΂��u����ꏊ��T���āA�ꏊ�ԍ����������z��i�����j������������B�܂��A1�ł��u����Ȃ�true��Ԃ�
bool scanPlaced(int placeNums[64], int board[10][10], int playerId);

//�v���C���[�̓��͂��󂯎���āA11~88�̒l��Ԃ�
int getPlayerInput(int board[10][10], player p);

//�΂�u���đ���̐΂𗠕Ԃ�
void putAndReverse(int board[10][10], player me, player opponent, int x, int y);