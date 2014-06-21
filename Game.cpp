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


int getCardValue(const Card&);

Game::Game() 
	:deck_(Deck::getInstance()) {
	for(int i=0; i<kNumbeOfPlayers; i++)
		player_[i] = NULL;
	initGame();

}

void Game::initGame() {
	StraightStrategy *strategy;
	char type;

	for(int i=0; i<kNumbeOfPlayers; i++) {
		cout<<"Is player "<<i<<" a human(h) or a computer(c)?"<<endl
			<<">";
		cin>>type;		


		//I think we should use exception here, but since sample program used assert
		assert(type == 'h' || type == 'H' || type == 'c' || type == 'C');

		if(type == 'h' || type == 'H') {
			strategy = new HumanStrategy;
		} else if (type == 'c' || type == 'C') {
			strategy = new ComputerStrategy;
		}

		if(NULL == player_[i]) {
			player_[i] = new Player(strategy, i+1);	
		} else {
			player_[i]->setStrategy(strategy);
		}
		player_[i]->setScore(0);
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
			endRound();
		}
	} catch (int) {
	}
}

bool Game::gameOver() {
	for(int i=0; i<kNumbeOfPlayers; i++) {
		if(80<=player_[i]->getScore())
			return true;
	}
	return false;
}
void Game::playRound() {
	int numOfCardsPerPlayer = player_[0]->getHand().size();
	for(int i=0; i<numOfCardsPerPlayer; i++){
		for(int p = 0; p<kNumbeOfPlayers; p++) {
			//calculate who's turn it is
			int currentPlayer = (p+firstPlayer_)%kNumbeOfPlayers;
			
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
					cout<<"Player "<<currentPlayer+1<<" ragequits. A computer will now take over."<<endl;
					StraightStrategy* strategy = new ComputerStrategy;
					player_[currentPlayer]->setStrategy(strategy);
					player_[currentPlayer]->makeMove(table); 
				}
			}
		}
	}
}

void Game::endRound() {
	for(int p=0; p<kNumbeOfPlayers; p++) {
		int roundScore = 0;;

		cout<<"Player "<<p+1<<"\'s discards:";
		vector<Card> discard = player_[p]->getDiscard();
		for(unsigned i=0; i<discard.size(); i++) {
			cout<<" "<<discard[i];
			roundScore += (discard[i].getRank()+1);
		}
		cout<<endl;

		int newScore = player_[p]->getScore() + roundScore;
		cout<<"Player "<<p+1<<"\'s score: "
			<<player_[p]->getScore()<<" + "<<roundScore<<" = "<<newScore<<endl;
		player_[p]->setScore(newScore);
	}
}

Game::~Game() {
	for(int i=0; i<kNumbeOfPlayers; i++)
		delete player_[i];
}