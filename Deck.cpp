#include "Deck.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// check if there are more cards to deal
bool Deck::isEmpty() const {
	return !(index_ < CARD_COUNT);
}


// get singleton instance
Deck& Deck::getInstance() {
	static Deck deck;
	return deck;
}

// private constructor that getInstance calls
Deck::Deck() : index_(0) {
	for (int suit = Card::CLUB; suit < Card::SUIT_COUNT; suit++) {
		for (int rank = Card::ACE; rank < Card::RANK_COUNT; rank++) {
			Card* card = new Card((Card::Suit)suit, (Card::Rank)rank);
			cards_.push_back(card);
		}
	}
}

// destroctor, release cards memory allocation
Deck::~Deck() {
	while(!cards_.empty()) {
		Card *tmp = cards_.back();
		cards_.pop_back();
		delete tmp;
	}
}

// shuffle with given algorithm by school
void Deck::shuffle() {
	int n = CARD_COUNT;
	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}

	index_ = 0;
}

//return next card
Card Deck::deal() {
	//should throw exception in production code if there is no more cards
	//but since this is completely useless for this project, I didn't do ti
	return *cards_[index_++];
}

//output stream overload
ostream &operator<<(ostream &out, const Deck &deck) {
	for (int i = 0; i < Card::SUIT_COUNT; i++) {
		for (int j = 0; j < Card::RANK_COUNT; j++) {
			out << *deck.cards_[i*Card::RANK_COUNT + j];
			if (j != Card::RANK_COUNT - 1) {
				out << " ";
			} 
		}
		out << endl;
	}
	return out;
}