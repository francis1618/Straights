#include "Player.h"
#include "StaightStrategy.h"
using namespace std;

Player::player()
	: score_(0) {}

void Player::addCard(Card &card) {
	hand_.push_back(card);
}

void Player::remove(Card &card) {
	if(find(hand_.begin(), hand_.end(), card) != hand_.end()) {
    	hand_.remove(hand_.begin(), hand_.end(), card);
	} else {
		throw InvalidMoveException();
	}
}

//might throw exception
void Player::discard(Card &card) {
	remove(card);
	discard_.push_back(card);
}

const vector<Card>& getHand() {
	return hand_;
}