#pragma once

#include <math.h>

namespace mhe
{

class Vec3f
{
public:
	Vec3f(float x, float y, float z);
	~Vec3f() = default;

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float x() const { return m_x; }
	float y() const { return m_y; }
	float z() const { return m_z; }

	float magSq() const;
	float mag() const;
	Vec3f unit() const;
	Vec3f project(const Vec3f &v, bool flip = false) const;
	void normalize();
	void lerpTo(const Vec3f &v, float t);
	void constrainMag(float c);
	void clamp(float low, float high);

  public:
	Vec3f operator+() const;
	Vec3f operator-() const;
	Vec3f operator+(const Vec3f &v) const;
	Vec3f operator-(const Vec3f &v) const;
	Vec3f operator*(float s) const;
	Vec3f operator/(float s) const;

	Vec3f &operator+=(const Vec3f &v);
	Vec3f &operator-=(const Vec3f &v);
	Vec3f &operator*=(float s);
	Vec3f &operator/=(float s);

private:
	float m_x;
	float m_y;
	float m_z;
};

float dot(const Vec3f &a, const Vec3f &b);
Vec3f cross(const Vec3f &a, const Vec3f &b);


/* Inline implementation */
__forceinline Vec3f::Vec3f(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

__forceinline void Vec3f::setX(float x)
{
	m_x = x;
}

__forceinline void Vec3f::setY(float y)
{
	m_y = y;
}

__forceinline void Vec3f::setZ(float z)
{
	m_z = z;
}

__forceinline float Vec3f::magSq() const
{
	return m_x * m_x + m_y * m_y + m_z * m_z;
}

__forceinline float Vec3f::mag() const
{
	return sqrt(magSq());
}

__forceinline Vec3f Vec3f::unit() const
{
	const float norm = mag();
	return Vec3f(m_x / norm, m_y / norm, m_z / norm);
}

__forceinline Vec3f Vec3f::project(const Vec3f &v, bool flip) const
{
	return v * dot(*this, v) / v.magSq() * (flip ? -1.0f : 1.0f);
}

__forceinline void Vec3f::normalize()
{
	*this /= mag();
}

__forceinline void Vec3f::lerpTo(const Vec3f &v, float t)
{
	*this *= 1.0f - t;
	*this += v * t;
}

__forceinline void Vec3f::constrainMag(float c)
{
	const float magnitudeSquared = magSq();
	const float cSquared = c * c;
	if (magnitudeSquared >= cSquared)
	{
		*this *= cSquared / magnitudeSquared;
	}
}

__forceinline void Vec3f::clamp(float low, float high)
{
	m_x = m_x < low ? low : (m_x > high ? high : m_x);
	m_y = m_y < low ? low : (m_y > high ? high : m_y);
	m_z = m_z < low ? low : (m_z > high ? high : m_z);
}

__forceinline Vec3f Vec3f::operator+() const
{
	return *this;
}

__forceinline Vec3f Vec3f::operator-() const
{
	return Vec3f(-m_x, -m_y, -m_z);
}

__forceinline Vec3f Vec3f::operator+(const Vec3f &v) const
{
	return Vec3f(m_x + v.x(), m_y + v.y(), m_z + v.z());
}

__forceinline Vec3f Vec3f::operator-(const Vec3f &v) const
{
	return Vec3f(m_x - v.x(), m_y - v.y(), m_z - v.z());
}

__forceinline Vec3f Vec3f::operator*(float s) const
{
	return Vec3f(m_x * s, m_y * s, m_z * s);
}

__forceinline Vec3f Vec3f::operator/(float s) const
{
	return Vec3f(m_x / s, m_y / s, m_y / s);
}

__forceinline Vec3f &Vec3f::operator+=(const Vec3f &v)
{
	m_x += v.x();
	m_y += v.y();
	m_z += v.z();
	return *this;
}

__forceinline Vec3f &Vec3f::operator-=(const Vec3f &v)
{
	m_x -= v.x();
	m_y -= v.y();
	m_z -= v.z();
	return *this;
}

__forceinline Vec3f &Vec3f::operator*=(float s)
{
	m_x *= s;
	m_y *= s;
	m_z *= s;
	return *this;
}

__forceinline Vec3f &Vec3f::operator/=(float s)
{
	m_x /= s;
	m_y /= s;
	m_z /= s;
	return *this;
}

__forceinline float dot(const Vec3f &a, const Vec3f &b)
{
	return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

__forceinline Vec3f cross(const Vec3f &a, const Vec3f &b)
{
	return Vec3f(
		a.y() * b.z() - a.z() * b.y(),
		a.z() * b.x() - a.x() * b.z(),
		a.x() * b.y() - a.y() * b.x()
	);
}

} // namespace mhe