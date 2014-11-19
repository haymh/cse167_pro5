#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Const.h"
#include <vector>

#define MAX_LIGHTS 8

using namespace control;

class Light{

public:
	Light();
	void setAmbient(f4 am);
	void setDiffuse(f4 di);
	void setSpecular(f4 sp);
	void setPosition(f4 po);
	void setSpotDirection(f3 sp_di);
	void setExponent(float exp);
	void setCutOff(float cf);
	void setAttenuation(float c, float l, float q);

private:
	f4 ambient, diffuse, specular, position;
	f3 spot_direction;
	float exponent, cut_off, c_attenuation, l_attenuation, q_attenuation;
	static int lightCount;
};

#endif