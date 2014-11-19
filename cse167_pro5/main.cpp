#include "Window.h"
#include "Cube.h"
#include "MatrixTransform.h"
#include "Sphere.h"
#include "GL\glut.h"
#include "Matrix4d.h"
#include "parser.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	/*
	vector<Coordinate3d> position;
	vector<Vector3d> normal;
	vector<Coordinate3i> posIndex;
	vector<Coordinate3i> norIndex;
	Coordinate3d min;
	Coordinate3d max;

	Parser::parseObj("dragon.obj", position, normal, posIndex, norIndex, min, max);

	cout << "# of vertice : " << position.size() << endl;
	cout << "# of normal : " << normal.size() << endl;
	cout << "# of indices of position : " << posIndex.size() << endl;
	cout << "# of indices of normal : " << norIndex.size() << endl;
	cout << "min:  ( " << min.x << ", " << min.y << ", " << min.z << " )" << endl;
	cout << "max:  ( " << max.x << ", " << max.y << ", " << max.z << " )" << endl;

	system("pause");
	*/
	///*
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float shininess[] = { 100.0 };
	float position[] = { 0.0, 10.0, 1.0, 0.0 };	// lightsource position

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(Window::width, Window::height);
	glutCreateWindow("project 5");

	glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
	glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
	glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
	glShadeModel(GL_SMOOTH);             	      // set shading to smooth
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	/*
	// Generate material properties:
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Generate light source:
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	glEnable(GL_LIGHT0);
	*/
	//Arm a(2.5, 5, 1, Vector3d(1.0, 0, 0), Vector3d(0, 1.0, 0), Vector3d(0, 0, 1.0));
	
	//a.rotateWhole(-45);
	//a.rotateLower(-15);
	//Leg a(5.0, 2.5, 1, Vector3d(1.0, 0, 0), Vector3d(0, 1.0, 0), Vector3d(0, 0, 1.0), Vector3d(0, 1.0, 1.0));
	//a.rotateWhole(-45);
	//a.rotateLower(-15);
	//Robot a;
	//Window::addNode(Window::getRoot(), a.getRoot());
	
	Window::init();
	glutReshapeFunc(Window::reshapeCallback);
	glutDisplayFunc(Window::displayCallback);
	glutKeyboardFunc(Window::keyboardProcess); 
	glutIdleFunc(Window::idleCallback);
	glutMouseFunc(Window::mouseProcess);
	glutMotionFunc(Window::mouseMotionProcess);
	//glutPassiveMotionFunc(Window::mousePassiveMotionProcess);
	glutSpecialFunc(Window::processSpecialKeys);
	glutMainLoop();
	//*/
}