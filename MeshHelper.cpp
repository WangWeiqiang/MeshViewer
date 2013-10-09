#include <GL/glut.h>
#include "MeshViewer.h"
static int g_Width = Environment::windowWidth;                          // Initial window width
static int g_Height = Environment::windowHeight;                         // Initial window height
static GLfloat g_nearPlane = 5;
static GLfloat g_farPlane = 100;

void reshape(GLint width, GLint height)
{
	glViewport(0, 0, (GLsizei) Environment::windowWidth, (GLsizei) Environment::windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawAxes(void){
	glPushMatrix();
	/* No name for grey sphere */
	glColor3f(0.3,0.3,0.3);
	glutSolidSphere(0.2, 10, 10);
	glPushMatrix();
	
	glPushName(1);            /* Red cone is 1 */
	glColor3f(1,0,0);
	glRotatef(90,0,1,0);
	glutSolidCone(0.1, 4.0,10,10);
	glPopName();
	glPopMatrix();
	glPushMatrix ();

	glPushName(2);            /* Green cone is 2 */
	glColor3f(0,1,0);
	glRotatef(-90,1,0,0);
	glutSolidCone(0.1, 4.0, 10, 10);
	glPopName();
	glPopMatrix();
	
	glColor3f(0,0,1);         /* Blue cone is 3 */
	glPushName(3);
	glutSolidCone(0.1, 4.0, 10,10);
	glPopName();
	glPopMatrix();
	
}