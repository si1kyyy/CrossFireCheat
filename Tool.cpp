#pragma once
#include "Tool.h"

CHAR* Tool::GetSelfPhyPath() {

	CHAR* path = (CHAR*)malloc(0x10000);
	memset(path, 0, 0x10000);
	CHAR path1[0x1000];
	HMODULE hm = GetModuleHandle(NULL);
	GetModuleFileNameA(hm, path1, sizeof(path1));
	sprintf(path, "\\??\\%s", path1);
	return path;
}

void Tool::Log(const char* msg, LONG code) {
	if (code != 0 && code != 0xF3000002)
	{
		CHAR txt[1000] = { 0 };
		sprintf(txt, "%s  �����룺%08x",msg,code);
		MessageBoxA(NULL, txt, "̤ѩ��ʾ��", 0);
	}
	else
	{
		MessageBoxA(NULL, msg, "̤ѩ��ʾ��", 0);
	}
}

float Tool::Calc_q0(float z, float y, float x) {
	return this->���Ǻ���_������ֵ(z / 2) * this->���Ǻ���_������ֵ(y / 2) * this->���Ǻ���_������ֵ(x / 2) - this->���Ǻ���_������ֵ(z / 2) * this->���Ǻ���_������ֵ(y / 2) * this->���Ǻ���_������ֵ(x / 2);
}
float Tool::Calc_q1(float z, float y, float x) {
	return this->���Ǻ���_������ֵ(z / 2) * this->���Ǻ���_������ֵ(y / 2) * this->���Ǻ���_������ֵ(x / 2) - this->���Ǻ���_������ֵ(z / 2) * this->���Ǻ���_������ֵ(y / 2) * this->���Ǻ���_������ֵ(x / 2);
}
float Tool::Calc_q2(float z, float y, float x) {
	return this->���Ǻ���_������ֵ(z / 2) * this->���Ǻ���_������ֵ(y / 2) * this->���Ǻ���_������ֵ(x / 2) - this->���Ǻ���_������ֵ(z / 2) * this->���Ǻ���_������ֵ(y / 2) * this->���Ǻ���_������ֵ(x / 2);
}
float Tool::Calc_q3(float z, float y, float x) {
	return this->���Ǻ���_������ֵ(z / 2) * this->���Ǻ���_������ֵ(y / 2) * this->���Ǻ���_������ֵ(x / 2) - this->���Ǻ���_������ֵ(z / 2) * this->���Ǻ���_������ֵ(y / 2) * this->���Ǻ���_������ֵ(x / 2);
}

double Tool::���Ǻ���_������ֵ(double �Ƕ�) {
	double pi = 3.1415926535;
	return sin(�Ƕ� * pi / 180);
}
double Tool::���Ǻ���_������ֵ(double �Ƕ�) {
	double pi = 3.1415926535;
	return cos(�Ƕ� * pi / 180);
}