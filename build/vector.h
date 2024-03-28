#pragma once

namespace Math {
	class vec3d {
		public:
			float x, y, z;

			vec3d() : x(0), y(0), z(0) {}
			vec3d(float x, float y, float z) : x(x), y(y), z(z) {}

			float vecLength(vec3d v);

			float vecSqrLength(vec3d v);

			vec3d vecNormalize(vec3d v);

			vec3d vecAdd(vec3d v1, vec3d v2);
			vec3d vecSubtract(vec3d v1, vec3d v2);
			vec3d vecScale(vec3d v, float f);

			vec3d vecComponentP(vec3d v1, vec3d v2);
			float vecDotP(vec3d v1, vec3d v2);
			vec3d vecCrossP(vec3d v1, vec3d v2);
	};
}