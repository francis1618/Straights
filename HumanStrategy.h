#ifndef HUMANSTRATEGY_H
#define HUMANSTRATEGY_H

#include "Command.h"
#include "StraightStrategy.h"
#include <vector>

class StraightStrategy;
class Player;
class HumanStrategy : public StraightStrategy {
public:
	void executeStrategy(Player&, std::vector<Card>&);
public:
	class InvalidHumanStrategyException {
	public:
		 InvalidHumanStrategyException(Command);
		Command getCommand() const;
	private:
		Command command_;	
	};
};

#endif