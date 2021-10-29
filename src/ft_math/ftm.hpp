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
	T magnitude(const Vec3<T> &v) {
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	template <typename T>
	T magnitude(const Quat<T> &v) {
		return sqrtf(v.i * v.i + v.j * v.j + v.k * v.k + v.w * v.w);
	}


	template <typename T>
	Vec3<T> rotateY(const Vec3<T> &vec, T angle_rad) {
		Mat3<T> rotY_mat(1);

		T c = cosf(angle_rad);
		T s = sinf(angle_rad);

		rotY_mat.r0 = Vec3<T> (c, 0, s);
		rotY_mat.r2 = Vec3<T> (-s, 0, c);

		return rotY_mat * vec;
	}

	template <typename T>
	Vec3<T> rotate(const Vec3<T> &vec, float angle_rad, const Vec3<T> &axis) {
		mat4 rotation = ftm::rotate(angle_rad, axis);
		mat3 res;

		res.r0 = Vec3<T> (rotation.r0.x, rotation.r0.y, rotation.r0.z);
		res.r1 = Vec3<T> (rotation.r1.x, rotation.r1.y, rotation.r1.z);
		res.r2 = Vec3<T> (rotation.r2.x, rotation.r2.y, rotation.r2.z);

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
	Quat<T> normalize(const Quat<T> &v) {
		T mag = magnitude(v);
		if (fabs(mag) < std::numeric_limits<T>::epsilon()) {
			return v;
		}

		return {v.i / mag, v.j / mag, v.k / mag, v.w / mag};
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
	float angle(const Quat<T>& q) {	// Note(Vitalii): https://ru.abcdef.wiki/wiki/Quaternions_and_spatial_rotation
		float quat_mag = sqrtf(q.i * q.i + q.j * q.j + q.k * q.k);
		return 2 * atan2(quat_mag, q.w);
	}

	template <typename T>
	Vec3<T> axis(const Quat<T>& q) {
		float quat_mag = sqrtf(q.i * q.i + q.j * q.j + q.k * q.k);
		return Vec3<T> (q.i / quat_mag, q.j / quat_mag, q.k / quat_mag);
	}

	template <typename T>
	Mat4<T> mat4_cast(const Quat<T> &q) {
		Mat4<T> rotation (1.f);

		rotation.r0 = Vec4<T> (1 - 2 * (q.j * q.j + q.k * q.k),	2 * (q.i * q.j + q.k * q.w),		2 * (q.i * q.k - q.j * q.w),		0);
		rotation.r1 = Vec4<T> (	2 * (q.i * q.j - q.k * q.w),		1 - 2 * (q.i * q.i + q.k * q.k),	2 * (q.j * q.k + q.i * q.w),		0);
		rotation.r2 = Vec4<T> (2 * (q.i * q.k + q.j * q.w),		2 * (q.j * q.k - q.i * q.w),		1 - 2 * (q.i * q.i + q.j * q.j),	0);
		rotation.r3 = Vec4<T> (0, 0, 0, 1);

		return rotation;
	}

	// Utils

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

	template <typename T>
	T mix(const T& a, const T& b, float t) {
		return (a + (b - a) * t);
	}

	float radians(float deg);
}

#endif //FTM_HPP
