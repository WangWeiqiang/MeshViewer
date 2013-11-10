//Copyright reserved by Wang weiqiang 2013
//GlobalVariable.h
//Version 0.1	Wang Weiqiang
#include <windows.h>
#include <glut.h>
#include <stdlib.h>
#include <vector>
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

typedef int BOOL;
#define TRUE 1
#define FALSE 0
using namespace std;

static class Environment{
public:
	static GLfloat	PI;

	static vector<string> modelFiles;
	static char		*windowTitle;
	static int		windowWidth;
	static int		windowHeight;
	static int		windowPosX;
	static int		windowPosY;

	static bool		lightingEnabled;
	static GLint	projection;
	static bool		fillPolygons;
	static int		shadeModel;
	static float	*modelRenderColor;
	static bool		modelColorNoise;
	static GLfloat  modelPos[3];
	static int		PolygonMode;
	static bool		showLoading;

	static bool		buttonLeftDown;
	static bool		buttonRightDown;
	static bool		buttonMiddleDown;
	static int		yClick;
	static int		xClick;
	static bool		rotateObject;
	static bool		rotateCordinate;
	static bool		zoom;
	static bool		move;

	static GLfloat	center[3];
	static GLfloat	xRotate;
	static GLfloat	yRotate;
	static GLfloat	zRotate;
	static float	scale;
	
	static bool		showPoint;
	static bool		showModelBox;
	static bool		showCoordinateAxises;
};
#endif