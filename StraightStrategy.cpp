#include "StraightStrategy.h"
#include "Player.h"
#include "Card.h"
using namespace std;


void add(vector<Card>&, const Card&);

vector<Card> StraightStrategy::validStraightPlays(const Player& player, const vector<Card>& table) const {

	const vector<Card>& hand = player.getHand();
	vector<Card> valid;

	for(int i=0; i<table.size(); i++) {
		// get suit rank
		int suit = table[i].getSuit();
		int rank = table[i].getRank();
		
		//check all same rank, different suit
		for(int s = CLUB, s<SUIT_COUNT; s++) {
			//different suit
			if(s!=suit) {
				Card card(suit, rank);
				addIfValid(valid,hand,card);
			}	
		}

		if(ACE <= rank-1) {
			Card card(suit, rank-1);
			addIfValid(valid,hand,card);
		}

		if(rank+1 <= KING) {
			Card card(suit, rank+1);
			addIfValid(valid,hand,card);
		}
	}

	return valid;
}


void addIfValid(vector<Card>& valid, vector<Card>& hand, const Card& card) {
	//check if it's  in player's hand
	if(find(hand.begin(), hand.end(), card) != hand.end()) {
		//add if it's already in valid
		if(find(valid.begin(), valid.end(), valid) == valid.end) {
			valid.push_back(card);
		}
	}
}