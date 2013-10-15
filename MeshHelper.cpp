#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include "MeshViewer.h"
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "MeshModel.cpp"
static int g_Width = Environment::windowWidth;                          // Initial window width
static int g_Height = Environment::windowHeight;                         // Initial window height
static GLfloat g_nearPlane = 5;
static GLfloat g_farPlane = 100;
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10; 
struct MeshModel;

void setfont(char* name, int size)
{
	font_style = GLUT_BITMAP_HELVETICA_10;
	if (strcmp(name, "helvetica") == 0) {
		if (size == 12)
			font_style = GLUT_BITMAP_HELVETICA_12;
		else if (size == 18)
			font_style = GLUT_BITMAP_HELVETICA_18;
        } else if (strcmp(name, "times roman") == 0) {
			font_style = GLUT_BITMAP_TIMES_ROMAN_10;
			if (size == 24)
				font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	} else if (strcmp(name, "8x13") == 0) {
		font_style = GLUT_BITMAP_8_BY_13;
		} else if (strcmp(name, "9x15") == 0) {
			font_style = GLUT_BITMAP_9_BY_15;
	}
}

void drawstr(GLuint x, GLuint y, const char* format, int length)
{
	glRasterPos2i(x, y);
	for(int i=0; i<length; ++i)
		glutBitmapCharacter(font_style, *(format+i) );
}

void drawAxes(MeshModel &model){
	glPushMatrix();
	/* No name for grey sphere */
	glColor3f(0.3,0.3,0.3);
	glutSolidSphere(0.1, 10, 10);
	glPushMatrix();
	
	glPushName(1);            /* Red cone is 1 */
	glColor3f(1,0,0);
	glRotatef(90,0,1,0);
	glutSolidCone(0.05,model.size[0]*2,1000,1000);
	glPopName();
	glPopMatrix();
	glPushMatrix ();

	glPushName(2);            /* Green cone is 2 */
	glColor3f(0,1,0);
	glRotatef(-90,1,0,0);
	glutSolidCone(0.05,model.size[1]*2, 1000, 1000);
	glPopName();
	glPopMatrix();
	
	glColor3f(0,0,1);         /* Blue cone is 3 */
	glPushName(3);
	glutSolidCone(0.05, model.size[2]*2, 1000,1000);
	glPopName();
	glPopMatrix();
	
}

void loadMesh(const char* filename, MeshModel &model){
	model.vertex.clear();
	model.faces.clear();
	model.h_edges.clear();

	FILE* f = fopen(filename, "r");
	
	ifstream myfile(filename);
	
	char vertext[7];
	char* ver="Vertex";
	char* face="Face";
	int index;
	float p1,p2,p3;
	char  line[1024]={0};  

	while (myfile.getline(line,sizeof(line))){
		sscanf(line, "%s %d %f %f %f", &vertext, &index, &p1,&p2,&p3);
		if(strcmp(vertext,ver)==0 || strcmp(vertext,face)==0)
		{
			if(strcmp(vertext,ver)==0){
				he_vertex* vect=new he_vertex();
				vect->p[0]=p1;
				vect->p[1]=p2;
				vect->p[2]=p3;
				vect->index=index;
				model.vertex.push_back(vect);
			}
			else
			{
				he_face* face=new he_face();
				face->index=index;
				face->vertex1=model.vertex[(int)p1-1];
				face->vertex2=model.vertex[(int)p2-1];
				face->vertex3=model.vertex[(int)p3-1];
				model.faces.push_back(face);
			}
		}
	}

	
	myfile.clear();
	myfile.close();

	int halfedgenum=model.faces.size()+2;

	for(int i=0;i<model.faces.size();i++){		
		he_edge* edge1=new he_edge;
		edge1->he_inv=NULL;
		edge1->he_next=new he_edge;
		edge1->he_prev=new he_edge;
		edge1->v_begin=model.faces[i]->vertex1;
		edge1->f_left=model.faces[i];
		edge1->he_next->v_begin=model.faces[i]->vertex2;
		edge1->he_next->f_left=model.faces[i];
		edge1->he_prev->v_begin=model.faces[i]->vertex3;
		edge1->he_prev->f_left=model.faces[i];
		model.h_edges.push_back(edge1);
		model.faces[i]->edge=edge1;

		he_edge* edge2=new he_edge;
		edge2->he_inv=NULL;
		edge2->he_next=new he_edge;
		edge2->he_prev=new he_edge;
		edge2->v_begin=model.faces[i]->vertex2;
		edge2->f_left=model.faces[i];
		edge2->he_next->v_begin=model.faces[i]->vertex3;
		edge2->he_next->f_left=model.faces[i];
		edge2->he_prev=edge1;
		edge1->he_next=edge2;
		model.h_edges.push_back(edge2);
		
		he_edge* edge3=new he_edge;
		edge3->he_inv=NULL;
		edge3->he_next=new he_edge;
		edge3->he_prev=new he_edge;
		edge3->v_begin=model.faces[i]->vertex3;
		edge3->f_left=model.faces[i];
		edge3->he_next->v_begin=model.faces[i]->vertex3;
		edge3->he_next->f_left=model.faces[i];
		edge2->he_next=edge3;
		edge3->he_prev=edge2;
		edge3->he_next=edge1;
		edge1->he_prev=edge3;
		model.h_edges.push_back(edge3);
	}

}

void rendMesh(MeshModel &model){
	glBegin(GL_TRIANGLES);
	for(int i=0;i<model.faces.size();i++){
		GLfloat p11=model.faces[i]->edge->v_begin->p[0];
		GLfloat p12=model.faces[i]->edge->v_begin->p[1];
		GLfloat p13=model.faces[i]->edge->v_begin->p[2];
		
		GLfloat p21=model.faces[i]->edge->he_next->v_begin->p[0];
		GLfloat p22=model.faces[i]->edge->he_next->v_begin->p[1];
		GLfloat p23=model.faces[i]->edge->he_next->v_begin->p[2];

		GLfloat p31=model.faces[i]->edge->he_next->he_next->v_begin->p[0];
		GLfloat p32=model.faces[i]->edge->he_next->he_next->v_begin->p[1];
		GLfloat p33=model.faces[i]->edge->he_next->he_next->v_begin->p[2];

		glVertex3f(p11,p12,p13);
		glVertex3f(p21,p22,p23);
		glVertex3f(p31,p32,p33);
	}
	glEnd();
}

void computCenterAndSizeOfMesh(MeshModel &model)
{
	GLfloat minTempX=model.vertex[0]->p[0];
	GLfloat minTempY=model.vertex[0]->p[1];
	GLfloat minTempZ=model.vertex[0]->p[2];

	GLfloat maxTempX=model.vertex[0]->p[0];
	GLfloat maxTempY=model.vertex[0]->p[1];
	GLfloat maxTempZ=model.vertex[0]->p[2];
	
	int nv =model.vertex.size();

  for (int i = 1; i < nv; i++) {
	  if(model.vertex[i]->p[0] < minTempX) minTempX = model.vertex[i]->p[0];
	  if(model.vertex[i]->p[0] > maxTempX) maxTempX = model.vertex[i]->p[0];
	  if(model.vertex[i]->p[1] < minTempY) minTempY = model.vertex[i]->p[1];
	  if(model.vertex[i]->p[1] > maxTempY) maxTempY = model.vertex[i]->p[1];
	  if(model.vertex[i]->p[2] < minTempZ) minTempZ = model.vertex[i]->p[2];
	  if(model.vertex[i]->p[2] > maxTempZ) maxTempZ = model.vertex[i]->p[2];
  }
  model.center[0] = 0.5f * (minTempX+maxTempX);
  model.center[1] = 0.5f * (minTempY+maxTempY);
  model.center[2] = 0.5f * (minTempZ+maxTempZ);

  model.size[0] = maxTempX-minTempX;
  model.size[1] = maxTempY-minTempY;
  model.size[2] = maxTempZ-minTempZ;

  //adjust model center to (0,0,0)
  for(int i=0;i<model.vertex.size();i++){
	  model.vertex[i]->p[0]-=model.center[0];
	  model.vertex[i]->p[1]-=model.center[1];
	  model.vertex[i]->p[2]-=model.center[2];
  }
}