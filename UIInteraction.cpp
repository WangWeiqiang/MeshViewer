#include <iostream>
#include "MeshViewer.h"
using namespace std;

void SetCameraPosition(){
	
	if(Environment::g_yRotate>2*Environment::PI)
		Environment::g_yRotate=-2*Environment::PI;
	if(Environment::g_yRotate<-2*Environment::PI)
		Environment::g_yRotate=0.01;
	
	if(Environment::g_xRotate>2*Environment::PI)
		Environment::g_xRotate=0.01;
	if(Environment::g_xRotate<0)
		Environment::g_xRotate=2*Environment::PI;
	
	if(Environment::g_fViewDistance>50)
		Environment::g_fViewDistance=50;
	if(Environment::g_fViewDistance<5)
		Environment::g_fViewDistance=5;

	Environment::camera[0]=Environment::center[0]+Environment::g_fViewDistance*sin(Environment::g_yRotate)*cos(Environment::g_xRotate);
	Environment::camera[2]=Environment::center[1]+Environment::g_fViewDistance*sin(Environment::g_yRotate)*sin(Environment::g_xRotate);
	Environment::camera[1]=Environment::center[2]+Environment::g_fViewDistance*cos(Environment::g_yRotate);
}

void RotateUp(){
	Environment::g_yRotate-=Environment::rSpeed;
	SetCameraPosition();
}

void RotateDown(){
	Environment::g_yRotate+=Environment::rSpeed;
	SetCameraPosition();
}

void RotateRight(){
	Environment::g_xRotate+=Environment::rSpeed;
	SetCameraPosition();
}

void RotateLeft(){
	Environment::g_xRotate-=Environment::rSpeed;
	SetCameraPosition();
}

void ZoomIn(){
	Environment::center[0]+=Environment::mSpeed*cos(Environment::g_xRotate);
	Environment::center[2]+=Environment::mSpeed*sin(Environment::g_xRotate);
	SetCameraPosition();
}

void ZoomOut(){
	Environment::center[0]==Environment::mSpeed*cos(Environment::g_xRotate);
	Environment::center[2]-=Environment::mSpeed*sin(Environment::g_xRotate);
	SetCameraPosition();
}

void KeyboardEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 37:
		RotateUp();
		break;
	case 38:
		RotateDown();
		break;
	case 39:
		RotateRight();
		break;
	case 40:
		RotateLeft();
		break;
	case 'z':
		ZoomIn();
		break;
	case 'x':
		ZoomOut();
		break;
	case 27:
		exit (0);
		break;
	case 'l':
		//menu.MenuEvent(MENU_LIGHTING);
		break;
	case 'p':
		//menu.MenuEvent(MENU_POLYMODE);
		break;
	case 't':
		//menu.MenuEvent(MENU_TEXTURING);
		break;
	}
}


void MouseMotion(int x, int y)
{
	if(Environment::g_bButtonLeftDown){
		Environment::g_xRotate-=(x-Environment::g_xClick)/80.0f;
		Environment::g_yRotate-=(y-Environment::g_yClick)/80.0f;
	}

	if(Environment::g_bButtonMiddleDown){
		Environment::g_fViewDistance+=(y-Environment::g_yClick)/25.0f;
	}

	Environment::g_xClick=x;
	Environment::g_yClick=y;


	SetCameraPosition();
	glutPostRedisplay();
}

void MouseEvent(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN){
		Environment::g_bButtonLeftDown=button==GLUT_LEFT_BUTTON;
		Environment::g_bButtonRightDown=button==GLUT_RIGHT_BUTTON;
		Environment::g_bButtonMiddleDown=button==GLUT_MIDDLE_BUTTON;

		Environment::g_xClick=x;
		Environment::g_yClick=y;
	}
	else
	{
		Environment::g_bButtonLeftDown=false;
		Environment::g_bButtonRightDown=false;
		Environment::g_bButtonMiddleDown=false;
	}
}

void windowResize(int width,int height){
	int viewPort=0;
	int viewPortX=0,viewPortY=0;
	if(width>height){
		viewPort=height;
		viewPortX=(width-height)/2;
	}
	else
	{
		viewPort=width;
		viewPortY=(height-width)/2;
	}
	glViewport(viewPortX,viewPortY,viewPort,viewPort);
	
	glLoadIdentity();
	glutPostRedisplay();
}