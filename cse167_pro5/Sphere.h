#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Geode.h"
#include "Const.h"
#include "Vector3d.h"

class Sphere : public Geode{
public:
	Sphere(double r, int slices, int stacks, Vector3d color, draw::mode);
	Bs update();
private:
	void render();
	double radius;
	int slices;
	int stacks;
	Vector3d color; 
	draw::mode mode;
};

#endif