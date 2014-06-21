#include <vector>
#include <algorithm>
#include "StraightStrategy.h"
#include "Player.h"
#include "Card.h"
using namespace std;


void addIfAdjacentExist(vector<Card>&, const Card&, const vector<Card>&, const Card&);

vector<Card> StraightStrategy::validStraightPlays(const Player& player, const vector<Card>& table) {
	vector<Card> valid;
	vector<Card> hand = player.getHand();

	//check 7 of spades, if so, return 7 of spades
	Card sevenSpade(SPADE, SEVEN);
	if(find(hand.begin(), hand.end(), sevenSpade) != hand.end()) {
		valid.push_back(sevenSpade);
	} else {

		for(unsigned i=0; i<hand.size(); i++) {
			int suit = hand[i].getSuit();
			int rank = hand[i].getRank();
			
			if( rank == SEVEN ) {
				valid.push_back(hand[i]);
			} else {
				if(ACE <= rank-1)
					addIfAdjacentExist(valid, hand[i], table, Card((Suit)suit, (Rank)(rank-1)));
				if(rank+1 <= KING)
					addIfAdjacentExist(valid, hand[i], table, Card((Suit)suit, (Rank)(rank+1)));

			}
		}
	}
	return valid;
}

// since there is a virtual function, there should be a virtual destructor
StraightStrategy::~StraightStrategy() {
	// just for children to inherit
}

void addIfAdjacentExist(vector<Card>& valid, const Card& card, const vector<Card>& table, const Card& adjacent) {
	//if adjacent exist
	if(find(table.begin(), table.end(), adjacent) != table.end()) {
		//and card is not an option you knew about before
		if(find(valid.begin(), valid.end(), card) == valid.end()) {
			//add the option
			valid.push_back(card);
		}
	}
}