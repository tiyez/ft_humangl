#ifndef FTM_HPP
#define FTM_HPP

#include "vector.hpp"
#include "matrix.hpp"
#include "quaternion.hpp"

#include <cmath>
#include <limits>

namespace ftm {
	typedef Vec4<float> vec4;
	typedef Vec3<float> vec3;
	typedef Vec2<float> vec2;

	typedef Mat4<float> mat4;
	typedef Mat3<float> mat3;

	typedef Quat<float> quat;

	// Matrix
	mat4 scale(const vec3 &v);
	mat4 rotate(float angle_rad, const vec3 &axis);
	mat4 translate(const vec3 &v);

	// Vector
	template <typename T>
	float magnitude(const Vec3<T> &v) {
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	}


	template <typename T>
	Vec3<T> rotateY(const Vec3<T> &vec, float angle_rad) {
		Mat3<float> rotY_mat(1);

		float c = cosf(angle_rad);
		float s = sinf(angle_rad);

		rotY_mat.c0 = Vec3<float> (c, 0, -s);
		rotY_mat.c2 = Vec3<float> (s, 0, c);

		return rotY_mat * vec;
	}

	template <typename T>
	Vec3<T> rotate(const Vec3<T> &vec, float angle_rad, const Vec3<T> &axis) {
		mat4 rotation = ftm::rotate(angle_rad, axis);
		mat3 res;

		res.c0 = Vec3<T> (rotation.c0.x, rotation.c0.y, rotation.c0.z);
		res.c1 = Vec3<T> (rotation.c1.x, rotation.c1.y, rotation.c1.z);
		res.c2 = Vec3<T> (rotation.c2.x, rotation.c2.y, rotation.c2.z);

		return res * vec;
	}

	template <typename T>
	Vec3<T> normalize(const Vec3<T> &v) {
		T mag = magnitude(v);
		if (fabs(mag) < std::numeric_limits<T>::epsilon()) {
			return v;
		}

		return {v.x / mag, v.y / mag, v.z / mag};
	}

	template <typename T>
	Vec3<T> normalize(const Vec3<T> &&v) {
		return normalize(v);
	}

	template <typename T>
	Vec3<T> cross(const Vec3<T> &u, const Vec3<T> &v) {
		return {u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x};
	}

	template <typename T>
	Vec3<T> cross(const Vec3<T> &&u, const Vec3<T> &&v) {
		return cross(u, v);
	}

	// Camera
	mat4 infinitePerspective(float fov, float aspect, float znear);

	mat4 lookAt(const ftm::vec3 &cam_pos, const ftm::vec3 &cam_dir, const ftm::vec3 &up_dir);

	// Quaternion
	template <typename T>
	Quat<T> angleAxis(float angle_rad, const Vec3<T> &axis) {
		Quat<T> res;

		Vec3<T> norm_axis = normalize(axis);

		float s = sinf(angle_rad / 2);
		float c = cosf(angle_rad / 2);

		res.i = s * norm_axis.x;
		res.j = s * norm_axis.y;
		res.k = s * norm_axis.z;
		res.w = c;

		return res;
	}

	template <typename T>
	float angle(const Quat<T>& quaternion) {	// Note(Vitalii) if not working apply https://ru.abcdef.wiki/wiki/Quaternions_and_spatial_rotation
		return acos(quaternion.w) * 2;
	}

	template <typename T>
	Vec3<T> axis(const Quat<T>& quaternion) {	// Note(Vitalii) if not working apply https://ru.abcdef.wiki/wiki/Quaternions_and_spatial_rotation
		float rad = angle(quaternion);
		float s = sinf(rad / 2);
		return Vec3<T> (quaternion.i / s, quaternion.j / s, quaternion.k / s);
	}

	template <typename T>
	Mat4<T> mat4_cast(const Quat<T> &q) {
		Mat4<T> rotation (1.f);

		rotation.c0 = Vec4<T> (1 - 2  * (q.j * q.j + q.k * q.k), 2 * (q.i * q.j + q.k * q.w), 2 * (q.i * q.k - q.j * q.w), 0);
		rotation.c1 = Vec4<T> (2 * (q.i * q.j - q.k * q.w), 1 - 2 * (q.i * q.i + q.k * q.k), 2 * (q.j * q.k + q.i * q.w), 0);
		rotation.c2 = Vec4<T> (2 * (q.i * q.k + q.j * q.w), 2 * (q.j * q.k - q.i * q.w), 1 - 2 * (q.i * q.i + q.j * q.j), 0);
		rotation.c3 = Vec4<T> (0, 0, 0, 1);
		return rotation;
	}

	// Utils
	template <typename T>
	T mix(const T& a, const T& b, float t) {
		return (a * (1 - t) + b * t);
	}

	template<>
	Vec3<float> ftm::mix(const Vec3<float> &a, const Vec3<float> &b, float t);

	template<>
	Quat<float> ftm::mix(const Quat<float> &a, const Quat<float> &b, float t);

	template <typename T>
	const T & max(const T& a, const T& b) {
		if (a > b)
			return a;
		return b;
	}

	template <typename T>
	T & max(T& a, T& b) {
		if (a > b)
			return a;
		return b;
	}

	template <typename T>
	T clamp(const T &min, const T &max, const T &value) {
		if (value < min) {
			return T(min);
		}
		if (value > max) {
			return T(max);
		}
		return T(value);
	}

	template <typename T>
	T clamp(const T &&min, const T &&max, const T &&value) {
		return clamp(min, max, value);
	}

	template <typename T>
	T abs(const T &val) {
		if (val < 0) {
			return -val;
		}
		return val;
	}

	float radians(float deg);
}

#endif //FTM_HPP
