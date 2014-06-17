#include "Player.h"
#include "StaightStrategy.h"
using namespace std;

Player::Player(StraightStrategy* strategy)
	: score_(0), strategy_(strategy) {}

void Player::setStrategy(StraightStrategy* strategy) {
	this->strategy_ = strategy;
}

void Player::addCard(const Card &card) {
	hand_.push_back(card);
}

//might throw exception
void Player::discard(const Card &card) {
	remove(card);
	discard_.push_back(card);
}

void Player::remove(const Card &card) {
	if(find(hand_.begin(), hand_.end(), card) != hand_.end()) {
    	hand_.remove(hand_.begin(), hand_.end(), card);
	}
}

const vector<Card>& getHand() const {
	return hand_;
}