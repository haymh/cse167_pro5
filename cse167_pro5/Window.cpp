#include <stdlib.h>
#include "shader.h"
#include "Window.h"
#include <iostream>
#include "Matrix4d.h"

#include "Debug.h"
#include "Const.h"
#include "Light.h"
#include "Material.h"
#include "ObjNode.h"
#include "Cone.h"




#define ROTSCALE 180.0;
#define ZOOMSCALE 2.0;

using namespace std;



int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
int Window::old_x = width / 2;
int Window::old_y = height / 2;

MatrixTransform * Window::root = new MatrixTransform(Matrix4d());
MatrixTransform * Window::bunny = new MatrixTransform(Matrix4d());
MatrixTransform * Window::dragon = new MatrixTransform(Matrix4d());
MatrixTransform * Window::bear = new MatrixTransform(Matrix4d());
MatrixTransform * Window::spotL;
MatrixTransform * Window::pointL;

// camera parameters
Vector3d eye(0, 0, 20);
Vector3d lookat(0, 0, 0);
Vector3d up(0, 1, 0);

// bunny data
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
MatrixTransform* Window::scaling_mt;
MatrixTransform* Window::rotate_mt;

// light sources parameters
f4 ambient(1.0, 1.0, 1.0, 1.0);
f4 p_ambient(0.2, 0.2, 0.2, 1.0);
f4 diffuse(1.0, 1.0, 1.0, 1.0);
f4 p_diffuse(0.2, 0.2, 0.2, 1.0);
f4 specular(1.0, 1.0, 1.0, 1.0);
f4 position(3.0, 10.0, 0.0, 1.0);
f4 position2(-3.0, 10.0, 0.0, 0.0);
f3 spot_direction(-3.0, -10.0, 0.0);
Light spotLight(ambient, diffuse, specular, position);

Light pointLight(p_ambient, p_diffuse, specular, position2);

// material parameters
f4 m_ambient(0.5, 1.0, 0.5, 1.0);
f4 m_diffuse(1.0, 1.0, 1.0, 1.0);
f4 m_specular(1.0, 1.0, 1.0, 1.0);
f4 m_emission(0.8, 0.8, 0.8, 0.0);
float shininess = 50;
Material material;
Material emissive_ma;


void Window::init(){
	/// loading bunny
	Parser::parseObj("bunny.obj", bunny_pos, bunny_nor, bunny_pos_ind, bunny_nor_ind, bunny_min, bunny_max);
	bunny_tran.makeTranslate(-(bunny_min.x + bunny_max.x) / 2,
		-(bunny_min.y + bunny_max.y) / 2, -(bunny_min.z + bunny_max.z) / 2);
	bunny_scale = calculateScalingMatrix(width, height, bunny_min, bunny_max);
	bunny_tran.print("bunny translate: ");
	bunny_scale.print("bunny scaling: ");
	

	//setting up light sources
	spotLight.setExponent(shininess);
	spotLight.setCutOff(2);
	spotLight.setSpotDirection(spot_direction);
	spotLight.setAttenuation(1.0, 0.1, 0.0);

	//setting up material
	material.setAmbient(m_ambient);
	material.setDiffuse(m_diffuse);
	material.setSpecular(m_specular);
	material.setShininess(shininess);

	//setting up emissive material
	emissive_ma.setAmbient(ambient);
	emissive_ma.setDiffuse(diffuse);
	emissive_ma.setSpecular(specular);
	emissive_ma.setEmission(f4(0.1,0.1,0.1,1.0));


	
	//building scene graph
	scaling_mt = new MatrixTransform(Matrix4d());
	rotate_mt = new MatrixTransform(Matrix4d());
	MatrixTransform * bunny = new MatrixTransform(bunny_scale * bunny_tran);
	root->addChild(rotate_mt);
	rotate_mt->addChild(scaling_mt);
	scaling_mt->addChild(bunny);
	bunny->addChild(new ObjNode(&bunny_pos, &bunny_nor, &bunny_pos_ind, &bunny_nor_ind, bunny_min, bunny_max, &material));

	Matrix4d t1;
	t1.makeTranslate(-3.0, 10.0, 0.0);
	pointL = new MatrixTransform(t1);
	root->addChild(pointL);
	pointL->addChild(new Sphere(1, 20, 20, Vector3d(1, 1, 1), draw::SOLID, &emissive_ma));

	Vector3d vCone(-3, -10, 0);
	vCone.normalize();
	Vector3d axis = Vector3d(0, 0, -1) * vCone;
	axis.normalize();
	Matrix4d rCone;
	rCone.makeRotate(acos(vCone.dot(Vector3d(0, 0, -1))) * 180 / M_PI, axis);
	Matrix4d t2;
	t2.makeTranslate(3, 10, 0);
	spotL = new MatrixTransform(t2 * rCone);
	root->addChild(spotL);
	spotL->addChild(new Cone(1, 2, 20, 20, Vector3d(0.0, 0.0, 0.0),draw::SOLID));
}

Matrix4d Window::calculateScalingMatrix(int w, int h, Coordinate3d min, Coordinate3d max){
	double x = (max.x - min.x) / 2;
	double y = (max.y - min.y) / 2;
	double z = (max.z - min.z) / 2;

	//cout << "x : " << x << " y : " << y << " z : " << z << endl;

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
	
	spotLight.apply();
	pointLight.apply();
	// recalculate bunny_scale matrix
	bunny_scale = calculateScalingMatrix(w, h, bunny_min, bunny_max);
	bunny->setMatrix(bunny_scale * bunny_tran);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	spotLight.apply();
	pointLight.apply();
	glMatrixMode(GL_MODELVIEW);
	root->draw(Matrix4d());
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
		//curPoint = trackBallMapping(x, y);
		direction = curPoint - lastPoint;
		double velocity = direction.magnitude();
		if (velocity > 0.0001){
			Vector3d rotAxis = lastPoint * curPoint;
			rotAxis.normalize();
			rot_angle = velocity * ROTSCALE;
			Matrix4d r;
			r.makeRotate(rot_angle, rotAxis);
			rotation = r * rotation;
			rotate_mt->setMatrix(rotation);
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
		scaling_mt->setMatrix(scaling);
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


Vector3d Window::trackBallMapping(int x, int y){
	Vector3d v(double (2*x - width) / double (width), double (height - 2*y) / double (height), 0);
	double d = v.magnitude();
	d = d < 1.0 ? d : 1.0;
	v.set(2, sqrt(1.001 - d*d));
	v.normalize();
	return v;
}