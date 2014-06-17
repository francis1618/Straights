#ifndef StraightStrategy_H
#define StraightStrategy_H

#include "Player.h"

class Player;

class StraightStrategy {
public:
	virtual void executeStrategy(Player&, const vector<Card>&) = 0;
	const vector<Card>& validStraightPlays(Player&, const vector<Card>&);
	~StraightStrategy();
};

#endif