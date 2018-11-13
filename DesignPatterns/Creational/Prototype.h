#pragma once

#include <iostream>
#include <string>

// Prototype is used when we need to create an object that is very similar to an existing one
// but creating one from scratch is more expensive

class Player
{
public:
	Player(std::string name, int experience, int currency)
	{
		m_name = name;
		m_experience = experience;
		m_currency = currency;
	}

	// Getter
	const std::string& getName() const { return m_name; }
	const int getExperience() const { return m_experience; }
	const int getCurrency() const { return m_currency; }

	// Setter
	void setName(const std::string& name) { m_name = name; }
	void setExperience(const int experience) { m_experience = experience; }
	void setCurrency(const int currency) { m_currency = currency; }

	// !!! Clone the object
	Player* clone()
	{
		return new Player(*this);
	}

private:
	std::string m_name;
	int m_experience;
	int m_currency;
};

// How it's used ???
namespace prototype
{
	void example()
	{
		Player* player1 = new Player("Frisk", 0, 100);

		// Clone player 1 and change a few things to make player 2
		Player* player2 = player1->clone();
		player2->setName("Chara");
		player2->setExperience(5);
	}
}