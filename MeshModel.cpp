#include <glut.h>
#include <vector>
#include <unordered_map>
#if __GNUC__>2
#include <ext/hash_map>
using __gnu_cxx::hash_map;
#else
#include <hash_map>
#endif

using namespace std;

struct coordinate;
struct he_vertex;
struct he_face;
struct he_edge;

struct coordinate
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct he_vertex
{
	int index;
	coordinate *P;
	coordinate *normal;
};

struct he_face
{
	int index;
	he_edge* edge;
	he_vertex* vertex1;
	he_vertex* vertex2;
	he_vertex* vertex3;
	coordinate *normal;
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

class pair_hasher
{
public:
	size_t operator()(const pair<int,int> &p) const
    {
		return p.first;
    }
};

typedef unordered_map <pair<int, int>, he_edge, pair_hasher> pair_edge;

struct MeshModel 
{
	vector<he_vertex*> vertex;
	vector<he_face*> faces;
	pair_edge edges;
	GLfloat center[3];
	float size[3];
	float translation[3];
	GLfloat renderColor[3];
	float diagonalLength;
};