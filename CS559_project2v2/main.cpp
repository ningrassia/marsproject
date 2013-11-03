/* Comment header */


//Enum increment taken from http://www.cplusplus.com/forum/beginner/41790/
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "Starfield.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Spaceship.h"
#include "Mars.h"

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
	bool normals_enabled;

	bool paused;
	float current_time, time_last_pause_began, total_time_paused;
	int period;
	float rotate_factor;

	int polygon_detail;
	bool starfield_enabled;
	double starfield_depth;
	double starfield_inner_radius;
	int starfield_num_stars;

	float ship_height;
	float ship_rotate;
	float ship_size;
	
	vec3 light_position;

	float horiz_cam_angle, vert_cam_angle, cam_radius;
	enum DisplayModes {Ship, Mars, FirstPerson, ThirdPerson, Stars};
	DisplayModes current_mode;
	vector<std::string> onscreen_text;



} globals;

inline Globals::DisplayModes& operator++(Globals::DisplayModes& disp_modes, int)  // <--- note -- must be a reference
{
   const int i = static_cast<int>(disp_modes);
   disp_modes = static_cast<Globals::DisplayModes>((i + 1) % 5);
   return disp_modes;
}

Globals::Globals() 
{
	this->window_size = vec2(1366, 768);
	this->aspect_ratio = (float)(window_size.x) / (float)(window_size.y);
	this->window_closed = true;

	this->near_plane = 0.1f;
	this->far_plane = 90.0f;
	this->fov = 50.0f;

	this->wireframe_enabled = false;
	this->normals_enabled = false;

	this->paused = false;
	this->current_time = 0;
	this->time_last_pause_began = 0;
	this->total_time_paused = 0;
	this->period = 1000 / 60;
	this->rotate_factor = 4.0f;

	this->polygon_detail = 40;
	this->starfield_enabled = true;
	this->starfield_depth = 20.0;
	this->starfield_inner_radius = 25.0;
	this->starfield_num_stars = 10000;

	this->ship_height = 3.2f;
	this->ship_rotate = 0.0f;
	this->ship_size = 0.07f;

	this->current_mode = Ship;
	this->horiz_cam_angle = 0;
	this->vert_cam_angle = 0;
	this->cam_radius = 10;

	this->light_position = vec3(30.0f, 0.0f, 0.0f);
}

Starfield starfield;
Spaceship spaceship;
Mars mars;

// Utility function for conversion from degree to radians
float toRadian(float d)
{
	return (float)(d / 180.0f * M_PI);
}

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
	mat4 orth = ortho(0.0f, (float)globals.window_size.x, 0.0f, (float)globals.window_size.y, 0.1f, 10.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(orth));

	// Look at the same place constantly, and shift the modelview matrix in front of the near plane
	mat4 text = lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	
	glMatrixMode(GL_MODELVIEW);

	// Draw pause text if paused
	// not working right now - fix later!
	
	if(globals.paused)
	{
		text = translate(text, vec3(globals.window_size.x/2, globals.window_size.y/2, -1.0f));
		text = scale(text, vec3(.25f, .25f, .25f));
		text = translate(text, vec3(-3 * glutStrokeWidth(GLUT_STROKE_MONO_ROMAN, 'P'),  -glutStrokeHeight(GLUT_STROKE_MONO_ROMAN) / 2, 0.0f));
		glLoadMatrixf(value_ptr(text));
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)"PAUSED");
		//reset modelview text matrix when done drawing centered text.
		text = lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	}
	
	text = translate(text, vec3(0.0f, 5.0f, -1.0f));
	text = scale(text, vec3(.15f, .15f, .15f));
	

	vector<string> * s = &globals.onscreen_text;
	for(auto i = s->begin(); i < s->end(); i++) {
		glLoadMatrixf(value_ptr(text));
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *)(*i).c_str());
		text = translate(text, vec3(0.0f, glutStrokeHeight(GLUT_STROKE_MONO_ROMAN), 0.0f));
	}
}

void ShipModeDraw(mat4 proj)
{
	mat4 mv(1.0f);
	//Temporary lookat - always looking at the center point?
	vec3 eyePos = vec3(globals.cam_radius * cos(toRadian(globals.vert_cam_angle)) * cos(toRadian(globals.horiz_cam_angle)),
						(globals.cam_radius * sin(toRadian(globals.vert_cam_angle))),
						(globals.cam_radius * cos(toRadian(globals.vert_cam_angle)) * sin(toRadian(globals.horiz_cam_angle))));
	mv = lookAt(eyePos, vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));

	// current_time may not be part of globals
	
	// also draw a starfield
	if(globals.starfield_enabled)
	{
		starfield.Draw(proj, mv, globals.window_size, 0);
	}

	spaceship.Draw(proj, mv, globals.window_size, ((globals.paused ? globals.time_last_pause_began : globals.current_time) - globals.total_time_paused) / globals.rotate_factor, globals.light_position);



}

void MarsModeDraw(mat4 proj)
{
	//Just using our mesh, replace the mesh with Mars eventually!

	mat4 mv(1.0f);
	//Temporary lookat - always looking at the center point?
	vec3 eyePos = vec3(globals.cam_radius * cos(toRadian(globals.vert_cam_angle)) * cos(toRadian(globals.horiz_cam_angle)),
						(globals.cam_radius * sin(toRadian(globals.vert_cam_angle))),
						(globals.cam_radius * cos(toRadian(globals.vert_cam_angle)) * sin(toRadian(globals.horiz_cam_angle))));
	mv = lookAt(eyePos, vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));


	// also draw a starfield
	if(globals.starfield_enabled)
	{
		starfield.Draw(proj, mv, globals.window_size, 0);
	}

	mars.Draw(proj, mv, globals.window_size, ((globals.paused ? globals.time_last_pause_began : globals.current_time) - globals.total_time_paused) / globals.rotate_factor, globals.light_position);

}

void FirstPersonModeDraw(mat4 proj)
{


	mat4 mv(1.0f);
	//set up our position, view, and up vectors!
	//The angle adjustments are to ensure that default values have us facing a good direction
	vec3 eyePos = vec3(0.0f, 0.0f, 4.0f);
	vec3 lookVec = vec3(cos(toRadian(globals.vert_cam_angle/2.0f - 45.0f)) * sin(toRadian(globals.horiz_cam_angle - 90.0f)),
						(cos(toRadian(globals.vert_cam_angle/2.0f - 45.0f)) * cos(toRadian(globals.horiz_cam_angle - 90.0f))),
						(sin(toRadian(globals.vert_cam_angle/2.0f - 45.0f))))
						+ eyePos;

	vec3 upVec = vec3(0.0f,	0.0f, 1.0f);
	mv = lookAt(eyePos, lookVec, upVec);

	// also draw a starfield
	if(globals.starfield_enabled)
	{
		starfield.Draw(proj, mv, globals.window_size, ((globals.paused ? globals.time_last_pause_began : globals.current_time) - globals.total_time_paused) / globals.rotate_factor);
	}
	
	mars.Draw(proj, mv, globals.window_size, ((globals.paused ? globals.time_last_pause_began : globals.current_time) - globals.total_time_paused) / globals.rotate_factor, globals.light_position);


}

void ThirdPersonModeDraw(mat4 proj)
{

	mat4 mv(1.0f);
	//set up our position, view, and up vectors!
	//The angle adjustments are to ensure that default values have us facing a good direction
	vec3 eyePos = vec3(0.0f, 0.0f, 4.0f);
	vec3 lookVec = vec3(-cos(toRadian(globals.vert_cam_angle/2.0f - 45.0f)),
						0.0f,
						sin(toRadian(globals.vert_cam_angle/2.0f - 45.0f))
						)
						+ eyePos;

	vec3 upVec = vec3(0.0f,	0.0f, 1.0f);
	mv = lookAt(eyePos, lookVec, upVec);
	mat4 saved_mv = mv;
	
	//limit rotation - only for TPV
	if(globals.horiz_cam_angle > 89.0f)
	{
		globals.horiz_cam_angle = 89.0f;
	}
	else if(globals.horiz_cam_angle < -89.0f)
	{
		globals.horiz_cam_angle = -89.0f;
	}
	//first rotate is experiment!
	mv = rotate(mv, globals.horiz_cam_angle/2.0f, vec3(0.0f, 0.0f, 1.0f));
	mv = rotate(mv, globals.horiz_cam_angle, vec3(1.0f, 0.0f, 0.0f));


	// also draw a starfield
	if(globals.starfield_enabled)
	{
		starfield.Draw(proj, mv, globals.window_size, ((globals.paused ? globals.time_last_pause_began : globals.current_time) - globals.total_time_paused) / globals.rotate_factor);
	}
	
	mars.Draw(proj, mv, globals.window_size, ((globals.paused ? globals.time_last_pause_began : globals.current_time) - globals.total_time_paused) / globals.rotate_factor, globals.light_position);



	//translate/scale values are guesses right now.
	//restore unrotated modelview so we control the ship!
	mv = saved_mv;
	mv = translate(mv, vec3(-1.0f, 0.0f, globals.ship_height));
	mv = scale(mv, vec3(globals.ship_size));
	//rotate is good though
	mv = rotate(mv, -10.0f, vec3(0.0f, 1.0f, 0.0f));
	mv = rotate(mv, 90.0f, vec3(0.0f, 0.0f, 1.0f));
	spaceship.Draw(proj, mv, globals.window_size, globals.ship_rotate, globals.light_position);

}
void StarsModeDraw(mat4 proj)
{

	mat4 mv(1.0f);
	//make sure we're outside of the starfield!
	vec3 eyePos = vec3(0.0f,0.0f, 2.0f * (globals.starfield_inner_radius + globals.starfield_depth));
	mv = lookAt(eyePos, vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));

	//rotate based on the time!
	//divide by rotate_factor to control speed of rotation!
	mv = rotate(mv,
		(((globals.paused ? globals.time_last_pause_began : globals.current_time) - globals.total_time_paused)
			/globals.rotate_factor),
		vec3(0.0f, 1.0f, 0.0f)); 

	starfield.Draw(proj, mv, globals.window_size, ((globals.paused ? globals.time_last_pause_began : globals.current_time) - globals.total_time_paused) / globals.rotate_factor);

}

void DisplayFunc()
{
	//this is all common setup no matter what mode we're in!
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, (globals.wireframe_enabled == true) ? GL_LINE : GL_FILL);

	glViewport(0, 0, globals.window_size.x, globals.window_size.y);

	mat4 proj = perspective(globals.fov, globals.aspect_ratio, globals.near_plane, globals.far_plane);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(proj));

	//select our mode and draw it! Using an enum. Not perfect yet, but yeah.
	switch(globals.current_mode)
	{
		case Globals::DisplayModes::Ship:
			ShipModeDraw(proj);
			break;
		case Globals::DisplayModes::Mars:
			MarsModeDraw(proj);
			break;
		case Globals::DisplayModes::FirstPerson:
			FirstPersonModeDraw(proj);
			break;
		case Globals::DisplayModes::ThirdPerson:
			ThirdPersonModeDraw(proj);
			break;
		case Globals::DisplayModes::Stars:
			StarsModeDraw(proj);
			break;
		default:
			ShipModeDraw(proj);
			break;

	}
	//no use repeating code!
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
	starfield.TakeDown();
	spaceship.TakeDown();
	mars.TakeDown();
	glutLeaveMainLoop();
}

void KeyboardFunc(unsigned char c, int x, int y)
{
	//ignore keyboard function except unpause and quit when paused
	if((c != 27) && (c != 'x') && (c != 'p') && globals.paused)
	{
		return;
	}
	switch(c) {
		case 'x':
		case 27:
			CloseFunc();
			break;
		case 'n':
			globals.normals_enabled = !globals.normals_enabled;
			spaceship.EnableNormals(globals.normals_enabled);
			mars.EnableNormals(globals.normals_enabled);
			break;
		case 'w':
			globals.wireframe_enabled = !globals.wireframe_enabled;
			break;
		case 's':
			globals.starfield_enabled = !globals.starfield_enabled;
			break;
		case 'p':
			globals.paused = !globals.paused;
			//if we've just paused, set the time we just paused at!
			if(globals.paused)
			{
				globals.time_last_pause_began = globals.current_time;
			}
			//if we've just unpaused, add to the total time paused.
			else
			{
				globals.total_time_paused += (globals.current_time - globals.time_last_pause_began);
			}
			break;
		case '+':
			if(globals.rotate_factor > 0.25f)
			{
				globals.rotate_factor = globals.rotate_factor / 2.0f;
			}
			break;
		case '-':
			if(globals.rotate_factor < 16.0f)
			{
				globals.rotate_factor = globals.rotate_factor * 2.0f;
			}
			break;
		case '[':
			if(globals.polygon_detail > 4) 
			{
				globals.polygon_detail--;
			}
			spaceship.TakeDown();
			spaceship.Initialize(globals.polygon_detail, globals.polygon_detail, vec3(1.0f, 0.0f, 0.0f));
			break;
		case ']':
			if(globals.polygon_detail< 200) 
			{
				globals.polygon_detail++;
			}
			spaceship.TakeDown();
			spaceship.Initialize(globals.polygon_detail, globals.polygon_detail, vec3(1.0f, 0.0f, 0.0f));
			break;
		case '2':
			globals.ship_height -= 0.01f;
			break;
		case '4':
			globals.ship_rotate -= float(M_PI)/3.0f;
			break;
		case '6':
			globals.ship_rotate += float(M_PI)/3.0f;
			break;
		case '8':
			globals.ship_height += 0.01f;
			break;
	}
	return;
}

void SpecialFunc(int key, int x, int y)
{
	//ignore special keys when paused.
	if(globals.paused)
	{
		return;
	}

	switch(key)	{
	case GLUT_KEY_LEFT:
		globals.horiz_cam_angle = fmod((globals.horiz_cam_angle - 1.0f), 360.0f);
		break;
	case GLUT_KEY_RIGHT:
		globals.horiz_cam_angle = fmod((globals.horiz_cam_angle + 1.0f), 360.0f);
		break;
	case GLUT_KEY_UP:
		if(globals.vert_cam_angle < 89.0f)
		globals.vert_cam_angle += 1.0f;
		break;
	case GLUT_KEY_DOWN:
		if(globals.vert_cam_angle > -89.0f)
		globals.vert_cam_angle -= 1.0f;
		break;
	case GLUT_KEY_F1:
		globals.current_mode++;
		globals.horiz_cam_angle = globals.vert_cam_angle = 0.0f;
		//update the display text!
		globals.onscreen_text.pop_back();
		switch(globals.current_mode)
		{
			case Globals::DisplayModes::Ship:
				globals.onscreen_text.push_back("Ship Mode");
				return;
			case Globals::DisplayModes::Mars:
				globals.onscreen_text.push_back("Mars Mode");
				break;
			case Globals::DisplayModes::FirstPerson:
				globals.onscreen_text.push_back("First Person Mode");
				break;
			case Globals::DisplayModes::ThirdPerson:
				globals.onscreen_text.push_back("Third Person Mode");
				break;
			case Globals::DisplayModes::Stars:
				globals.onscreen_text.push_back("Starfield Mode");
				break;
		}
		break;
	}
}

void TimerFunc(int value)
{

	//update our current time.
	globals.current_time++;
	glutTimerFunc(globals.period, TimerFunc, 0);
	//make sure our window is open when we draw again!
	if(!globals.window_closed)
	{
		glutPostRedisplay();
	}
}

int main(int argc, char * argv[])
{
	//make sure we have a filename in argv! argc must equal 2
#ifndef _DEBUG
	if(argc != 2)
	{
		cout << "specify a mars file por favor!" << endl;
		return -1;
	}
#endif
	

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

	// Add onscreen text to string vector - we always start in ship mode!
	globals.onscreen_text.push_back("Nik Ingrassia and Jackson Reed for CS559");
	globals.onscreen_text.push_back("Esc to close");
	globals.onscreen_text.push_back("w to toggle wireframe - n to noggle normals");
	globals.onscreen_text.push_back("Ship Mode");

	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW failed to initialize." << endl;
		return -1;
	}
	if(!spaceship.Initialize(globals.polygon_detail, globals.polygon_detail, vec3(1.0f, 0.0f, 0.0f)))
	{
		return -1;
	}
	// initialize a starfield - lots of stars!
	if(!starfield.Initialize(globals.starfield_inner_radius,globals.starfield_depth,globals.starfield_num_stars))
	{
		return -1;
	}

#ifdef _DEBUG
	if(!mars.Initialize("mars_low_rez.txt", 3.0f, 0.15f, vec3(0.6f, 0.1f, 0.1f)))
#else
	if(!mars.Initialize(argv[1], 3.0f, 0.15f, vec3(0.6f, 0.1f, 0.1f)))
#endif
	{
		return -1;
	}
	glutTimerFunc(globals.period, TimerFunc, 0);
	glutMainLoop();
	return 0;
}
