#include <iostream>
#include "MeshViewer.h"
using namespace std;

void main_reshape(int width,int height);

void fullScreenSubWindow(int windowid){
	
	for(int i=2;i<6;i++){
		if(i!=windowid){
			glutSetWindow(i);
			glutHideWindow();
		}
	}
	Environment::fullSubWindowID=windowid;
	glutSetWindow(windowid);
	glutPositionWindow(0,0);
	glutReshapeWindow(Environment::mainWindowWidth,Environment::mainWindowHeight);
	
}
void toggleSubWindowSize(int windowid){
	if(Environment::fullSubWindowID==windowid){
		Environment::fullSubWindowID=0;
		for(int i=2;i<6;i++){
			glutSetWindow(i);
			glutShowWindow();
		}
		main_reshape(Environment::mainWindowWidth,Environment::mainWindowHeight);
	}
	else
	{
		fullScreenSubWindow(windowid);
	}
}

void SetCameraPosition(){
	
	if(Environment::viewDistance>1000)
		Environment::viewDistance=1000;
	if(Environment::viewDistance<0.1)
		Environment::viewDistance=0.1;

	Environment::camera[0]=Environment::center[0]+Environment::viewDistance*sin(Environment::yRotate)*cos(Environment::xRotate);
	Environment::camera[2]=Environment::center[1]+Environment::viewDistance*sin(Environment::yRotate)*sin(Environment::xRotate);
	Environment::camera[1]=Environment::center[2]+Environment::viewDistance*cos(Environment::yRotate);
}

void KeyUp(unsigned char key,int x, int y){
	switch (key)
	{
	case 'x':
	case 'X':
		Environment::rotateCordinate=false;
		Environment::rotateObject=true;
		break;
	case 'z':
	case 'Z':
		Environment::zoom=false;
		break;
	case 'm':
	case 'M':
		Environment::move=false;
		break;
	}
}

void KeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
	case 'X':
		Environment::rotateCordinate=true;
		Environment::rotateObject=false;
		Environment::move=false;
		break;
	case 'z':
	case 'Z':
		Environment::zoom=true;
		Environment::rotateCordinate=false;
		Environment::rotateObject=false;
		break;
	case 'm':
	case 'M':
		Environment::move=true;
		Environment::rotateCordinate=false;
		Environment::rotateObject=false;
		break;
	}
}

void clamp (GLfloat *v)
{
    int i;
    for (i = 0; i < 3; i ++)
        if (v[i] > 360 || v[i] < -360)
            v[i] = 0.0f;
}

void MouseMotion(int x, int y)
{
	if(Environment::rotateObject){
		Environment::xRotate += (x - Environment::xClick)/5.0; 
		if (Environment::xRotate > 180) 
			Environment::xRotate -= 360; 
		else if (Environment::xRotate <-180) 
			Environment::xRotate += 360; 

		cout<<"x-x1 "<< (x - Environment::xClick)/5.0 <<endl;
		cout<<"rotate "<<Environment::xRotate<<endl;

		Environment::xClick = x; 
	   
		Environment::yRotate += (y - Environment::yClick)/5.0; 

		if (Environment::yRotate > 180) 
			Environment::yRotate -= 360; 
		else if (Environment::yRotate <-180) 
			Environment::yRotate += 360; 
      	
		Environment::yClick = y; 


		

		glutPostRedisplay();

		glutSetWindow(Environment::frontView);
		glutPostRedisplay();

		glutSetWindow(Environment::topView);
		glutPostRedisplay();

		glutSetWindow(Environment::leftView);
		glutPostRedisplay();
		
	}

	if(Environment::zoom){
		float old_size = Environment::scale;
		Environment::scale *= (1 + (y - Environment::yClick)/200.0); 
		if (Environment::scale <0) 
			Environment::scale = old_size; 
		Environment::yClick = y; 
		glutPostRedisplay();
		
		glutSetWindow(Environment::frontView);
		glutPostRedisplay();

		glutSetWindow(Environment::topView);
		glutPostRedisplay();

		glutSetWindow(Environment::leftView);
		glutPostRedisplay();
		
	}

	if(Environment::move){

	}
	
}

void MouseEvent(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN){
		Environment::xClick = x;
		Environment::yClick = y; 

		Environment::buttonLeftDown=button==GLUT_LEFT_BUTTON;
		Environment::buttonRightDown=button==GLUT_RIGHT_BUTTON;
		Environment::buttonMiddleDown=button==GLUT_MIDDLE_BUTTON;

	}
	else
	{
		Environment::buttonLeftDown=false;
		Environment::buttonRightDown=false;
		Environment::buttonMiddleDown=false;
	}

	if(Environment::buttonLeftDown){
		Environment::rotateObject=true;
	
		double duration; 
		clock_t now=clock();
		if((double)(now-Environment::doubleClickFirst)<Environment::doubleClickPeriod){
			toggleSubWindowSize(glutGetWindow());
		}
		Environment::doubleClickFirst=now;
	}
}