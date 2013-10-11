#include <GL\glut.h>
#include <cmath>
#include "MeshViewer.h"
#include <Windows.h>

GLfloat	Environment::PI=3.1415926f;

char	*Environment::windowTitle	="Mesh Viewer - DMT Assignment";
int		Environment::windowWidth	=575;
int		Environment::windowHeight	=575;
int		Environment::windowPosX		=0;
int		Environment::windowPosY		=0;
GLuint	Environment::parentWidnow	=0;
GLuint	Environment::frontView		=0;
GLuint	Environment::topView		=0;
GLuint	Environment::leftView		=0;
GLuint	Environment::cameraView		=0;
int		Environment::fullSubWindowID=0;
int		Environment::mainWindowWidth=0;
int		Environment::mainWindowHeight=0;
int		Environment::subWindowWidth	=256;
int		Environment::subWindowHeight=256;

bool	Environment::fillPolygons		=false;
bool	Environment::lightingEnabled	=false;
GLfloat	Environment::lightPos[4]		={31,61,10,1};
GLfloat	Environment::lightAmbient[4]	={1.0f,1.0f,1.0f,1.0f};
GLfloat	Environment::lightDiffuse[4]	={1.0f,1.0f,1.0f,0.5f};
GLfloat	Environment::lightSpecular[4]	={1.0f,1.0f,1.0f,1.0f};
bool	Environment::shadeModel			=GL_FLAT;

bool	Environment::buttonLeftDown		=false;
bool	Environment::buttonRightDown	=false;
bool	Environment::buttonMiddleDown	=false;
bool	Environment::keySpaceDown		=false;
bool	Environment::keyShiftDown		=false;
int		Environment::xClick				=0;
int		Environment::yClick				=0;
clock_t	Environment::doubleClickFirst	=clock();
double	Environment::doubleClickPeriod	=400;

GLfloat Environment::viewDistance		=30.0f;
GLfloat Environment::globalRoration[3]	={0.0f,0.0f,0.0f};
GLfloat Environment::xRotate			=PI/4;
GLfloat Environment::yRotate			=PI/4;
GLfloat Environment::zRotate			=PI/4;
GLfloat Environment::camera[3]			={15.0f,15.0f,-viewDistance};
GLfloat Environment::center[3]			={0.0f,0.0f,0.0f};
GLfloat	Environment::move[3]			={0.0f,0.0f,0.0f};


DWORD	Environment::last_idle_time=GetTickCount();
GLfloat Environment::g_fTeapotAngle = 0.0f;
GLfloat Environment::g_fTeapotAngle2 = 0.0f;
GLfloat	Environment::mSpeed=0.4f;
GLfloat	Environment::rSpeed=0.02f;
GLfloat	Environment::lSpeed=0.4f;

bool	Environment::trackballMove=false;
bool	Environment::trackingMouse=false;
bool	Environment::redrawContinue=false;