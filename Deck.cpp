#include "Deck.h"
#include <iostream>
#include <string>

using namespace std;

bool Deck::isEmpty() {
	return !(index_ < CARD_COUNT);
}

Deck::Deck() : index_(0)
{
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
	if (!isEmpty()) {
		return *cards_[index_++];
	}
	// *** IMPLEMENT LATER *** //
	// else {
	// 	throw DealingFromEmptyDeckException();
	// } 
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
