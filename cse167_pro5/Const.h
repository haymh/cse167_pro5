#ifndef _CONST_H_
#define _CONST_H_

namespace control{
	enum KEY{ F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12 };
	enum MOVEMENT{NONE, ROTATION, SCALING, TRANSLATION};
	enum MATERIAL{AMBIENT, DIFFUSE, SPECULAR, SHININESS, EMISSION};
	struct f4{
		float f[4];
		f4(){
			f[0] = f[1] = f[2] = f[3] = 0.0;
		}
		f4(f4 & other){
			f[0] = other.f[0];
			f[1] = other.f[1];
			f[2] = other.f[2];
			f[3] = other.f[3];
		}
	};

	struct f3{
		float f[3];
		f3(){
			f[0] = f[1] = f[2] = 0.0;
		}
		f3(f3 & other){
			f[0] = other.f[0];
			f[1] = other.f[1];
			f[2] = other.f[2];
		}
	};
}

namespace draw{
	enum mode{WIRE, SOLID}; 
}

#endif