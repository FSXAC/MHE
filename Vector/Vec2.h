#pragma once

#include <math.h>

namespace mhe
{

class Vec2f
{
public:
	Vec2f(float x, float y);
	~Vec2f() = default;

	void setX(float x);
	void setY(float y);

	float x() const { return m_x; }
	float y() const { return m_y; }

	float magSq() const;
	float mag() const;
	float heading() const;
	Vec2f unit() const;
	Vec2f project(const Vec2f &v, bool flip = false) const;
	void normalize();
	void lerpTo(const Vec2f &v, float t);
	void constrainMag(float c);
	void clamp(float low, float high);

public:
	Vec2f operator+() const;
	Vec2f operator-() const;
	Vec2f operator+(const Vec2f &v) const;
	Vec2f operator-(const Vec2f &v) const;
	Vec2f operator*(float s) const;
	Vec2f operator/(float s) const;

	Vec2f &operator+=(const Vec2f &v);
	Vec2f &operator-=(const Vec2f &v);
	Vec2f &operator*=(float s);
	Vec2f &operator/=(float s);

private:
	float m_x;
	float m_y;
};

float dot(const Vec2f &a, const Vec2f &b);
float cross(const Vec2f &a, const Vec2f &b);


/* Inline implementation */
__forceinline Vec2f::Vec2f(float x, float y)
{
	m_x = x;
	m_y = y;
}

__forceinline void Vec2f::setX(float x)
{
	m_x = x;
}

__forceinline void Vec2f::setY(float y)
{
	m_y = y;
}

__forceinline float Vec2f::magSq() const
{
	return m_x * m_x + m_y * m_y;
}

__forceinline float Vec2f::mag() const
{
	return sqrt(magSq());
}

__forceinline float Vec2f::heading() const
{
	return atan(static_cast<float>(m_y) / m_x);
}

__forceinline Vec2f Vec2f::unit() const
{
	const float norm = mag();
	return Vec2f(m_x / norm, m_y / norm);
}

__forceinline Vec2f Vec2f::project(const Vec2f &v, bool flip) const
{
	return v * dot(*this, v) / v.magSq() * (flip ? -1.0f : 1.0f);
}

__forceinline void Vec2f::normalize()
{
	*this /= mag();
}

__forceinline void Vec2f::lerpTo(const Vec2f &v, float t)
{
	*this *= 1.0f - t;
	*this += v * t;
}

__forceinline void Vec2f::constrainMag(float c)
{
	const float magnitudeSquared = magSq();
	const float cSquared = c * c;
	if (magnitudeSquared >= cSquared)
	{
		*this *= cSquared / magnitudeSquared;
	}
}

__forceinline void Vec2f::clamp(float low, float high)
{
	m_x = m_x < low ? low : (m_x > high ? high : m_x);
	m_y = m_y < low ? low : (m_y > high ? high : m_y);
}

__forceinline Vec2f Vec2f::operator+() const
{
	return *this;
}

__forceinline Vec2f Vec2f::operator-() const
{
	return Vec2f(-m_x, -m_y);
}

__forceinline Vec2f Vec2f::operator+(const Vec2f &v) const
{
	return Vec2f(m_x + v.x(), m_y + v.y());
}

__forceinline Vec2f Vec2f::operator-(const Vec2f &v) const
{
	return Vec2f(m_x - v.x(), m_y - v.y());
}

__forceinline Vec2f Vec2f::operator*(float s) const
{
	return Vec2f(m_x * s, m_y * s);
}

__forceinline Vec2f Vec2f::operator/(float s) const
{
	return Vec2f(m_x / s, m_y / s);
}

__forceinline Vec2f &Vec2f::operator+=(const Vec2f &v)
{
	m_x += v.x();
	m_y += v.y();
	return *this;
}

__forceinline Vec2f &Vec2f::operator-=(const Vec2f &v)
{
	m_x -= v.x();
	m_y -= v.y();
	return *this;
}

__forceinline Vec2f &Vec2f::operator*=(float s)
{
	m_x *= s;
	m_y *= s;
	return *this;
}

__forceinline Vec2f &Vec2f::operator/=(float s)
{
	m_x /= s;
	m_y /= s;
	return *this;
}

__forceinline float dot(const Vec2f &a, const Vec2f &b)
{
	return a.x() * b.x() + a.y() * b.y();
}

__forceinline float cross(const Vec2f &a, const Vec2f &b)
{
	return a.x() * b.x() - a.y() * b.y();
}

} // namespace mhe