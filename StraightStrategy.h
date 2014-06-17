#ifndef StraightStrategy_H
#define StraightStrategy_H

#include "Player.h"

class Player;

class StraightStrategy {
public:
	void setPlayer(Player&);
	virtual void executeStrategy() = 0;
	virtual ~playMove();
private:
	class UnsetPlayerException {
	};
private:
	Player *player_;
};

#endif