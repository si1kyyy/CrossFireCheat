#pragma once
#include "global.hpp"

class Tool
{

public:
	CHAR* GetSelfPhyPath();
	void Log(const char* msg,LONG code);

	float Calc_q0(float z, float y, float x);
	float Calc_q1(float z, float y, float x);
	float Calc_q2(float z, float y, float x);
	float Calc_q3(float z, float y, float x);

	double 三角函数_求正弦值(double 角度);
	double 三角函数_求余弦值(double 角度);
};

