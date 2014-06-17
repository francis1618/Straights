#ifndef StraightStrategy_H
#define StraightStrategy_H

#include "StraightStrategy.h"
#include "Player.h"
#include "Command.h"

class HumanStragety : public StraightStrategy {
public:
	HumanStragety(Command &command);
	void executeStrategy(Player&, const vector<Card>&);
public:
	class InvalidHumanStrategyException() {		
	};
private:
	Command &command_;
};

#endif