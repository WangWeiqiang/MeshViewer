#include <GL/glut.h>
#include <vector>

#if __GNUC__>2
#include <ext/hash_map>
using __gnu_cxx::hash_map;
#else
#include <hash_map>
#endif

using namespace std;



struct he_vertex;
struct he_face;
struct he_edge;


struct he_vertex
{
	GLfloat p[3];
	int index;
	vector<he_face*> faces;
	he_vertex *normal;
};

struct he_face
{
	int index;
	he_edge* edge;
	he_vertex* vertex1;
	he_vertex* vertex2;
	he_vertex* vertex3;
	he_vertex normal;
};

struct he_edge
{
	he_vertex* v_begin;	
	he_edge* he_inv;
	he_edge* he_next;
	he_edge* he_prev;
	he_face* f_left;
	int index;

	static const size_t bucket_size = 4;    
	static const size_t min_buckets = 8;
	size_t operator()(const he_edge& e) const
	{
	   return size_t(e.v_begin->index);
	}
	bool operator()(const he_edge& p1, const he_edge& p2) const{
		return p1.v_begin->index == p2.he_next->v_begin->index
			&& p1.he_next->v_begin->index==p2.v_begin->index;
	}
};


typedef hash_map<const he_edge*, he_edge, hash<const he_edge>, equal_to< he_edge>> TwinEdge;

struct MeshModel 
{
	vector<he_vertex*> vertex;
	vector<he_face*> faces;
	vector<he_edge*> h_edges;
	hash_map<he_edge*,he_edge*> edges;
	GLfloat center[3];
	float size[3];
	float translation[3];
	GLfloat renderColor[3];
	float diagonalLength;
};