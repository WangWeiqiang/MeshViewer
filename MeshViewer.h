//Copyright reserved by Wang weiqiang 2013
//GlobalVariable.h
//Version 0.1	Wang Weiqiang
#include <GL/glut.h>
#include <Windows.h>
#ifndef MESHVIEWER_H
#define MESHVIEWER_H

#define VIEWING_DISTANCE_MIN  3.0
#define TEXTURE_ID_CUBE 1


typedef int BOOL;
#define TRUE 1
#define FALSE 0

static class Environment{
public:
	static int		windowWidth;
	static int		windowHeight;
	static int		windowPosX;
	static int		windowPosY;
	static bool		g_bLightingEnabled;
	static bool		g_bFillPolygons;
	static bool		g_bButtonLeftDown;
	static bool		g_bButtonRightDown;
	static bool		g_bButtonMiddleDown;
	static GLfloat	g_fViewDistance;
	static int		g_yClick;
	static int		g_xClick;
	static GLfloat	g_xRotate;
	static GLfloat	g_yRotate;
	static GLfloat	g_zRotate;
	static float	g_lightPos[4];
	static float	g_lightAmbient[4];
	static float	g_lightDiffuse[4];
	static float	g_lightSpecular[4];
	static DWORD	last_idle_time;
	static GLfloat	g_fTeapotAngle;
	static GLfloat	g_fTeapotAngle2;
	static GLfloat	PI;
	static GLfloat	mSpeed;
	static GLfloat	rSpeed;
	static GLfloat	lSpeed;
	static GLfloat	camera[3];
	static GLfloat	center[3];
};


#endif