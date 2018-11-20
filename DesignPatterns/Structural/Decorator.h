/* Attach more behavior or states to objects at run time
 *
 * Source: https://sourcemaking.com/design_patterns/decorator
 * 
 * 1. Create lowest common denominator interface
 * 2. Create 2nd level base class for optional functionality
 * 3. CORE and DECORATOR classes has "is a" relationship with interface
 * 4. DECORATOR class "has a" instance of interface
 * 5. DECORATOR class delagates to "has a" object
 * 6. Create DECORATOR derived class to serve their functionality
 * 7. DECORATOR derived class delegate to base class etc
 * 8. Client composes desired configuration
 */

#pragma once

#include <iostream>


// [1]
class Widget
{
public:
	virtual void draw() = 0;
};

// [1][3] Core class
class TextField : public Widget
{
public:
	TextField(int w, int h)
	{
		m_width = w;
		m_height = h;
	}

	void draw() override
	{
		std::cout << "TextField(" << m_width << ", " << m_height << ")\n";
	}

protected:
	int m_width;
	int m_height;
};


// [2][3] 2nd level base decorator class
class Decorator : public Widget
{
public:
	Decorator(Widget *widget)
	{
		m_widget = widget;
	}

	void draw() override
	{
		// [5]
		m_widget->draw();
	}

protected:
	// [4]
	Widget *m_widget;
};

// [6] Derived decorator classes
class BorderDecorator : public Decorator
{
public:
	BorderDecorator(Widget *widget) : Decorator(widget) { };

	void draw() override
	{
		// Call parent
		Decorator::draw();
		
		// Own functionality
		std::cout << "Border decorator draws\n";
	}
};

class ScrollDecorator : public Decorator
{
public:
	ScrollDecorator(Widget *widget) : Decorator(widget) { };
	void draw() override
	{
		Decorator::draw();
		std::cout << "Scroll decorator draws\n";
	}
};

// How it's used ???

namespace decorator
{
	void example()
	{
		// We can create a base widget
		Widget *textFieldWidget = new TextField(200, 50);

		// Then decorate it with a "chain" of wrappers
		Widget *wrappedWidget = new BorderDecorator(
			new ScrollDecorator(
				new BorderDecorator(
					new ScrollDecorator(textFieldWidget)
				)
			)
		);

		// Notice that all are applied when we call the outer wrapped widget
		wrappedWidget->draw();
	}
}