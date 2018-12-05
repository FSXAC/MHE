/* Memento pattern is a way to store an object state, so that the object
 * may choose to restore to it at a later time
 * 
 * It externalizes an object's internal state
 * 
 * 'Originator' is the object that knows how to save itself
 * 'Caretaker' is the object that knows when and why a save needs to be restored
 * 'Memento' is the private info written and read by originator, but kept by the caretaker
 * 
 * Checklist:
 * 1. Identify "caretaker" and "originator"
 * 2. Create Memento class, originator is a friend
 * 3. Caretaker knows when to "check point" the originator
 * 4. Originator creates memento and copies its state to it
 * 5. Caretaker holds memento
 * 6. Caretaker knows when to "roll back" the originator
 * 7. Originator restores using memento
 *
 * Command vs. Memento:
 * - Command passes request, Memento passes the internal state
 * - Memento is often used with iterator to caputre the state of an interation
 * 
 * Source:
 * - https://sourcemaking.com/design_patterns/memento
 * - https://sourcemaking.com/design_patterns/memento/cpp/1
 * - https://github.com/kamranahmedse/design-patterns-for-humans#-memento
 * 
 */

#pragma once

#include <iostream>
#include <string>

// Suppose we have an interactive textbox
// [1] Textbox will be the originator since it has the internal states and data
//     We let the parent window be the caretaker as it handles commands
class Textbox;

// [2] The memento should store the position, the size of the textbox and the text in it
class TextboxMemento
{
	friend Textbox;
public:
	TextboxMemento()
	: m_width(-1)
	, m_height(-1)
	, m_x(-1)
	, m_y(-1)
	, m_text("")
	{
	}
	
private:
	int m_width;
	int m_height;
	int m_x;
	int m_y;
	std::string m_text;
};

// Implementing textbox
class Textbox
{
public:
	Textbox(int x, int y, int width, int height)
	: m_text("")
	, m_changed(false)
	{
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
	}

	// Some methods to set the internal states
	void setText(const std::string& text) { m_text = text; m_changed = true; }
	void addChar(char character) { m_text += character; m_changed = true; }
	void resize(int width, int height) { m_width = width; m_height = height; m_changed = true; }
	void move(int x, int y) { m_x = x; m_y = y; m_changed = true; }

	// Get changed
	bool getChanged() const { return m_changed; }

	// [4] Originator "save state" method
	TextboxMemento* saveState()
	{
		TextboxMemento *memento = new TextboxMemento();
		memento->m_x = m_x;
		memento->m_y = m_y;
		memento->m_width = m_width;
		memento->m_height = m_height;
		memento->m_text = m_text;

		// Set changed flag to false, so next time we request for memento, we don't get an exact copy
		m_changed = false;

		return memento;
	}

	// [7] Originator "load state" method
	void loadState(TextboxMemento* memento, bool forceLoad = false)
	{
		// [TODO] we could do save-checking to see if we want to save or discard unsaved changes
		if (m_changed && !forceLoad)
		{
			// Do something...
			std::cout << "Unable to load memento: unsaved changes exist.\n";
			return;
		}

		if (memento->m_x >= 0)
			m_x = memento->m_x;
		if (memento->m_y >= 0)
			m_y = memento->m_y;
		if (memento->m_width > 0)
			m_width = memento->m_width;
		if (memento->m_height > 0)
			m_height = memento->m_height;

		m_text = memento->m_text;
	}

	// Output
	void display() const
	{
		std::cout << "Textbox at (" << m_x << ", " << m_y << "), ";
		std::cout << "dimensions: (" << m_width << "x" << m_height << "), ";
		std::cout << "content: " << m_text << "\n";
	}

private:
	int m_width;
	int m_height;
	int m_x;
	int m_y;
	std::string m_text;

	// We may choose to optimize a big
	bool m_changed;
};

// Caretaker class
class Window
{
public:

	Window() { }
	void setTextbox(Textbox* textbox) { m_textbox = textbox; }

	// Suppose we have these two handlers to call

	// Save command
	void onSavePressed()
	{
		// Check that we have the necessity to save state
		if (m_textbox->getChanged())
		{
			m_textboxMemento = m_textbox->saveState();
			std::cout << "State saved!\n";
		}
		else
		{
			std::cout << "State already saved; nothing changed.\n";
		}
	}

	// Load command
	void onLoadPressed(bool forceLoad)
	{
		if (m_textboxMemento)
		{
			m_textbox->loadState(m_textboxMemento, forceLoad);
			std::cout << "State loaded!\n";
		}
		else
		{
			std::cout << "Attempt to load uninitialized state; nothing changed.\n";
		}
	}

	void display() const { m_textbox->display(); }

private:
	Textbox* m_textbox;
	TextboxMemento* m_textboxMemento;
};

// How to use it ???
namespace memento
{
	void example()
	{
		// Setup
		Window* window = new Window();
		Textbox* textbox = new Textbox(0, 0, 100, 100);
		window->setTextbox(textbox);

		// 
		window->display();
		textbox->setText("Hello World");
		
		// Save state
		window->onSavePressed();

		// Modify
		textbox->move(20, 40);
		textbox->resize(200, 60);
		textbox->addChar('!');
		window->display();

		// Save again
		window->onSavePressed();

		// Save again (due to our optional optimziation, this should now actually save)
		window->onSavePressed();

		// Modify (don't save)
		textbox->setText("Goodbye");
		textbox->move(99, 66);
		window->display();

		// Load (don't force; should not restore state because state has changed since last save)
		window->onLoadPressed(false);
		window->display();

		// Load again (force)
		window->onLoadPressed(true);
		window->display();
	}
}