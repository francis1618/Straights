#ifndef COMMAND_H
#define COMMAND_H

#include "Card.h"
#include <istream>

//interpreter for user command
struct Command{

	//command types
	enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

	//internal record of command type
	Type type;
	Card card;
	
	//default constructor
	Command() : type(BAD_COMMAND), card(Card::SPADE, Card::ACE) {}
};

//input stream overload
std::istream &operator>>(std::istream &, Command &);

#endif