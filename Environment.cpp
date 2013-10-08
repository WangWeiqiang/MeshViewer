#include <GL\glut.h>
#include <cmath>
#include "MeshViewer.h"
int		Environment::windowWidth	=500;
int		Environment::windowHeight	=500;
int		Environment::windowPosX		=0;
int		Environment::windowPosY		=0;
int		Environment::g_xClick		=0;
int		Environment::g_yClick		=0;
GLfloat	Environment::PI				=3.1415926f;
GLfloat Environment::g_xRotate=PI/4;
GLfloat Environment::g_yRotate=PI/4;
GLfloat Environment::g_zRotate=PI/4;
bool	Environment::g_bButtonLeftDown	=false;
bool	Environment::g_bButtonRightDown	=false;
bool	Environment::g_bButtonMiddleDown=false;
bool	Environment::g_bFillPolygons=false;
bool	Environment::g_bLightingEnabled=false;
GLfloat Environment::g_fViewDistance=10.0f;
float	Environment::g_lightPos[4]={ 10, 10, -100, 1 };
DWORD	Environment::last_idle_time=GetTickCount();
GLfloat Environment::g_fTeapotAngle = 0.0f;
GLfloat Environment::g_fTeapotAngle2 = 0.0f;
GLfloat	Environment::mSpeed=0.4f;
GLfloat	Environment::rSpeed=0.02f;
GLfloat	Environment::lSpeed=0.4f;
GLfloat Environment::camera[3]={0.0f,0.0f,-g_fViewDistance};
GLfloat Environment::center[3] = {0.0f, 0.0f, 0.0f};
