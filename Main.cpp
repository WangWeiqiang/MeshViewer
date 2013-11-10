#include <iostream>
#include <Windows.h>
#include <glut.h>
#include <stdio.h>
#include <ddraw.h>
#include <stdlib.h>
#include "Environment.h"
#include "MeshHelper.cpp"
#include "Menu.cpp"
#include "UIInteraction.cpp"
using namespace std;

HANDLE hThread;
int windowid=0;
GLuint unTexture=0;
AUX_RGBImageRec *TextureImage;
MeshModel model;
const char* modelfilename;
float loadingAngle=0;

void displayView()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_MODELVIEW);

	if(Environment::projection==1){
		gluPerspective(45,Environment::windowWidth/Environment::windowWidth,0.01,10000);
	}
	else
	{
		glOrtho(-1,1,-1,1,0.001,10000);
	}
	glLoadIdentity();

	

	gluLookAt(0,1,2,0,0.7,0,0, 1, 0);
	glEnable(Environment::shadeModel);
	glShadeModel(Environment::shadeModel);
	glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_NORMALIZE);

	Environment::lightingEnabled?glEnable(GL_LIGHTING):glDisable(GL_LIGHTING);
	
	drawGroundAndAxis();

	glPolygonMode (GL_FRONT_AND_BACK,Environment::PolygonMode);

	if(Environment::showLoading){
		glTranslatef (Environment::modelPos[0],Environment::modelPos[1],sin(loadingAngle)*0.1);
		//glRotatef (loadingAngle, 1, 0, 0);
		glScalef(1,1,1);
		showLoading(TextureImage);
		loadingAngle+=0.01;

		glutPostWindowRedisplay(windowid);
	}
	else
	{
		glTranslatef (Environment::modelPos[0],Environment::modelPos[1],0);
		glRotatef (Environment::xRotate, 0, 1, 0);
		glRotatef (Environment::yRotate, 1, 0, 0);
		glScalef(Environment::scale,Environment::scale,Environment::scale);
		rendMesh(model);
		glutPostWindowRedisplay(windowid);
	}
	
	glutSwapBuffers();
}

void reshape(int width,  int height) 
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(Environment::projection==1){
		gluPerspective(45, (GLfloat)width/(GLfloat)height,0.01,10000);
	}
	else
	{
		glOrtho(-1,1,-1,1,0.001,10000);
	}
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
	
	GLfloat lightambient[] = {1,1,1,1.0};
	GLfloat lightdiffuse[] = {1.0,1.0,1.0,1.0};
	GLfloat lightspecular[] = {1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightdiffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lightspecular);

	glLightModelf(GL_LIGHT_MODEL_AMBIENT, (0.0, 0.0, 0.0));

	GLfloat emission[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat ambient[] ={0.2,0.2,0.2,0.0};
	GLfloat diffuse[] ={0.5,0.5,0.5,0.5};
	GLfloat specular[] ={0.5,0.5,0.5,0.0 };
	GLfloat shininess[] ={180.0};
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

int main(int argc, char** argv) {
	unTexture = 0;
	

	string filename="";
	string appPath=getAppFolder();
	appPath+="\\models\\";
	getFilesFromDirectory(Environment::modelFiles,appPath);

	string loadingimg = appPath+"loading.bmp";
	char *cstr = new char[loadingimg.length() + 1];
	strcpy(cstr, loadingimg.c_str());

	TextureImage=LoadBMP(cstr);
	
	if(argc>=2)
	{
      for(int i=0;i<argc;i++){
		  if(strstr(argv[i],".m")!=NULL){
			  filename=argv[i];
		  }
	  }
	}

	
	if(filename==""){
		if(Environment::modelFiles.size()>0){
			filename=Environment::modelFiles[0];
		}
	}
	if(filename!=""){
		modelfilename=filename.c_str();
		
		hThread = CreateThread(NULL, 0, loadData, NULL, 0, NULL);
	}
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
	HDC hdc = GetDC (NULL);
	int width = GetDeviceCaps (hdc, HORZRES);
	int height = GetDeviceCaps (hdc, VERTRES);
	ReleaseDC (NULL, hdc);

	glutInitWindowPosition((width-Environment::windowWidth)/2, (height-Environment::windowWidth)/2); //make the window align to center of screen
	glutInitWindowSize(Environment::windowWidth, Environment::windowHeight);
	windowid=glutCreateWindow(Environment::windowTitle);
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