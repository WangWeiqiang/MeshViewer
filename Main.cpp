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
void RenderObjects();
MeshModel model;
void displayView(int windowid){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,Environment::subWindowWidth,Environment::subWindowHeight);
	gluPerspective(Environment::viewAngle,Environment::subWindowWidth/Environment::subWindowHeight,0.1,10000);

	if(windowid==Environment::frontView){
		gluLookAt(0,0,-Environment::viewDistance,Environment::center[0], Environment::center[1], Environment::center[2],0, 1, 0);
	}

	if(windowid==Environment::topView){
		gluLookAt(0,-Environment::viewDistance,0,Environment::center[0], Environment::center[1], Environment::center[2],0, 0, 1);
	}

	if(windowid==Environment::leftView){
		gluLookAt(-Environment::viewDistance,0,0,Environment::center[0], Environment::center[1], Environment::center[2],0, 1, 0);
	}

	if(windowid==Environment::cameraView){
		gluLookAt(Environment::viewDistance,Environment::viewDistance,-Environment::viewDistance,Environment::center[0], Environment::center[1], Environment::center[2],0, 1, 0);
	}

	SetCameraPosition();
	glPushMatrix ();

	drawAxes(model);
	//glTranslatef (Environment::move[0],Environment::move[1],Environment::move[2]);

	glRotatef (Environment::xRotate, 0, 1, 0);
	glRotatef (Environment::yRotate, 1, 0, 0);
	glScalef(Environment::scale,Environment::scale,Environment::scale);

	rendMesh(model);

	glPopMatrix();
	glutSwapBuffers();
}

void ResetViewport()  
{  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}

void displayFrontView(){
	displayView(Environment::frontView);
}
void reshapeFrontView(int width, int height){
	glViewport(0, 0, width, height);
	glLoadIdentity();
	gluPerspective(Environment::viewAngle,width/height,0.1,10000);
	glutPostRedisplay();
}

void displayTopView(){
	displayView(Environment::topView);
}
void reshapeTopView(int width,int height){
	glViewport(0, 0, width, height);
	glLoadIdentity();
	gluPerspective(Environment::viewAngle,width/height,0.1,10000);
	glutPostRedisplay();
}

void displayLeftView(){
	displayView(Environment::leftView);
}
void reshapeLeftView(int width,int height){
	glViewport(0, 0, width, height);
	glLoadIdentity();
	gluPerspective(Environment::viewAngle,width/height,0.1,10000);
	glutPostRedisplay();
}


void reshapeCameraView(int width,int height){
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(Environment::viewAngle,width/height,0.1,10000);
	glutPostRedisplay();
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
	Environment::mainWindowWidth=width;
	Environment::mainWindowHeight=height;
    if(Environment::fullSubWindowID>0){
		fullScreenSubWindow(Environment::fullSubWindowID);
	}
	else
	{
		//main view setting
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, width, height, 0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Environment::subWindowWidth= (width-GAP*3)/2.0;
		Environment::subWindowHeight= (height-GAP*3)/2.0;

		display();

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

		glutSetWindow(Environment::parentWidnow);
		glutPostRedisplay();
	}
}

void displayCameraView(){
	displayView(Environment::cameraView);
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
	string filename="";

	if(argc>=2)
	{
      for(int i=0;i<argc;i++){
		  if(strstr(argv[i],".m")!=NULL){
			  filename=argv[i];
		  }

	  }
	}

	cout<<"Loading mesh model ..."<<endl;
	if(filename==""){
		filename="F:\hand.m";
	}
	if(filename!=""){
		loadMesh(filename.c_str(),model);
		computCenterAndSizeOfMesh(model);
		float modelSize=model.size[0];
		if(model.size[1]>modelSize)
			modelSize=model.size[1];
		if(model.size[2]>modelSize)
			modelSize=model.size[2];
		Environment::viewDistance=(modelSize/2)/(tan(Environment::viewAngle/2));
		Environment::viewDistance+=Environment::viewDistance*0.1;

		cout<<"Center:"<<model.center[0]<<","<<model.center[1]<<","<<model.center[2]<<endl;
		cout<<"H:"<<model.size[0]<<",W:"<<model.size[1]<<",L:"<<model.size[2];
	}
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	HDC hdc = GetDC (NULL);
	int width = GetDeviceCaps (hdc, HORZRES);
	int height = GetDeviceCaps (hdc, VERTRES);
	ReleaseDC (NULL, hdc);
	glutInitWindowPosition((width-Environment::windowWidth)/2, (height-Environment::windowWidth)/2); //make the window align to center of screen
	glutInitWindowSize(Environment::windowWidth, Environment::windowHeight);
	
	Environment::parentWidnow=glutCreateWindow(Environment::windowTitle);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutReshapeFunc(main_reshape);
	glutDisplayFunc(display);

	
	Environment::frontView = glutCreateSubWindow(Environment::parentWidnow, GAP, GAP, Environment::subWindowWidth, Environment::subWindowHeight);
	BuildPopupMenu();
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	glutDisplayFunc(displayFrontView);
	glutReshapeFunc(reshapeFrontView);
  
    //screen Window and Display  
    Environment::topView = glutCreateSubWindow(Environment::parentWidnow, 2*GAP+Environment::subWindowWidth, GAP, Environment::subWindowWidth, Environment::subWindowHeight);
	BuildPopupMenu();
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	glutDisplayFunc(displayTopView); 
	glutReshapeFunc(reshapeTopView);
  
    //command Window and Display  
    Environment::leftView = glutCreateSubWindow(Environment::parentWidnow, GAP, 2*GAP+Environment::subWindowHeight, Environment::subWindowWidth, Environment::subWindowHeight);  
	BuildPopupMenu();
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	glutDisplayFunc(displayLeftView);
	glutReshapeFunc(reshapeLeftView);
  
    Environment::cameraView = glutCreateSubWindow(Environment::parentWidnow, 2*GAP+Environment::subWindowWidth, 2*GAP+Environment::subWindowHeight, Environment::subWindowWidth, Environment::subWindowHeight);  
	BuildPopupMenu();
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	glutDisplayFunc(displayCameraView); 
	glutReshapeFunc(reshapeCameraView);
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMotion);

	glutMainLoop();
	return 0;
}