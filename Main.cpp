#include <iostream>
#include <Windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "MeshViewer.h"
#include "MeshHelper.cpp"
#include "Menu.cpp"
#include "UIInteraction.cpp"
using namespace std;

void RenderObjects(void)
{
	float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
	float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
	float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
	float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };
	
	// Child object (teapot) ... relative transform, and render
	//glPushMatrix();
	//glTranslatef(0, 0, 0);
	//glRotatef(g_fTeapotAngle2, 1, 1, 0);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
	//glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	glColor4fv(colorBronzeDiff);
	//glBindTexture(GL_TEXTURE_2D, 0);
	GLfloat earth_mat_ambient[]   = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat earth_mat_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat earth_mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat earth_mat_emission[] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat earth_mat_shininess   = 100.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
	glutSolidTeapot(0.8);
	//glPopMatrix(); 
}

void display() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	gluPerspective(5,1,5,100);

	SetCameraPosition();

	gluLookAt(Environment::camera[0], Environment::camera[1],-Environment::camera[2],Environment::center[0], Environment::center[1], Environment::center[2],0, 1, 0);

	

	glPushMatrix ();
	
	drawAxes();
	RenderObjects();
	
	glPopMatrix();
	glutSwapBuffers();
}

void AnimateScene(void)
{
	float dt;
	DWORD time_now;
	time_now = GetTickCount();
	dt = (float) (time_now - Environment::last_idle_time) / 1000.0;
	
	// Animate the teapot by updating its angles
	Environment::g_fTeapotAngle += dt * 30.0;
	Environment::g_fTeapotAngle2 += dt * 100.0;
	// Save time_now for next time
	Environment::last_idle_time = time_now;
	// Force redraw
	glutPostRedisplay();
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//inital window and set it's properties
	glutCreateWindow("Mesh Viewer - DMT Assignment");
	glutInitWindowSize(Environment::windowWidth, Environment::windowHeight);
	HDC hdc = GetDC (NULL);
	int width = GetDeviceCaps (hdc, HORZRES);
	int height = GetDeviceCaps (hdc, VERTRES);
	ReleaseDC (NULL, hdc);
	glutInitWindowPosition((width-Environment::windowWidth)/2, (height-Environment::windowWidth)/2); //make the window align to center of screen

	init();

	//register functions
	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	glutKeyboardFunc(KeyboardEvent);
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMotion);
	//glutIdleFunc(AnimateScene);
	glutReshapeFunc(windowResize);
	
	//create popupmenu
	BuildPopupMenu();
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	
	glutMainLoop();
	return 0;
}



