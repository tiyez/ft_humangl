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
	Quat operator*(const T &scalar) const {
		Quat	result;
		result.i = i * scalar;
		result.j = j * scalar;
		result.k = k * scalar;
		result.w = w * scalar;
		return *this;
	};
	Quat operator+(const Quat<T> &rhs) const {
		Quat	result;
		result.i = i + rhs.i;
		result.j = j + rhs.j;
		result.k = k + rhs.k;
		result.w = w + rhs.w;
		return *this;
	};
	Quat operator-(const Quat<T> &rhs) const {
		Quat	result;
		result.i = i - rhs.i;
		result.j = j - rhs.j;
		result.k = k - rhs.k;
		result.w = w - rhs.w;
		return *this;
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
