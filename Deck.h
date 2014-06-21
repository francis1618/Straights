#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>


// The fact that I made this into a singleton is literally for hacks(globalization)
// I explained why I made this into a singleton in HumanStrategy.cpp. This
// could be avoided if I use multithread, or a global variable, but singleton is 
// A LOT better than global variable so I settled on it


//Singleton deck object
class Deck {
friend std::ostream &operator<<(std::ostream &, const Deck &);

//single get instance, reference because you should NEVER be able to destroy it
public:
	static Deck& getInstance();
private:
	//pirvate constructor because this is a singleton
	Deck();
	//prohibited cus this is a singleton, these are not implemented
    Deck(Deck const& copy);            
    Deck& operator=(Deck const& copy);


public:
	~Deck();
	void shuffle();
	Card deal();
	bool isEmpty() const;

private: 
	std::vector<Card*> cards_;
	int index_;
	const static int CARD_COUNT = SUIT_COUNT * RANK_COUNT;
};

std::ostream &operator<<(std::ostream &, const Deck &);

#endif