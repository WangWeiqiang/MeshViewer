#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "MeshHelper.h"
#include "Menu.h"
#include "UIInteraction.h"
using namespace std;

void RenderObjects(void)
{
  float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
  float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
  float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
  float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };

  // Child object (teapot) ... relative transform, and render
  glPushMatrix();
  glTranslatef(0, 0, 0);
  //glRotatef(g_fTeapotAngle2, 1, 1, 0);
  //glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
  //glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
  //glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
  glColor4fv(colorBronzeDiff);
  //glBindTexture(GL_TEXTURE_2D, 0);
  glutSolidTeapot(0.8);
  glPopMatrix(); 

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BITS);   // Clear the color buffer with current clearing color
	
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0, 0, -g_fViewDistance, 0, 0, -1, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);
	
	drawAxes();
	RenderObjects();
	glutSwapBuffers();	
	glFlush();  // Render now
}

void AnimateScene(void)
{
  float dt;
#ifdef _WIN32
  DWORD time_now;
  time_now = GetTickCount();
  dt = (float) (time_now - last_idle_time) / 1000.0;
#else
  // Figure out time elapsed since last call to idle function
  struct timeval time_now;
  gettimeofday(&time_now, NULL);
  dt = (float)(time_now.tv_sec  - last_idle_time.tv_sec) +
  1.0e-6*(time_now.tv_usec - last_idle_time.tv_usec);
#endif
  // Animate the teapot by updating its angles
  g_fTeapotAngle += dt * 30.0;
  g_fTeapotAngle2 += dt * 100.0;
  // Save time_now for next time
  last_idle_time = time_now;
  // Force redraw
  glutPostRedisplay();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);          // Initialize GLUT
   glutCreateWindow("Mesh Viewer");  // Create window with the given title
   glutInitWindowSize(320, 320);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   gluPerspective(0.0,0.0,1,100);
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutMouseFunc (MouseButton);
   glutMotionFunc (MouseMotion);
   glutIdleFunc (AnimateScene);
   glutReshapeFunc(windowResize);
   BuildPopupMenu ();
   glutAttachMenu (GLUT_RIGHT_BUTTON);
   //initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the event-processing loop
   return 0;
}



