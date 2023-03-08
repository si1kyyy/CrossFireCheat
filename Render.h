#pragma once
#include "global.hpp"


class Render
{
private:




public:
	void DrStartDraw();
	void DrEndDraw();

	void DrDrawText(float x, float y, float r, float g, float b, float a, const char* text);
	void DrDrawStrokeText(float X, float Y, float R, float G, float B, float A, float R1, float G1, float B1, float A1, const char* text);
	void DrDrawBoxEx(float X, float Y, float W, float H, float R, float G, float B, float A, int T);

};

