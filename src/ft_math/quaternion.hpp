#ifndef QUATERNION_HPP
#define QUATERNION_HPP

template <typename T>
struct Quat {
	Quat operator*(const Quat<T> &rhs) const {
		Quat res;
		res.i = w * rhs.i + i * rhs.w + j * rhs.k - k * rhs.j;
		res.j = w * rhs.j + j * rhs.w + k * rhs.i - i * rhs.k;
		res.k = w * rhs.k + k * rhs.w + i * rhs.j - j * rhs.i;
		res.w = w * rhs.w - i * rhs.i - j * rhs.j - k * rhs.k;
		return res;
	};
	Quat & operator*=(const Quat<T> &rhs) {
		*this = *this * rhs;
		return *this;
	};
	T i;
	T j;
	T k;
	T w;
};

#endif //QUATERNION_HPP
