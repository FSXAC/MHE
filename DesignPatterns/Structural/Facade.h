/* Facade is a single class that represents an entire subsystem
 *
 * This is used to abstract away the complexity, and expose a simple interface for the client
 * This is used to minimize commmunication and dependency between subsystems
 * 
 * 
 * 1. Identify a simpler interface for the subsystem
 * 2. Design a warpper that encapsulates the system
 * 3. The wrapper takes all the complexity and collaborations of a system and delegates to methods
 * 4. client couples/uses the wrapper facade
 */

#pragma once

#include <iostream>

// Suppose printer is a complicated subsystem
class Printer
{
public:
	void enablePowerSupply() { std::cout << "Power supply on\n"; }
	void enableMotor1() { std::cout << "Motor 1 active.\n"; }
	void enableMotor2() { std::cout << "Motor 2 active.\n"; }
	void heatBed(int temperature) { std::cout << "Bed set to heat to " << temperature << ".\n"; }
	void heatNozzle(int temperature) { std::cout << "Nozzle set to heat to " << temperature << ".\n"; }
	void homePosition() { std::cout << "Homing..."; }
	void print() { std::cout << "Printing..."; }
	void disableMotor1() { std::cout << "Motor 1 deactivated.\n"; }
	void disableMotor2() { std::cout << "Motor 2 deactivated.\n"; }
	void disablePowerSupply() { std::cout << "Shutting down.\n"; }

protected:
	bool m_hasPower = false;
	
};

// We don't want the client to call these individual methods, so we make a wrapper that abstract
// the more primitive method calls into wrapper methods, these will ease the communication between the two

// Facade class
class PrinterFacade
{
public:
	// Create instance of the system we are working wiht
	PrinterFacade() { m_printer = new Printer(); }

	void turnOn()
	{
		m_printer->enablePowerSupply();
		m_printer->enableMotor1();
		m_printer->enableMotor2();
		m_printer->homePosition();
	}

	void print()
	{
		m_printer->heatBed(60);
		m_printer->heatNozzle(220);
		m_printer->print();
		m_printer->heatBed(25);
		m_printer->heatNozzle(25);
	}

	void turnOff()
	{
		m_printer->disableMotor1();
		m_printer->disableMotor2();
		m_printer->disablePowerSupply();
	}

protected:
	Printer* m_printer;

};

// How it's used???
namespace facade
{
	void example()
	{
		PrinterFacade *printer = new PrinterFacade();
		printer->turnOn();
		printer->print();
		printer->turnOff();
	}
}