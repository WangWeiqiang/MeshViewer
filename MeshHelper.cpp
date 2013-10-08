#include <GL/glut.h>
#include "MeshViewer.h"
static int g_Width = Environment::windowWidth;                          // Initial window width
static int g_Height = Environment::windowHeight;                         // Initial window height
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;

void reshape(GLint width, GLint height)
{
   g_Width = width;
   g_Height = height;
   glViewport(0, 0, g_Width, g_Height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(65.0, (float)g_Width / g_Height, g_nearPlane, g_farPlane);
   glMatrixMode(GL_MODELVIEW);
}

void drawAxes(void){
	
	//glRotatef (0 , 1,0,0);
	//glRotatef (0, 0,1,0);
	//glScalef (0.25, 0.25, 0.25);
	float ORG[3] = {0,0,0};
	float XP[3] = {10,0,0}, XN[3] = {-10,0,0},YP[3] = {0,10,0}, YN[3] = {0,-10,0},ZP[3] = {0,0,10}, ZN[3] = {0,0,10};

	
	glBegin (GL_LINES);
	glLineWidth (4.0);

	glColor3f (1,0,0); // X axis is red.
	glVertex3fv (ORG);
	glVertex3fv (XP );

	glColor3f (0,1,0); // Y axis is green.
	glVertex3fv (ORG);
	glVertex3fv (YP );
	
	glColor3f (0,0,1); // z axis is blue.
	glVertex3fv (ORG);
	glVertex3fv (ZP ); 
	glEnd();
	
}