#include <iostream>
#include "Menu.h"
using namespace std;
void Keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27:             // ESCAPE key
	  exit (0);
	  break;
  case 'l':
	  SelectFromMenu(MENU_LIGHTING);
	  break;
  case 'p':
	  SelectFromMenu(MENU_POLYMODE);
	  break;
  case 't':
	  SelectFromMenu(MENU_TEXTURING);
	  break;
  }
}


void MouseMotion(int x, int y)
{
  // If button1 pressed, zoom in/out if mouse is moved up/down.
  if (g_bButton1Down)
    {
      g_fViewDistance += (y - g_yClick) / 100;
      if (g_fViewDistance < VIEWING_DISTANCE_MIN)
         g_fViewDistance = VIEWING_DISTANCE_MIN;
      glutPostRedisplay();
	  cout<<g_fViewDistance<<endl;
    }
}

void MouseButton(int button, int state, int x, int y)
{
  // Respond to mouse button presses.
  // If button1 pressed, mark this state so we know in motion function.
  if (button == GLUT_LEFT_BUTTON)
    {
      g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
      g_yClick = y;
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutPostRedisplay();
}