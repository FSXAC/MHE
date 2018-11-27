/* Proxy pattern
 *
 * Placeholder to another obejct to control access to it
 * Provides an additional in-between level to support more controlled access
 * Wraps the object and add delegation
 * 
 * A proxy instantiates the real object the first time client requests for it
 * 
 * Applications of proxy
 * 1. Virtual proxy: placeholder for expensive objects; the object is created
 *    when client first requests/access the object
 * 2. Remote proxy: local representation of an object in a different space
 * 3. Protective proxy: controls acccses to sensitive object
 * 4. Smart proxy: interposes additional actions between client and object
 *    examples of smart proxy:
 *    - count number of references to the object so it can be freed
 *      automatically (smart pointer)
 *    - loading persistent object into memory
 *    - checking if real object is locked before access and ensure no other
 *      calls can change it
 * 
 * Checklist:
 * 1. Define interface that makes proxy and original object interchangeable
 * 2. Factory to decide whether a proxy or object is desirable
 * 3. Wrapper class holds pointer to real object and implements the interface
 * 4. Pointer may be initialized at construction or at first use
 * 5. Wrapper delegates to wrappee object
 * 
 * Source: https://sourcemaking.com/design_patterns/proxy
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>

// !!! Virtal proxy example

// Real object
class Dog
{
public:
	Dog(std::string& name)
	{
		m_name = name;
		std::cout << "Dog " << m_name << " created\n";
	}

	~Dog() { std::cout << "Dog " << m_name << "destroyed\n"; }

	void bark() { std::cout << m_name << " barks\n"; }

protected:
	int m_id;
	std::string m_name;
};

// Proxy objecty
class DogProxy
{
public:
	// Here we don't initialize the object in constructor
	DogProxy(std::string name)
	{
		m_name = name;
		m_dog = nullptr;
	}

	~DogProxy()
	{
		delete m_dog;
	}

	// Instead we initialize during first use
	void bark()
	{
		if (!m_dog)
			m_dog = new Dog(m_name);

		// Delegate to real object's methods
		m_dog->bark();
	}

private:
	Dog* m_dog;
	std::string m_name;
};

// !!! Protective Proxy (for avoiding accessing/modifiying objects from multiple clients)
class DogStack
{
public:
	DogStack() : m_accessKey(0) {}
	void getAccess(int accessKey) { m_accessKey = accessKey; }
	void pushDog(int accessKey, std::string name)
	{
		// Don't do anything if access key is not set or not correct
		if (m_accessKey == 0 || m_accessKey != accessKey)
			return;

		m_dogs.push_back(new DogProxy(name));
	}

	DogProxy* popDog(int accessKey)
	{
		if (m_accessKey == 0 || m_accessKey || accessKey)
			return;

		DogProxy *dog = m_dogs.back();
		m_dogs.pop_back();
		return dog;
	}
	void releaseAcess() { m_accessKey = 0; }

private:
	std::vector<DogProxy*> m_dogs;
	int m_accessKey;
};