#pragma once

namespace mhe
{

// Base class
<template typename T> class Vec3
{
  public:
    Vec3(T x, T y, T z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
    ~Vec3() = default;

    void setX(T x);
    void setY(T y);
    void setZ(T z);

    T x() const { return m_x; }
    T y() const { return m_y; }
    T z() const { return m_z; }

    double magSq() const;
    double mag() const;
    Vec3<T> unit() const;
    Vec3<T> project(const Vec3<T> &v, bool flip = false) const;

  public:
    Vec3<T> operator+() const;
    Vec3<T> operator-() const;
    Vec3<T> operator+(const Vec3<T> &v) const;
    Vec3<T> operator-(const Vec3<T> &v) const;
    Vec3<T> operator*(double s) const;
    Vec3<T> operator/(double s) const;

    Vec3<T> &operator+=(const Vec3<T> &v);
    Vec3<T> &operator-=(const Vec3<T> &v);
    Vec3<T> &operator*=(double s);
    Vec3<T> &operator/=(double s);

    T &operator[](int i);
    const T &operator[](int i) const;

    friend double dot(const Vec3<T> &a, const Vec3<T> &b);
    friend Vec3<T> cross(const Vec3<T> &a, const Vec3<T> &b);

  private:
    T m_x;
    T m_y;
    T m_z;
}

// Derived classes
class Vec3i : public Vec3<int>
{
    Vec3i(int x, int y, int z) : Vec3<int>(x, y, z) {}
    ~Vec3i() = default;
}

class Vec3f : public Vec3<float>
{
    Vec3f(float x, float y, float z) : Vec3<float>(x, y, z) {}
    ~Vec3f() = default;
}

class Vec3lf : public Vec3<double>
{
    Vec3lf(double x, double y, double z) : Vec3<double>(x, y, z) {}
    ~Vec3lf() = default;
}

} // namespace mhe