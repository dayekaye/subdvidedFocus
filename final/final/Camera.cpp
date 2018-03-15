#include "Camera.h"

Camera::Camera() {
	eye = vec4(0, 2, 0, 0);
	n = vec4(0, 0, 1, 0);
	v = vec4(0, 1, 0, 0);
	u = vec4(1, 0, 0, 0);
	cameraMatrix = LookAt(eye, eye - n, v);
}

void Camera::changeProjection(int width, int height) {
	GLfloat fov = 65;
	GLfloat nearp = 1.0;
	GLfloat farp = 100.0;
	mat4 proj = Perspective(fov, GLfloat(width) / height, nearp, farp);
	setProjection(proj);
}

void Camera::positionCamera(vec4 ei, vec4 ni, vec4 vi, vec4 ui) {
	eye = ei;
	n = ni;
	v = vi;
	u = ui;
	cameraMatrix = LookAt(eye, eye - n, v);
}

void Camera::setCoords(vec4 vrp, vec4 normal, vec4 viewUp) {
	eye = vrp;
	at = normal;
	up = viewUp;

	cameraMatrix = LookAt(eye, at, up);
}


//called with parameters based on keyboard input.  
void Camera::moveZCamera(float z) {

	if (z > 0) {
		eye = eye + n;
		at = eye - n;
		up = v;
	}
	else {
		eye = eye - n;
		at = eye - n;
		up = v;
	}


	cameraMatrix = LookAt(eye, at, up);
	setCameraMatrix(cameraMatrix);

	glutPostRedisplay();

}

void Camera::moveXCamera(float x) {

	if (x > 0) {
		eye = eye + u;
		at = eye - n;
		up = v;
	}
	else {
		eye = eye - u;
		at = eye - n;
		up = v;
	}


	cameraMatrix = LookAt(eye, at, up);
	setCameraMatrix(cameraMatrix);
	glutPostRedisplay();

}

void Camera::pitchCamera(float theta) {

	theta *= DegreesToRadians;
	vec4 vp = cos(theta) * v - sin(theta) * n;
	vec4 np = sin(theta) * v + cos(theta) * n;

	v = vp;
	n = np;

	at = eye - np;
	up = vp;

	cameraMatrix = LookAt(eye, at, up);
	setCameraMatrix(cameraMatrix);
	glutPostRedisplay();

}

void Camera::rollCamera(float theta) {

	theta *= DegreesToRadians;
	vec4 vp = cos(theta) * u - sin(theta) * v;
	vec4 uprime = sin(theta) * u + cos(theta) * v;

	v = vp;
	u = uprime;

	at = eye - n;
	up = vp;

	cameraMatrix = LookAt(eye, at, up);
	setCameraMatrix(cameraMatrix);
	glutPostRedisplay();

}


void Camera::yawCamera(float theta) {

	theta *= DegreesToRadians;
	vec4 uprime = cos(theta) * u + sin(theta) * n;
	vec4 np = -sin(theta) * u + cos(theta) * n;

	u = uprime;
	n = np;

	at = eye - n;

	cameraMatrix = LookAt(eye, at, up);
	setCameraMatrix(cameraMatrix);
	glutPostRedisplay();

}