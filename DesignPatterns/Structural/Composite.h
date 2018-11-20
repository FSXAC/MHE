/*
 *
 * 1. Identify scalar/primitive classes and vector/container classes
 * 2. Create interface that can make all concrete classes interchangeable
 * 3. All concrete class has "is a" relationship to interface (derived)
 * 4. All container classes couple themselves to the interface
 * 5. All contianer classes use polymorphism tod elegate to children
 * 
 * Source: https://github.com/kamranahmedse/design-patterns-for-humans#-composite
 * Source: https://sourcemaking.com/design_patterns/composite
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Interface that uses lowest common denominator of the derived classes
class Widget
{
public:
	virtual void setName(string name) { m_name = name; };
	virtual void setId(int id) { m_id = id; };

	virtual const string& getName() const { return m_name; };
	virtual const int getId() const { return m_id; };

	virtual void display() = 0;

protected:
	string m_name;
	int m_id;
};

// Scalar/primitive class that has "is a" relationship with interface
class Entity : public Widget
{
public:
	Entity(string name, int id)
	{
		setName(name);
		setId(id);
	}

	void display() override { cout << "Entity " << m_name << "(id: " << m_id << ")\n"; }
};

// Vector/Container class
class EntityContainer : public Widget
{
public:
	EntityContainer(string name, int id)
	{
		setName(name);
		setId(id);
	}

	// Add children
	void addChild(Widget *widget)
	{
		m_children.push_back(widget);
	}

	// Add children by creating one by itself
	Widget* createEntityChild(string name, int id)
	{
		Entity* newEntity = new Entity(name, id);
		m_children.push_back(newEntity);

		return newEntity;
	}

	Widget* createContainerChild(string name, int id)
	{
		EntityContainer* newContainer = new EntityContainer(name, id);
		m_children.push_back(newContainer);

		return newContainer;
	}

	void display() override {
		cout << "Container " << m_name << "(id: " << m_id << ")\n";
		for (Widget *widget : m_children)
		{
			widget->display();
		}
	}

protected:
	// Container class holds a list of children
	vector<Widget *> m_children;
};

namespace composite
{
	void example()
	{
		EntityContainer *mainWidget = new EntityContainer("root", 0);

		mainWidget->createEntityChild("child1", 1);
		mainWidget->createEntityChild("child2", 2);

		EntityContainer *inner1 = static_cast<EntityContainer*>(mainWidget->createContainerChild("inner container", 3));
		
		for (int i = 0; i < 4; i++)
		{
			inner1->createEntityChild("inner entity", 4 + i);
		}

		EntityContainer *inner2 = static_cast<EntityContainer*>(mainWidget->createContainerChild("inner inner container", 10));


		// display
		mainWidget->display();
	}
}