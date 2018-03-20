#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>

using namespace std;
class Sphere :public Drawable {
public:
	Sphere();
	void draw(Camera, vector<Light>);
	~Sphere();
	void setMaterial(vec4, vec4, vec4, float);

private:
	//(4 triangular faces per tetrahedron)^(numDivisions+1)*3 vertices per triangle
	static const unsigned int numVertices = 3072;
	void build();
	void buildTriangle(const vec4& a, const vec4& b, const vec4& c);
	GLuint vPosition, vNormal;
	
	
	vec4 vertexLocations[numVertices];
	vec3 vertexNormals[numVertices];

	//materials
	vec4 matDiffuse, matSpecular, matAmbient;
	float shininess;

	//uniform transformation matrix variable locations
	GLuint mmLoc, cmLoc, pmLoc;
	//uniform material variables
	GLuint maLoc, msLoc, mdLoc, mAlphaLoc;
	//uniform light variables
	GLuint laLoc, lsLoc, ldLoc, lpLoc;

	//helper stuff
	unsigned int index;
	float sqrt2, sqrt6;
	void tetrahedron(int);
	void divideTriangle(const vec4&, const vec4&, const vec4&, int);
	void triangle(const vec4&, const vec4&, const vec4&);
	vec4 unit(const vec4&);
};
#endif