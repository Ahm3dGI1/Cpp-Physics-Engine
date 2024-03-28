#include "vector.h"
#include <math.h>

using namespace Math;

float vecLength(vec3d v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vecSqrLength(vec3d v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

vec3d vecNormalize(vec3d v) {
	float l = vecLength(v);
	return vec3d(v.x/l, v.y / l, v.z / l);
}

vec3d vecAdd(vec3d v1, vec3d v2) {
	return vec3d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

vec3d vecSubtract(vec3d v1, vec3d v2) {
	return vec3d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vec3d vecScale(vec3d v, float f) {
	return vec3d(v.x * f, v.y * f, v.z * f);
}

vec3d vecComponenetP(vec3d v1, vec3d v2) {
	return vec3d(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

float vecDotP(vec3d v1, vec3d v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3d vecCrossP(vec3d v1, vec3d v2) {
	return vec3d(v1.y * v2.z - v1.z - v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.z);
}