#include <iostream>
#include "MeshViewer.h"
using namespace std;

float lastPos[3] = {0.0, 0.0, 0.0};
float angle = 0.0, axis[3], trans[3];
int curx, cury;
int startX, startY;
int oldX= -13;
int oldY= -13;

void toggleSubWindowSize(int windowid){
	if(Environment::fullSubWindowID==windowid){

	}
	else
	{
		glutSetWindow(Environment::fullSubWindowID);
		glutPositionWindow(0,0);
		glutReshapeWindow(700,700);
		Environment::fullSubWindowID=windowid;
	}
}
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
	
	if(Environment::yRotate>2*Environment::PI)
		Environment::yRotate=-2*Environment::PI;
	if(Environment::yRotate<-2*Environment::PI)
		Environment::yRotate=0.01;
	
	if(Environment::xRotate>2*Environment::PI)
		Environment::xRotate=0.01;
	if(Environment::xRotate<0)
		Environment::xRotate=2*Environment::PI;
	
	if(Environment::viewDistance>50)
		Environment::viewDistance=50;
	if(Environment::viewDistance<5)
		Environment::viewDistance=5;

	Environment::camera[0]=Environment::center[0]+Environment::viewDistance*sin(Environment::yRotate)*cos(Environment::xRotate);
	Environment::camera[2]=Environment::center[1]+Environment::viewDistance*sin(Environment::yRotate)*sin(Environment::xRotate);
	Environment::camera[1]=Environment::center[2]+Environment::viewDistance*cos(Environment::yRotate);
}

void RotateUp(){
	Environment::yRotate-=Environment::rSpeed;
	SetCameraPosition();
}

void RotateDown(){
	Environment::yRotate+=Environment::rSpeed;
	SetCameraPosition();
}

void RotateRight(){
	Environment::xRotate+=Environment::rSpeed;
	SetCameraPosition();
}

void RotateLeft(){
	Environment::xRotate-=Environment::rSpeed;
	SetCameraPosition();
}

void ZoomIn(){
	Environment::center[0]+=Environment::mSpeed*cos(Environment::xRotate);
	Environment::center[2]+=Environment::mSpeed*sin(Environment::xRotate);
	SetCameraPosition();
}

void ZoomOut(){
	Environment::center[0]==Environment::mSpeed*cos(Environment::xRotate);
	Environment::center[2]-=Environment::mSpeed*sin(Environment::xRotate);
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

void KeyUp(unsigned char key,int x, int y){
	switch(key){
	case 32:
		Environment::keySpaceDown=false;
		break;
	case 16:
		Environment::keyShiftDown=false;
		break;
	}
}

void KeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 16:
		Environment::keyShiftDown=true;
		break;
	case 32:
		Environment::keySpaceDown=true;
		break;
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
	if(Environment::buttonLeftDown){
		Environment::xRotate-=(x-Environment::xClick)/80.0f;
		Environment::yRotate-=(y-Environment::yClick)/80.0f;

		if(Environment::keySpaceDown){
			Environment::move[0]-=(float)(oldX - x)/500;
			Environment::move[1]+=(float)(oldY - y)/500;
		}
		else
		{
			Environment::globalRoration[0]-= ((oldY - y) * 180.0f) / 100.0f;
			Environment::globalRoration[1]-= ((oldX - x) * 180.0f) / 100.0f;
			clamp (Environment::globalRoration);
		}
		
		oldX = x; 
		oldY = y;
		glutPostRedisplay();
		
	}

	if(Environment::buttonMiddleDown && Environment::keySpaceDown){

		Environment::move[2]-=(float)(oldY - y)/10;
		oldX = x; 
		oldY = y;
		glutPostRedisplay();
	}

	Environment::xClick=x;
	Environment::yClick=y;
	
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

			
		}
	}
}

void MouseEvent(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN){
		Environment::buttonLeftDown=button==GLUT_LEFT_BUTTON;
		Environment::buttonRightDown=button==GLUT_RIGHT_BUTTON;
		Environment::buttonMiddleDown=button==GLUT_MIDDLE_BUTTON;

		Environment::xClick=x;
		Environment::yClick=y;
		oldX = x; 
		oldY = y;
	}
	else
	{
		Environment::buttonLeftDown=false;
		Environment::buttonRightDown=false;
		Environment::buttonMiddleDown=false;
	}

	if(Environment::buttonLeftDown){
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
	if(Environment::buttonLeftDown){
		double duration; 
		clock_t now=clock();
		if((double)(now-Environment::doubleClickFirst)<Environment::doubleClickPeriod){
			cout<<"Double Clicked"<<endl;
			Environment::fullSubWindowID=Environment::cameraView;
			toggleSubWindowSize();
		}
		Environment::doubleClickFirst=now;
	}
	
}

void windowResize(int width,int height){
	double asratio;
	if(width<Environment::windowWidth || height<Environment::windowHeight){
		width=Environment::windowWidth;
		height=Environment::windowHeight;
		glutReshapeWindow(width,height);
	}
    if (height == 0) height = 1;
    asratio = width / (double) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(5, asratio, 1, 1000); //adjust perspective
	gluLookAt(Environment::camera[0], Environment::camera[1],-Environment::camera[2],Environment::center[0], Environment::center[1], Environment::center[2],0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
}