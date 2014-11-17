#ifndef _PARSER_H_
#define _PARSER_H_

#include <vector>
#include "Vector3d.h"

using namespace std;

struct Coordinate3d{
	double x, y, z;
};

struct Coordinate3i{
	int x, y, z;
};

class Parser	  // OpenGL output window related routines
{
public:
	static void parse(char* file, vector<double> &position, vector<Vector3d> &normal, double &x_min, double &x_max, double &y_min, double &y_max, double &z_min, double &z_max);
	static void parseObj(char* file, vector<Coordinate3d> &position, vector<Vector3d> &normal, vector<Coordinate3i> & posIndex, vector<Coordinate3i> & norIndex, Coordinate3d & min, Coordinate3d & max);
};
 
#endif

