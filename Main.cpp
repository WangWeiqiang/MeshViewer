#include <iostream>
#include <Windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <string.h>
#include "MeshViewer.h"
#include "MeshHelper.cpp"
#include "Menu.cpp"
#include "UIInteraction.cpp"
using namespace std;


#ifndef UNICODE  
  typedef std::string String; 
#else
  typedef std::wstring String; 
#endif

MeshModel model;


void displayView()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_MODELVIEW);

	gluPerspective(45,Environment::windowWidth/Environment::windowWidth,0.01,10000);
	glLoadIdentity();

	glPushMatrix ();

	gluLookAt(0,1,2,0,0.7,0,0, 1, 0);
	glEnable(Environment::shadeModel);
	glShadeModel(Environment::shadeModel);
	glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_NORMALIZE);
	
	Environment::lightingEnabled?glEnable(GL_LIGHTING):glDisable(GL_LIGHTING);
	
	drawGroundAndAxis();

	glTranslatef (Environment::modelPos[0],Environment::modelPos[1],0);
	glRotatef (Environment::xRotate, 0, 1, 0);
	glRotatef (Environment::yRotate, 1, 0, 0);
	glScalef(Environment::scale,Environment::scale,Environment::scale);

	glPolygonMode (GL_FRONT_AND_BACK,Environment::PolygonMode);
	rendMesh(model);
	
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int width,  int height) 
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)width/(GLfloat)height,0.01,10000);

	glMatrixMode(GL_MODELVIEW);
} 

void init(){
	glClearColor(0.0,0.0,0.0,1.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	GLfloat lightambient[] = {0.5,0.5,0.5,1.0};
	GLfloat lightdiffuse[] = {1.0,1.0,1.0,1.0};
	GLfloat lightspecular[] = {1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightdiffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lightspecular);
	glLightModelf(GL_LIGHT_MODEL_AMBIENT, (0.0, 0.0, 0.0));

	GLfloat emission[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat ambient[] ={0.2,0.2,0.2,0.0};
	GLfloat diffuse[] ={1.0,0.5,0.5,0.5};
	GLfloat specular[] ={0.5,0.5,0.5,0.0 };
	GLfloat shininess[] ={100.0};
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

int main(int argc, char** argv) {
	string filename="";
	string appPath=getAppFolder();
	appPath+="\\models\\";
	getFilesFromDirectory(Environment::modelFiles,appPath);

	if(argc>=2)
	{
      for(int i=0;i<argc;i++){
		  if(strstr(argv[i],".m")!=NULL){
			  filename=argv[i];
		  }
	  }
	}

	cout<<"Loading mesh model ..."<<endl;
	if(filename==""){
		if(Environment::modelFiles.size()>0){
			filename=Environment::modelFiles[0];
		}
	}
	if(filename!=""){
		loadMesh(filename.c_str(),model);
		computCenterAndSizeOfMesh(model);
		float modelSize=model.size[0];
		if(model.size[1]>modelSize)
			modelSize=model.size[1];
		if(model.size[2]>modelSize)
			modelSize=model.size[2];
		
		cout<<"Center:"<<model.center[0]<<","<<model.center[1]<<","<<model.center[2]<<endl;
		cout<<"H:"<<model.size[0]<<",W:"<<model.size[1]<<",L:"<<model.size[2];
	}
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
	HDC hdc = GetDC (NULL);
	int width = GetDeviceCaps (hdc, HORZRES);
	int height = GetDeviceCaps (hdc, VERTRES);
	ReleaseDC (NULL, hdc);

	glutInitWindowPosition((width-Environment::windowWidth)/2, (height-Environment::windowWidth)/2); //make the window align to center of screen
	glutInitWindowSize(Environment::windowWidth, Environment::windowHeight);
	glutCreateWindow(Environment::windowTitle);
	init();
	glutDisplayFunc(displayView);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMotion);
	BuildPopupMenu();
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	glEnable(GL_DEPTH_TEST);
	
	glutMainLoop();
	return 0;
}