#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>


// The teacher told us she didn't want us to be able to differentiate between a computer player and a human player by 
// checking something like a bit or a function return value. Instead she want they to simply have a play() function that
// Game class can call. This raised a problem, because Player has to internally handle user input and deal with it if it can.
// In the case that user asks to display deck, Player can't transfer control back into Game, because if it does, then after
// Game print the deck, and Game calls player's play function again, player won't know not to print the information(about possible
// moves, cards situation). Therefor player has to print the deck itself. So I made Deck into a singleton for globalization.


//Singleton deck object
class Deck {

//output stream overload
friend std::ostream &operator<<(std::ostream &, const Deck &);

public:
	// Only way to access singleton, I used a reference because you should NEVER be able to destroy
	// the instance which you could if I pass you back a pointer
	static Deck& getInstance();

private:
	//pirvate constructor because this is a singleton
	Deck();
	//prohibited because this is a singleton, these are not implemented
    Deck(Deck const& copy);            
    Deck& operator=(Deck const& copy);


public:
	~Deck();			//destructor
	void shuffle();		//shuffle according to given algorithm
	Card deal();		//card dealer
	bool isEmpty() const;	//query if empty

private: 

	int index_;												//index of next card to deal
	const static int CARD_COUNT = Card::SUIT_COUNT * Card::RANK_COUNT;	//number of cards in the deck
	std::vector<Card*> cards_;								//vector of cards in the deck
};

//ouput stream overload
std::ostream &operator<<(std::ostream &, const Deck &);

#endif