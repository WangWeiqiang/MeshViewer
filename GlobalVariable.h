#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif


#define VIEWING_DISTANCE_MIN  3.0
#define TEXTURE_ID_CUBE 1


typedef int BOOL;
#define TRUE 1
#define FALSE 0

static bool g_bLightingEnabled = true;
static bool g_bFillPolygons = true;
static bool g_bButton1Down = false;
static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;
static GLfloat g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;


static int g_yClick = 0;
static float g_lightPos[4] = { 10, 10, -100, 1 };  // Position of light

float w, h, tip = 0, turn = 0;

float ORG[3] = {0,0,0};

float XP[3] = {10,0,0}, XN[3] = {-10,0,0},YP[3] = {0,10,0}, YN[3] = {0,-10,0},ZP[3] = {0,0,10}, ZN[3] = {0,0,-10};

#ifdef _WIN32
static DWORD last_idle_time;
#else
static struct timeval last_idle_time;
#endif