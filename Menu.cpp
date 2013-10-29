#include <GL/glut.h>
#include "MeshViewer.h"

enum {
  MENU_LIGHTING = 1,
  MENU_FILL,
  MENU_POINT,
  MENU_WIREFRAME,
  MENU_FLAT,
  MENU_SMOOTH,
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
				break;
			case MENU_WIREFRAME:
				Environment::PolygonMode=GL_LINE;
				Environment::showPoint=false;
				break;
			case MENU_FILL:
				Environment::PolygonMode=GL_FILL;
				Environment::showPoint=false;
				break;
			case MENU_FLAT:
				Environment::showPoint=false;
				Environment::shadeModel=GL_FLAT;
				break;
			case MENU_SMOOTH:
				Environment::shadeModel=GL_SMOOTH;
				Environment::showPoint=false;
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
	int mainMenu,subMenuModelFils,subMenuModelColor,subMenuPolygon,subMenuShapeMode;

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

	subMenuPolygon=glutCreateMenu(MenuEvent);
	glutAddMenuEntry("Point",MENU_POINT);
	glutAddMenuEntry("Line",MENU_WIREFRAME);
	glutAddMenuEntry("Fill",MENU_FILL);

	subMenuShapeMode=glutCreateMenu(MenuEvent);
	glutAddMenuEntry("Flat",MENU_FLAT);
	glutAddMenuEntry("Smooth",MENU_SMOOTH);


	mainMenu = glutCreateMenu(MenuEvent);
	if(Environment::modelFiles.size()>0){
		glutAddSubMenu("Mesh File",subMenuModelFils);
	}
	glutAddSubMenu("Color",subMenuModelColor);
	glutAddSubMenu("Ploygon",subMenuPolygon);
	glutAddSubMenu("Shading",subMenuShapeMode);
	glutAddMenuEntry ("Toggle lighting", MENU_LIGHTING);
	glutAddMenuEntry("Toggle Bounding Box",MENU_BOX);
	glutAddMenuEntry ("Exit", MENU_EXIT);
	return mainMenu;
}