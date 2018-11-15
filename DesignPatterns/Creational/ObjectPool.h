#pragma once

/* Mose useful in:
 * 		- initializing is expensive
 * 		- need lots of initialization
 * Object pool caches objects for re-use
 * Object pool let others check-out objects from the pool
 * Object pool instantiates new objects when required
 * Object pool manages life time of objects in the pool and do clean up of unused objects periodically
 */

#include <iostream>
#include <string>
#include <list>


// !!! Suppose this is the object we want to pool
class Resource
{
public:
	Resource() { m_value = 0; }
	void reset() { m_value = 0; }
	void setValue(int value) { m_value = value; }
	int getValue() const { return m_value; }

private:
	int m_value;
};

// !!! have a singleton object pool class
class ObjectPool
{
public:
	// Static method for accessing the object pool instance
	static ObjectPool* getInstance()
	{
		if (!m_instance)
		{
			m_instance = new ObjectPool;
		}

		return m_instance;
	}


	// !!! Acquire
	Resource* acquireResource()
	{
		if (m_resources.empty())
		{
			return new Resource();
		}
		
		else
		{
			Resource* resource = const_cast<Resource*>(m_resources.front());
			m_resources.pop_front();
			return resource;
		}
	}

	// !!! Release
	void releaseResource(Resource* resource)
	{
		resource->reset();
		m_resources.push_back(resource);
	}

private:
	ObjectPool();

private:
	static ObjectPool* m_instance;
	std::list<Resource*> m_resources;
};