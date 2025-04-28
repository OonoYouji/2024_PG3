#include <stdio.h>
#include <iostream>
#include <format>

//#include "project/Variables.h"

struct Vec2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;

	//Vec2& xz;

	//Vec3() : x(0), y(0), z(0), xz{ x, z } {}
};


int main() {

	Vec3 vec3;
	vec3.x = 1.0f;
	vec3.y = 2.0f;
	vec3.z = 3.0f;

	printf("vec3.x: %f\n", vec3.x);
	printf("vec3.y: %f\n", vec3.y);
	printf("vec3.z: %f\n", vec3.z);

	//printf(std::format("vec3.xy:{},{} \n", vec3.xy.x, vec3.xy.y).c_str());
	//printf(std::format("vec3.xz:{},{} \n", vec3.xz.x, vec3.xz.y).c_str());
	//printf(std::format("vec3.yx:{},{} \n", vec3.yx.x, vec3.yx.y).c_str());
	//printf(std::format("vec3.zx:{},{} \n", vec3.zx.x, vec3.zx.y).c_str());
	//printf(std::format("vec3.zy:{},{} \n", vec3.zy.x, vec3.zy.y).c_str());
	//printf(std::format("vec3.yz:{},{} \n", vec3.yz.x, vec3.yz.y).c_str());


	return 0;
}