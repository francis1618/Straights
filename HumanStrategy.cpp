#include <algorithm>
#include <iostream>
#include "HumanStrategy.h"
#include "Player.h"
#include "Command.h"
#include "Card.h"
using namespace std;

void printTable(const vector<Card>&, Suit);

//excpetion class
HumanStrategy::InvalidHumanStrategyException::InvalidHumanStrategyException(Command command) 
	:command_(command){};

Command HumanStrategy::InvalidHumanStrategyException::getCommand() const {
	return command_;
}

void HumanStrategy::executeStrategy(Player& player, vector<Card>& table) {
	//find possible plays
	vector<Card>choices = validStraightPlays(player, table);

	//sort table
	sort(table.begin(), table.end());

	//print table
	cout<<"Cards on the table:"<<endl;
	for(unsigned s=0; s<SUIT_COUNT; s++)
		printTable(table, (Suit)s);

	//print hand
	cout<<"Your hand:";
	const vector<Card>& hand = player.getHand();
	for(unsigned i=0; i<hand.size(); i++)
		cout<<" "<<hand[i];


	//print legal plays
	cout<<"Legal plays:";
	for(unsigned i=0; i<choices.size(); i++)
		cout<<" "<<choices[i];

	Command command;
	while(true) {
		cin>>command;
		if(command.type == PLAY && (find(choices.begin(), choices.end(), command.card)!=choices.end())) {
			if( player.playCard(command.card)) 
				break;
		} else if(command.type == DISCARD) {
			if(player.discard(command.card))
				break;
		} else {
			throw InvalidHumanStrategyException(command);		
		}
	}

}

void printTable(const vector<Card>& table, Suit suit) {
	if(suit == CLUB) cout<<"Clubs:";
	else if(suit == DIAMOND) cout<<"Diamonds:";
	else if(suit == HEART) cout<<"Hearts:";
	else if(suit == SPADE) cout<<"Spades:";

	for(unsigned i = 0; i<table.size(); i++)
	if(table[i].getSuit() == suit)
		cout<<" "<<table[i];
}