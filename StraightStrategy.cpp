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

	for(unsigned i=0; i<table.size(); i++) {
		// get suit rank
		int suit = table[i].getSuit();
		int rank = table[i].getRank();
		
		//check all same rank, different suit
		for(int s = CLUB; s<SUIT_COUNT; s++) {
			//check different suit
			if(s!=suit) {
				Card card((Suit)s, (Rank)rank);
				addIfValid(valid,hand,card);
			}	
		}

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
	return valid;
}


void addIfValid(vector<Card>& valid, const vector<Card>& hand, const Card& card) {
	//if it's not in your hand
	if(find(hand.begin(), hand.end(), card) != hand.end()) {
		//and its not an option you knew about before
		if(find(valid.begin(), valid.end(), card) == valid.end()) {
			//add the option
			valid.push_back(card);
		}
	}
}