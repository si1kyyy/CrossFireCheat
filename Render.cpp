#pragma once
#include "Render.h"

void Render::DrStartDraw() {
	Api_DwmDrStartDraw();
}
void Render::DrEndDraw() {
	Api_DwmDrEndDraw();
}
void Render::DrDrawText(float x, float y, float r, float g, float b, float a, const char* text) {
	Api_DwmDrDrawString(x,y,r,g,b,a,text);
}
void Render::DrDrawStrokeText(float X, float Y, float R, float G, float B, float A, float R1, float G1, float B1, float A1, const char* text) {
	Api_DwmDrDrawStrokeText(X,Y,R,G,B,A,R1,G1,B1,A1,text);
}
void Render::DrDrawBoxEx(float X, float Y, float W, float H, float R, float G, float B, float A, int T) {
	Api_DwmDrDrawBox(X,Y,W,H,R,G,B,A,T);
}

