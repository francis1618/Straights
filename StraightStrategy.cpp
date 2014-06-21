#include <vector>
#include <algorithm>
#include "StraightStrategy.h"
#include "Player.h"
#include "Card.h"
using namespace std;


void addIfValid(vector<Card>&, const vector<Card>&, const Card&);

vector<Card> StraightStrategy::validStraightPlays(const Player& player, const vector<Card>& table) {

	vector<Card> valid;
	const vector<Card>& hand = player.getHand();



	//check 7 of spades, if so, return 7 of spades
	Card sevenSpade(SPADE, SEVEN);
	if(find(hand.begin(), hand.end(), sevenSpade) != hand.end()) {
	
		valid.push_back(sevenSpade);

	} else {

		//check all suit for SEVEN
		for(int s = CLUB; s<SUIT_COUNT; s++) {
			Card card((Suit)s, SEVEN);
			addIfValid(valid,hand,card);
		}	

		//check all different rank, same suit
		for(unsigned i=0; i<table.size(); i++) {
			// get suit rank
			int suit = table[i].getSuit();
			int rank = table[i].getRank();
			

			//check one card below with same suit
			if(ACE <= rank-1) {
				Card card((Suit)suit, (Rank)(rank-1));
				addIfValid(valid,hand,card);
			}
			//check one card above with same suit
			if(rank+1 <= KING) {
				Card card((Suit)suit, (Rank)(rank+1));
				addIfValid(valid,hand,card);
			}


		}
	}
	return valid;
}

// since there is a virtual function, there should be a virtual destructor
StraightStrategy::~StraightStrategy() {
	// just for children to inherit
}

void addIfValid(vector<Card>& valid, const vector<Card>& hand, const Card& card) {
	//if it's in your hand
	if(find(hand.begin(), hand.end(), card) != hand.end()) {
		//and its not an option you knew about before
		if(find(valid.begin(), valid.end(), card) == valid.end()) {
			//add the option
			valid.push_back(card);
		}
	}
}