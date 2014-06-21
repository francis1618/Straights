#include "HumanStrategy.h"
#include "Player.h"
#include "Command.h"
#include "Card.h"
#include "Deck.h"
#include <algorithm>
#include <iostream>
using namespace std;

void printCardsOfSuit(const vector<Card>&, Suit);

//excpetion class
HumanStrategy::InvalidHumanStrategyException::InvalidHumanStrategyException(Command command) 
	:command_(command){};

Command HumanStrategy::InvalidHumanStrategyException::getCommand() const {
	return command_;
}

void HumanStrategy::executeStrategy(Player& player, vector<Card>& table) {
	//find possible plays
	vector<Card>choices = validStraightPlays(player, table);

	//sort and print table
	sort(table.begin(), table.end());
	cout<<"Cards on the table:"<<endl;
	for(unsigned s=0; s<SUIT_COUNT; s++)
		printCardsOfSuit(table, (Suit)s);

	//print hand
	cout<<"Your hand:";
	const vector<Card>& hand = player.getHand();
	for(unsigned i=0; i<hand.size(); i++)
		cout<<" "<<hand[i];
	cout<<endl;

	//print legal plays
	cout<<"Legal plays:";
	for(unsigned i=0; i<choices.size(); i++)
		cout<<" "<<choices[i];
	cout<<endl;

	Command command;
	while(true) {
		cout<<">";
		cin>>command;
		if(command.type == DECK) {
			cout<<Deck::getInstance();
		} else if(command.type == PLAY) {
			if(find(choices.begin(), choices.end(), command.card)==choices.end()) {
				cout<<"This is not a legal play."<<endl;
			} else if( player.playCard(command.card)) {
				table.push_back(command.card);
				break;
			}

		} else if(command.type == DISCARD) {
			if( !choices.empty() )
				cout<<"You have a legal play. You may not discard."<<endl;
			else if(player.discard(command.card))
				break;
		} else {
			throw InvalidHumanStrategyException(command);		
		}
	}

}

void printCardsOfSuit(const vector<Card>& table, Suit suit) {
	if(suit == CLUB) cout<<"Clubs:";
	else if(suit == DIAMOND) cout<<"Diamonds:";
	else if(suit == HEART) cout<<"Hearts:";
	else if(suit == SPADE) cout<<"Spades:";

	for(unsigned i = 0; i<table.size(); i++) {
		if(table[i].getSuit() == suit)
			cout<<" "<<(table[i].getRank()+1);
	}
	cout<<endl;
}