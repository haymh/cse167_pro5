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
	static void addNode(Group * parent, Node * child);
	static MatrixTransform* getRoot();

private :
	static MatrixTransform* root; 
	static FrustumCulling fc;

};

#endif

