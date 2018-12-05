/* Observer pattern defines a 1-to-many dependency
 * when one object's state changes, all of its dependants are notified
 * 
 * This is the "view" part of the model-view-controller
 *
 * Checklist:
 * 1. Differentiate between the core functions (independent) and optional functions (dependent)
 * 2. Model the independent function with "subject" abstraction
 * 3. Model the dependent function with "observer" hierachy
 * 4. Subject is coupled only to the observer base class
 * 5. Client configures the number and type of observers
 * 6. Observer register themselves to subject
 * 7. Subject broadcasts events to all registered observers
 * 8. The subject may "push" information to observers OR
 *    The observers may "pull" information from subject
 * 
 * Source: https://sourcemaking.com/design_patterns/observer
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>


// Forward declare
class Subject;

// Observer abstract class
class Observer
{
public:
	Observer(Subject *subject)
	{
		m_subject = subject;

		// [6] Observers register themselves
		m_subject->registerObserver(this);
	}

	// Unregister when observer is destroyed so subject don't access invalid memory
	~Observer() { m_subject->unregisterObserver(this); }

	// Update is up to the derived class
	virtual void update(int code) = 0;

protected:
	Subject* getSubject() const { return m_subject; }

private:
	Subject* m_subject;
};

// [1] Subject class
class Subject
{
public:

	Subject() : m_previousMessage("") { }

	// [2] Subject's core function
	// Setter
	void setText(std::string message)
	{
		m_previousMessage = message;
		std::cout << "Subject says: " << message << "\n";

		sendEvent(m_previousMessage.size());
	}

	// Getter
	const std::string& getPreviousMessage() const {
		return m_previousMessage;
	}
	
	// Register/unregister for potential observers
	void registerObserver(Observer* observer) { m_observers.push_back(observer); }
	void unregisterObserver(Observer* observer)
	{
		for (std::vector<Observer *>::iterator observerIter = m_observers.begin(); observerIter != m_observers.end(); observerIter++)
		{
			if (*observerIter == observer)
				m_observers.erase(observerIter);
		}
	}

private:
	// [7] Subject broadcasts to all registered observers
	void sendEvent(int code)
	{
		for (auto observer : m_observers)
		{
			// [8][Optional] Subject pushes information to observers via arguments
			observer->update(code);
		}
	}

private:
	std::string m_previousMessage;

	// [4]
	std::vector<Observer*> m_observers;
};

// [1] Observer derived classes
class MessageObserver : public Observer
{
public:
	MessageObserver(Subject *subject) : Observer(subject) { }

	// [3] Observers have their own behaviours
	void update(int code) override
	{
		// [8][Optional] Observer pulls information
		std::cout << "MessageObserver observes subject saying " << getSubject()->getPreviousMessage() << ".\n";
	}
};

// [1]
class LengthObserver : public Observer
{
public:
	LengthObserver(Subject *subject) : Observer(subject) {}

	// [3] Observers have their own behaviours
	void update(int code) override
	{
		std::cout << "LengthObserver observer message with length " << code << ".\n";
	}
};

// [1]
class LongMessageObserver : public Observer
{
public:
	LongMessageObserver(Subject *subject) : Observer(subject) {}

	// [3] Observers have their own behaviours
	void update(int code) override
	{
		if (code > 20)
			std::cout << "LongMessageObserver notices the size of message: " << code << ", which is over 20!\n";
		else
			std::cout << "LongMessageObserver is not impressed with the size.\n";
	}
};

// How it's used ???
namespace observer
{
	void example()
	{
		// Subject
		Subject* subject = new Subject();

		// Observers
		MessageObserver msgObs(subject);
		LengthObserver lenObs(subject);
		LongMessageObserver lmsgObs(subject);

		// Do whatever with subject and expect observer to do something too
		subject->setText("Hello world!");
		subject->setText("What the fuck did you just fucking say about me, you little bitch?");
	}
}