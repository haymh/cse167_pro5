#include "ObjNode.h"

ObjNode::ObjNode(vector<Coordinate3d> * p, vector<Vector3d> * n, vector<Coordinate3i> * pi, vector<Coordinate3i> * ni, Coordinate3d mi, Coordinate3d ma, Material * m){
	pos = p;
	nor = n;
	pos_ind = pi;
	nor_ind = ni;
	min = mi;
	max = max;
	material = m;
	double x = (max.x - min.x) / 2;
	double y = (max.y - min.y) / 2;
	double z = (max.z - min.z) / 2;
	double a = x > y ? x : y;
	bs.radius = a > z ? a : z;
	bs.center = Vector3d((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);
}

Bs ObjNode::update(){
	return bs;
}

void ObjNode::render(){
	if (material != NULL)
		material->apply();
	else
		glColor3d(0.8, 0.8, 0.8);
	glBegin(GL_TRIANGLES);


	for (int i = 0; i < pos_ind->size(); i++){
		Vector3d normal = (*nor)[(*nor_ind)[i].x - 1];
		glNormal3d(normal[0], normal[1], normal[2]);
		Coordinate3d position = (*pos)[(*pos_ind)[i].x - 1];
		glVertex3d(position.x, position.y, position.z);

		normal = (*nor)[(*nor_ind)[i].y - 1];
		glNormal3d(normal[0], normal[1], normal[2]);
		position = (*pos)[(*pos_ind)[i].y - 1];
		glVertex3d(position.x, position.y, position.z);

		normal = (*nor)[(*nor_ind)[i].z - 1];
		glNormal3d(normal[0], normal[1], normal[2]);
		position = (*pos)[(*pos_ind)[i].z - 1];
		glVertex3d(position.x, position.y, position.z);
	}
	

	glEnd();
}