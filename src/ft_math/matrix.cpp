#include "vector.hpp"
#include "matrix.hpp"

#include "ftm.hpp"

#include <cmath>

Mat4<float> ftm::scale(const Vec3<float> &v) {
	Mat4<float> scale(1);

	scale.r0.x = v.x;
	scale.r1.y = v.y;
	scale.r2.z = v.z;
	return scale;
}

Mat4<float> ftm::rotate(float angle_rad, const Vec3<float> &a) {
	Mat4<float> rotation(1);

	float c = cosf(angle_rad);
	float s = sinf(angle_rad);

	rotation.r0 = Vec4<float> (c + (1 - c) * a.x * a.x, (1 - c) * a.x * a.y - s * a.z, (1 - c) * a.x * a.z + s * a.y, 0);
	rotation.r1 = Vec4<float> ((1 - c) * a.y * a.x + s * a.z, c + (1 - c) * a.y * a.y, (1 - c) * a.y * a.z - s * a.x, 0);
	rotation.r2 = Vec4<float> ((1 - c) * a.z * a.x - s * a.y, (1 - c) * a.z * a.y + s * a.x, c + (1 - c) * a.z * a.z, 0);
	rotation.r3 = Vec4<float> (0, 0, 0, 1);
	return rotation;
}

Mat4<float> ftm::translate(const Vec3<float> &v) {
	Mat4<float> translation(1);

	translation.r3.x = v.x;
	translation.r3.y = v.y;
	translation.r3.z = v.z;

	return translation;
}