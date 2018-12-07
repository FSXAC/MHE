/* Visitor allows client to define new opertion
 * without changing the classes of elements
 * on which it operates
 * 
 * Real life example (sourcemaking):
 * - Visitor (passenger) uses app to request an Uber
 * - Uber internal system sends a driver to pickup visitor
 * - Visitor enter Uber (visitor no longer in control)
 * - Once arrived, the Uber driver lets visitor "regain control"
 * 
 * Checklist:
 * 1. Confirm element hiearchy
 * 2. Create visitor base class with `visit(...)` for each type of
 *    element
 * 3. Add `accept(Visitor)` to element hiearchy
 * 4. Element hiearchy is coupled on to the visitor base
 * 5. Visitor hiearchy is coupled to derived element derived
 * 6. Create visitor derived class for each operation
 * 7. Client creates visitor objects and passes each to element
 * 
 * Source: https://sourcemaking.com/design_patterns/visitor
 * 
 */

#pragma once

#include <iostream>
#include <string>

// Fwd declare
class IVisitor;

// Element hiearchy
class IElement
{
public:
	virtual void accept(class IVisitor &v) = 0;
};

// Derived element classes
class Wind : public IElement
{
public:
	void accept(class IVisitor &v) override { v.visit(this); }
};

class Fire : public IElement
{
public:
	void accept(class IVisitor &v) override { v.visit(this); }
};

class Earth : public IElement
{
public:
	void accept(class IVisitor &v) override { v.visit(this); }
};

class Water : public IElement
{
public:
	void accept(class IVisitor &v) override { v.visit(this); }
};

// Visitor interface class
class IVisitor
{
public:
	virtual void visit(Wind *e) = 0;
	virtual void visit(Fire *e) = 0;
	virtual void visit(Earth *e) = 0;
	virtual void visit(Water *e) = 0;
};

// Derived visitor class does different things
class TasteVisitor : public IVisitor
{
public:
	void visit(Wind *e) override { std::cout << "[TASTE] Taste like air.\n"; }
	void visit(Fire *e) override { std::cout << "[TASTE] HOT HOT HOT!\n"; }
	void visit(Earth *e) override { std::cout << "[TASTE] Earth taste gross.\n"; }
	void visit(Water *e) override { std::cout << "[TASTE] This satisfied my thirst.\n"; }
};

class LookVisitor : public IVisitor
{
public:
	void visit(Wind *e) override { std::cout << "[LOOK] Nothing is here.\n"; }
	void visit(Fire *e) override { std::cout << "[LOOK] Pretty flames.\n"; }
	void visit(Earth *e) override { std::cout << "[LOOK] Earth looks boring.\n"; }
	void visit(Water *e) override { std::cout << "[LOOK] Nice river!\n"; }
};

// How it's used ???
namespace visitor
{
	void example()
	{
		// Elements
		IElement* elements[] = { new Wind(), new Fire(), new Earth(), new Water() };

		// Visitors
		IVisitor* senses[] = { new LookVisitor(), new TasteVisitor() };

		// Client passes visitor to elements to do "visiting"
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				elements[i]->accept(*senses[j]);
			}
		}
	}
}