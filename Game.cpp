#include "Deck.h"
#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "StraightStrategy.h"
#include "HumanStrategy.h"
#include "ComputerStrategy.h"
#include <iostream>
using namespace std;

Game::Game() {
	char type;
	StraightStrategy *strategy;
	for(int i=0; i<kNumbeOfPlayers; i++) {
		cout<<"Is player "<<i<<" a human(h) or a computer(c)?"<<endl;
		cin>>type;
		if(type == 'h' || type == 'H') {
			strategy = new HumanStrategy;
		} else if (type == 'c' || type == 'C') {
			strategy = new ComputerStrategy;
		} /*else {
		}*/
		player_[i] = new Player(strategy, i);
	}
	//initRound());
}

void Game::initRound() {
	deck_.shuffle();
	Card startCard(SPADE, SEVEN);
	for(int i=0; i<kNumbeOfPlayers; i++) {
		for(int j=0; j<SUIT_COUNT*RANK_COUNT/kNumbeOfPlayers; j++) {
			Card card = deck_.deal();
			if(card == startCard)
				firstPlayer = i;
			player_[i]->addCard(card);
		}
	}
	cout<<"A new round begins. It's player "<<firstPlayer+1<<"\'s turn to play."<<endl;
}
