#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cmath>
#include <stdio.h>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include "Environment.h"
#define _CRT_SECURE_NO_DEPRECATE
#include "MeshModel.cpp"
struct MeshModel;

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
    // move to the start point
    glTranslated( x0, y0, z0 );  
    //get length
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
    //transform matrix
    GLdouble  m[16] = { side_x, side_y, side_z, 0.0,  
        up_x,   up_y,   up_z,   0.0,  
        dir_x,  dir_y,  dir_z,  0.0,  
        0.0,    0.0,    0.0,    1.0 };  
    glMultMatrixd( m );  
   

    GLdouble slices = 8.0;
    GLdouble stack = 3.0;
    gluCylinder( quad_obj, r, r, bone_length, slices, stack );   
    glPopMatrix();  
}

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

coordinate* computeVector(coordinate v1,coordinate v2){
	coordinate* P=new coordinate;
	P->x=v2.x-v1.x;
	P->y=v2.y-v1.y;
	P->z=v2.z-v1.z;
	return P;
}

coordinate* crossVectors(coordinate* v1,coordinate* v2){

	coordinate* P=new coordinate;
	P->x=v1->y*v2->z-v1->z*v2->y;
	P->y=v1->z*v2->x-v1->x*v2->z;
	P->z=v1->x*v2->y-v1->y*v2->x;
	return P;
}

coordinate *getNormal(vector<coordinate> normals){
	coordinate *normal=new coordinate();
	
	for(int i=0;i<normals.size();i++){
		normal->x+=normals[i].x;
		normal->y+=normals[i].y;
		normal->z+=normals[i].z;
	}
	normal->x/=normals.size();
	normal->y/=normals.size();
	normal->z/=normals.size();
	GLfloat L=sqrtf(normal->x*normal->x+normal->y*normal->y+normal->z*normal->z);
	normal->x/=L;
	normal->y/=L;
	normal->z/=L;
	return normal;
}

coordinate* normilised(coordinate* v){
	float L = sqrt(v->x*v->x+v->y*v->y+v->z*v->z);
	coordinate *vn=new coordinate;
	vn->x= v->x/L;
	vn->y= v->y/L;
	vn->z= v->z/L;
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
	std::cout<<"Loading mesh model:"<<filename <<endl;
	while (myfile.getline(line,sizeof(line))){
		sscanf(line, "%s %d %f %f %f", &vertext, &index, &p1,&p2,&p3);
		if(strcmp(vertext,ver)==0 || strcmp(vertext,face)==0)
		{
			if(strcmp(vertext,ver)==0){
				he_vertex* vertex=new he_vertex();
				vertex->P=new coordinate;
				vertex->P->x=p1;
				vertex->P->y=p2;
				vertex->P->z=p3;
				vertex->index=index;
				vertex->normal=NULL;
				model.vertex.push_back(vertex);
			}
			else
			{
				he_face* face=new he_face();
				face->index=index;
				face->vertex1=model.vertex[(int)p1-1];
				face->vertex2=model.vertex[(int)p2-1];
				face->vertex3=model.vertex[(int)p3-1];

				coordinate *normal=normilised(crossVectors(computeVector(*face->vertex1->P,*face->vertex2->P),computeVector(*face->vertex1->P,*face->vertex3->P)));
				
				face->normal=new coordinate;
				face->normal->x=normal->x;
				face->normal->y=normal->y;
				face->normal->z=normal->z;

				he_edge* edge1=new he_edge;
				edge1->he_next=new he_edge;
				edge1->he_prev=new he_edge;
				edge1->he_inv=NULL;
				edge1->v_begin=face->vertex1;
				edge1->f_left=face;
				face->edge=edge1;

				he_edge* edge2=new he_edge;	
				edge2->he_next=new he_edge;
				edge2->he_prev=new he_edge;
				edge2->he_inv=NULL;
				edge2->v_begin=face->vertex2;
				edge2->f_left=face;
				edge2->he_prev=edge1;
				edge1->he_next=edge2;

				he_edge* edge3=new he_edge;
				edge3->he_next=new he_edge;
				edge3->he_prev=new he_edge;
				edge3->he_inv=NULL;
				edge3->v_begin=face->vertex3;
				edge3->f_left=face;
				edge2->he_next=edge3;
				edge3->he_prev=edge2;
				edge3->he_next=edge1;
				edge1->he_prev=edge3;

				pair<int, int> e1key = make_pair<int&, int&>(edge1->v_begin->index,edge1->he_next->v_begin->index);
				model.edges[e1key]=*edge1;
				pair<int, int> e2key = make_pair<int&, int&>(edge2->v_begin->index,edge2->he_next->v_begin->index);
				model.edges[e2key]=*edge2;
				pair<int, int> e3key = make_pair<int&, int&>(edge3->v_begin->index,edge3->he_next->v_begin->index);
				model.edges[e3key]=*edge3;
					
				pair<int, int> e1keypair = make_pair<int&, int&>(edge1->he_next->v_begin->index,edge1->v_begin->index);
				if(model.edges[e1keypair].v_begin){
					model.edges[e1key].he_inv=&model.edges[e1keypair];
					model.edges[e1keypair].he_inv=&model.edges[e1key];
				}


				
				pair<int, int> e2keypair = make_pair<int&, int&>(edge2->he_next->v_begin->index,edge2->v_begin->index);
				if(model.edges[e2keypair].v_begin){
					model.edges[e2key].he_inv=&model.edges[e2keypair];
					model.edges[e2keypair].he_inv=&model.edges[e2key];
				}


									
				pair<int, int> e3keypair = make_pair<int&, int&>(edge3->he_next->v_begin->index,edge3->v_begin->index);
				if(model.edges[e3keypair].v_begin){
					model.edges[e3key].he_inv=&model.edges[e3keypair];
					model.edges[e3keypair].he_inv=&model.edges[e3key];
				}

				
				model.faces.push_back(face);
			}
		}
	}
	
	myfile.clear();
	myfile.close();

	


	//calculate vertex normal
	std::cout<<"Load vertext normal data ..." <<endl;
	for(hash_map <const std::pair<int,int>, he_edge> :: const_iterator it=model.edges.begin();it!=model.edges.end();it++)
    { 
		if(it->second.v_begin==NULL || it->second.v_begin->normal!=NULL)
			continue;

		vector<coordinate> f_normals;
		
		he_edge e=it->second;
		f_normals.push_back(*e.f_left->normal);
		if(e.he_inv!=NULL){
			if(e.he_inv->v_begin!=NULL)
			e=*e.he_inv;
		}

		if(e.he_next->v_begin!=NULL){
			e=*e.he_next;
		}

		while(e.v_begin->index!=it->second.v_begin->index){

				f_normals.push_back(*e.f_left->normal);
				if(e.he_inv!=NULL)
					e=*e.he_inv;
				else
					break;
				if(e.he_next!=NULL)
					e=*e.he_next;
				else
					break;
		}

		coordinate* n=getNormal(f_normals);
		it->second.v_begin->normal=n;
	}
}

void rendMesh(MeshModel &model){

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
		
			//glNormal3f(model.faces[i]->normal.p);
			
			
			if(Environment::modelColorNoise){
				if(Environment::shadeModel==GL_SMOOTH)
				{
					glColor3f(adjust(v1.P->x),adjust(v1.P->y),adjust(v1.P->z));
					glNormal3f(v1.normal->x,v1.normal->y,v1.normal->z);
					glVertex3f(v1.P->x,v1.P->y,v1.P->z);
					glNormal3f(v2.normal->x,v2.normal->y,v2.normal->z);
					glColor3f(adjust(v2.P->x),adjust(v2.P->y),adjust(v2.P->z));
					glVertex3f(v2.P->x,v2.P->y,v2.P->z);
					glNormal3f(v3.normal->x,v3.normal->y,v3.normal->z);
					glColor3f(adjust(v3.P->x),adjust(v3.P->y),adjust(v3.P->z));
					glVertex3f(v3.P->x,v3.P->y,v3.P->z);
				}
				else
				{
					glNormal3f(model.faces[i]->normal->x,model.faces[i]->normal->y,model.faces[i]->normal->z);
					glColor3f(adjust(v1.P->x),adjust(v1.P->y),adjust(v1.P->z));
					glVertex3f(v1.P->x,v1.P->y,v1.P->z);
					glColor3f(adjust(v2.P->x),adjust(v2.P->y),adjust(v2.P->z));
					glVertex3f(v2.P->x,v2.P->y,v2.P->z);
					glColor3f(adjust(v3.P->x),adjust(v3.P->y),adjust(v3.P->z));
					glVertex3f(v3.P->x,v3.P->y,v3.P->z);
				}

			}
			else{
				if(Environment::shadeModel==GL_SMOOTH){
					glNormal3f(v1.normal->x,v1.normal->y,v1.normal->z);
					glVertex3f(v1.P->x,v1.P->y,v1.P->z);
					glNormal3f(v2.normal->x,v2.normal->y,v2.normal->z);
					glVertex3f(v2.P->x,v2.P->y,v2.P->z);
					glNormal3f(v3.normal->x,v3.normal->y,v3.normal->z);
					glVertex3f(v3.P->x,v3.P->y,v3.P->z);
				}
				else
				{
					glNormal3f(model.faces[i]->normal->x,model.faces[i]->normal->y,model.faces[i]->normal->z);
					glVertex3f(v1.P->x,v1.P->y,v1.P->z);					
					glVertex3f(v2.P->x,v2.P->y,v2.P->z);					
					glVertex3f(v3.P->x,v3.P->y,v3.P->z);
				}
			}
		}
		glEnd();
	}
	else
	{
		glDisable(GL_LIGHTING);
		glPointSize(2.0f);
		glColor3fv(Environment::modelRenderColor);
		glBegin(GL_POINTS);
		
		for(int i=0;i<model.faces.size();i++){
			glVertex3f(model.faces[i]->vertex1->P->x,model.faces[i]->vertex1->P->y,model.faces[i]->vertex1->P->z);
			glVertex3f(model.faces[i]->vertex2->P->x,model.faces[i]->vertex2->P->y,model.faces[i]->vertex2->P->z);
			glVertex3f(model.faces[i]->vertex3->P->x,model.faces[i]->vertex3->P->y,model.faces[i]->vertex3->P->z);
		}
		
		glEnd();
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

		//show axises with bound box

		GLfloat size=model.diagonalLength/5;;
		GLfloat r=size/20;
		glColor3d(1.0,0,0);
		RenderBone(-model.size[0]/2,-model.size[1]/2,-model.size[2]/2,-model.size[0]/2+size,-model.size[1]/2,-model.size[2]/2,r); //x
		glColor3d(0,1.0,0);
		RenderBone(-model.size[0]/2,-model.size[1]/2,-model.size[2]/2,-model.size[0]/2,-model.size[1]/2+size,-model.size[2]/2,r); //y
		glColor3d(0,0,1.0);
		RenderBone(-model.size[0]/2,-model.size[1]/2,-model.size[2]/2,-model.size[0]/2,-model.size[1]/2,-model.size[2]/2+size,r); //z

		glTranslated(-model.size[0]/2,-model.size[1]/2,-model.size[2]/2);//asix orgianl point
		glColor3d(1.0,1.0,0);
		glutSolidSphere(1.5*r,100,100);
		
		
		//x arrow
		glColor3d(1.0,0,0);
		glTranslated(size,0,0); //x asix end point
		glRotatef(90,0,1,0);
		glutSolidCone(r*1.5, r*3,100,100);
		glRotatef(90,0,-1,0);
		glTranslatef(-size,0,0);//back to asix original point
		
		//y arrow
		glColor3d(0,1.0,0);		
		glTranslatef(0,size,0); //y asix end point
		glRotatef(-90,1,0,0);
		glutSolidCone(r*1.5, r*3,100,100);
		glRotatef(-90,-1,0,0);
		glTranslatef(0,-size,0); //back to asix orignal point;

		//z axis
		glColor3d(0,0,1.0);
		glTranslatef(0,0,size);
		glutSolidCone(r*1.5, r*3,100,100);
		glTranslatef(0,0,-1.0f); //back to asix orignal point
		

	}
}

void computCenterAndSizeOfMesh(MeshModel &model)
{
	GLfloat minTempX=model.vertex[0]->P->x;
	GLfloat minTempY=model.vertex[0]->P->y;
	GLfloat minTempZ=model.vertex[0]->P->z;

	GLfloat maxTempX=model.vertex[0]->P->x;
	GLfloat maxTempY=model.vertex[0]->P->y;
	GLfloat maxTempZ=model.vertex[0]->P->z;
	
	int nv =model.vertex.size();

  for (int i = 1; i < nv; i++) {
	  if(model.vertex[i]->P->x < minTempX) minTempX = model.vertex[i]->P->x;
	  if(model.vertex[i]->P->x > maxTempX) maxTempX = model.vertex[i]->P->x;
	  if(model.vertex[i]->P->y < minTempY) minTempY = model.vertex[i]->P->y;
	  if(model.vertex[i]->P->y > maxTempY) maxTempY = model.vertex[i]->P->y;
	  if(model.vertex[i]->P->z < minTempZ) minTempZ = model.vertex[i]->P->z;
	  if(model.vertex[i]->P->z > maxTempZ) maxTempZ = model.vertex[i]->P->z;
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
  model.diagonalLength=maxSize;
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
	  model.vertex[i]->P->x-=(model.center[0]+Environment::center[0]);
	  model.vertex[i]->P->y-=(model.center[1]+Environment::center[1]);
	  model.vertex[i]->P->z-=(model.center[2]+Environment::center[2]);
  }
}

