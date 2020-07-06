//Setting.cpp : ini�t�@�C�����������߂̊֐����W�߂��v���O����

#include "stdafx.h"
#include "Setting.h"
#include <stdio.h>
#include <Windows.h>


//int���\���ݒ�t�@�C������ǂݍ���
int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath) {
	int result;
	result = GetPrivateProfileInt(section, keyword, defaultValue, filePath);
	return result;
}

//�������ǂݍ���
bool readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath) {
	if (GetPrivateProfileString(section, keyword, "none", returnValue, BUFFLENGTH, filePath)) {
		return true;
	}
	else {
		return false;
	}
}

//double��ǂݍ���
double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath) {
	double result;
	char tmp[BUFFLENGTH];
	GetPrivateProfileString(section, keyword, "none", tmp, BUFFLENGTH, filePath);
	result = strtod(tmp, NULL);
	return result;
}

//���݂̃f�B���N�g�����擾����
void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(BUFFLENGTH, currentDirectory);
}

//���������������
bool writeChar(const char *section, const char *keyword, const char *returnValue, const char *filePath) {
	if (WritePrivateProfileString(section, keyword, returnValue, filePath)) {
		return true;
	}
	else {
		return false;
	}
}

//int����������
bool writeInt(const char *section, const char *keyword, int returnValue, const char *filePath) {
	char result[BUFFLENGTH];
	sprintf_s(result, "%d", returnValue);
	if (WritePrivateProfileString(section, keyword, result, filePath)) {
		return true;
	}
	else {
		return false;
	}
}

//double����������
bool writeDouble(const char *section, const char *keyword, double returnValue, const char *filePath) {
	char result[BUFFLENGTH];
	sprintf_s(result, "%lf", returnValue);
	if (WritePrivateProfileString(section, keyword, result, filePath)) {
		return true;
	}
	else {
		return false;
	}
}