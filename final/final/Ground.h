#ifndef __GROUND_H__
#define __GROUND_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>

using namespace std;

class Ground : public Drawable {


public:
	Ground();
	~Ground();
	void draw(Camera, vector<Light>);
	void setMaterial(vec4, vec4, vec4, float);


private:
	void buildGround();
	void makeQuad(int, int, int, int);

	vec4 vertexLocations[6];
	vec3 vertexNormals[6];

	//materials
	vec4 matDiffuse, matSpecular, matAmbient;
	float shininess;

	//uniform transformation matrix variable locations
	GLuint mmLoc, cmLoc, pmLoc;
	//uniform material variables
	GLuint maLoc, msLoc, mdLoc, mAlphaLoc;
	//uniform light variables
	GLuint laLoc, lsLoc, ldLoc, lpLoc;

	unsigned int index;

	vec4 vertices[4] = { vec4(-0.5,-0.5,0.5,1),vec4(-0.5,0.5,0.5,1),vec4(0.5,0.5,0.5,1),vec4(0.5,-0.5,0.5,1)};

};
#endif
#pragma once
