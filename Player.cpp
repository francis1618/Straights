#include <iostream>
#include <vector>
#include <algorithm> 
#include "Player.h"
#include "StraightStrategy.h"
using namespace std;

Player::Player(StraightStrategy* strategy, int playerNumber)
	: strategy_(strategy), playerNumber_(playerNumber) {}

void Player::setStrategy(StraightStrategy* strategy) {
	if(this->strategy_)
		delete this->strategy_;
	this->strategy_ = strategy;
}

void Player::setPlayerNumber(int number) {
	playerNumber_ = number;
}

void Player::addCard(const Card &card) {
	hand_.push_back(card);
}

bool Player::playCard(const Card &card) {
	if(remove(card)) {
		cout<<"Player "<<playerNumber_<<" plays"<<card<<"."<<endl;
		return true;
	}
	else{
		return false;
	}
}

//might throw exception
bool Player::discard(const Card &card) {
	if(remove(card)) {
		discard_.push_back(card);
		cout<<"Player "<<playerNumber_<<" discards"<<card<<"."<<endl;
		return true;
	} else {
		return false;
	}
}

bool Player::remove(const Card &card) {
	if(find(hand_.begin(), hand_.end(), card) != hand_.end()) {
    	hand_.erase(find(hand_.begin(), hand_.end(), card));
    	return true;
	} else {
		return false;
	}
}

const vector<Card>& Player::getHand() const {
	return hand_;
}

const vector<Card>& Player::getDiscard() const {
	return discard_;
}