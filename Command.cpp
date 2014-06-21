#include "Command.h"
#include <cassert>
#include <sstream>
using namespace std;


// interpret user command, assert if valid command
// keep record of valid command type
istream &operator>>(istream &in, Command &c){
	c.type = Command::BAD_COMMAND;
	
	string cmd;
	in >> cmd;
	
	if (cmd == "play") {
		c.type = Command::PLAY;
		in >> c.card;
	} else if (cmd == "discard") {
		c.type = Command::DISCARD;
		in >> c.card;
	} else if (cmd == "deck") {
		c.type = Command::DECK;
	} else if (cmd == "quit") {
		c.type = Command::QUIT;
	} else if (cmd == "ragequit") {
		c.type = Command::RAGEQUIT;
	}
	
	assert(!in.fail() && c.type != Command::BAD_COMMAND);
	
	return in;
}
