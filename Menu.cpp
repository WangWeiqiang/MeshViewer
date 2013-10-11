#include <GL/glut.h>
#include "MeshViewer.h"

enum {
  MENU_LIGHTING = 1,
  MENU_FILL=2,
  MENU_WIREFRAME=3,
  MENU_FLAT=4,
  MENU_SMOOTH=5,
  MENU_EXIT=6
};


void MenuEvent(int idCommand)
{
	switch (idCommand)
	{
		case MENU_LIGHTING:
			Environment::lightingEnabled = !Environment::lightingEnabled;
			if (Environment::lightingEnabled)
			{
				glLightfv(GL_LIGHT0, GL_POSITION,Environment::lightPos);
				glLightfv(GL_LIGHT0, GL_AMBIENT,Environment::lightAmbient);
				glLightfv(GL_LIGHT0, GL_DIFFUSE,Environment::lightDiffuse);
				glLightfv(GL_LIGHT0, GL_SPECULAR,Environment::lightSpecular);
				glEnable(GL_LIGHT0);
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_LIGHTING);
			}
			else
				glDisable(GL_LIGHTING);
			break;
		case MENU_WIREFRAME:
			glPolygonMode (GL_FRONT_AND_BACK,GL_LINE);
			break;
		case MENU_FILL:
			glPolygonMode (GL_FRONT_AND_BACK,GL_FILL);
			break;
		case MENU_FLAT:
			glShadeModel(GL_FLAT);
			break;
		case MENU_SMOOTH:
			glShadeModel(GL_SMOOTH);
			break;
		case MENU_EXIT:
			exit (0);
			break;
	}
	//Redraw
	glutPostRedisplay();
}

int BuildPopupMenu(){
	int mainMenu,subMenuModel,subMenuShapeMode;

	
	
	subMenuModel=glutCreateMenu(MenuEvent);
	glutAddMenuEntry("Rubbat",0);
	glutAddMenuEntry("Rubbat1",1);
	glutAddMenuEntry("Rubbat2",2);

	subMenuShapeMode=glutCreateMenu(MenuEvent);
	glutAddMenuEntry("Wire frame",MENU_WIREFRAME);
	glutAddMenuEntry("Fill",MENU_FILL);
	glutAddMenuEntry("Flat",MENU_FLAT);
	glutAddMenuEntry("Smooth",MENU_SMOOTH);

	mainMenu = glutCreateMenu(MenuEvent);
	glutAddSubMenu("Model",subMenuModel);
	glutAddSubMenu("Shape Mode",subMenuShapeMode);
	glutAddMenuEntry ("Toggle lighting\tl", MENU_LIGHTING);

	
	glutAddMenuEntry ("Exit demo\tEsc", MENU_EXIT);
	return mainMenu;
}