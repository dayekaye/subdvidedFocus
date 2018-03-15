#ifndef __QUADTEXTURED_H__
#define __QUADTEXTURED_H__

#include "Angel.h"
#include "Drawable.h"
#include "Light.h"
#include "Camera.h"
#include <vector>

class QuadTextured: public Drawable{  //derived from drawable class


public:	

	//constructors
	QuadTextured();

	//destructor
	~QuadTextured();

	void build();
	void draw(Camera, vector<Light>);

private:
	GLuint texture;

	vec4 vertexLocations[6];
	vec2 vertexTextureLocations[6];

	void makeQuad(vec4, vec4, vec4, vec4);

	unsigned int index;
	
	//uniform transformation matrix variable locations
	GLuint mmLoc, cmLoc, pmLoc;
	//uniform texture location
	GLuint tex_loc;
};
#endif
