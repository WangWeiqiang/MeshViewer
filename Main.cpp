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
	glutSolidTeapot(0.8);
	//glPopMatrix(); 
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BITS);   // Clear the color buffer with current clearing color
	
	glMatrixMode(GL_MODELVIEW);
	
	SetCameraPosition();
	gluLookAt(1, 0, -Environment::camera[2], 0, 0, 0, 0, 1.0, 0);
	//gluLookAt(Environment::camera[0], Environment::camera[1],-Environment::camera[2],Environment::center[0], Environment::center[1], Environment::center[2],0, 1, 0);

	//gluLookAt(0, 0,-10,Environment::center[0], Environment::center[1], Environment::center[2],0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, Environment::g_lightPos);
	
	glPushMatrix ();
	
	drawAxes();
	RenderObjects();
	
	glPopMatrix ();
	
	
	glutSwapBuffers();	
	glFlush();
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

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	//inital window and set it's properties
	glutCreateWindow("Mesh Viewer - DMT Assignment");
	glutInitWindowSize(Environment::windowWidth, Environment::windowHeight);
	HDC hdc = GetDC (NULL);
	int width = GetDeviceCaps (hdc, HORZRES);
	int height = GetDeviceCaps (hdc, VERTRES);
	ReleaseDC (NULL, hdc);
	glutInitWindowPosition((width-Environment::windowWidth)/2, (height-Environment::windowWidth)/2); //make the window align to center of screen


	

	//register functions
	glutDisplayFunc(display);
	glutKeyboardFunc(KeyboardEvent);
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(AnimateScene);
	glutReshapeFunc(windowResize);
	
	//create popupmenu
	BuildPopupMenu();
	glutAttachMenu (GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}



