#include <GL/glut.h>
#include "MeshViewer.h"

enum {
  MENU_LIGHTING = 1,
  MENU_FILL,
  MENU_POINT,
  MENU_WIREFRAME,
  MENU_FLAT,
  MENU_SMOOTH,
  MENU_SHOWEDGE,
  MENU_AXIS,
  MENU_BOX,

  MENU_COLOR_GOLDEN,
  MENU_COLOR_BLACK,
  MENU_COLOR_WHITE,
  MENU_COLOR_GYPSUM,
  MENU_COLOR_NOISE,
  MENU_EXIT
};
float colorBlack[3]={0.1f,0.1f,0.1f};
float colorGold[3]={0.9f,0.5f,0.1f};
float colorWhite[3]={0.7f,0.7f,0.7f};
float colorPlaster[3]={0.5f,0.5f,0.5f};
float color[3];

extern MeshModel model;

void MenuEvent(int idCommand)
{
	if(idCommand>=100){
		loadMesh(Environment::modelFiles[idCommand/100-1].c_str(),model);
		computCenterAndSizeOfMesh(model);
		float modelSize=model.size[0];
		if(model.size[1]>modelSize)
			modelSize=model.size[1];
		if(model.size[2]>modelSize)
			modelSize=model.size[2];
		Environment::viewDistance=(modelSize/2)/(tan(Environment::viewAngle/2));
	}
	else
	{
		switch (idCommand)
		{
			case MENU_LIGHTING:
				Environment::lightingEnabled = !Environment::lightingEnabled;
				break;
			case MENU_POINT:
				Environment::showPoint=true;
				Environment::showEdge=false;
				break;
			case MENU_SHOWEDGE:
				Environment::showEdge=!Environment::showEdge;
				Environment::showPoint=false;
				break;
			case MENU_WIREFRAME:
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				Environment::showPoint=false;
				break;
			case MENU_FILL:
				glPolygonMode (GL_FRONT_AND_BACK,GL_FILL);
				Environment::showPoint=false;
				break;
			case MENU_FLAT:
				glPolygonMode (GL_FRONT_AND_BACK,GL_FILL);
				Environment::showPoint=false;
				glShadeModel(GL_FLAT);
				break;
			case MENU_SMOOTH:
				glPolygonMode (GL_FRONT_AND_BACK,GL_FILL);
				Environment::showPoint=false;
				glShadeModel(GL_SMOOTH);
				break;
			case MENU_AXIS:
				Environment::showCoordinateAxises=!Environment::showCoordinateAxises;
				break;
			case MENU_BOX:
				Environment::showModelBox=!Environment::showModelBox;
				break;

			case MENU_COLOR_BLACK:			
				Environment::modelRenderColor=colorBlack;
				Environment::modelColorNoise=false;
				break;
			case MENU_COLOR_GYPSUM:
				Environment::modelRenderColor=colorPlaster;
				Environment::modelColorNoise=false;
				break;
			case MENU_COLOR_WHITE:
				Environment::modelRenderColor=colorWhite;
				Environment::modelColorNoise=false;
				break;
			case MENU_COLOR_GOLDEN:
				Environment::modelRenderColor=colorGold;
				Environment::modelColorNoise=false;
				break;
			case MENU_COLOR_NOISE:
				Environment::modelColorNoise=true;
				break;
			case MENU_EXIT:
				exit (0);
				break;
		}
	}
	//Redraw
	glutPostRedisplay();
}

int BuildPopupMenu(){
	int mainMenu,subMenuModelFils,subMenuModelColor,subMenuShapeMode;

	if(Environment::modelFiles.size()>0){
		subMenuModelFils=glutCreateMenu(MenuEvent);
		for(int i=0;i<Environment::modelFiles.size();i++){
			glutAddMenuEntry(Environment::modelFiles[i].c_str(),100*(i+1));
		}
	}
	
	subMenuModelColor=glutCreateMenu(MenuEvent);
	glutAddMenuEntry("Plaster",MENU_COLOR_GYPSUM);
	glutAddMenuEntry("Golden",MENU_COLOR_GOLDEN);
	glutAddMenuEntry("White",MENU_COLOR_WHITE);
	glutAddMenuEntry("Black",MENU_COLOR_BLACK);
	glutAddMenuEntry("Random",MENU_COLOR_NOISE);

	subMenuShapeMode=glutCreateMenu(MenuEvent);
	glutAddMenuEntry("Point",MENU_POINT);
	glutAddMenuEntry("Wire frame",MENU_WIREFRAME);
	glutAddMenuEntry("Fill",MENU_FILL);
	glutAddMenuEntry("Flat",MENU_FLAT);
	glutAddMenuEntry("Smooth",MENU_SMOOTH);
	glutAddMenuEntry("Toggle Edge",MENU_SHOWEDGE);

	mainMenu = glutCreateMenu(MenuEvent);
	if(Environment::modelFiles.size()>0){
		glutAddSubMenu("Load Model",subMenuModelFils);
	}
	glutAddSubMenu("Model Color",subMenuModelColor);
	glutAddSubMenu("Shape Mode",subMenuShapeMode);

	glutAddMenuEntry ("Toggle lighting", MENU_LIGHTING);
	glutAddMenuEntry("Toggle Axises",MENU_AXIS);
	glutAddMenuEntry("Toggle Box",MENU_BOX);
	glutAddMenuEntry ("Exit", MENU_EXIT);
	return mainMenu;
}