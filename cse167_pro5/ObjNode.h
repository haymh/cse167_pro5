#ifndef _OBJNODE_H_
#define _OBJNODE_H_

#include "Geode.h"
#include "Material.h"
#include "Const.h"
#include <vector>
#include "parser.h"
#include "Vector3d.h"

class ObjNode : public Geode{
public :
	ObjNode(vector<Coordinate3d> *, vector<Vector3d> *, vector<Coordinate3i> *, vector<Coordinate3i> *, Coordinate3d min, Coordinate3d max, Material * m = NULL);
	Bs update();
private :
	void render();
	Coordinate3d min, max;
	std::vector<Coordinate3d> * pos;
	std::vector<Vector3d> * nor;
	std::vector<Coordinate3i> * pos_ind;
	std::vector<Coordinate3i> * nor_ind;
	Material * material;
};


#endif