#include "Cone.h"

Cone::Cone(double ba, double he, int st, int sl, Vector3d co, draw::mode m, Material *ma){
	base = ba;
	height = he;
	stacks = st;
	slices = sl;
	color = co;
	mode = m;
	material = ma;
	bs.radius = ba > he ? ba : he;
	bs.center = Vector3d(0, 0, 0);
}

Bs Cone::update(){
	return bs;
}

void Cone::render(){
	if (material != NULL)
		material->apply();
	else
		glColor3d(color[0], color[1], color[2]);
	switch (mode){
	case draw::SOLID:
		glutSolidCone(base, height, slices, stacks);
		break;
	case draw::WIRE:
		glutWireCone(base, height, slices, stacks);
		break;
	}
}