#ifndef STRAIGHTSTRATEGY_H
#define STRAIGHTSTRATEGY_H

#include <vector>

class Card;
class Player;

class StraightStrategy {
public:
	virtual void executeStrategy(Player&, std::vector<Card>&) = 0;
	virtual ~StraightStrategy();
//embedding the rules of Straight into the Strategy class
//potentially the Game class and choose between different types of games by
//using different strategy hierarchies
public:
	static std::vector<Card> validStraightPlays(const Player&, const std::vector<Card>&);
};

#endif