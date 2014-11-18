#include <iostream>
#include "Window.h"
#include "Matrix4d.h"
#include "GL\glew.h"
#include "GL\glut.h"
#include "Debug.h"
#include "Const.h"

#define ROTSCALE 80.0;
#define ZOOMSCALE 2.0;

using namespace std;



int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
int Window::old_x = width / 2;
int Window::old_y = height / 2;

MatrixTransform* Window::root = new MatrixTransform(Matrix4d());

Vector3d eye(0, 0, 20);
Vector3d lookat(0, 0, 0);
Vector3d up(0, 1, 0);
FrustumCulling Window::fc(60.0, double(width) / (double)height, 1.0, 1000.0, eye, lookat, up);

Matrix4d bunny_tran, bunny_scale;
Coordinate3d bunny_min, bunny_max;
vector<Coordinate3d> bunny_pos;
vector<Vector3d> bunny_nor;
vector<Coordinate3i> bunny_pos_ind;
vector<Coordinate3i> bunny_nor_ind;

//trackball variables
control::MOVEMENT movement = control::NONE;
Vector3d lastPoint;
Matrix4d rotation;
Matrix4d scaling;

void Window::init(){
	Parser::parseObj("bunny.obj", bunny_pos, bunny_nor, bunny_pos_ind, bunny_nor_ind, bunny_min, bunny_max);
	bunny_tran.makeTranslate(-(bunny_min.x + bunny_max.x) / 2,
		-(bunny_min.y + bunny_max.y) / 2, -(bunny_min.z + bunny_max.z) / 2);
	cout << "min: " << bunny_min.x << " , " << bunny_min.y << " , " << bunny_min.z << endl;
	cout << "max: " << bunny_max.x << " , " << bunny_max.y << " , " << bunny_max.z << endl;
	system("pause");
	bunny_scale = calculateScalingMatrix(width, height, bunny_min, bunny_max);
	bunny_tran.print("bunny translate: ");
	bunny_scale.print("bunny scaling: ");
	//Debug::debug("size of bunny_pos: ", (int)bunny_pos.size());
	//Debug::debug("size of bunny_nor: ", (int)bunny_nor.size());
	//Debug::debug("size of bunny_pos_ind: ", (int)bunny_pos_ind.size());
	//Debug::debug("size of bunny_nor_ind: ", (int)bunny_nor_ind.size());
}

Matrix4d Window::calculateScalingMatrix(int w, int h, Coordinate3d min, Coordinate3d max){
	double x = (max.x - min.x) / 2;
	double y = (max.y - min.y) / 2;
	double z = (max.z - min.z) / 2;

	cout << "x : " << x << " y : " << y << " z : " << z << endl;

	double a = z / y;
	double ymax = 20 / (a + 1 / tan(30 * M_PI / 180));
	double sy = ymax / y;

	double xmax = ymax * double(w) / double(h);
	double sx = xmax / x;

	double factor = sy < sx ? sy : sx;
	Matrix4d s;
	s.makeScale(factor, factor, factor);
	return s;
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	
	displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
	cerr << "Window::reshapeCallback called" << endl;
	width = w;
	height = h;
	glViewport(0, 0, w, h);  // set new viewport size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0); // set perspective projection viewing frustum
	gluLookAt(eye[0], eye[1], eye[2], lookat[0], lookat[1], lookat[2], up[0], up[1], up[2]);
	bunny_scale = calculateScalingMatrix(w, h, bunny_min, bunny_max);
	//glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers

	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
	Matrix4d m = rotation * bunny_scale * scaling * bunny_tran;
	glLoadMatrixd(m.getPointer());
	drawBunny();
	glFlush();
	glutSwapBuffers(); 
}


void Window::keyboardProcess(unsigned char key, int x, int y){

}
void Window::processSpecialKeys(int k, int x, int y){

}
void Window::mouseMotionProcess(int x, int y){
	Vector3d direction;
	double pixel_diff;
	double rot_angle, zoom_factor;
	Vector3d curPoint;
	curPoint = trackBallMapping(x, y);
	switch (movement){
	case control::ROTATION:
	{
		curPoint = trackBallMapping(x, y);
		direction = curPoint - lastPoint;
		double velocity = direction.magnitude();
		if (velocity > 0.0001){
			Vector3d rotAxis = lastPoint * curPoint;
			rot_angle = velocity * ROTSCALE;
			Matrix4d r;
			r.makeRotate(rot_angle, rotAxis);
			//r.makeRotateY(rot_angle);
			rotation = r * rotation;
		}
	}
	break;
	case control::SCALING:
	{
		pixel_diff = curPoint[1] - lastPoint[1];
		zoom_factor = 1.0 + pixel_diff * ZOOMSCALE;
		Matrix4d s;
		s.makeScale(zoom_factor, zoom_factor, zoom_factor);
		scaling = scaling * s;
		displayCallback();
	}
		break;
	}
	lastPoint = curPoint;
}


void Window::mouseProcess(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		movement = control::ROTATION;
		old_x = x;
		old_y = y;
		lastPoint = trackBallMapping(x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		movement = control::SCALING;
		old_x = x;
		old_y = y;
		lastPoint = trackBallMapping(x, y);
	}
	else
		movement = control::NONE;
}

void Window::drawBunny(){
	glBegin(GL_TRIANGLES);
	
	for (int i = 0; i < bunny_pos_ind.size(); i++){
		Vector3d nor = bunny_nor[bunny_nor_ind[i].x - 1];
		glNormal3d(nor[0], nor[1], nor[2]);
		Coordinate3d pos = bunny_pos[bunny_pos_ind[i].x - 1];
		glVertex3d(pos.x, pos.y, pos.z);

		nor = bunny_nor[bunny_nor_ind[i].y - 1];
		glNormal3d(nor[0], nor[1], nor[2]);
		pos = bunny_pos[bunny_pos_ind[i].y - 1];
		glVertex3d(pos.x, pos.y, pos.z);
		
		nor = bunny_nor[bunny_nor_ind[i].z - 1];
		glNormal3d(nor[0], nor[1], nor[2]);
		pos = bunny_pos[bunny_pos_ind[i].z - 1];
		glVertex3d(pos.x, pos.y, pos.z);
	}
	
	glEnd();
}

Vector3d Window::trackBallMapping(int x, int y){
	Vector3d v(double (2*x - width) / double (width), double (height - 2*y) / double (height), 0);
	double d = v.magnitude();
	d = d < 1.0 ? d : 1.0;
	v.set(2, sqrt(1.001 - d*d));
	v.normalize();
	return v;
}