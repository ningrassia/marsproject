#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <math.h>

using namespace std;
using namespace glm;

void DisplayFunc()
{
	glClearColor(.1, .1, .1, 1);



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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutSetOption(GLUT_RENDERING_CONTEXT, GLUT_USE_CURRENT_CONTEXT);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1366, 768);
	glutCreateWindow("MARS");
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutCloseFunc(CloseFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	if(!InitializeGL())
	{
		CloseFunc();
		return -1;
	}

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutMainLoop();
	return 0;

}