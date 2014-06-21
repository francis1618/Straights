#ifndef HUMANSTRATEGY_H
#define HUMANSTRATEGY_H

#include "Command.h"
#include "StraightStrategy.h"
#include <vector>

//strategy that relies on user input, if command is
//not in score of human plays, transfer control back
//to game via exception
class HumanStrategy : public StraightStrategy {
public:
	//exception class, embedded command that caused the issue
	class InvalidHumanStrategyException {
	public:
		 InvalidHumanStrategyException(Command);
		Command getCommand() const;
	private:
		Command command_;	
	};

public:
	void executeStrategy(Player&, std::vector<Card>&);
};

#endif