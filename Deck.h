#include "Card.h"
#include <vector>

class Deck {
	friend std::ostream &operator<<(std::ostream &, const Deck &);

	public:
		Deck();
		~Deck();
		void shuffle();
		Card deal();
		bool isEmpty();
	private: 
		std::vector<Card*> cards_;
		int index_;
		const static int CARD_COUNT = SUIT_COUNT * RANK_COUNT;
};

std::ostream &operator<<(std::ostream &, const Deck &);