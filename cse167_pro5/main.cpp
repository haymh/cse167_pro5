#include "Window.h"
#include "Cube.h"
#include "MatrixTransform.h"
#include "Sphere.h"
#include "GL\glut.h"
#include "Matrix4d.h"
#include "Arm.h"
#include "Leg.h"
#include "Robot.h"

int main(int argc, char** argv) {
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float shininess[] = { 100.0 };
	float position[] = { 0.0, 10.0, 1.0, 0.0 };	// lightsource position

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(Window::width, Window::height);
	glutCreateWindow("scene graph");

	glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
	glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
	glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
	glShadeModel(GL_SMOOTH);             	      // set shading to smooth
	glMatrixMode(GL_PROJECTION);

	// Generate material properties:
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Generate light source:
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Arm a(2.5, 5, 1, Vector3d(1.0, 0, 0), Vector3d(0, 1.0, 0), Vector3d(0, 0, 1.0));
	
	//a.rotateWhole(-45);
	//a.rotateLower(-15);
	//Leg a(5.0, 2.5, 1, Vector3d(1.0, 0, 0), Vector3d(0, 1.0, 0), Vector3d(0, 0, 1.0), Vector3d(0, 1.0, 1.0));
	//a.rotateWhole(-45);
	//a.rotateLower(-15);
	//Robot a;
	//Window::addNode(Window::getRoot(), a.getRoot());
	/*
	Matrix4d m;
	//m.makeTranslate(5, 0, 0);
	MatrixTransform * mt = new MatrixTransform(m);
	Window::addNode(Window::getRoot(), mt);
	mt->addChild(new Cube(5, Vector3d(1.0, 0, 0), draw::SOLID));
	*/
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
}