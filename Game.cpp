#include "Deck.h"
#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "StraightStrategy.h"
#include "HumanStrategy.h"
#include "ComputerStrategy.h"
#include <iostream>
#include <cassert>
using namespace std;

Game::Game() 
	:deck_(Deck::getInstance()) {
	initGame();

}

void Game::initGame() {
	StraightStrategy *strategy;
	char type;

	for(int i=0; i<kNumbeOfPlayers; i++) {
		cout<<"Is player "<<i<<" a human(h) or a computer(c)?"<<endl;
		cin>>type;		

		//I think we should use exception here, but since sample program used assert
		assert(type == 'h' || type == 'H' || type == 'c' || type == 'C');

		if(type == 'h' || type == 'H') {
			strategy = new HumanStrategy;
		} else if (type == 'c' || type == 'C') {
			strategy = new ComputerStrategy;
		}
		if(player_[i])
			delete player_[i];
		player_[i] = new Player(strategy, i);
	}
}

void Game::initRound() {
	deck_.shuffle();
	Card startCard(SPADE, SEVEN);
	for(int i=0; i<kNumbeOfPlayers; i++) {
		for(int j=0; j<SUIT_COUNT*RANK_COUNT/kNumbeOfPlayers; j++) {
			Card card = deck_.deal();
			if(card == startCard)
				firstPlayer_ = i;
			player_[i]->addCard(card);
		}
	}
	cout<<"A new round begins. It's player "<<firstPlayer_+1<<"\'s turn to play."<<endl;
}

void Game::playGame() {
	//try catch just for internal flow control, no need to make new exception class
	try {
		while(!gameOver()) {
		initRound();
		playRound();
		}
	} catch (int) {
	}
}

bool Game::gameOver() {
	for(int i=0; i<kNumbeOfPlayers; i++) {
		if(player_[i]->getScore() >= 80)
			return true;
	}
	return false;
}
void Game::playRound() {
	int numOfCard = player_[0]->getHand().size();
	for(int i=0; i<numOfCard; i++){
		for(int p = 0; p<kNumbeOfPlayers; p++) {
			//calculate who's turn it is
			int currentPlayer = (i+firstPlayer_)%kNumbeOfPlayers;
			
			//try to play according to player strategy
			try {
				player_[currentPlayer]->makeMove(table);

			//if player is Human and makes a something other than a play, discard, or view deck, catch the command exception and deal with it
			} catch(HumanStrategy::InvalidHumanStrategyException err) {
				
				Command command = err.getCommand();
				//if the command is quit, throw exception
				if(command.type == QUIT) {
					throw -1;
				//if rage quit, switch player behavior to computer, and let computer make move
				} else if(command.type == RAGEQUIT) {
					StraightStrategy* strategy = new ComputerStrategy;
					player_[currentPlayer]->setStrategy(strategy);
					player_[currentPlayer]->makeMove(table); 
				}
			}
		}
	}
}

Game::~Game() {
	for(int i=0; i<kNumbeOfPlayers; i++)
		delete player_[i];
}