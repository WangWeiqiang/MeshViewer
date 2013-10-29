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
int		Environment::shadeModel=GL_SMOOTH;
float	*Environment::modelRenderColor	=colorGolden;
bool	Environment::modelColorNoise=false;;
GLfloat Environment::modelPos[3]={0,0.7,0};
int		Environment::PolygonMode=GL_FILL;

bool	Environment::buttonLeftDown		=false;
bool	Environment::buttonRightDown	=false;
bool	Environment::buttonMiddleDown	=false;
bool	Environment::rotateObject		=false;
bool	Environment::move				=false;
bool	Environment::zoom				=false;
int		Environment::xClick				=0;
int		Environment::yClick				=0;

GLfloat Environment::xRotate			=0.0;
GLfloat Environment::yRotate			=0.0;
GLfloat Environment::zRotate			=0.0;
GLfloat Environment::center[3]			={0.0f,0.0f,0.0f};
float	Environment::scale				=1;

bool	Environment::showPoint=false;
bool	Environment::showModelBox =false;
bool	Environment::showCoordinateAxises=true;