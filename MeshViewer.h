//Copyright reserved by Wang weiqiang 2013
//GlobalVariable.h
//Version 0.1	Wang Weiqiang
#include <GL/glut.h>
#include <Windows.h>
#include <time.h>
#ifndef MESHVIEWER_H
#define MESHVIEWER_H

typedef int BOOL;
#define TRUE 1
#define FALSE 0

static class Environment{
public:
	static GLfloat	PI;

	static char		*windowTitle;
	static int		windowWidth;
	static int		windowHeight;
	static int		windowPosX;
	static int		windowPosY;
	static int		parentWidnow;
	static int		frontView;
	static int		topView;
	static int		leftView;
	static int		cameraView;
	static int		mainWindowWidth;
	static int		mainWindowHeight;
	static int		fullSubWindowID;
	static int		subWindowWidth;
	static int		subWindowHeight;

	static bool		lightingEnabled;
	static float	lightPos[4];
	static float	lightAmbient[4];
	static float	lightDiffuse[4];
	static float	lightSpecular[4];
	static bool		fillPolygons;
	static bool		shadeModel;

	static bool		buttonLeftDown;
	static bool		buttonRightDown;
	static bool		buttonMiddleDown;
	static int		yClick;
	static int		xClick;
	static bool		rotateObject;
	static bool		rotateCordinate;
	static bool		zoom;
	static bool		move;
	static clock_t	doubleClickFirst;
	static double	doubleClickPeriod;
	
	static int		viewAngle;
	static GLfloat	viewDistance;
	static GLfloat	camera[3];
	static GLfloat	center[3];
	static GLfloat	globalRoration[3];
	static GLfloat	xRotate;
	static GLfloat	yRotate;
	static GLfloat	zRotate;
	static float	scale;
	
	static DWORD	last_idle_time;
	static GLfloat	g_fTeapotAngle;
	static GLfloat	g_fTeapotAngle2;
	static GLfloat	mSpeed;
	static GLfloat	rSpeed;
	static GLfloat	lSpeed;
	
	static bool		trackballMove;
	static bool		trackingMouse;
	static bool		redrawContinue;
};


#endif