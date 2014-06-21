#ifndef COMPUTERSTRATEGY_H
#define COMPUTERSTRATEGY_H

#include "StraightStrategy.h"
#include <vector>


// implement artificial intelligence behaviour strategy
class ComputerStrategy : public StraightStrategy {
public:
	void executeStrategy(Player&, std::vector<Card>&);
};

#endif