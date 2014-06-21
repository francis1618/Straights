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

namespace {
	int getCardValue(const Card&);
}

//Constructor, create new game immediately
Game::Game() 
	:deck_(Deck::getInstance()) {
	for(int i=0; i<kNumbeOfPlayers; i++)
		player_[i] = NULL;
	initGame();

}

//create new game, get each player's behavior, reset their score to 0
void Game::initGame() {
	StraightStrategy *strategy;
	char type;

	for(int i=0; i<kNumbeOfPlayers; i++) {
		//get user to input if player is computer or human
		cout<<"Is player "<<i+1<<" a human(h) or a computer(c)?"<<endl
			<<">";
		cin>>type;		

		//I think we should use exception here, but since sample program used assert
		assert(type == 'h' || type == 'H' || type == 'c' || type == 'C');

		//set strategy according to user input
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
		//reset player's score
		player_[i]->setScore(0);
	}
}


//start new round, shuffle deck, deal cards, find firstPlayer of the round
void Game::initRound() {
	//shuffle deck
	deck_.shuffle();

	//deal cards, find firstPlayer of the round
	Card startCard(Card::SPADE, Card::SEVEN);
	for(int i=0; i<kNumbeOfPlayers; i++) {
		for(int j=0; j<Card::SUIT_COUNT*Card::RANK_COUNT/kNumbeOfPlayers; j++) {
			Card card = deck_.deal();
			if(card == startCard)
				firstPlayer_ = i;
			player_[i]->addCard(card);
		}
	}
	cout<<"A new round begins. It's player "<<firstPlayer_+1<<"\'s turn to play."<<endl;
}

//play the game
void Game::playGame() {
	//try catch just for internal flow control, no need to make new exception class
	//playRound with throw integer if user decide to quit
	try {

		//while the game is not over, continue playing new rounds
		while(!gameOver()) {
			initRound();
			playRound();
			endRound();
		}

		//output ewho who won

		//find the lowest score of players
		int min = player_[0]->getScore(); // what happens if there is no player 0? We cry, that's what
		for(int i=0; i<kNumbeOfPlayers; i++)
			if(player_[i]->getScore()<min)
				min = player_[i]->getScore();

		//output all players with that score
		for(int i=0; i<kNumbeOfPlayers; i++)
			if(player_[i]->getScore() == min)
				cout<<"Player "<<i+1<<" wins!"<<endl;
	} catch (int) {
		//endGame, which is do nothing
	}
}


//check if at least one player is over 80 points
bool Game::gameOver() {
	for(int i=0; i<kNumbeOfPlayers; i++) {
		if(80<=player_[i]->getScore())
			return true;
	}
	return false;
}

//play the round
void Game::playRound() {

	int numOfCardsPerPlayer = player_[0]->getHand().size();
	for(int i=0; i<numOfCardsPerPlayer; i++){
		for(int p = 0; p<kNumbeOfPlayers; p++) {
			//calculate who's turn it is
			int currentPlayer = (p+firstPlayer_)%kNumbeOfPlayers;
			
			//try to play according to player strategy
			try {
				player_[currentPlayer]->makeMove(table_);

			//if player is Human and makes a something other than a play, discard, or view deck, catch the command exception and deal with it
			} catch(HumanStrategy::InvalidHumanStrategyException err) {
				
				Command command = err.getCommand();
				//if the command is quit, throw exception
				if(command.type == Command::QUIT) {
					throw -1;
				//if rage quit, switch player behavior to computer, and let computer make move
				} else if(command.type == Command::RAGEQUIT) {
					cout<<"Player "<<currentPlayer+1<<" ragequits. A computer will now take over."<<endl;
					StraightStrategy* strategy = new ComputerStrategy;
					player_[currentPlayer]->setStrategy(strategy);
					player_[currentPlayer]->makeMove(table_); 
				}
			}
		}
	}
}

//end of round cleanup, update player points, reset their discards
void Game::endRound() {

	for(int p=0; p<kNumbeOfPlayers; p++) {
		int roundScore = 0;;

		//find new discards of each player
		cout<<"Player "<<p+1<<"\'s discards: ";
		vector<Card> discard = player_[p]->getDiscard();
		for(unsigned i=0; i<discard.size(); i++) {
			if( 0 < i )
				cout<<" ";
			cout<<discard[i];
			roundScore += (discard[i].getRank()+1);
		}
		cout<<endl;

		//output each player's old scores and round score and new score
		int newScore = player_[p]->getScore() + roundScore;
		cout<<"Player "<<p+1<<"\'s score: "
			<<player_[p]->getScore()<<" + "<<roundScore<<" = "<<newScore<<endl;
		
		//update player's scores
		player_[p]->resetDiscard();
		player_[p]->setScore(newScore);
	}

	//clear cards on the table
	table_.clear();
}

//release all the player memory allocation
Game::~Game() {
	for(int i=0; i<kNumbeOfPlayers; i++)
		delete player_[i];
}
