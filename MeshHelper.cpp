#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cmath>
#include <list>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <algorithm>
#include <functional>
#include "MeshViewer.h"
#define _CRT_SECURE_NO_DEPRECATE
#include "MeshModel.cpp"

#define E(u,v)

struct MeshModel;

void RenderBone(float x0, float y0, float z0, float x1, float y1, float z1,GLdouble r);

void drawGroundAndAxis(){
	glPolygonMode (GL_FRONT_AND_BACK,GL_FILL);
	glShadeModel(GL_SMOOTH);
	glColor3d(0.5,0.5,0.5);
	glBegin(GL_QUADS);
	glVertex3d(-3,0,-3);
	glVertex3d(3,0,-3);
	glVertex3d(3,0,3);
	glVertex3d(-3,0,3);
	glEnd();

	glColor3d(0.3,0.3,0.3);
	
	glLineWidth(2.0);
	double i=-3;
	glBegin(GL_LINES);
	while(i<=3)
	{
		
		glVertex3d(-3,0,i);
		glVertex3d(3,0,i);
		
		i+=0.2;
	}
	glEnd();
	
	i=-3;
	glBegin(GL_LINES);
	while(i<=3)
	{
		
		glVertex3d(i,0,3);
		glVertex3d(i,0,-3);
		
		i+=0.2;
	}
	glEnd();


		GLfloat r=0.02;
		GLfloat axislength=r*20;
		GLfloat size=0.1;
		glColor3d(1.0,0,0);
		RenderBone(-1.0f,0,-2.0f,0,0,-2.0f,r); //x
		glColor3d(0,1.0,0);
		RenderBone(-1.0f,0,-2.0f,-1.0f,1.0f,-2.0f,r); //y
		glColor3d(0,0,1.0);
		RenderBone(-1.0f,0,-2.0f,-1.0f,0,-1.0f,r); //z

		glTranslated(-1.0f,0,-2.0f);//asix orgianl point
		glColor3d(1.0,1.0,0);
		glutSolidSphere(1.5*r,100,100);
		
		
		//x arrow
		glColor3d(1.0,0,0);
		glTranslated(1.0f,0,0); //x asix end point
		glRotatef(90,0,1,0);
		glutSolidCone(r*1.5, r*3,100,100);
		glRotatef(90,0,-1,0);
		glTranslatef(-1.0f,0,0);//back to asix original point
		
		//y arrow
		glColor3d(0,1.0,0);		
		glTranslatef(0,1.0f,0); //y asix end point
		glRotatef(-90,1,0,0);
		glutSolidCone(r*1.5, r*3,100,100);
		glRotatef(-90,-1,0,0);
		glTranslatef(0,-1.0f,0); //back to asix orignal point;

		//z axis
		glColor3d(0,0,1.0);
		glTranslatef(0,0,1.0f);
		glutSolidCone(r*1.5, r*3,100,100);
		glTranslatef(0,0,-1.0f); //back to asix orignal point
		glRotatef(-90,1,0,0);
		glTranslatef(1.0f,-2.0f,0.5f); //back to world center
		glRotatef(90,1,0,0);
		glTranslatef(0,-0.5f,0); //back to world center
}

string getAppFolder(){
	TCHAR s[CHAR_MAX];
	DWORD a = GetCurrentDirectory(100, s);
	string c(&s[0]);
	string d( c.begin(), c.end() );
	return d;
}

void getFilesFromDirectory(std::vector<string> &out, const string &directory)
{

    HANDLE dir;
    WIN32_FIND_DATA file_data;

    if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
    	return; /* No files found */

    do {
    	const string file_name = file_data.cFileName;
    	const string full_file_name = directory + file_name;
    	const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

    	if (file_name[0] == '.')
    		continue;

    	out.push_back(full_file_name);
    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
} 

float adjust(float f){
	if(f>1 && f<10)
		return f/10;
	if(f>=10 && f<100)
		return f/100;
	if(f>=100 && f<1000)
		return f/1000;
	if(f<1&& f>=0.1)
		return f;
	if(f<0.1&& f>=0.01)
		return f*10;
	if(f<0.01&&f>=0.001)
		return f*100;
	if(f<0.001&&f>=0.0001)
		return f*1000;
		
}


he_vertex computeVector(he_vertex v1,he_vertex v2){
	he_vertex v;
	v.p[0]=v2.p[0]-v1.p[0];
	v.p[1]=v2.p[1]-v1.p[1];
	v.p[2]=v2.p[2]-v1.p[2];
	return v;
}

he_vertex crossVectors(he_vertex v1,he_vertex v2){
	he_vertex v;
	v.p[0]=v1.p[1]*v2.p[2]-v1.p[2]*v2.p[1];
	v.p[1]=v1.p[2]*v2.p[0]-v1.p[0]*v2.p[2];
	v.p[2]=v1.p[0]*v2.p[1]-v1.p[1]*v2.p[0];
	return v;
}

he_vertex normilised(he_vertex v){
	float L = sqrt(v.p[0]*v.p[0]+v.p[1]*v.p[1]+v.p[2]*v.p[2]);
	he_vertex vn;
	vn.p[0]= v.p[0]/L;
	vn.p[1]= v.p[1]/L;
	vn.p[2]= v.p[2]/L;
	return vn;
}

void loadMesh(const char* filename, MeshModel &model){
	model.vertex.clear();
	model.faces.clear();
	model.h_edges.clear();

	
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
				face->normal=normilised(crossVectors(computeVector(*face->vertex1,*face->vertex2),computeVector(*face->vertex1,*face->vertex3)));
				model.faces.push_back(face);
			}
		}
	}

	
	myfile.clear();
	myfile.close();
	vector<he_edge> tempEdge;
	int halfedgenum=model.faces.size()+2;

	for(int i=0;i<model.faces.size();i++){		
		he_edge* edge1=new he_edge;
		
		edge1->he_next=new he_edge;
		edge1->he_prev=new he_edge;
		edge1->he_inv=new he_edge;
		edge1->v_begin=model.faces[i]->vertex1;
		edge1->f_left=model.faces[i];
		edge1->he_next->v_begin=model.faces[i]->vertex2;
		edge1->he_next->f_left=model.faces[i];
		edge1->he_prev->v_begin=model.faces[i]->vertex3;
		edge1->he_prev->f_left=model.faces[i];

		
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

		model.h_edges.push_back(edge1);
		model.h_edges.push_back(edge2);
		model.h_edges.push_back(edge3);
		
	}

	for(int i=0;i<model.h_edges.size();i++){
		if(model.h_edges[i]->he_inv==NULL){
			std::vector<he_edge*>::iterator it = model.h_edges.end();
			it = std::find_if(model.h_edges.begin(),model.h_edges.end(), edge_finder(model.h_edges[i]));
			if(it!=model.h_edges.end()){
				model.h_edges[i]->he_inv=*it;
				model.h_edges[i]->he_inv->he_inv=model.h_edges[i];
			
			}
			
		}
		
	}

	//calculate vertex normal

}


void rendMesh(MeshModel &model){
	glPushMatrix();
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_NORMALIZE);

	if (Environment::showEdge) {
		glPolygonOffset(1, 1);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}

	if(!Environment::showPoint){
		
		if(!Environment::modelColorNoise){
			glColor3fv(Environment::modelRenderColor);
		}
		glBegin(GL_TRIANGLES);
		for(int i=0;i<model.faces.size();i++){
			
			const he_edge &myedge=*model.faces[i]->edge;
			he_vertex &v1=*model.faces[i]->edge->v_begin;
			he_vertex &v2=*model.faces[i]->edge->he_next->v_begin;
			he_vertex &v3=*model.faces[i]->edge->he_next->he_next->v_begin;
		
			glNormal3fv(model.faces[i]->normal.p);
			
			
			if(Environment::modelColorNoise){

				glColor3f(adjust(v1.p[0]),adjust(v1.p[1]),adjust(v1.p[2]));
				glVertex3fv(v1.p);
				glColor3f(adjust(v2.p[0]),adjust(v2.p[1]),adjust(v2.p[2]));
				glVertex3fv(v2.p);
				glColor3f(adjust(v3.p[0]),adjust(v3.p[1]),adjust(v3.p[2]));
				glVertex3fv(v3.p);

			}
			else{
				glVertex3fv(v1.p);
				glVertex3fv(v2.p);
				glVertex3fv(v3.p);
			}
		}
		glEnd();
	}


	if(Environment::showEdge){
		glDisable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(1.0);

		for(int i=0;i<model.faces.size();i++){
			glBegin(GL_TRIANGLES);
			const he_edge &myedge=*model.faces[i]->edge;
			he_vertex &v1=*model.faces[i]->edge->v_begin;
			he_vertex &v2=*model.faces[i]->edge->he_next->v_begin;
			he_vertex &v3=*model.faces[i]->edge->he_next->he_next->v_begin;
			he_vertex &vnormal=crossVectors(computeVector(v1,v2),computeVector(v1,v3));
			glNormal3fv(vnormal.p);
			glVertex3fv(v1.p);
			glVertex3fv(v2.p);
			glVertex3fv(v3.p);
			glEnd();

			glBegin(GL_LINES);
			glLineStipple(4, 0xAAAA);
			glEnable(GL_LINE_STIPPLE);
			glColor3f(1.0, 1.0, 1.0);
			glVertex3fv(v1.p);
			glVertex3fv(v2.p);
			glEnd();
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if(Environment::showPoint){
		glDisable(GL_LIGHTING);
		glPointSize(1.0f);
		for (int i = 0; i <model.vertex.size(); i++)
		{
			glBegin(GL_POINTS);
			glColor3fv(Environment::modelRenderColor);
			glVertex3fv(model.vertex[i]->p);
			glEnd();
		}
		
	}


	if(Environment::showModelBox){
		glColor3d(1.0,0,0);
		glBegin(GL_LINES);
		
		glVertex3f(-model.size[0]/2,-model.size[1]/2,-model.size[2]/2);
		glVertex3f(model.size[0]/2,-model.size[1]/2,-model.size[2]/2);

		glVertex3f(model.size[0]/2,-model.size[1]/2,-model.size[2]/2);
		glVertex3f(model.size[0]/2,model.size[1]/2,-model.size[2]/2);

		glVertex3f(model.size[0]/2,model.size[1]/2,-model.size[2]/2);
		glVertex3f(-model.size[0]/2,model.size[1]/2,-model.size[2]/2);
		
		glVertex3f(-model.size[0]/2,model.size[1]/2,-model.size[2]/2);
		glVertex3f(-model.size[0]/2,-model.size[1]/2,-model.size[2]/2);


		glVertex3f(-model.size[0]/2,-model.size[1]/2,model.size[2]/2);
		glVertex3f(model.size[0]/2,-model.size[1]/2,model.size[2]/2);

		glVertex3f(model.size[0]/2,-model.size[1]/2,model.size[2]/2);
		glVertex3f(model.size[0]/2,model.size[1]/2,model.size[2]/2);

		glVertex3f(model.size[0]/2,model.size[1]/2,model.size[2]/2);
		glVertex3f(-model.size[0]/2,model.size[1]/2,model.size[2]/2);
		
		glVertex3f(-model.size[0]/2,model.size[1]/2,model.size[2]/2);
		glVertex3f(-model.size[0]/2,-model.size[1]/2,model.size[2]/2);


		glVertex3f(-model.size[0]/2,-model.size[1]/2,-model.size[2]/2);
		glVertex3f(-model.size[0]/2,-model.size[1]/2,model.size[2]/2);

		glVertex3f(-model.size[0]/2,model.size[1]/2,-model.size[2]/2);
		glVertex3f(-model.size[0]/2,model.size[1]/2,model.size[2]/2);

		glVertex3f(model.size[0]/2,-model.size[1]/2,model.size[2]/2);
		glVertex3f(model.size[0]/2,-model.size[1]/2,-model.size[2]/2);

		glVertex3f(model.size[0]/2,model.size[1]/2,model.size[2]/2);
		glVertex3f(model.size[0]/2,model.size[1]/2,-model.size[2]/2);

		glEnd();
	}

	

	glPopMatrix();

	
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
  float scale=1;
  float maxSize=model.size[0];
  if(model.size[1]>maxSize)
	  maxSize=model.size[1];
  if(model.size[2]>maxSize)
	  maxSize=model.size[2];

  if(Environment::scale<1){

	  glScalef(1/Environment::scale,1/Environment::scale,1/Environment::scale);

	  Environment::scale=1/maxSize;
  }
  else
  {
	Environment::scale=1/maxSize;
  }

  //adjust model center to (0,0,0)
  for(int i=0;i<model.vertex.size();i++){
	  model.vertex[i]->p[0]-=model.center[0];
	  model.vertex[i]->p[1]-=model.center[1];
	  model.vertex[i]->p[2]-=model.center[2];
  }
}

void RenderBone(float x0, float y0, float z0, float x1, float y1, float z1,GLdouble r)  
{  
    GLdouble  dir_x = x1 - x0;  
    GLdouble  dir_y = y1 - y0;  
    GLdouble  dir_z = z1 - z0;  
    GLdouble  bone_length = sqrt( dir_x*dir_x + dir_y*dir_y + dir_z*dir_z );  
    static GLUquadricObj *  quad_obj = NULL;  
    if ( quad_obj == NULL )  
        quad_obj = gluNewQuadric();  
    gluQuadricDrawStyle( quad_obj, GLU_FILL );  
    gluQuadricNormals( quad_obj, GLU_SMOOTH );  
    glPushMatrix();  
    // 平移到起始点  
    glTranslated( x0, y0, z0 );  
    // 计算长度  
    double  length;  
    length = sqrt( dir_x*dir_x + dir_y*dir_y + dir_z*dir_z );  
    if ( length < 0.0001 ) {   
        dir_x = 0.0; dir_y = 0.0; dir_z = 1.0;  length = 1.0;  
    }  
    dir_x /= length;  dir_y /= length;  dir_z /= length;  
    GLdouble  up_x, up_y, up_z;  
    up_x = 0.0;  
    up_y = 1.0;  
    up_z = 0.0;  
    double  side_x, side_y, side_z;  
    side_x = up_y * dir_z - up_z * dir_y;  
    side_y = up_z * dir_x - up_x * dir_z;  
    side_z = up_x * dir_y - up_y * dir_x;  
    length = sqrt( side_x*side_x + side_y*side_y + side_z*side_z );  
    if ( length < 0.0001 ) {  
        side_x = 1.0; side_y = 0.0; side_z = 0.0;  length = 1.0;  
    }  
    side_x /= length;  side_y /= length;  side_z /= length;  
    up_x = dir_y * side_z - dir_z * side_y;  
    up_y = dir_z * side_x - dir_x * side_z;  
    up_z = dir_x * side_y - dir_y * side_x;  
    // 计算变换矩阵  
    GLdouble  m[16] = { side_x, side_y, side_z, 0.0,  
        up_x,   up_y,   up_z,   0.0,  
        dir_x,  dir_y,  dir_z,  0.0,  
        0.0,    0.0,    0.0,    1.0 };  
    glMultMatrixd( m );  
    // 圆柱体参数  

    GLdouble slices = 8.0;      //  段数  
    GLdouble stack = 3.0;       // 递归次数  
    gluCylinder( quad_obj, r, r, bone_length, slices, stack );   
    glPopMatrix();  
}

void setup_lighting()
{
	//Add ambient light
    GLfloat ambientColor[] = {0.5f,0.5f,0.5f, 1.0f};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightAmbient[] = {0, 0, 0, 1.0};
	GLfloat lightDiffuse[]   = {0.5, 0.5, 0.5, 1.0};
	GLfloat lightSpecular[] = {1.0,1.0, 1.0, 1.0};
	GLfloat lightPos1[] = {-1.0f, -1.0f, 0,1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void close_lighting(){
	glDisable(GL_LIGHTING);
}
