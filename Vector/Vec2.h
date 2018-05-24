#pragma once

namespace mhe {


/* 2D Vectors */

// Base class
<template typename T>
class Vec2
{
public:
    Vec2(T x, T y) { m_x = x; m_y = y; }
    ~Vec2() = default;

    void setX(T x);
    void setY(T y);

    T x() const { return m_x; }
    T y() const { return m_y; }

    double magSq() const;
    double mag() const;
    double heading() const;
    Vec2<T> unit() const;
    Vec2<T> project(const Vec2<T> &v, bool flip = false) const;

public:
    Vec2<T> operator+() const;
    Vec2<T> operator-() const;
    Vec2<T> operator+(const Vec2<T> &v) const;
    Vec2<T> operator-(const Vec2<T> &v) const;
    Vec2<T> operator*(double s) const;
    Vec2<T> operator/(double s) const;

    Vec2<T> & operator+=(const Vec2<T> &v);
    Vec2<T> & operator-=(const Vec2<T> &v);
    Vec2<T> & operator*=(double s);
    Vec2<T> & operator/=(double s);

    T& operator[](int i);
    const T& operator[](int i) const;

    friend double dot(const Vec2<T> &a, const Vec2<T> &b);

private:
    T m_x;
    T m_y;
}

// Derived classes
class Vec2i : public Vec2<int>
{
    Vec2i(int x, int y) : Vec2<int>(x, y) {}
    ~Vec2i() = default;
}

class Vec2f : public Vec2<float>
{
    Vec2f(float x, float y) : Vec2<float>(x, y) {}
    ~Vec2f() = default;
}

class Vec2lf : public Vec2<double>
{
    Vec2lf(double x, double y) : Vec2<double>(x, y) {}
    ~Vec2lf() = default;
}

}