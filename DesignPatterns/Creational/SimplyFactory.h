#pragma once


// NOTE: SUPPOSE WE HAVE THE FOLLOWING SCENARIO:

// Base class
class Shape
{
public:
	// Virutal methods act as interface framework
	virtual float getArea();

protected:
	float m_width;
	float m_height;
};


// Derived class
class Rectangle : public Shape
{

public:
	Rectangle(float width, float height)
	{
		m_width = width;
		m_height = height;
	}

	float getArea()
	{
		return m_width * m_height;
	}
};

class Triangle : public Shape
{
public:
	Triangle(float width, float height)
	{
		m_width = width;
		m_height = height;
	}

	float getArea()
	{
		return m_width * m_height / 2.0;
	}
};


// Factory itself
class ShapeFactory
{
public:
	static Shape* makeRectangle(float width, float height)
	{
		return new Rectangle(width, height);
	}

	static Shape* makeTriangle(float width, float height)
	{
		return new Triangle(width, height);
	}
}