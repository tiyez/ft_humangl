#ifndef MAT_HPP
#define MAT_HPP

#include "vector.hpp"
#include <glm/glm.hpp>
#include <algorithm>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

//#include "Skeleton.hpp"
// TODO: remove before evaluation
//std::ostream &operator<<(std::ostream &o, const glm::vec4 &v);

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

		res.r0.x = r0.x * mat.r0.x + r1.x * mat.r0.y + r2.x * mat.r0.z + r3.x * mat.r0.w;
		res.r0.y = r0.y * mat.r0.x + r1.y * mat.r0.y + r2.y * mat.r0.z + r3.y * mat.r0.w;
		res.r0.z = r0.z * mat.r0.x + r1.z * mat.r0.y + r2.z * mat.r0.z + r3.z * mat.r0.w;
		res.r0.w = r0.w * mat.r0.x + r1.w * mat.r0.y + r2.w * mat.r0.z + r3.w * mat.r0.w;

		res.r1.x = r0.x * mat.r1.x + r1.x * mat.r1.y + r2.x * mat.r1.z + r3.x * mat.r1.w;
		res.r1.y = r0.y * mat.r1.x + r1.y * mat.r1.y + r2.y * mat.r1.z + r3.y * mat.r1.w;
		res.r1.z = r0.z * mat.r1.x + r1.z * mat.r1.y + r2.z * mat.r1.z + r3.z * mat.r1.w;
		res.r1.w = r0.w * mat.r1.x + r1.w * mat.r1.y + r2.w * mat.r1.z + r3.w * mat.r1.w;

		res.r2.x = r0.x * mat.r2.x + r1.x * mat.r2.y + r2.x * mat.r2.z + r3.x * mat.r2.w;
		res.r2.y = r0.y * mat.r2.x + r1.y * mat.r2.y + r2.y * mat.r2.z + r3.y * mat.r2.w;
		res.r2.z = r0.z * mat.r2.x + r1.z * mat.r2.y + r2.z * mat.r2.z + r3.z * mat.r2.w;
		res.r2.w = r0.w * mat.r2.x + r1.w * mat.r2.y + r2.w * mat.r2.z + r3.w * mat.r2.w;

		res.r3.x = r0.x * mat.r3.x + r1.x * mat.r3.y + r2.x * mat.r3.z + r3.x * mat.r3.w;
		res.r3.y = r0.y * mat.r3.x + r1.y * mat.r3.y + r2.y * mat.r3.z + r3.y * mat.r3.w;
		res.r3.z = r0.z * mat.r3.x + r1.z * mat.r3.y + r2.z * mat.r3.z + r3.z * mat.r3.w;
		res.r3.w = r0.w * mat.r3.x + r1.w * mat.r3.y + r2.w * mat.r3.z + r3.w * mat.r3.w;

		return res;
	};
	Mat4 & operator*=(const Mat4<T> &mat) {
		*this = *this * mat;
		return *this;
	};
	explicit operator glm::mat4() {
//		std::cout << v0 << std::endl;
//		std::cout << v1 << std::endl;
//		std::cout << v2 << std::endl;
//		std::cout << v3 << std::endl;
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
	Vec4<T> r0;
	Vec4<T> r1;
	Vec4<T> r2;
	Vec4<T> r3;
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
