#include "Light.h"

int Light::lightCount = -1;

Light::Light(){
	ambient.f[0] = 0.0;
	ambient.f[1] = 0.0;
	ambient.f[2] = 0.0;
	ambient.f[3] = 1.0;

	diffuse.f[0] = 1.0;
	diffuse.f[1] = 1.0;
	diffuse.f[2] = 1.0;
	diffuse.f[3] = 1.0;

	specular.f[0] = 1.0;
	specular.f[1] = 1.0;
	specular.f[2] = 1.0;
	specular.f[3] = 1.0;

	position.f[0] = 0.0;
	position.f[1] = 0.0;
	position.f[2] = 1.0;
	position.f[3] = 0.0;

	cut_off = 180;
	spot_direction.f[0] = 0.0;
	spot_direction.f[1] = 0.0;
	spot_direction.f[2] = -1.0;
	spot = false;
}

Light::Light(f4 am, f4 di, f4 sp, f4 po){
	ambient = am;
	diffuse = di;
	specular = sp;
	position = po;
	cut_off = 180;
	spot_direction.f[0] = 0.0;
	spot_direction.f[1] = 0.0;
	spot_direction.f[2] = -1.0;
	spot = false;
}

void Light::setAmbient(f4 am){
	ambient = am;
}
void Light::setDiffuse(f4 di){
	diffuse = di;
}
void Light::setSpecular(f4 sp){
	specular = sp;
}
void Light::setPosition(f4 po){
	position = po;
}
void Light::setSpotDirection(f3 sp_di){
	spot_direction = sp_di;
	spot = true;
}
void Light::setExponent(float exp){
	exponent = exp;
}
void Light::setCutOff(float cf){
	cut_off = cf;
	spot = true;
}

void Light::setAttenuation(float c, float l, float q){
	glLightfv()
}

void Light::isSpotLight(bool b){
	spot = b;
}