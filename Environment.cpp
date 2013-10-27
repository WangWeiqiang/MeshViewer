#include <GL\glut.h>
#include <vector>
#include <iostream>
#include <cmath>
#include "MeshViewer.h"
#include <Windows.h>
using namespace std;
GLfloat	Environment::PI=3.1415926f;
float colorGolden[3]={0.7f,0.3f,0.1f};

vector<string> Environment::modelFiles;
char	*Environment::windowTitle	="Mesh Viewer - DMT Assignment";
int		Environment::windowWidth	=600;
int		Environment::windowHeight	=600;
int		Environment::windowPosX		=0;
int		Environment::windowPosY		=0;

bool	Environment::fillPolygons		=false;
bool	Environment::lightingEnabled	=true;
GLfloat	Environment::lightPos[4]		={1.0,1.0,1.0,0.0};
GLfloat	Environment::lightAmbient[4]	={1.0f,1.0f,1.0f,1.0f};
GLfloat	Environment::lightDiffuse[4]	={1.0f,1.0f,1.0f,0.5f};
GLfloat	Environment::lightSpecular[4]	={1.0f,1.0f,1.0f,1.0f};
int		Environment::shadeModel=GL_SMOOTH;
float	*Environment::modelRenderColor	=colorGolden;
bool	Environment::modelColorNoise=false;;
GLfloat Environment::modelPos[3]={0,0.7,0};
int		Environment::PolygonMode=GL_FILL;

bool	Environment::buttonLeftDown		=false;
bool	Environment::buttonRightDown	=false;
bool	Environment::buttonMiddleDown	=false;
bool	Environment::rotateObject		=false;
bool	Environment::rotateCordinate	=false;
bool	Environment::move				=false;
bool	Environment::zoom				=false;
int		Environment::xClick				=0;
int		Environment::yClick				=0;

int		Environment::viewAngle			=45;
GLfloat Environment::viewDistance		=2.0f;
GLfloat Environment::globalRoration[3]	={0.0f,0.0f,0.0f};
GLfloat Environment::xRotate			=0.0;
GLfloat Environment::yRotate			=0.0;
GLfloat Environment::zRotate			=0.0;
GLfloat Environment::camera[3]			={0,1.0f,viewDistance};
GLfloat Environment::center[3]			={0.0f,0.0f,0.0f};
float	Environment::scale				=1;


DWORD	Environment::last_idle_time=GetTickCount();
GLfloat	Environment::mSpeed=0.4f;
GLfloat	Environment::rSpeed=0.02f;
GLfloat	Environment::lSpeed=0.4f;

bool	Environment::trackballMove=false;
bool	Environment::trackingMouse=false;
bool	Environment::redrawContinue=false;

bool	Environment::showPoint=false;
bool	Environment::showEdge=false;
bool	Environment::showModelBox =false;
bool	Environment::showCoordinateAxises=true;