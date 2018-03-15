//TEXTURE MAPPING SAMPLE CODE

#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "QuadTextured.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Ground.h"
#include "Cube.h"

#define SPACEBAR 32

//Forward declarations
void init(void);
void display(void);
void keyboard(unsigned char, int, int);
//void mouse(int, int, int, int);
void resize(int width, int height);
void close(void);
void special(int key, int x, int y);
void close(void);
//void timerCallback(int value);


vector<Light> lights;
Camera cam;

QuadTextured *myQuad;
vector<Drawable*>drawables;

GLuint windowID = 0;

//----------------------------------------------------------------------------
int main( int argc, char **argv )
{
    glutInit( &argc, argv );	//initialize glut
#ifdef __APPLE__
    glutInitDisplayMode( GLUT_3_2_CORE_PROFILE|GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH);
#else
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH);
#endif
    glutInitWindowSize( 512, 512 );	//set window size to be 512x512 pixels

    windowID = glutCreateWindow( "Texture Mapping" );  //open a window with a title

	//initialize glew if necessary (don't need to on Macs)
	#ifndef __APPLE__
	GLenum err = glewInit();
	#endif

    init();  //do some initialize for our program

	//set up the callback functions
    glutDisplayFunc( display );  //REQUIRED.  What to do when it's time to draw
    glutKeyboardFunc( keyboard );  //What to do if a keyboard event is detected
	glutWMCloseFunc(close);
	glutReshapeFunc(resize);  //use for recomputing projection matrix on reshape
	glutSpecialFunc(special);
    glutMainLoop();  //start infinite loop, listening for events
    return 0;
}


//Initialization
void init()
{
	//set up the camera
	cam.positionCamera(vec4(0, 2, 0, 1), vec4(0, 1, 0, 0), vec4(0, 0, -1, 0), vec4(1, 0, 0, 0));
	
	//set up the lights
	lights.push_back(Light(vec4(2, 1, 0, 1), vec4(1, 1, 1, 1), vec4(0.2f, 0.2f, 0.2f, 1), vec4(1, 1, 1, 1)));  //the light

	//make a triangle and set its material
	myQuad = new QuadTextured();
	drawables.push_back(myQuad);
	
	glEnable(GL_DEPTH_TEST); //since we're doing 3D graphics, enable the Z-buffer depth test
	
	//define color to use when color buffer is cleared
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  //clear out the color of the framebuffer and the depth info from the depth buffer
	
	for (unsigned int i = 0; i < drawables.size(); i++)
		drawables[i]->draw(cam, lights);
			
	glutSwapBuffers();
}

//----------------------------------------------------------------------------

void resize(int w, int h){
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	cam.setProjection(Perspective(65.0, GLfloat(w / h), 1.0, 100.0));
}

void keyboard(unsigned char key, int x, int y)
{
	bool camType = 0;
	switch (key) {
	case 033:  // Escape key
	case 'q': case 'Q':
		close();
		break;
	case SPACEBAR:
		//timerCallback(10);
		glutPostRedisplay();
		break;
	case 'x':
		cam.pitchCamera(5.0f);
		//msphere->setCameraMatrix(cam.cameramatrix);
		//mground->setCameraMatrix(cam.cameramatrix);
		break;
	case 'X':
		//rotate around u axis
		cam.pitchCamera(-5.0f);
		//msphere->setCameraMatrix(cam.cameramatrix);
		//mground->setCameraMatrix(cam.cameramatrix);
		break;
	case 'c':
		cam.yawCamera(5.0f);
		//msphere->setCameraMatrix(cam.cameramatrix);
		//mground->setCameraMatrix(cam.cameramatrix);
		break;
	case 'C':
		//rotate around v axis
		cam.yawCamera(-5.0f);
		//msphere->setCameraMatrix(cam.cameramatrix);
		//mground->setCameraMatrix(cam.cameramatrix);
		break;
	case 'z':
		cam.rollCamera(1.0f);
		//msphere->setCameraMatrix(cam.cameramatrix);
		//mground->setCameraMatrix(cam.cameramatrix);
		break;
	case 'Z':
		//rotate around n axis
		cam.rollCamera(-1.0f);
		//msphere->setCameraMatrix(cam.cameramatrix);
		//mground->setCameraMatrix(cam.cameramatrix);
		break;

	}
}

void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		//change position of camera on n axis
		cam.moveZCamera(.1);
		//cout << "moving camera forward" << endl;
		break;
	case GLUT_KEY_DOWN:
		//change position of camera on n axis
		cam.moveZCamera(-.1);
		//msphere->setCameraMatrix(cam.cameramatrix);
		//mground->setCameraMatrix(cam.cameramatrix);
		//cout << "moving camera backward" << endl;
		break;
	case GLUT_KEY_LEFT:
		//change position of camera on u axis
		cam.moveXCamera(.1);
		//msphere->setCameraMatrix(cam.cameramatrix);
		//mground->setCameraMatrix(cam.cameramatrix);
		//cout << "moving camera left" << endl;
		break;
	case GLUT_KEY_RIGHT:
		//change position of camera on u axis
		cam.moveXCamera(-.1);
		//msphere->setCameraMatrix(cam.cameramatrix);
		//mground->setCameraMatrix(cam.cameramatrix);
		//cout << "moving camera right" << endl;
		break;
	}
}
void close() {
	for (unsigned int i = 0; i < drawables.size(); i++)
		delete(drawables[i]);

	if (windowID>0)
		glutDestroyWindow(windowID);
	exit(EXIT_SUCCESS);
}

//----------------------------------------------------------------------------
