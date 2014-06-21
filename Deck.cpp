#include <iostream>
#include <string>
#include <cstdlib>
#include "Deck.h"
using namespace std;


using namespace std;

bool Deck::isEmpty() const {
	return !(index_ < CARD_COUNT);
}

Deck& Deck::getInstance() {
	static Deck deck;
	return deck;
}

Deck::Deck() : index_(0) {
	for (int suit = CLUB; suit < SUIT_COUNT; suit++) {
		for (int rank = ACE; rank < RANK_COUNT; rank++) {
			Card* card = new Card((Suit)suit, (Rank)rank);
			cards_.push_back(card);
		}
	}
}


Deck::~Deck() {
	while(!cards_.empty()) {
		Card *tmp = cards_.back();
		cards_.pop_back();
		delete tmp;
	}
}

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

Card Deck::deal() {
	//should throw exception in production code if there is no more cards
	return *cards_[index_++];
}

ostream &operator<<(ostream &out, const Deck &deck) {
	for (int i = 0; i < SUIT_COUNT; i++) {
		for (int j = 0; j < RANK_COUNT; j++) {
			out << *deck.cards_[i*RANK_COUNT + j];
			if (j != RANK_COUNT - 1) {
				out << " ";
			} 
		}
		out << endl;
	}
	return out;
}
