#include <GL/glut.h>
#include "GlobalVariable.h"
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
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
	glPushMatrix ();
	glRotatef (tip , 1,0,0);
	glRotatef (turn, 0,1,0);
	glScalef (0.25, 0.25, 0.25);

	glLineWidth (2.0);

	glBegin (GL_LINES);
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

	glPopMatrix ();

}