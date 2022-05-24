#pragma once
#define BUFFLENGTH 128

//intを構成設定ファイルから読み込む
int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath);

//文字列を読み込む
bool readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath);

//doubleを読み込む
double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath);

//現在のディレクトリを取得する
void getCurrentDirectory(char *currentDirectory);

//文字列を書きこむ
bool writeChar(const char *section, const char *keyword, const char *returnValue, const char *filePath);

//intを書き込む
bool writeInt(const char *section, const char *keyword, int returnValue, const char *filePath);

//doubleを書き込む
bool writeDouble(const char *section, const char *keyword, double returnValue, const char *filePath);