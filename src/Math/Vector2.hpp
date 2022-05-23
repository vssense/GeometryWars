#ifndef _VECTOR2_HPP_INCLUDED
#define _VECTOR2_HPP_INCLUDED

#include <cassert>
#include <cmath>

template <typename T>
struct Vec2
{
    Vec2(T x, T y) : x(x), y(y) {}
    ~Vec2() {}

    Vec2& operator+=(const Vec2& vec);
    Vec2& operator-=(const Vec2& vec);
    Vec2& operator*=(float k);
    Vec2& operator/=(float k);

    float GetLength() const;
    Vec2 Normalize();
    void Rotate(float alpha);

    T x;
    T y;
};

template <typename T>
Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs)
{
    return lhs += rhs;
}

template <typename T>
Vec2<T> operator-(Vec2<T> lhs, const Vec2<T>& rhs)
{
    return lhs -= rhs;
}

template <typename T>
float operator*(const Vec2<T>& lhs, const Vec2<T>& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename T>
Vec2<T> operator*(float lhs, Vec2<T> rhs)
{
    return rhs *= lhs;
}

template <typename T>
Vec2<T> operator/(Vec2<T> lhs, float rhs)
{
    return lhs /= rhs;
}

template <typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2& vec)
{
    x += vec.x;
    y += vec.y;

    return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2& vec)
{
    x -= vec.x;
    y -= vec.y;

    return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator*=(float k)
{
    x *= k;
    y *= k;

    return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator/=(float k)
{
    assert(k);

    x /= k;
    y /= k;

    return *this;
}

template <typename T>
float Vec2<T>::GetLength() const
{
    return sqrt(x * x + y * y);
}

template <typename T>
Vec2<T> Vec2<T>::Normalize()
{
    float lenght = GetLength();
    assert(lenght > __FLT_EPSILON__);

    return *this / lenght;
}

template <typename T>
void Vec2<T>::Rotate(float alpha)
{
    float old_x = x;
    float old_y = y;

    x = old_x * cos(alpha) - old_y * sin(alpha);
    y = old_x * sin(alpha) + old_y * cos(alpha);
}

#endif /* _VECTOR2_HPP_INCLUDED */

