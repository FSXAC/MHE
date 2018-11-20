/* Bridge decouples abstraction from its implemenation
 *
 * Bridge changes a inheritance hierachy into orthogonal hierarchies
 * 
 * Checklist:
 * 		- 
 * 
 * Source: https://sourcemaking.com/design_patterns/bridge
 */

#pragma once

#include <iostream>
#include <string>

// Forward declaration

// !!! Abstract
class AbstractButton
{
public:
	AbstractButton() { }
	AbstractButton(const std::string& buttonName, int id)
	{
		m_impl = new ButtonImpl(buttonName, id);
	}

	// Virtual functions
	virtual void display()
	{
		m_impl->display();
	}

protected:
	ButtonImpl *m_impl;
};

// !!! Derived abstract classes
class AbstractPushButton : public AbstractButton
{
public:
	AbstractPushButton(const std::string& buttonName, int id, float pressure)
	{
		m_impl = new PushButtonImpl(buttonName, id, pressure);
	}
};

class AbstractRadialButton : public AbstractButton
{
public:
	AbstractRadialButton(const std::string& buttonName, int id, float angle)
	{
		m_impl = new RadialButtonImpl(buttonName, id, angle);
	}
};


// !!! Implemenation Base class
class ButtonImpl
{
public:
	ButtonImpl(const std::string& buttonName, int id)
	{
		m_buttonName = buttonName;
		m_id = id;
	}

	virtual void display()
	{
		std::cout << "Button name: " << m_buttonName << "(id: " << m_id << ")\n";
	}

protected:
	std::string m_buttonName;
	int m_id;
};

// !!! Derived implementation classes

class PushButtonImpl : public ButtonImpl
{
public:
	PushButtonImpl(const std::string& buttonName, int id, float pressure)
	: ButtonImpl(buttonName, id)
	{
		m_pressure = pressure;
		m_isEasyToPress = pressure < 10.0;
	}

	// overriding base class method
	void display() override
	{
		std::cout << "Push button name: " << m_buttonName << "(id: " << m_id << ")\n";

		if (m_isEasyToPress)
			std::cout << "This push button is easy to press.\n";
		else
			std::cout << "This push button is difficult to press.\n";
	}

protected:
	float m_pressure;
	bool m_isEasyToPress;
};

class RadialButtonImpl : public ButtonImpl
{
public:
	RadialButtonImpl(const std::string& buttonName, int id, float angle)
	: ButtonImpl(buttonName, id)
	{
		m_angle = angle;
	}

	void display() override
	{
		std::cout << "Radial button name: " << m_buttonName << "(id: " << m_id << ")\n";
		std::cout << "This radial button has displacement of " << m_angle << " rad.";
	}

protected:
	float m_angle;
};

// How is it used ???

namespace bridge
{
	void example()
	{
		// Let's make an assortment of different buttons and put them in the "Button" abstract array

		AbstractButton *buttons[4];

		buttons[0] = new AbstractButton("plain button", 0);
		buttons[1] = new AbstractPushButton("bottom push button", 1, 1.5);
		buttons[2] = new AbstractPushButton("top push button", 2, 10.1);
		buttons[3] = new AbstractPushButton("radial push button", 3, 1.67);

		for (int i = 0; i < 4; i++)
		{
			buttons[i]->display();
		}
	}
}