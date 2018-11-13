#pragma once

#include <iostream>


// !!! say we have the following class set up
class Employee
{
public:
	virtual void giveReport();
};

class Programmer : public Employee
{
public:
	void giveReport() override
	{
		std::cout << "There are over 9000 bugs!\n";
	}
};

class Artist : public Employee
{
public:
	void giveReport() override
	{
		std::cout << "There are art to be made!\n";
	}
};

// !!!
class EmployeeLead
{

public:
	void performMeeting()
	{
		Employee* employee = makeEmployee();
		employee->giveReport();
	}

protected:
	virtual Employee *makeEmployee();
};

// !!! We can make derived `Lead` classes that would make the `makeEmployee` specific

class ProgrammerLead : public EmployeeLead
{
protected:
	Employee *makeEmployee() override
	{
		return new Programmer();
	}
};

class ArtistLead : public EmployeeLead
{
protected:
	Employee *makeEmployee() override
	{
		return new Artist();
	}
};

// How it can be used ???
namespace factory_method
{
	void example()
	{
		auto programmingLead = new ProgrammerLead();
		auto artistLead = new ArtistLead();

		// Conduct meeting
		programmingLead->performMeeting();	// programmer reports
		artistLead->performMeeting();		// artist reports
	}
}