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


#define GAP  25 

void display();

void ResetViewport()  
{  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}

void initFrontView(){
	ResetViewport();  
  
    glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(1.0, 1.0, 1.0);  
    glPushMatrix();  
    gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  
    display();  
    glPopMatrix();  
    glutSwapBuffers(); 
}

void initPlanView(){
	ResetViewport();  
  
    glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(1.0, 1.0, 1.0);  
    glPushMatrix();  
    gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  
    display();  
    glPopMatrix();  
    glutSwapBuffers(); 
}

void initSideView(){
	ResetViewport();  
  
    glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(1.0, 1.0, 1.0);  
    glPushMatrix();  
    gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);  
    display();  
    glPopMatrix();  
    glutSwapBuffers();  
}

void initFreeView(){
	ResetViewport();  
  
    glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(1.0, 1.0, 1.0);  
    glMatrixMode(GL_PROJECTION);  
    glPushMatrix();  
	glLoadIdentity();  
    gluPerspective(30, 1.0, 3.0, 50.0);  
    glMatrixMode(GL_MODELVIEW);  
    glPushMatrix();  
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  
    display();  
    glPopMatrix();  
    glMatrixMode(GL_PROJECTION);  
    glPopMatrix();  
    glFlush();  
    glutSwapBuffers();  
}


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
	if (Environment::trackballMove) 
	{
		//glRotatef(angle, axis[0], axis[1], axis[2]);
	}
	glutSolidTeapot(0.8);
	//glPopMatrix(); 
}

void display() {

	//Background Color
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//font color and style
	glColor3ub(0, 0, 0);
	setfont("helvetica", 12);
	
	//1st window name
	string str = "Front";
	drawstr(GAP, GAP-5, str.c_str(), str.length());
	
	//2st window name
	str = "Top";
	drawstr(2*GAP+Environment::subWindowWidth, GAP-5, str.c_str(), str.length());
	
	//3st widnow name
	str = "Left";
	drawstr(GAP, 2*GAP+Environment::subWindowHeight-5, str.c_str(), str.length());
	
	//4st widnow name
	str = "Camera";
	drawstr(2*GAP+Environment::subWindowWidth, 2*GAP+Environment::subWindowHeight-5, str.c_str(), str.length());
	
	//last
	glutSwapBuffers();
}

void main_reshape(int width,  int height) 
{
        //main view setting
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, width, height, 0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

		Environment::subWindowWidth= (width-GAP*3)/2.0;
		Environment::subWindowHeight= (height-GAP*3)/2.0;

        //Front View Display
		glutSetWindow(Environment::frontView);
        glutPositionWindow(GAP, GAP);
        glutReshapeWindow(Environment::subWindowWidth, Environment::subWindowHeight);

        //Top View Display
		glutSetWindow(Environment::topView);
        glutPositionWindow(GAP+Environment::subWindowWidth+GAP, GAP);
        glutReshapeWindow(Environment::subWindowWidth, Environment::subWindowHeight);

        //Left View Display
		glutSetWindow(Environment::leftView);
        glutPositionWindow(GAP, 2*GAP+Environment::subWindowHeight);
        glutReshapeWindow(Environment::subWindowWidth, Environment::subWindowHeight);


        //Camera View Display
		glutSetWindow(Environment::cameraView);
        glutPositionWindow(2*GAP+Environment::subWindowWidth, 2*GAP+Environment::subWindowHeight);
        glutReshapeWindow(Environment::subWindowWidth, Environment::subWindowHeight);
        
}

void displayFreeView(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	gluPerspective(5,1,5,100);

	//SetCameraPosition();

	gluLookAt(Environment::camera[0], Environment::camera[1],-Environment::camera[2],Environment::center[0], Environment::center[1], Environment::center[2],0, 1, 0);
	
	glPushMatrix ();

	drawAxes();
	glTranslatef (Environment::move[0],Environment::move[1],Environment::move[2]);
	glRotatef (Environment::globalRoration[0], 1.0, 0.0, 0.0);
	glRotatef (Environment::globalRoration[1], 0.0, 1.0, 0.0);
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

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	HDC hdc = GetDC (NULL);
	int width = GetDeviceCaps (hdc, HORZRES);
	int height = GetDeviceCaps (hdc, VERTRES);
	ReleaseDC (NULL, hdc);
	glutInitWindowPosition((width-Environment::windowWidth)/2, (height-Environment::windowWidth)/2); //make the window align to center of screen
	glutInitWindowSize(Environment::windowWidth, Environment::windowHeight);
	Environment::parentWidnow=glutCreateWindow(Environment::windowTitle);
	
	glutReshapeFunc(main_reshape);
	glutDisplayFunc(display);

	
	Environment::frontView = glutCreateSubWindow(Environment::parentWidnow, GAP, GAP, Environment::subWindowWidth, Environment::subWindowHeight);
	glutDisplayFunc(initFrontView);
  
    //screen Window and Display  
    Environment::topView = glutCreateSubWindow(Environment::parentWidnow, 2*GAP+Environment::subWindowWidth, GAP, Environment::subWindowWidth, Environment::subWindowHeight);
	glutDisplayFunc(initPlanView); 
  
    //command Window and Display  
    Environment::leftView = glutCreateSubWindow(Environment::parentWidnow, GAP, 2*GAP+Environment::subWindowHeight, Environment::subWindowWidth, Environment::subWindowHeight);  
	glutDisplayFunc(initSideView);  
  
    Environment::cameraView = glutCreateSubWindow(Environment::parentWidnow, 2*GAP+Environment::subWindowWidth, 2*GAP+Environment::subWindowHeight, Environment::subWindowWidth, Environment::subWindowHeight);  
	//create popupmenu
	BuildPopupMenu();
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	glutDisplayFunc(displayFreeView);  
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMotion);
	//glutIdleFunc(AnimateScene);
	glutMainLoop();
	return 0;
}



