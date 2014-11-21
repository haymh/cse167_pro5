#ifndef _GEODE_H_
#define _GEODE_H_

#include "Node.h"
#include "GL\glut.h"

class Geode : public Node{
public:
	Geode(){};
	void draw(Matrix4d & m){
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(m.getPointer());
		render();
	};
	void draw(Matrix4d & m, FrustumCulling & fc){
		switch(fc.sphereInFrustum(bs.center, bs.radius)){
			case FrustumCulling::INSIDE:
				glMatrixMode(GL_MODELVIEW);
				glLoadMatrixd(m.getPointer());
				render();
				break;
		}
	};
	virtual Bs update() = 0;
protected:
	virtual void render() = 0; 

};


#endif