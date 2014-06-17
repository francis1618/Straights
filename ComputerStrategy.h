#ifndef ComputerStrategy_h
#define ComputerStrategy_h

#include "StraightStrategy.h"

class ComputerStrategy : public StraightStrategy {
public:
	void executeStrategy(Player& const vector<Card>&);
};

#endif