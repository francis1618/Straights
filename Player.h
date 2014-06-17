#ifndef PLAYER_H
#define PLAYER_H


#include <vector>
#include "Card.h"
#include "StraightStrategy.h"

class StraightStrategy;

class Player {
public:
	Player(StraightStrategy*);
	void setStrategy(StraightStrategy*);
	void addCard(const Card&);
	void remove(const Card&);
	void discard(const Card&);
	void makeMove();
	const vector<Card>& getHand() const;
private:
	StraightStrategy *strategy_;
	std::vector<Card> discard_;
	std::vector<Card> hand_;
};


#endif