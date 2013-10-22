//info on file streams from http://www.cplusplus.com/reference/fstream/fstream/open/
//CheckGLErrors based off of code from OGLTTA example
//also lots of general ideas taken from the OGLTTA example

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "Globals.h"
#include "Shader.h"
#include "Light.h"
#include "Mars.h"
#include "Spaceship.h"
#include "Starfield.h"


using namespace std;
using namespace glm;

// Is this the way to do it?
Globals globals = Globals();

void DrawAxes()
{
	glBegin(GL_LINES);
		glLineWidth(1.0);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 10.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 10.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
}

void DisplayFunc()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, (globals.wireframe_enabled == true) ? GL_LINE : GL_FILL);

	glViewport(0, 0, globals.window_size.x, globals.window_size.y);

	mat4 proj = perspective(globals.fov, globals.aspect_ratio, globals.near_plane, globals.far_plane);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(proj));

	mat4 mv(1.0f);
	//Temporary lookat
	mv = lookAt(vec3(20.0, 20.0, 20.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(mv));

	DrawAxes();

	//TEXT wait - can we do this with the oldschool opengl?
	glColor3f(.7f, .7f, .7f);
	mat4 orth = ortho(0.0f, (float)globals.window_size.x, 0.0f, (float)globals.window_size.y, 1.0f, 10.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(orth));

	// Look at the same place constantly, and shift the modelview matrix in front of the near plane
	mat4 text = lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	text = translate(text, vec3(0.0f, 5.0f, -1.0f));
	text = scale(text, vec3(.25f, .25f, .25f));
	glMatrixMode(GL_MODELVIEW);

	vector<string> * s = &globals.onscreen_text;
	for(auto i = s->begin(); i < s->end(); i++) {
		glLoadMatrixf(value_ptr(text));
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)(*i).c_str());
		text = translate(text, vec3(0.0f, glutStrokeHeight(GLUT_STROKE_MONO_ROMAN), 0.0f));
	}

	//Blatantly ripping off the structure of OGLTTA
	//Use an enum to go through the list of possible states

	
	glutSwapBuffers();
}

void ReshapeFunc(int w, int h)
{
	if(!globals.window_closed && h > 0) {
		globals.window_size = vec2(w, h);
		globals.aspect_ratio = (float)(w) / (float)(h);
		glutPostRedisplay();
	}
}

void CloseFunc()
{
	globals.window_closed = true;
	glutLeaveMainLoop();
}

void KeyboardFunc(unsigned char c, int x, int y)
{
	switch(c) {
		case 'x':
		case 27:
			CloseFunc();
			return;
	}
}

void SpecialFunc(int key, int x, int y)
{

}

void TimerFunc(int value)
{
	//check to make sure our window is still here before we redisplay?
	//perhaps?
	glutPostRedisplay();
}

int main(int argc, char * argv[])
{
	//set up some constants
	static const double light_distance = 80.0;

	/*
	//make sure we have a filename in argv! argc must equal 2
	if(argc != 2){
		cout << "Don't forget to specify a Mars data file! Good luck next time!" << endl;
		CloseFunc();
		return -1;
	} */

	//initialize and set options
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutSetOption(GLUT_RENDERING_CONTEXT, GLUT_USE_CURRENT_CONTEXT);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	//create our window and set up callbacks
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(globals.window_size.x, globals.window_size.y);
	glutCreateWindow("MARS");
	globals.window_closed = false;
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutCloseFunc(CloseFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);

	// Add onscreen text to string vector
	globals.onscreen_text.push_back("Esc to close");

	/* We want a shader per object maybe.
	//also initialize our shader
	if(!shader.Initialize("phong_shader.frag","phong_shader.vert"))
	{
		CloseFunc();
		return -1;
	}
	*/


	//here we create our objects!

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
	
	//our planet - create the file in mars class!
	Mars mars = Mars(/*argv[1]*/);

	//our ship
	Spaceship ship = Spaceship();

	//our starfield
	Starfield stars = Starfield();

	//enter the main loop!
	glutMainLoop();
	return 0;

}