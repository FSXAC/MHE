#pragma once

#include <math.h>

namespace mhe
{

class Vec4f
{
  public:
    Vec4f(float x, float y, float z, float w);
    ~Vec4f() = default;

    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setW(float w);

    float x() const { return m_x; }
    float y() const { return m_y; }
    float z() const { return m_z; }
    float w() const { return m_w; }

    float magSq() const;
    float mag() const;
    Vec4f unit() const;
    Vec4f project(const Vec4f &v, bool flip = false) const;
    void normalize();
    void lerpTo(const Vec4f &v, float t);

  public:
    Vec4f operator+() const;
    Vec4f operator-() const;
    Vec4f operator+(const Vec4f &v) const;
    Vec4f operator-(const Vec4f &v) const;
    Vec4f operator*(float s) const;
    Vec4f operator/(float s) const;

    Vec4f &operator+=(const Vec4f &v);
    Vec4f &operator-=(const Vec4f &v);
    Vec4f &operator*=(float s);
    Vec4f &operator/=(float s);

  private:
    float m_x;
    float m_y;
    float m_z;
    float m_w;
};

float dot(const Vec4f &a, const Vec4f &b);

/* Inline implementation */
__forceinline Vec4f::Vec4f(float x, float y, float z, float w)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_w = w;
}

__forceinline void Vec4f::setX(float x)
{
    m_x = x;
}

__forceinline void Vec4f::setY(float y)
{
    m_y = y;
}

__forceinline void Vec4f::setZ(float z)
{
    m_z = z;
}

__forceinline void Vec4f::setW(float w)
{
    m_w = w;
}

__forceinline float Vec4f::magSq() const
{
    return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
}

__forceinline float Vec4f::mag() const
{
    return sqrt(magSq());
}

__forceinline Vec4f Vec4f::unit() const
{
    const float norm = mag();
    return Vec4f(m_x / norm, m_y / norm, m_z / norm, m_w / norm);
}

__forceinline Vec4f Vec4f::project(const Vec4f &v, bool flip) const
{
    return v * dot(*this, v) / v.magSq() * (flip ? -1.0f : 1.0f);
}

__forceinline void Vec4f::normalize()
{
    *this /= mag();
}

__forceinline void Vec4f::lerpTo(const Vec4f &v, float t)
{
    *this *= 1.0f - t;
    *this += v * t;
}

__forceinline Vec4f Vec4f::operator+() const
{
    return *this;
}

__forceinline Vec4f Vec4f::operator-() const
{
    return Vec4f(-m_x, -m_y, -m_z, -m_z);
}

__forceinline Vec4f Vec4f::operator+(const Vec4f &v) const
{
    return Vec4f(m_x + v.x(), m_y + v.y(), m_z + v.z(), m_w + v.w());
}

__forceinline Vec4f Vec4f::operator-(const Vec4f &v) const
{
    return Vec4f(m_x - v.x(), m_y - v.y(), m_z - v.z(), m_w - v.w());
}

__forceinline Vec4f Vec4f::operator*(float s) const
{
    return Vec4f(m_x * s, m_y * s, m_z * s, m_w * s);
}

__forceinline Vec4f Vec4f::operator/(float s) const
{
    return Vec4f(m_x / s, m_y / s, m_y / s, m_y / s);
}

__forceinline Vec4f &Vec4f::operator+=(const Vec4f &v)
{
    m_x += v.x();
    m_y += v.y();
    m_z += v.z();
    m_w += v.w();
    return *this;
}

__forceinline Vec4f &Vec4f::operator-=(const Vec4f &v)
{
    m_x -= v.x();
    m_y -= v.y();
    m_z -= v.z();
    m_w -= v.w();
    return *this;
}

__forceinline Vec4f &Vec4f::operator*=(float s)
{
    m_x *= s;
    m_y *= s;
    m_z *= s;
    m_w *= s;
    return *this;
}

__forceinline Vec4f &Vec4f::operator/=(float s)
{
    m_x /= s;
    m_y /= s;
    m_z /= s;
    m_w /= s;
    return *this;
}

__forceinline float dot(const Vec4f &a, const Vec4f &b)
{
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z() + a.w() * b.w();
}

} // namespace mhe