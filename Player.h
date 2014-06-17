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
	void addCard(Card&);
	void discard(Card&);
	const vector<Card>& getHand();

//exception class
private:
	class InvalidCommandException {
	public:
		Command command();
	private:
		Command command_;
	};

private:
	void remove(Card&);
private:
	StraightStrategy *strategy;
	std::vector<Card> discard_;
	std::vector<Card> hand_;
};


#endif