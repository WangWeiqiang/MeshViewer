#include <GL/glut.h>
#include "MeshViewer.h"

enum {
  MENU_LIGHTING = 1,
  MENU_POLYMODE=2,
  MENU_TEXTURING=3,
  MENU_EXIT=4
};


void MenuEvent(int idCommand)
{
	switch (idCommand)
	{
		case MENU_LIGHTING:
			Environment::g_bLightingEnabled = !Environment::g_bLightingEnabled;
			if (Environment::g_bLightingEnabled)
				glEnable(GL_LIGHTING);
			else
				glDisable(GL_LIGHTING);
			break;
		case MENU_POLYMODE:
			Environment::g_bFillPolygons = !Environment::g_bFillPolygons;
			glPolygonMode (GL_FRONT_AND_BACK, Environment::g_bFillPolygons ? GL_FILL : GL_LINE);
			break;
		case MENU_EXIT:
			exit (0);
			break;
	}
	//Redraw
	glutPostRedisplay();
}

int BuildPopupMenu(){
	int menu=0;
	menu = glutCreateMenu(MenuEvent);
	glutAddMenuEntry ("Toggle lighting\tl", MENU_LIGHTING);
	glutAddMenuEntry ("Toggle polygon fill\tp", MENU_POLYMODE);
	glutAddMenuEntry ("Toggle texturing\tt", MENU_TEXTURING);
	glutAddMenuEntry ("Exit demo\tEsc", MENU_EXIT);
	return menu;
}