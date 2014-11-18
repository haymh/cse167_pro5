#include "parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void Parser::parse(char* file, vector<double> &position, vector<Vector3d> &normal, double &x_min, double &x_max, double &y_min, double &y_max, double &z_min, double &z_max){
	ifstream infile;
	infile.open(file, std::ifstream::in);
	if (!infile.is_open()){
		std::cout << "failed to open file" << std::endl;
		return;
	}
	else
		std::cout << "file has been opened" << std::endl;

	string line;
	x_min = y_min = z_min = std::numeric_limits<double>::max();
	x_max = y_max = z_max = std::numeric_limits<double>::min();

	while (getline(infile, line)){
		std::istringstream iss(line);
		double d;
		iss >> d;
		if (d > x_max)
			x_max = d;
		if (d < x_min)
			x_min = d;
		position.push_back(d);

		iss >> d;
		if (d > y_max)
			y_max = d;
		if (d < y_min)
			y_min = d;
		position.push_back(d);

		iss >> d;
		if (d > z_max)
			z_max = d;
		if (d < z_min)
			z_min = d;
		position.push_back(d);

		Vector3d n;
		for (int i = 0; i < 3; i++){
			iss >> d;
			n.set(i, d);
		}
		n.normalize();
		normal.push_back(n);
	}
	std::cout << "x min: " << x_min << "x max: " << x_max << "y min: " << y_min << "y max: " << y_max << "z min: " << z_min << "z max: " << z_max << std::endl;
}


void Parser::parseObj(char* file, vector<Coordinate3d> &position, vector<Vector3d> &normal, vector<Coordinate3i> & posIndex, vector<Coordinate3i> & norIndex, Coordinate3d & min, Coordinate3d & max){
	FILE* fp;
	double x, y, z;
	int c1, c2;

	fp = fopen(file, "rb");
	if (fp == NULL){
		cerr << "error loading file" << endl;
		exit(-1);
	}

	min.x = min.y = min.z = std::numeric_limits<double>::max();
	max.x = max.y = max.z = std::numeric_limits<double>::min();
	
	while (true){
		char line[128];
		int res = fscanf(fp, "%s", line);
		if (res == EOF)
			break;
		if (strcmp(line, "v") == 0){			// reading vertex and color   v 0.145852 0.104651 0.517576 0.2 0.8 0.4
			Coordinate3d c;
			fscanf(fp, "%f %f %f\n", &(c.x), &(c.y), &(c.z));
			if (c.x > max.x)
				max.x = c.x;
			if (c.x < min.x)
				min.x = c.x;

			if (c.y > max.y)
				max.y = c.y;
			if (c.y < min.y)
				min.y = c.y;

			if (c.z > max.z)
				max.z = c.z;
			if (c.z < min.z)
				min.z = c.z;
			position.push_back(c);
		}
		else if (strcmp(line, "vn") == 0){      // reading vertex normal   vn -0.380694 3.839313 4.956321
			fscanf(fp, "%f %f %f\n", &x, &y, &z);
			Vector3d n(x, y, z);
			n.normalize();
			normal.push_back(n);
		}
		else if (strcmp(line, "f") == 0){		// reading faces  f 31514//31514 31465//31465 31464//31464
			Coordinate3i pos;
			Coordinate3i nor;
			fscanf(fp, "%d//%d %d//%d %d//%d\n", &(pos.x), &(nor.x), &(pos.y), &(nor.y), &(pos.z), &(nor.z));
			posIndex.push_back(pos);
			norIndex.push_back(nor);
		}
		else
			continue;
	}

	fclose(fp);
}
