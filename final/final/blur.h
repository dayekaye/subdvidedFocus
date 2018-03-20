#pragma once
#ifndef __BLUR_H__
#define __BLUR_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;
class Blur :public Drawable {
public:
	Blur();
	~Blur();
	int init(double amount);
	void blurX(float w, float h);
	void blurY(float w, float h);

	GLuint VAO;
	GLuint vert;
	GLuint frag_y;
	GLuint frag_x;
	GLuint prog_x;
	GLuint prog_y;
	GLint xtex_w;
	GLint xtex_h;
	GLint ytex_w;
	GLint ytex_h;
};
#endif