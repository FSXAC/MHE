/* Wraps incompatible objects in an adapter
 * so that it's compatible/interfaceable with other objects
 * 
 * This is especially useful when working with third party code like libraries
 * or APIs
 * 
 * Checklist:
 * 		- Identify the componenets that need to be accommodated (client)
 * 		- Identify the components that need to be adapted (adaptee)
 * 		- Wrapper class that can "impedance match" adaptee to client
 * 		- Wrapper class has instance of adaptee class
 * 		- Wrapper class maps client interface to adaptee interface
 * 		- Client uses new interface (of the wrapper)
 * 
 * Source: https://sourcemaking.com/design_patterns/adapter
 */

#pragma once
#include <iostream>

using Vec2 = struct {
	int x;
	int y;
};

// !!! Suppose we have the following legacy class that needs to be adapted to be used
class LegacyRectangle
{
public:
	LegacyRectangle(int x1, int y1, int x2, int y2)
	{
		m_x1 = x1;
		m_x2 = x2;
		m_y1 = y1;
		m_y2 = y2;
	}
	
	// The legacy rectangle uses a differnet method name than preferred
	void render() { /* Something here */ }

private:
	int m_x1;
	int m_x2;
	int m_y1;
	int m_y2;
};

// !!! Suppose our client code needs to call draw() and pass in vec2 instead of int
// Desired rectangle class interface
class Rectangle
{
public:
	virtual void draw();
};

// !!! Adapter wrapper
class RectangleAdapter
	: public Rectangle
	, private LegacyRectangle
{
public:
	RectangleAdapter(Vec2 position, Vec2 size)
		: LegacyRectangle(position.x, position.y, position.x + size.x, position.y + size.y)
	{
		/* Legacy rectangle created; constructor interfacing correctly */	
	}

	// Calls the legacy function
	virtual void draw() override { render(); }
};

