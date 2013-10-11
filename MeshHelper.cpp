#include <GL/glut.h>
#include "MeshViewer.h"
static int g_Width = Environment::windowWidth;                          // Initial window width
static int g_Height = Environment::windowHeight;                         // Initial window height
static GLfloat g_nearPlane = 5;
static GLfloat g_farPlane = 100;
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10; 
void setfont(char* name, int size)
{
	font_style = GLUT_BITMAP_HELVETICA_10;
	if (strcmp(name, "helvetica") == 0) {
		if (size == 12)
			font_style = GLUT_BITMAP_HELVETICA_12;
		else if (size == 18)
			font_style = GLUT_BITMAP_HELVETICA_18;
        } else if (strcmp(name, "times roman") == 0) {
			font_style = GLUT_BITMAP_TIMES_ROMAN_10;
			if (size == 24)
				font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	} else if (strcmp(name, "8x13") == 0) {
		font_style = GLUT_BITMAP_8_BY_13;
		} else if (strcmp(name, "9x15") == 0) {
			font_style = GLUT_BITMAP_9_BY_15;
	}
}

void drawstr(GLuint x, GLuint y, const char* format, int length)
{
	glRasterPos2i(x, y);
	for(int i=0; i<length; ++i)
		glutBitmapCharacter(font_style, *(format+i) );
}

void drawAxes(void){
	glPushMatrix();
	/* No name for grey sphere */
	glColor3f(0.3,0.3,0.3);
	glutSolidSphere(0.1, 10, 10);
	glPushMatrix();
	
	glPushName(1);            /* Red cone is 1 */
	glColor3f(1,0,0);
	glRotatef(90,0,1,0);
	glutSolidCone(0.05, 4.0,10,10);
	glPopName();
	glPopMatrix();
	glPushMatrix ();

	glPushName(2);            /* Green cone is 2 */
	glColor3f(0,1,0);
	glRotatef(-90,1,0,0);
	glutSolidCone(0.05, 4.0, 10, 10);
	glPopName();
	glPopMatrix();
	
	glColor3f(0,0,1);         /* Blue cone is 3 */
	glPushName(3);
	glutSolidCone(0.05, 4.0, 10,10);
	glPopName();
	glPopMatrix();
	
}