#pragma once
#include "Command.h"

class QuitCommand : public Command {
	
protected:
	// Inherited via Command
	virtual void onActionStart() override;

	virtual void onActionEnd() override;

public:
	QuitCommand(std::vector<Input*> inputs);
};
