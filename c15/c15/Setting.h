#pragma once
#define BUFFLENGTH 128

//int���\���ݒ�t�@�C������ǂݍ���
int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath);

//�������ǂݍ���
bool readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath);

//double��ǂݍ���
double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath);

//���݂̃f�B���N�g�����擾����
void getCurrentDirectory(char *currentDirectory);

//���������������
bool writeChar(const char *section, const char *keyword, const char *returnValue, const char *filePath);

//int����������
bool writeInt(const char *section, const char *keyword, int returnValue, const char *filePath);

//double����������
bool writeDouble(const char *section, const char *keyword, double returnValue, const char *filePath);