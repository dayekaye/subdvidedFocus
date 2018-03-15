#ifndef __CUBE_H__
#define __CUBE_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>

using namespace std;

class Cube: public Drawable{


public:
	Cube();
	~Cube();
	void draw(Camera, vector<Light>);
	void setMaterial(vec4, vec4, vec4, float);

private:
	void buildCube();
	void makeQuad(int, int, int, int);
	//attribute data
	vec4 vertexLocations[36];
	vec3 vertexNormals[36];

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

	vec4 vertices[8] = { vec4(-0.5,-0.5,0.5,1),vec4(-0.5,0.5,0.5,1),vec4(0.5,0.5,0.5,1),vec4(0.5,-0.5,0.5,1),
						 vec4(-0.5,-0.5,-0.5,1),vec4(-0.5,0.5,-0.5,1),vec4(0.5,0.5,-0.5,1),vec4(0.5,-0.5,-0.5,1) };

	vec4 points[6 * 2 * 3]; //6 faces, 2 triangles/face, 3 vertices per triangle
};
#endif
