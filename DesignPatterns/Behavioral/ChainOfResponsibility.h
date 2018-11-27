/* Chain of commands pattern
 * 
 * Useful for handling some request with multiple handlers
 * The handlers are derived from a base class
 * Each handler points to another handler, effectively chaining them up
 * 
 * Each handler in the chain could choose to "consume" the request
 * Then handlers down the line won't receive the input
 * 
 * Example of this in Frostbite is input handling:
 * such as input handlers and dispatchers linked up together or
 * a mouse click "penetrating" through layers of mouse input hitzones
 * 
 */

#pragma once

#include <iostream>

// !!! handler base
class HandlerBase
{
public:
	void setNext(HandlerBase* handler) { m_next = handler; }
	virtual void handle(int request);

protected:
	HandlerBase* m_next;
};

// !!! Derived handlers
// This one simply handles the request, then pass the request on to the next handler
class Handler1 : public HandlerBase
{
public:
	void handle(int request) override
	{
		if (request == 0)
			std::cout << "Handler 1 handles!\n";

		if (m_next)
			m_next->handle(request);
	}
};

// This one handles the request, if handled correctly, it will consume the request
class Handler2 : public HandlerBase
{
public:
	void handle(int request) override
	{
		if (request % 2 == 0)
			std::cout << "Handler 2 handles!\n";
		else if (m_next)
			m_next->handle(request);
	}
};

// This one consumes request altogether
class Handler3 : public HandlerBase
{
public:
	void handle(int request) override
	{
		if (request > 10)
			std::cout << "Handler 3 handles!\n";
	}
};
