#ifndef COMMAND_DEMO_H
#define COMMAND_DEMO_H
#include <string>
#include <vector>
#include "Command.h"
#include "Unit.h"

class Command;
class CommandDemo
{
public:
	CommandDemo();
	~CommandDemo();
	void HandleInput(std::string _button);
	void Undo();

private:
	std::vector<Command*> m_commands;

	//Unit* m_unit;
	/*Command* m_commandJump;
	Command* m_commandFireGun;
	Command* m_commandSwapWeapon;
	Command* m_commandLurch;*/
};

#endif