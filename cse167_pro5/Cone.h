#ifndef _CONE_H_
#define _CONE_H_

#include "Const.h"
#include "Vector3d.h"
#include "Geode.h"
#include "Material.h"

class Cone : public Geode{

public:
	Cone(double ba, double he, int st, int sl, Vector3d color, draw::mode m, Material *ma = NULL);
	Bs update();

private :
	void render();
	double base, height;
	int stacks, slices;
	Vector3d color;
	Material * material;
	draw::mode mode;
};


#endif