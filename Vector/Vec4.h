#pragma once

namespace mhe
{

// Base class
<template typename T> class Vec4
{
  public:
    Vec4(T x, T y, T z, T w)
    {
        m_x = x;
        m_y = y;
        m_z = z;
        m_w = w;
    }
    ~Vec4() = default;

    void setX(T x);
    void setY(T y);
    void setZ(T z);
    void setW(T w);

    T x() const { return m_x; }
    T y() const { return m_y; }
    T z() const { return m_z; }
    T w() const { return m_w; }

    double magSq() const;
    double mag() const;
    Vec4<T> unit() const;
    Vec4<T> project(const Vec4<T> &v, bool flip = false) const;

  public:
    Vec4<T> operator+() const;
    Vec4<T> operator-() const;
    Vec4<T> operator+(const Vec4<T> &v) const;
    Vec4<T> operator-(const Vec4<T> &v) const;
    Vec4<T> operator*(double s) const;
    Vec4<T> operator/(double s) const;

    Vec4<T> &operator+=(const Vec4<T> &v);
    Vec4<T> &operator-=(const Vec4<T> &v);
    Vec4<T> &operator*=(double s);
    Vec4<T> &operator/=(double s);

    T &operator[](int i);
    const T &operator[](int i) const;

    friend double dot(const Vec4<T> &a, const Vec4<T> &b);

  private:
    T m_x;
    T m_y;
    T m_z;
    T m_w;
}

// Derived classes
class Vec4i : public Vec4<int>
{
    Vec4i(int x, int y, int z, int w) : Vec4<int>(x, y, z, w) {}
    ~Vec4i() = default;
}

class Vec4f : public Vec4<float>
{
    Vec4f(float x, float y, float z, float w) : Vec4<float>(x, y, z, w) {}
    ~Vec4f() = default;
}

class Vec4lf : public Vec4<double>
{
    Vec4lf(double x, double y, double z, double w) : Vec4<double>(x, y, z, w) {}
    ~Vec4lf() = default;
}

} // namespace mhe