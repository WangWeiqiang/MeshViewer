#include <GL/glut.h>
#include "GlobalVariable.h"
enum {
  MENU_LIGHTING = 1,
  MENU_POLYMODE,
  MENU_TEXTURING,
  MENU_EXIT
};

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