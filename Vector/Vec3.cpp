#include "Vec3.h"
#include <math.h>
#include <assert.h>

using namespace mhe;

<template typename T> void Vec3<T>::setX(T x)
{
    m_x = x;
}

<template typename T> void Vec3<T>::setY(T y)
{
    m_y = y;
}

<template typename T> void Vec3<T>::setZ(T z)
{
    m_z = z;
}

<template typename T> double Vec3<T>::magSq() const
{
    return m_x * m_x + m_y + m_y + m_z * m_z;
}

<template typename T> double Vec3<T>::mag() const
{
    return sqrt(magSq());
}

<template typename T> Vec3<T> Vec3<T>::unit() const
{
    const double norm = mag();
    return Vec3<T>(
        static_cast<T>(m_x / norm),
        static_cast<T>(m_y / norm),
        static_cast<T>(m_z / norm));
}

<template typename T> Vec3<T> Vec3<T>::project(const Vec3<T> &v, bool flip)
{
    return b * dot(*this, v) / b.magSq();
}

<template typename T> Vec3<T> Vec3<T>::operator+() const
{
    return *this;
}

<template typename T> Vec3<T> Vec3<T>::operator-() const
{
    return Vec3<T>(-m_x, -m_y, -m_z);
}

<template typename T> Vec3<T> Vec3<T>::operator+(const Vec3<T> &v) const
{
    return Vec3<T>(m_x + v.x(), m_y + v.y(), m_z + v.z());
}

<template typename T> Vec3<T> Vec3<T>::operator-(const Vec3<T> &v) const
{
    return Vec3<T>(m_x - v.x(), m_y - v.y(), m_z - v.z());
}

<template typename T> Vec3<T> Vec3<T>::operator*(double s) const
{
    return Vec3<T>(m_x * s, m_y * s, m_z * s);
}

<template typename T> Vec3<T> Vec3<T>::operator/(double s) const
{
    return Vec3<T>(m_x / s, m_y / s, m_z / s);
}

<template typename T> Vec3<T> &Vec3<T>::operator+=(const Vec3<T> &v)
{
    m_x += v.x();
    m_y += v.y();
    m_z += v.z();
    return *this;
}

<template typename T> Vec3<T> &Vec3<T>::operator-=(const Vec3<T> &v)
{
    m_x -= v.x();
    m_y -= v.y();
    m_z -= v.z();
    return *this;
}

<template typename T> Vec3<T> &Vec3<T>::operator*=(const Vec3<T> &v)
{
    m_x *= v.x();
    m_y *= v.y();
    m_z *= v.z();
    return *this;
}

<template typename T> Vec3<T> &Vec3<T>::operator/=(const Vec3<T> &v)
{
    m_x /= v.x();
    m_y /= v.y();
    m_z /= v.z();
    return *this;
}

<template typename T> T &Vec3<T>::operator[](int i)
{
    if (i == 0)
        return reinterpret_cast<T *>(m_x);
    else if (i == 1)
        return reinterpret_cast<T *>(m_y);
    else if (i == 2)
        return reinterpret_cast<T *>(m_z);
    else
        assert(false);
}

<template typename T> const T &Vec3<T>::operator[](int i) const
{
    if (i == 0)
        return reinterpret_cast<T *>(m_x);
    else if (i == 1)
        return reinterpret_cast<T *>(m_y);
    else if (i == 2)
        return reinterpret_cast<T *>(m_z);
    else
        assert(false);
}

<template typename T> double dot(const Vec3<T> &a, const Vec3<T> &b)
{
    return static_cast<double>(a.x()) * b.x() + static_cast<double>(a.y()) * b.y() + static_cast<double>(a.z()) * b.z();
}

<template typename T> Vec3<T> cross(const Vec3<T> &a, const Vec3<T> &b)
{
    return Vec3<T>(
        a.y() * b.z() - a.z() * b.y(),
        b.x() * a.z() - a.x() * b.z(),
        a.x() * b.y() - a.y() * b.x()
    );
}