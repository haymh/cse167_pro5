#ifndef _WINDOW_H_
#define _WINDOW_H_


#include "Vector4d.h"
#include "Camera.h"
#include "Group.h"
#include "Node.h"
#include "MatrixTransform.h"
#include "Cube.h"
#include "Sphere.h"
#include "FrustumCulling.h"
#include "parser.h"


class Window	  // OpenGL output window related routines
{
  public:
    static int width, height; 	            // window size
	static int old_x, old_y;

	static void init();
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void keyboardProcess(unsigned char key, int x, int y);
	static void processSpecialKeys(int k, int x, int y);
	static void mouseMotionProcess(int, int);
	static void mouseProcess(int, int, int, int);

private :
	static MatrixTransform* root; 
	static MatrixTransform* bunny;
	static MatrixTransform* dragon;
	static MatrixTransform* bear;
	static MatrixTransform* spotL;
	static MatrixTransform* pointL;
	static MatrixTransform* scaling_mt;
	static MatrixTransform* rotate_mt;
	static FrustumCulling fc;

	static Matrix4d calculateScalingMatrix(int w, int h, Coordinate3d min, Coordinate3d max);
	static Vector3d trackBallMapping(int x, int y);

};

#endif

