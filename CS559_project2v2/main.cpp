/* Comment header */

#include <iostream>
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PlanarMesh.h"

using namespace std;
using namespace glm;

static class Globals
{
public:
	Globals();
	glm::ivec2 window_size;
	float aspect_ratio;
	bool window_closed;

	float near_plane, far_plane, fov;

	bool wireframe_enabled;
	bool paused;
	float current_time, time_last_pause_began, total_time_paused;
	
	vector<std::string> onscreen_text;
} globals;

Globals::Globals() 
{
	this->window_size = vec2(1366, 768);
	this->aspect_ratio = (float)(window_size.x) / (float)(window_size.y);
	this->window_closed = true;

	this->near_plane = 5.0f;
	this->far_plane = 50.0f;
	this->fov = 50.0f;

	this->wireframe_enabled = false;
	this->paused = false;
	this->current_time = 0;
	this->time_last_pause_began = 0;
	this->total_time_paused = 0;
}

PlanarMesh mesh;

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

void DisplayOnscreenText()
{
	glColor3f(.9f, .9f, .9f);
	mat4 orth = ortho(0.0f, (float)globals.window_size.x, 0.0f, (float)globals.window_size.y, 1.0f, 10.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(orth));

	// Look at the same place constantly, and shift the modelview matrix in front of the near plane
	mat4 text = lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	text = translate(text, vec3(0.0f, 5.0f, -1.0f));
	text = scale(text, vec3(.15f, .15f, .15f));
	glMatrixMode(GL_MODELVIEW);

	vector<string> * s = &globals.onscreen_text;
	for(auto i = s->begin(); i < s->end(); i++) {
		glLoadMatrixf(value_ptr(text));
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)(*i).c_str());
		text = translate(text, vec3(0.0f, glutStrokeHeight(GLUT_STROKE_MONO_ROMAN), 0.0f));
	}
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

	// current_time may not be part of globals
	mesh.Draw(proj, mv, globals.window_size, (globals.paused ? globals.time_last_pause_began : globals.current_time) - globals.total_time_paused);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	

	//Blatantly ripping off the structure of OGLTTA
	//Use an enum to go through the list of possible states

	DisplayOnscreenText();
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
	//make sure we have a filename in argv! argc must equal 2

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

	// initialize our friggin' PlanarMesh
	if(!mesh.Initialize(4,4))
	{
		return 0;
	}
	glutMainLoop();
	return 0;
}
