#ifndef COMPUTERSTRATEGY_H
#define COMPUTERSTRATEGY_H

#include "StraightStrategy.h"
#include <vector>

class StraightStrategy;

class ComputerStrategy : public StraightStrategy {
public:
	void executeStrategy(Player&, std::vector<Card>&);
};

#endif