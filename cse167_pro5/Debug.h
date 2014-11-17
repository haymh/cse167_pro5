#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <iostream>
using namespace std;

class Debug{
public:
	static void debug(char* n, int a){
		cout << n << ": " << a << endl;
		system("pause");
	};
	static void debug(char* n, long a){
		cout << n << ": " << a << endl;
		system("pause");
	};
	static void debug(char* n, char a){
		cout << n << ": " << a << endl;
		system("pause"); 
	};
	static void debug(char* n, double a){
		cout << n << ": " << a << endl;
		system("pause");
	};
	static void debug(char* n, float a){
		cout << n << ": " << a << endl;
		system("pause");
	};
	static void debug(char* n, bool a){
		cout << n << ": " << a << endl;
		system("pause");
	};
};

#endif