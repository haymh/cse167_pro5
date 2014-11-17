#include "Sphere.h"

Sphere::Sphere(double r, int sl, int st, Vector3d c, draw::mode m){
	radius = r;
	slices = sl;
	stacks = st;
	color = c;
	mode = m;
}

void Sphere::render(){
	glColor3d(color[0], color[1], color[2]);
	switch (mode){
	case draw::SOLID:
		glutSolidSphere(radius, slices, stacks);
		break;
	case draw::WIRE:
		glutWireSphere(radius, slices, stacks);
		break;
	}
}

Bs Sphere::update(){
	bs.radius = radius; 
	bs.center = Vector3d(0, 0, 0);
	return bs;
}