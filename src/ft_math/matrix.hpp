#ifndef MAT_HPP
#define MAT_HPP

#include "vector.hpp"
#include <algorithm>
#include <iostream>

template <typename T>
struct Mat4 {
	Mat4() : r0(), r1(), r2(), r3() {}
	explicit Mat4(const T &&value) : r0(), r1(), r2(), r3() { r0.x = value; r1.y = value; r2.z = value; r3.w = value; };
	Mat4 & operator=(const Mat4<T> &o) {
		if (this == &o)
			return *this;
		r0 = o.r0;
		r1 = o.r1;
		r2 = o.r2;
		r3 = o.r3;
		return *this;
	};
	Mat4(const Mat4 &o) : r0(o.r0), r1(o.r1), r2(o.r2), r3(o.r3) {};
	Mat4 operator*(const Mat4<T> &mat) const {
		Mat4 res;

		res.r0.x = mat.r0.x * r0.x + mat.r0.y * r1.x + mat.r0.z * r2.x + mat.r0.w * r3.x;
		res.r0.y = mat.r0.x * r0.y + mat.r0.y * r1.y + mat.r0.z * r2.y + mat.r0.w * r3.y;
		res.r0.z = mat.r0.x * r0.z + mat.r0.y * r1.z + mat.r0.z * r2.z + mat.r0.w * r3.z;
		res.r0.w = mat.r0.x * r0.w + mat.r0.y * r1.w + mat.r0.z * r2.w + mat.r0.w * r3.w;

		res.r1.x = mat.r1.x * r0.x + mat.r1.y * r1.x + mat.r1.z * r2.x + mat.r1.w * r3.x;
		res.r1.y = mat.r1.x * r0.y + mat.r1.y * r1.y + mat.r1.z * r2.y + mat.r1.w * r3.y;
		res.r1.z = mat.r1.x * r0.z + mat.r1.y * r1.z + mat.r1.z * r2.z + mat.r1.w * r3.z;
		res.r1.w = mat.r1.x * r0.w + mat.r1.y * r1.w + mat.r1.z * r2.w + mat.r1.w * r3.w;

		res.r2.x = mat.r2.x * r0.x + mat.r2.y * r1.x + mat.r2.z * r2.x + mat.r2.w * r3.x;
		res.r2.y = mat.r2.x * r0.y + mat.r2.y * r1.y + mat.r2.z * r2.y + mat.r2.w * r3.y;
		res.r2.z = mat.r2.x * r0.z + mat.r2.y * r1.z + mat.r2.z * r2.z + mat.r2.w * r3.z;
		res.r2.w = mat.r2.x * r0.w + mat.r2.y * r1.w + mat.r2.z * r2.w + mat.r2.w * r3.w;

		res.r3.x = mat.r3.x * r0.x + mat.r3.y * r1.x + mat.r3.z * r2.x + mat.r3.w * r3.x;
		res.r3.y = mat.r3.x * r0.y + mat.r3.y * r1.y + mat.r3.z * r2.y + mat.r3.w * r3.y;
		res.r3.z = mat.r3.x * r0.z + mat.r3.y * r1.z + mat.r3.z * r2.z + mat.r3.w * r3.z;
		res.r3.w = mat.r3.x * r0.w + mat.r3.y * r1.w + mat.r3.z * r2.w + mat.r3.w * r3.w;

		return res;
	};
	Mat4 & operator*=(const Mat4<T> &mat) {
		*this = *this * mat;	// TODO: which order should be here?? )))
		return *this;
	};
/* Operator for glm cast */
/*
	explicit operator glm::mat4() {
		glm::mat4 res;

		float *matptr = glm::value_ptr(res);

		for (int i = 0; i < 4; ++i) {
			matptr[i] = *((float*)&r0 + i);
		}
		for (int i = 0; i < 4; ++i) {
			matptr[4 + i] = *((float*)&r1 + i);
		}
		for (int i = 0; i < 4; ++i) {
			matptr[8 + i] = *((float*)&r2 + i);
		}
		for (int i = 0; i < 4; ++i) {
			matptr[12 + i] = *((float*)&r3 + i);
		}

		return res;
	}
*/
	Vec4<T> r0;
	Vec4<T> r1;
	Vec4<T> r2;
	Vec4<T> r3;
};

template <typename T>
struct Mat3 {
	Mat3() : r0(), r1(), r2() {}
	explicit Mat3(const T &&value) : r0(), r1(), r2() { r0.x = value; r1.y = value; r2.z = value; };
	Mat3 & operator=(const Mat3<T> &o) {
		if (this == &o)
			return *this;
		r0 = o.r0;
		r1 = o.r1;
		r2 = o.r2;
		return *this;
	};
	Mat3 operator*(const Mat3<T> &mat) const {	// TODO: check
		Mat3 res;

		res.r0.x = r0.x * mat.r0.x + r0.y * mat.r1.x + r0.z * mat.r2.x;
		res.r0.y = r0.x * mat.r0.y + r0.y * mat.r1.y + r0.z * mat.r2.y;
		res.r0.z = r0.x * mat.r0.z + r0.y * mat.r1.z + r0.z * mat.r2.z;

		res.r1.x = r1.x * mat.r0.x + r1.y * mat.r1.x + r1.z * mat.r2.x;
		res.r1.y = r1.x * mat.r0.y + r1.y * mat.r1.y + r1.z * mat.r2.y;
		res.r1.z = r1.x * mat.r0.z + r1.y * mat.r1.z + r1.z * mat.r2.z;

		res.r2.x = r2.x * mat.r0.x + r2.y * mat.r1.x + r2.z * mat.r2.x;
		res.r2.y = r2.x * mat.r0.y + r2.y * mat.r1.y + r2.z * mat.r2.y;
		res.r2.z = r2.x * mat.r0.z + r2.y * mat.r1.z + r2.z * mat.r2.z;

		return res;
	};
	Vec3<T> operator*(const Vec3<T> &v) const {
		Vec3<T> res;

		res.x = r0.x * v.x + r0.y * v.y + r0.z * v.z;
		res.y = r1.x * v.x + r1.y * v.y + r1.z * v.z;
		res.z = r2.x * v.x + r2.y * v.y + r2.z * v.z;
		return res;
	};

	Mat3 & operator*=(const Mat3<T> &mat) {
		*this = *this * mat;
		return *this;
	};
	Vec3<T> r0;
	Vec3<T> r1;
	Vec3<T> r2;
};

#endif //MAT_HPP
