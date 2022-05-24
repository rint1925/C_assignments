//Setting.cpp : iniファイルを扱うための関数を集めたプログラム

#include "stdafx.h"
#include "Setting.h"
#include <stdio.h>
#include <Windows.h>


//intを構成設定ファイルから読み込む
int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath) {
	int result;
	result = GetPrivateProfileInt(section, keyword, defaultValue, filePath);
	return result;
}

//文字列を読み込む
bool readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath) {
	if (GetPrivateProfileString(section, keyword, "none", returnValue, BUFFLENGTH, filePath)) {
		return true;
	}
	else {
		return false;
	}
}

//doubleを読み込む
double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath) {
	double result;
	char tmp[BUFFLENGTH];
	GetPrivateProfileString(section, keyword, "none", tmp, BUFFLENGTH, filePath);
	result = strtod(tmp, NULL);
	return result;
}

//現在のディレクトリを取得する
void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(BUFFLENGTH, currentDirectory);
}

//文字列を書きこむ
bool writeChar(const char *section, const char *keyword, const char *returnValue, const char *filePath) {
	if (WritePrivateProfileString(section, keyword, returnValue, filePath)) {
		return true;
	}
	else {
		return false;
	}
}

//intを書き込む
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

//doubleを書き込む
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