#ifndef MAT_HPP
#define MAT_HPP

#include "vector.hpp"
#include <algorithm>

template <typename T>
struct Mat4 {
	Mat4() : c0(), c1(), c2(), c3() {}
	explicit Mat4(const T &&value) : c0(), c1(), c2(), c3() { c0.x = value; c1.y = value; c2.z = value; c3.w = value; };
	Mat4 & operator=(const Mat4<T> &o) {
		if (this == &o)
			return *this;
		c0 = o.c0;
		c1 = o.c1;
		c2 = o.c2;
		c3 = o.c3;
		return *this;
	};
	Mat4(const Mat4 &o) : c0(o.c0), c1(o.c1), c2(o.c2), c3(o.c3) {};
	Mat4 operator*(const Mat4<T> &mat) const {
		Mat4 res;

		res.c0.x = c0.x * mat.c0.x + c1.x * mat.c0.y + c2.x * mat.c0.z + c3.x * mat.c0.w;
		res.c0.y = c0.y * mat.c0.x + c1.y * mat.c0.y + c2.y * mat.c0.z + c3.y * mat.c0.w;
		res.c0.z = c0.z * mat.c0.x + c1.z * mat.c0.y + c2.z * mat.c0.z + c3.z * mat.c0.w;
		res.c0.w = c0.w * mat.c0.x + c1.w * mat.c0.y + c2.w * mat.c0.z + c3.w * mat.c0.w;

		res.c1.x = c0.x * mat.c1.x + c1.x * mat.c1.y + c2.x * mat.c1.z + c3.x * mat.c1.w;
		res.c1.y = c0.y * mat.c1.x + c1.y * mat.c1.y + c2.y * mat.c1.z + c3.y * mat.c1.w;
		res.c1.z = c0.z * mat.c1.x + c1.z * mat.c1.y + c2.z * mat.c1.z + c3.z * mat.c1.w;
		res.c1.w = c0.w * mat.c1.x + c1.w * mat.c1.y + c2.w * mat.c1.z + c3.w * mat.c1.w;

		res.c2.x = c0.x * mat.c2.x + c1.x * mat.c2.y + c2.x * mat.c2.z + c3.x * mat.c2.w;
		res.c2.y = c0.y * mat.c2.x + c1.y * mat.c2.y + c2.y * mat.c2.z + c3.y * mat.c2.w;
		res.c2.z = c0.z * mat.c2.x + c1.z * mat.c2.y + c2.z * mat.c2.z + c3.z * mat.c2.w;
		res.c2.w = c0.w * mat.c2.x + c1.w * mat.c2.y + c2.w * mat.c2.z + c3.w * mat.c2.w;

		res.c3.x = c0.x * mat.c3.x + c1.x * mat.c3.y + c2.x * mat.c3.z + c3.x * mat.c3.w;
		res.c3.y = c0.y * mat.c3.x + c1.y * mat.c3.y + c2.y * mat.c3.z + c3.y * mat.c3.w;
		res.c3.z = c0.z * mat.c3.x + c1.z * mat.c3.y + c2.z * mat.c3.z + c3.z * mat.c3.w;
		res.c3.w = c0.w * mat.c3.x + c1.w * mat.c3.y + c2.w * mat.c3.z + c3.w * mat.c3.w;

		return res;
	};
	Mat4 & operator*=(const Mat4<T> &mat) {
		*this = *this * mat;
		return *this;
	};
	Vec4<T> c0;
	Vec4<T> c1;
	Vec4<T> c2;
	Vec4<T> c3;
};

template <typename T>
struct Mat3 {
	Mat3() : c0(), c1(), c2() {}
	explicit Mat3(const T &&value) : c0(), c1(), c2() { c0.x = value; c1.y = value; c2.z = value; };
	Mat3 & operator=(const Mat3<T> &o) {
		if (this == &o)
			return *this;
		c0 = o.c0;
		c1 = o.c1;
		c2 = o.c2;
		return *this;
	};
	Mat3 operator*(const Mat3<T> &mat) const {
		Mat3 res;

		res.c0.x = c0.x * mat.c0.x + c1.x * mat.c0.y + c2.x * mat.c0.z;
		res.c0.y = c0.y * mat.c0.x + c1.y * mat.c0.y + c2.y * mat.c0.z;
		res.c0.z = c0.z * mat.c0.x + c1.z * mat.c0.y + c2.z * mat.c0.z;

		res.c1.x = c0.x * mat.c1.x + c1.x * mat.c1.y + c2.x * mat.c1.z;
		res.c1.y = c0.y * mat.c1.x + c1.y * mat.c1.y + c2.y * mat.c1.z;
		res.c1.z = c0.z * mat.c1.x + c1.z * mat.c1.y + c2.z * mat.c1.z;

		res.c2.x = c0.x * mat.c2.x + c1.x * mat.c2.y + c2.x * mat.c2.z;
		res.c2.y = c0.y * mat.c2.x + c1.y * mat.c2.y + c2.y * mat.c2.z;
		res.c2.z = c0.z * mat.c2.x + c1.z * mat.c2.y + c2.z * mat.c2.z;

		return res;
	};
	Vec3<T> operator*(const Vec3<T> &v) const {
		Vec3<T> res;

		res.x = c0.x * v.x + c1.x * v.y + c2.x * v.z;
		res.y = c0.y * v.x + c1.y * v.y + c2.y * v.z;
		res.z = c0.z * v.x + c1.z * v.y + c2.z * v.z;
		return res;
	};

	Mat3 & operator*=(const Mat3<T> &mat) {
		*this = *this * mat;
		return *this;
	};
	Vec3<T> c0;
	Vec3<T> c1;
	Vec3<T> c2;
};


#endif //MAT_HPP
