#include "CommandDemo.h"
CommandDemo::CommandDemo() {
	/*m_commandJump = new CommandJump();
	m_commandFireGun = new CommandFire();
	m_commandSwapWeapon = new CommandSwapWeapon();
	m_commandLurch = new CommandLurch();*/
	//m_unit = new Unit();
}

CommandDemo::~CommandDemo() {
	//delete m_unit;
	/*delete m_commandJump;
	delete m_commandFireGun;
	delete m_commandSwapWeapon;
	delete m_commandLurch;*/
}

void CommandDemo::HandleInput(std::string _button) {
	/*if (_button == "X") m_commandJump->Execute();
	else if (_button == "Y") m_commandFireGun->Execute();
	else if (_button == "A") m_commandSwapWeapon->Execute();
	else if (_button == "B") m_commandLurch->Execute();*/

	//CommandMoveUnit* moveCommand = nullptr;
	//if (_button == "W") moveCommand = new CommandMoveUnit(m_unit, m_unit->GetX(), m_unit->GetY() + 1);
	//else if (_button == "A") moveCommand = new CommandMoveUnit(m_unit, m_unit->GetX() - 1, m_unit->GetY());
	//else if (_button == "S") moveCommand = new CommandMoveUnit(m_unit, m_unit->GetX(), m_unit->GetY() - 1);
	//else if (_button == "D") moveCommand = new CommandMoveUnit(m_unit, m_unit->GetX() + 1, m_unit->GetY());

	/*if (moveCommand != nullptr) {
		moveCommand->Execute();
		m_commands.push_back(moveCommand);
	}*/
}

void CommandDemo::Undo() {
	Command* lastCommand = m_commands.back();//get last command
	lastCommand->Undo();
	delete lastCommand;
	m_commands.pop_back(); // remove last command 
}