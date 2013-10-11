//info on file streams from http://www.cplusplus.com/reference/fstream/fstream/open/

#include <iostream>
#include <fstream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <math.h>
#include "Light.h"
#include "Mars.h"
#include "Spaceship.h"
#include "Starfield.h"

using namespace std;
using namespace glm;

void DisplayFunc()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


	//draw our objects

	glutSwapBuffers();
}

void ReshapeFunc(int w, int h)
{

}

void CloseFunc()
{
	glutLeaveMainLoop();
}

void KeyboardFunc(unsigned char c, int x, int y)
{

}

void SpecialFunc(int key, int x, int y)
{

}

void TimerFunc(int value)
{
	glutPostRedisplay();
}

bool InitializeGL()
{
	return true;
}

int main(int argc, char * argv[])
{
	//set up some constants
	static const double light_distance = 80.0;

	//make sure we have a filename in argv! argc must equal 2
	if(argc != 2){
		cout << "Don't forget to specify a Mars data file! Good luck next time!" << endl;
		CloseFunc();
		return -1;
	}

	//initialize and set options
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutSetOption(GLUT_RENDERING_CONTEXT, GLUT_USE_CURRENT_CONTEXT);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	//create our window and set up callbacks
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1366, 768);
	glutCreateWindow("MARS");
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutCloseFunc(CloseFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);

	//make sure GL was initialized!
	if(!InitializeGL())
	{
		CloseFunc();
		return -1;
	}

	//here we create our objects!

	//our file! open in read mode only!
	fstream marsfs;
	marsfs.open(argv[1], fstream::in);

	
	//our light
	Light::lightInfo ourLight_info =
	{
	vec4(0.0f, 0.0f, light_distance, 1.0f), //distance
	vec3(0.9f, 0.9f, 0.9), //intensity
	vec3(0.6f, 0.6f, 0.6f), //diffuse
	vec3(0.6f, 0.6f, 0.6f), //ambient
	vec3(0.3f, 0.3f, 0.3f), //specular
	20.0f //the exponent in the specular equation!
	};
	Light ourLight = Light(ourLight_info);
	
	//our planet
	Mars mars = Mars();

	//our ship
	Spaceship ship = Spaceship();

	//our starfield
	Starfield stars = Starfield();

	//enter the main loop!
	glutMainLoop();
	return 0;

}