#include <iostream>
#include "MeshViewer.h"
using namespace std;

float lastPos[3] = {0.0, 0.0, 0.0};
float angle = 0.0, axis[3], trans[3];
int curx, cury;
int startX, startY;
int oldX = -13;
int oldY = -13;

void trackball_ptov(int x, int y, int width, int height, float v[3]){
	float d, a;
	/* project x,y onto a hemisphere centered 
	within width, height , note z is up here*/
	v[0] = (10.0*x - width) / width;
	v[1] = (height - 10.0F*y) / height; 
	d = sqrt(v[0]*v[0] + v[1]*v[1]);
	v[2] = cos((Environment::PI/2.0) * ((d < 1.0) ? d: 1.0));
	a = 1.0 / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	v[0] *= a; v[1] *= a; v[2] *= a;
}

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

void startMotion(int x, int y)
{
	Environment::trackingMouse = true;
	Environment::redrawContinue = false;
	startX = x;
	startY = y;
	curx = x;
	cury = y;
	trackball_ptov(x, y, Environment::windowWidth, Environment::windowHeight, lastPos);
	Environment::trackballMove=true;
}

void stopMotion(int x, int y)
{
	Environment::trackingMouse = false;
	/* check if position has changed */
	if (startX != x || startY != y)
		Environment::redrawContinue = true;
	else 
	{
		angle = 0.0;
		Environment::redrawContinue = false;
		Environment::trackballMove = false;
	}
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

void clamp (GLfloat *v)
{
    int i;
    for (i = 0; i < 3; i ++)
        if (v[i] > 360 || v[i] < -360)
            v[i] = 0.0f;
}

void MouseMotion(int x, int y)
{
	if(Environment::g_bButtonLeftDown){
		Environment::g_xRotate-=(x-Environment::g_xClick)/80.0f;
		Environment::g_yRotate-=(y-Environment::g_yClick)/80.0f;
		
		Environment::globalRoration[0]-= ((oldY - y) * 180.0f) / 100.0f;
		Environment::globalRoration[1]-= ((oldX - x) * 180.0f) / 100.0f;
		clamp (Environment::globalRoration);
		glutPostRedisplay();
	}

	if(Environment::g_bButtonMiddleDown){
		Environment::g_fViewDistance+=(y-Environment::g_yClick)/25.0f;
		glutPostRedisplay();
	}

	Environment::g_xClick=x;
	Environment::g_yClick=y;

	oldX = x; 
    oldY = y;
	//SetCameraPosition();
	

	float curPos[3],dx, dy, dz;
	/* compute position on hemisphere */
	trackball_ptov(x, y, Environment::windowWidth, Environment::windowHeight, curPos);
	if(Environment::trackingMouse)
	{ 
		/* compute the change in position on the hemisphere */
		dx = curPos[0] - lastPos[0];
		dy = curPos[1] - lastPos[1];
		dz = curPos[2] - lastPos[2];
		if (dx || dy || dz) 
		{
			/* compute theta and cross product */
			angle = 900.0 * sqrt(dx*dx + dy*dy + dz*dz);
			axis[0] =100* (lastPos[1]*curPos[2]-lastPos[2]*curPos[1]);
			axis[1] =100* (lastPos[2]*curPos[0]-lastPos[0]*curPos[2]);
			axis[2] =100* (lastPos[0]*curPos[1]-lastPos[1]*curPos[0]);
			/* update position */
			lastPos[0] = curPos[0];
			lastPos[1] = curPos[1];
			lastPos[2] = curPos[2];

			cout<<angle<<"|"<<axis[0]<<","<<axis[1]<<","<<axis[2]<<endl;
		}
	}
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

	if(Environment::g_bButtonLeftDown){
		switch (state)
		{
		case GLUT_DOWN:
			y=Environment::windowHeight-y;
			startMotion(x,y);
			break;
		case GLUT_UP:
			stopMotion(x,y);
			break;
		default:
			break;
		}

		oldX = x;
		oldY = y;
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

