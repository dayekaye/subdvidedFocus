#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "Angel.h"

class Camera {
public:
	Camera();
	mat4 getCameraMatrix() const { return cameraMatrix; }
	mat4 getProjectionMatrix() const { return projectionMatrix; }
	void positionCamera(vec4, vec4, vec4, vec4);
	void setProjection(mat4 p) { projectionMatrix = p; }
	void setCameraMatrix(mat4 c) { cameraMatrix = c; }
	void changeProjection(int width, int height);
	void moveZCamera(float z);
	void moveXCamera(float x);
	void pitchCamera(float theta);
	void rollCamera(float theta);
	void yawCamera(float theta);
	void setCoords(vec4 vrp, vec4 normal, vec4 viewUp);
private:
	vec4 eye, u, v, n, at, up;
	mat4 cameraMatrix, projectionMatrix;
};

#endif