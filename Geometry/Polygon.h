#pragma once
#include <vector>
#include <assert.h>
#include <exception>
#include "../Vector/Vector.h"

namespace mhe
{

class Polygon
{
public:
	Polygon();
	~Polygon() = default;

	void pushVertex(std::vector<Vec2f> &verts);
	void pushVertex(Vec2f &vert);
	void reset();

	bool isConvex() const;
	bool isPointInside(Vec2f &pt) const;
	Vec2f centerOfMass() const;

	Vec2f &operator[](unsigned int i);
	const Vec2f &operator[](unsigned int i) const;

protected:
	enum class VertexCoordMode {
		Polygon_rectangular,
		Polygon_polar
	};

private:
	std::vector<Vec2f> m_vertices;
	VertexCoordMode m_coordMode;
};

// Inline implementation
__forceinline Polygon::Polygon()
	: m_coordMode(VertexCoordMode::Polygon_rectangular)
{
}

__forceinline void Polygon::pushVertex(std::vector<Vec2f> &verts)
{
	for (auto &v : verts)
	{
		m_vertices.push_back(v);
	}
}

__forceinline void Polygon::pushVertex(Vec2f &vert)
{
	m_vertices.push_back(vert);
}

__forceinline void Polygon::reset()
{
	m_vertices.clear();
}

__forceinline bool Polygon::isConvex() const
{
	if (m_vertices.size() < 3)
		return false;

	Vec2f p, v, u;
	int r = 0;

	const unsigned int numVerts = m_vertices.size();
	for (unsigned int i = 0; i < numVerts; i++)
	{
		p = m_vertices[i];
		Vec2f t = m_vertices[(i + 1) % numVerts];
		v.setX(t.x() - p.x());
		v.setY(t.y() - p.y());
		u = m_vertices[(i + 2) % numVerts];

		if (i == 0)
			r = cross(u, v) + cross(v, p);
		else
		{
			const int newR = cross(u, v) + cross(v, p);
			if ((newR > 0 && r < 0) || (newR < 0 && r> 0))
				return false;
		}
	}

	return true;
}

__forceinline bool Polygon::isConvex() const
{
	// TODO:
	return false;
}

__forceinline bool Polygon::isPointInside(Vec2f &pt) const 
{
	// TODO:
	return false;
}

__forceinline Vec2f Polygon::centerOfMass() const
{
	// TODO:
	return Vec2f();
}


__forceinline Vec2f &Polygon::operator[](unsigned int i)
{
	if (i > m_vertices.size() - 1)
		throw std::runtime_error("Polygon access index out of bound.");

	return m_vertices[i];
}

__forceinline const Vec2f &Polygon::operator[](unsigned int i) const
{
	if (i > m_vertices.size() - 1)
		throw std::runtime_error("Polygon access index out of bound.");

	return m_vertices[i];
}

}