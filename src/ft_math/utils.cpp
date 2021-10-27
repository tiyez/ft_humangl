#include "ftm.hpp"

template<>
Vec3<float> ftm::mix(const Vec3<float> &a, const Vec3<float> &b, float t) {
	Vec3<float> res;

	res.x = mix(a.x, b.x, t);
	res.y = mix(a.y, b.y, t);
	res.z = mix(a.z, b.z, t);
	return res;
}

template<>	// TODO: (vitalii) not sure that this is correct
Quat<float> ftm::mix(const Quat<float> &a, const Quat<float> &b, float t) {
	Quat<float> res;

	res.i = mix(a.i, b.i, t);
	res.j = mix(a.j, b.j, t);
	res.k = mix(a.k, b.k, t);
	res.w = mix(a.w, b.w, t);
	return res;
}

#define PI 3.14159265358979f
float ftm::radians(float deg) {
	return PI / 180.f * deg;
}
#undef PI