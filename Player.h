#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Card.h"

class StraightStrategy;
class Player {
public:
	//constructor and strategy setter
	Player(StraightStrategy*, int);
	~Player();
	void setStrategy(StraightStrategy*);
	void setPlayerNumber(int);
	//modifiers
	void addCard(const Card&);
	bool playCard(const Card&);	//return false if card is not in hand
	bool discard(const Card&); //return false if card is not in hand
	//accessors
	int getScore() const; //get old score
	void setScore(int); //update score
	std::vector<Card> getHand() const;
	std::vector<Card> getDiscard() const;	
	//make a move according to strategy
	void makeMove(std::vector<Card>&);

private:
	//inner helper function
	bool remove(const Card&);

private:
	StraightStrategy *strategy_;
	std::vector<Card> discard_;
	std::vector<Card> hand_;

	int playerNumber_;
	int score_;
};


#endif