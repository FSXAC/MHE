/* Command pattern issue requests to objects without knowing anything about
 * the receiver (decouples the sender and receiver)
 * 
 * This could be useful for rebinding keyboard->actions
 * 
 * Command pattern would also allow undo/redo
 * 
 * Checklist:
 * 1. Define a command interface with method signature like execute()
 * 2. Derive class that encapsulate subset of:
 *    - receiver object
 *    - (or) method to invoke of receiver
 *    - (or) arguments to pass
 * 3. Instantiate command object for each deferred execution request
 * 4. Pass command object from sender to invoker (receiver)
 * 5. Receiver decides when to run execute() of the command
 * 
 * Source: https://en.wikipedia.org/wiki/Command_pattern#UML_class_diagram
 * Source: https://sourcemaking.com/design_patterns/command
 */

#pragma once

#include <iostream>

// !!! Some object we would like to interact with with commands
class Player
{
public:
	Player() : m_x(0), m_y(0) { }
	void moveUp() { m_y++; update(); }
	void moveDown() { m_y--; update(); }
	void moveLeft() { m_x--; update(); }
	void moveRight() { m_x++; update(); }
	void update() const { std::cout << "Player is at (" << m_x << ", " << m_y << ").\n"; }

private:
	int m_x;
	int m_y;
};

// !!! Command interface
class ICommand
{
public:
	virtual void execute() = 0;
};

// !!! Dervied class as commands
class MoveUpCommand : ICommand
{
public:
	MoveUpCommand(Player* player) {m_player = player; }
	void execute() override { m_player->moveUp(); }
private:
	Player* m_player;
};

class MoveDownCommand : ICommand
{
public:
	MoveDownCommand(Player* player) {m_player = player; }
	void execute() override { m_player->moveDown(); }
private:
	Player* m_player;
};

class MoveLeftCommand : ICommand
{
public:
	MoveLeftCommand(Player* player) {m_player = player; }
	void execute() override { m_player->moveLeft(); }
private:
	Player* m_player;
};

class MoveRightCommand : ICommand
{
public:
	MoveRightCommand(Player* player) {m_player = player; }
	void execute() override { m_player->moveRight(); }
private:
	Player* m_player;
};