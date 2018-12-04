/* Mediator responds to problem where reusable objects turns into complex spaghetti code
 *
 * Mediator is an intermediary to decouple objects
 * Promotes many-to-many relationships
 * 
 * Checklist:
 * 1. Identify collection of interacting objects that would benefit from decoupling
 * 2. Encapsulate those interactions in abstract class
 * 3. Create an instance of that new class and rework the stakeholder classes to interact with mediator only
 * 4. Distribute responsibility evenly
 * 5. No controller/god object
 * 
 * The simplist example is linked lists vs. arrays
 */

#pragma once
#include <iostream>

// Mediator Accessor
class LockMediator
{
public:
	LockMediator(bool defaultState = false) : m_locked(defaultState) { }
	void lock() { m_locked = true; }
	void unlock() { m_locked = false; }
	bool getLocked() const { return m_locked; }
private:
	bool m_locked;
};


// Something sets the lock
class Thing1
{
public:
	Thing1(LockMediator* lock)
	{
		m_lock = lock;
		lock->lock();
	}
	void finished() { m_lock->unlock(); }

private:
	LockMediator* m_lock;
};

// Something gets the status of the lock
class Thing2
{
public:
	Thing2(LockMediator *lock) { m_lock = lock; }
	void check()
	{
		if (m_lock->getLocked())
		{
			std::cout << "Thing 1 is not ready\n";
		}
		else
		{
			std::cout << "Thing 1 is finished\n";
		}
		
	}
private:
	LockMediator* m_lock;
};

// How to use it ???
namespace mediator
{
	void example() 
	{
		LockMediator lock(false);
		Thing1 thing1(&lock);
		Thing2 thing2(&lock);

		// check
		thing2.check();
		thing1.finished();
		thing2.check();
	}
}