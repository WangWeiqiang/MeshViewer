#include "Environment.h"
using namespace std;

void KeyUp(unsigned char key,int x, int y){
	switch (key)
	{
		case 32:
			Environment::move=false;
			break;
	}
}

void KeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 32:
		Environment::move=true;
		break;
	}
}

void MouseMotion(int x, int y)
{
	if(Environment::rotateObject){
		Environment::xRotate += (x - Environment::xClick)/5.0; 
		if (Environment::xRotate > 180) 
			Environment::xRotate -= 360; 
		else if (Environment::xRotate <-180) 
			Environment::xRotate += 360; 
		Environment::xClick = x; 
	   
		Environment::yRotate += (y - Environment::yClick)/5.0; 

		if (Environment::yRotate > 180) 
			Environment::yRotate -= 360; 
		else if (Environment::yRotate <-180) 
			Environment::yRotate += 360; 
      	
		Environment::yClick = y; 

		glutPostRedisplay();
		return;
	}

	if(Environment::zoom){
		float old_size = Environment::scale;
		Environment::scale *= (1 + (y - Environment::yClick)/200.0); 
		if (Environment::scale <0) 
			Environment::scale = old_size; 
		Environment::yClick = y; 
		glutPostRedisplay();
		return;
	
	}

	if(Environment::move){
		if(x - Environment::xClick>0)
			Environment::modelPos[0]+=1/100.0;
		if(x - Environment::xClick<0)
			Environment::modelPos[0]-=1/100.0;

		if(y - Environment::yClick>0)
			Environment::modelPos[1]-=1/100.0;
		if(y - Environment::yClick<0)
			Environment::modelPos[1]+=1/100.0;

		Environment::yClick=y;
		Environment::xClick=x;
		glutPostRedisplay();
		return;
	}
	
}

void MouseEvent(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN){		
		Environment::xClick = x;
		Environment::yClick = y; 

		if(button==GLUT_LEFT_BUTTON){
			if(Environment::move)
				glutSetCursor(GLUT_CURSOR_INFO);
			else
			{
				Environment::rotateObject=true;
				glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			}
		}
		if(button==GLUT_MIDDLE_BUTTON){
			Environment::zoom=true;
			glutSetCursor(GLUT_CURSOR_BOTTOM_SIDE);
		}
	}
	else
	{
		Environment::zoom=false;
		Environment::rotateObject=false;
	}
}
