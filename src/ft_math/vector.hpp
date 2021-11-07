#ifndef VEC3_HPP
#define VEC3_HPP

template <typename T>
struct Vec4 {
	Vec4() : x(T()), y(T()), z(T()), w(T()) {};
	Vec4(const T &x, const T &y, const T &z, const T &w) : x(x), y(y), z(z), w(w) {};
	Vec4(const T &&x, const T &&y, const T &&z, const T &&w) : x(x), y(y), z(z), w(w) {};
	Vec4(const Vec4<T> &o) : x(o.x), y(o.y), z(o.z), w(o.w) {};
	Vec4(const Vec4<T> &&o)  noexcept : x(o.x), y(o.y), z(o.z), w(o.w) {};
	Vec4 & operator=(const Vec4 &o) = default;
	Vec4 operator*(const T &scalar) const {
		Vec4	result;
		result.x = x * scalar;
		result.y = y * scalar;
		result.z = z * scalar;
		result.w = w * scalar;
		return result;
	};

/* Operator for glm cast */
/*
	explicit operator glm::vec4() {
		return glm::vec4 (x, y, z, w);
	}
*/
	T x;
	T y;
	T z;
	T w;
};

template <typename T>
struct Vec3 {
	Vec3() : x(T()), y(T()), z(T()) {};
	Vec3(const T &x, const T &y, const T &z) : x(x), y(y), z(z) {};
	Vec3(const T &&x, const T &&y, const T &&z) : x(x), y(y), z(z) {};
	Vec3(const Vec3<T> &o) : x(o.x), y(o.y), z(o.z) {};
	Vec3(const Vec3<T> &&o)  noexcept : x(o.x), y(o.y), z(o.z) {};
	explicit Vec3(const T &&scalar) : x(scalar), y(scalar), z(scalar) {};
	explicit Vec3(const T &scalar) : x(scalar), y(scalar), z(scalar) {};

	Vec3 & operator=(const Vec3 &o) = default;

	Vec3 operator*(const T scalar) const { Vec3<T> n_vec(*this); n_vec.x *= scalar; n_vec.y *= scalar; n_vec.z *= scalar; return n_vec; };
	Vec3 operator/(const T &&scalar) const { Vec3<T> n_vec(*this); n_vec.x /= scalar; n_vec.y /= scalar; n_vec.z /= scalar; return n_vec; };

	Vec3 operator*(const Vec3<T> &v) const { Vec3<T> n_vec(*this); n_vec.x *= v.x; n_vec.y *= v.y; n_vec.z *= v.z; return n_vec; }
	Vec3 operator+(const Vec3<T> &v) const { Vec3<T> n_vec(*this); n_vec.x += v.x; n_vec.y += v.y; n_vec.z += v.z; return n_vec; }
	Vec3 & operator+=(const Vec3<T> &rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; };
	Vec3 operator-(const Vec3<T> &rhs) const { Vec3<T> n_vec(*this); n_vec.x -= rhs.x; n_vec.y -= rhs.y; n_vec.z -= rhs.z; return n_vec; }

	Vec3 operator-() const { return Vec3<T> (-x, -y, -z); }
	T x;
	T y;
	T z;
};

template <typename T>
struct Vec2 {
	Vec2() : x(), y() {};
	Vec2(T &x, T &y, T &z) : x(x), y(y) {};
	Vec2(const Vec2<T> &o) : x(o.x), y(o.y) {};
	Vec2(const Vec2<T> &&o)  noexcept : x(o.x), y(o.y) {};
	Vec2 & operator=(const Vec2 &o) = default;
	Vec2 & operator*(T &scalar) { x *= scalar; y *= scalar; return *this; };
	T x;
	T y;
};

#endif //VEC3_HPP
