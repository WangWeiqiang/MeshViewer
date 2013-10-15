#include <GL/glut.h>

#include <vector>
using namespace std;


struct he_vertex;
struct he_face;
struct he_edge;


struct MeshModel 
{
	vector<he_vertex*> vertex;
	vector<he_face*> faces;
	vector<he_edge*> h_edges;
	GLfloat center[3];
	float size[3];
	float translation[3];
};

struct he_vertex
{
	GLfloat p[3];
	int index;
};

struct he_face
{
	int index;
	he_edge* edge;
	he_vertex* vertex1;
	he_vertex* vertex2;
	he_vertex* vertex3;
};

struct he_edge
{
	he_vertex* v_begin;	
	he_edge* he_inv;
	he_edge* he_next;
	he_edge* he_prev;
	he_face* f_left;
	int index;
};