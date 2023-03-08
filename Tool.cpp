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
		sprintf(txt, "%s  错误码：%08x",msg,code);
		MessageBoxA(NULL, txt, "踏雪提示：", 0);
	}
	else
	{
		MessageBoxA(NULL, msg, "踏雪提示：", 0);
	}
}

float Tool::Calc_q0(float z, float y, float x) {
	return this->三角函数_求余弦值(z / 2) * this->三角函数_求余弦值(y / 2) * this->三角函数_求余弦值(x / 2) - this->三角函数_求正弦值(z / 2) * this->三角函数_求正弦值(y / 2) * this->三角函数_求正弦值(x / 2);
}
float Tool::Calc_q1(float z, float y, float x) {
	return this->三角函数_求余弦值(z / 2) * this->三角函数_求余弦值(y / 2) * this->三角函数_求正弦值(x / 2) - this->三角函数_求正弦值(z / 2) * this->三角函数_求正弦值(y / 2) * this->三角函数_求余弦值(x / 2);
}
float Tool::Calc_q2(float z, float y, float x) {
	return this->三角函数_求余弦值(z / 2) * this->三角函数_求正弦值(y / 2) * this->三角函数_求余弦值(x / 2) - this->三角函数_求正弦值(z / 2) * this->三角函数_求余弦值(y / 2) * this->三角函数_求正弦值(x / 2);
}
float Tool::Calc_q3(float z, float y, float x) {
	return this->三角函数_求正弦值(z / 2) * this->三角函数_求余弦值(y / 2) * this->三角函数_求余弦值(x / 2) - this->三角函数_求余弦值(z / 2) * this->三角函数_求正弦值(y / 2) * this->三角函数_求正弦值(x / 2);
}

double Tool::三角函数_求正弦值(double 角度) {
	double pi = 3.1415926535;
	return sin(角度 * pi / 180);
}
double Tool::三角函数_求余弦值(double 角度) {
	double pi = 3.1415926535;
	return cos(角度 * pi / 180);
}