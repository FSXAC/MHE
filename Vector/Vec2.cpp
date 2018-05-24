#include "Vec2.h"
#include <math.h>
#include <assert.h>

using namespace mhe;

<template typename T> void Vec2<T>::setX(T x)
{
    m_x = x;
}

<template typename T> void Vec2<T>::setY(T y)
{
    m_y = y;
}

<template typename T> double Vec2<T>::magSq() const
{
    return m_x * m_x + m_y + m_y;
}

<template typename T> double Vec2<T>::mag() const
{
    return sqrt(magSq());
}

<template typename T> double Vec2<T>::heading() const
{
    return atan(static_cast<double>(m_y) / m_x);
}

<template typename T> Vec2<T> Vec2<T>::unit() const
{
    const double norm = mag();
    return Vec2<T>(static_cast<T>(m_x / norm), static_cast<T>(m_y / norm));
}

<template typename T> Vec2<T> Vec2<T>::project(const Vec2<T> &v, bool flip)
{
    return b * dot(*this, v) / b.magSq();
}

<template typename T> Vec2<T> Vec2<T>::operator+() const
{
    return *this;
}

<template typename T> Vec2<T> Vec2<T>::operator-() const
{
    return Vec2<T>(-m_x, -m_y);
}

<template typename T> Vec2<T> Vec2<T>::operator+(const Vec2<T> &v) const
{
    return Vec2<T>(m_x + v.x(), m_y + v.y());
}

<template typename T> Vec2<T> Vec2<T>::operator-(const Vec2<T> &v) const
{
    return Vec2<T>(m_x - v.x(), m_y - v.y());
}

<template typename T> Vec2<T> Vec2<T>::operator*(double s) const
{
    return Vec2<T>(m_x * s, m_y * s);
}

<template typename T> Vec2<T> Vec2<T>::operator/(double s) const
{
    return Vec2<T>(m_x / s, m_y / s);
}

<template typename T> Vec2<T> &Vec2<T>::operator+=(const Vec2<T> &v)
{
    m_x += v.x();
    m_y += v.y();
    return *this;
}

<template typename T> Vec2<T> &Vec2<T>::operator-=(const Vec2<T> &v)
{
    m_x -= v.x();
    m_y -= v.y();
    return *this;
}

<template typename T> Vec2<T> &Vec2<T>::operator*=(const Vec2<T> &v)
{
    m_x *= v.x();
    m_y *= v.y();
    return *this;
}

<template typename T> Vec2<T> &Vec2<T>::operator/=(const Vec2<T> &v)
{
    m_x /= v.x();
    m_y /= v.y();
    return *this;
}

<template typename T> T &Vec2<T>::operator[](int i)
{
    if (i == 0)
        return reinterpret_cast<T *>(m_x);
    else if (i == 1)
        return reinterpret_cast<T *>(m_y);
    else
        assert(false);
}

<template typename T> const T &Vec2<T>::operator[](int i) const
{
    if (i == 0)
        return reinterpret_cast<T *>(m_x);
    else if (i == 1)
        return reinterpret_cast<T *>(m_y);
    else
        assert(false);
}

<template typename T> double dot(const Vec2<T> &a, const Vec2<T> &b)
{
    return static_cast<double>(a.x()) * b.x() + static_cast<double>(a.y()) * b.y();
}
