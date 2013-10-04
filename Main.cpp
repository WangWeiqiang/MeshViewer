#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif


#define VIEWING_DISTANCE_MIN  1.0
#define TEXTURE_ID_CUBE 1

enum {
  MENU_LIGHTING = 1,
  MENU_POLYMODE,
  MENU_TEXTURING,
  MENU_EXIT
};

typedef int BOOL;
#define TRUE 1
#define FALSE 0

static bool g_bLightingEnabled = true;
static bool g_bFillPolygons = true;
static bool g_bTexture = false;
static bool g_bButton1Down = false;
static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static int g_yClick = 0;
static float g_lightPos[4] = { 10, 10, -100, 1 };  // Position of light

float w, h, tip = 0, turn = 0;

float ORG[3] = {0,0,0};

float XP[3] = {3,0,0}, XN[3] = {-3,0,0},YP[3] = {0,3,0}, YN[3] = {0,-3,0},ZP[3] = {0,0,3}, ZN[3] = {0,0,-3};

#ifdef _WIN32
static DWORD last_idle_time;
#else
static struct timeval last_idle_time;
#endif

void initGL() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

void DrawCubeFace(float fSize)
{
  fSize /= 2.0;
  glBegin(GL_QUADS);
  glVertex3f(-fSize, -fSize, fSize);    glTexCoord2f (0, 0);
  glVertex3f(fSize, -fSize, fSize);     glTexCoord2f (1, 0);
  glVertex3f(fSize, fSize, fSize);      glTexCoord2f (1, 1);
  glVertex3f(-fSize, fSize, fSize);     glTexCoord2f (0, 1);
  glEnd();
}

void DrawCubeWithTextureCoords (float fSize)
{
  glPushMatrix();
  DrawCubeFace (fSize);
  glRotatef (90, 1, 0, 0);
  DrawCubeFace (fSize);
  glRotatef (90, 1, 0, 0);
  DrawCubeFace (fSize);
  glRotatef (90, 1, 0, 0);
  DrawCubeFace (fSize);
  glRotatef (90, 0, 1, 0);
  DrawCubeFace (fSize);
  glRotatef (180, 0, 1, 0);
  DrawCubeFace (fSize);
  glPopMatrix();
}

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

void InitGraphics(void)
{
   int width=0, height=0;
   int nComponents;
   void* pTextureImage;
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   // Create texture for cube; load marble texture from file and bind it
   //pTextureImage = read_texture("marble.rgb", &width, &height, &nComponents);
   glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);
   /*
   gluBuild2DMipmaps(GL_TEXTURE_2D,     // texture to specify
                     GL_RGBA,           // internal texture storage format
                     width,             // texture width
                     height,            // texture height
                     GL_RGBA,           // pixel format
                     GL_UNSIGNED_BYTE,	// color component format
                     pTextureImage);    // pointer to texture image
   */
   glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
   glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

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

void MouseButton(int button, int state, int x, int y)
{
  // Respond to mouse button presses.
  // If button1 pressed, mark this state so we know in motion function.
  if (button == GLUT_LEFT_BUTTON)
    {
      g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
      g_yClick = y;
    }
}

void MouseMotion(int x, int y)
{
  // If button1 pressed, zoom in/out if mouse is moved up/down.
  if (g_bButton1Down)
    {
      g_fViewDistance += (y - g_yClick) / 100;
      if (g_fViewDistance < VIEWING_DISTANCE_MIN)
         g_fViewDistance = VIEWING_DISTANCE_MIN;
      glutPostRedisplay();
	  cout<<g_fViewDistance<<endl;
    }
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

void SelectFromMenu(int idCommand)
{
  switch (idCommand)
    {
    case MENU_LIGHTING:
      g_bLightingEnabled = !g_bLightingEnabled;
      if (g_bLightingEnabled)
         glEnable(GL_LIGHTING);
      else
         glDisable(GL_LIGHTING);
      break;
    case MENU_POLYMODE:
      g_bFillPolygons = !g_bFillPolygons;
      glPolygonMode (GL_FRONT_AND_BACK, g_bFillPolygons ? GL_FILL : GL_LINE);
      break;      
    case MENU_TEXTURING:
      g_bTexture = !g_bTexture;
      if (g_bTexture)
         glEnable(GL_TEXTURE_2D);
      else
         glDisable(GL_TEXTURE_2D);
      break;    
    case MENU_EXIT:
      exit (0);
      break;
    }
  // Almost any menu selection requires a redraw
  glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27:             // ESCAPE key
	  exit (0);
	  break;
  case 'l':
	  SelectFromMenu(MENU_LIGHTING);
	  break;
  case 'p':
	  SelectFromMenu(MENU_POLYMODE);
	  break;
  case 't':
	  SelectFromMenu(MENU_TEXTURING);
	  break;
  }
}

int BuildPopupMenu (void)
{
  int menu;
  menu = glutCreateMenu (SelectFromMenu);
  glutAddMenuEntry ("Toggle lighting\tl", MENU_LIGHTING);
  glutAddMenuEntry ("Toggle polygon fill\tp", MENU_POLYMODE);
  glutAddMenuEntry ("Toggle texturing\tt", MENU_TEXTURING);
  glutAddMenuEntry ("Exit demo\tEsc", MENU_EXIT);
  return menu;
}

int main2(int argcp,char **argv){
	glutInit(&argcp,argv);
	//glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600,600);
	glutCreateWindow("Mesh Viewer");
	//glEnable(GL_DEPTH_TEST);
	
	//InitGraphics();

	glutDisplayFunc (display);

	/*
	glutReshapeFunc (reshape);
	glutKeyboardFunc (Keyboard);
	glutMouseFunc (MouseButton);
	glutMotionFunc (MouseMotion);
	glutIdleFunc (AnimateScene);
	// Create our popup menu
	BuildPopupMenu ();
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	#ifdef _WIN32
	  last_idle_time = GetTickCount();
	#else
	  gettimeofday (&last_idle_time, NULL);
	#endif
	  // Turn the flow of control over to GLUT
	*/
	glutMainLoop ();
	return 0;
}

void windowResize(int width,int height){
	int viewPort=0;
	int viewPortX=0,viewPortY=0;
	if(width>height){
		viewPort=height;
		viewPortX=(width-height)/2;
	}
	else
	{
		viewPort=width;
		viewPortY=(height-width)/2;
	}
	glViewport(viewPortX,viewPortY,viewPort,viewPort);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
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
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the event-processing loop
   return 0;
}



