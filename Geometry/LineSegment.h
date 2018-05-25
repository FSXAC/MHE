#pragma once

namespace mhe
{

template <class Vec>
class LineSegment
{
public:
	LineSegment(Vec &a, Vec &b);
	~LineSegment() = default;

	Vec vector(bool flipped = false) const;
	float length() const;

private:
	Vec m_endPoints[2];
};

/* inline implementation */
template <class Vec>
__forceinline LineSegment<Vec>::LineSegment(Vec &a, Vec &b)
	: m_endPoints { a, b }
{
}

template <class Vec>
__forceinline Vec LineSegment<Vec>::vector(bool flipped) const
{
	if (flipped)
	{
		return m_endPoints[0] - m_endPoints[1];
	}
	else
	{
		return m_endPoints[1] - m_endPoints[0];
	}
}

template <class Vec>
__forceinline float LineSegment<Vec>::length() const
{
	return LineSegment::vector().mag();
}

}