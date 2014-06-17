#include "Player.h"
#include "Deck.h"
#include "Card.h"

class Game {
public:
	Game();
	~Game();
	void initRound();
	void playRound();
	void endGame();
	void finished();
	
private:
	static const int kNumbeOfPlayers = 4;
	Player* players_[kNumbeOfPlayers];
	Deck deck_;

	int firstPlayer;
	bool finished;

};

Game::Game() {
	char type;
	StraightStrategy *strategy;
	for(int i=0; i<kNumbeOfPlayers; i++) {
		cout<<"Is player "<<i<<" a human(h) or a computer(c)?"<<endl;
		cin>>type;
		if(type == "h") {
			strategy = new HumanStrategy;
		} else if (type == "c") {
			strategy = new ComputerStrategy;
		} else {
			//throw exception or while loop
		}
		player_[i] = new Player(strategy);
	}
	initRound());
}

void Game::initRound() {
	deck_.shuffle();
	Card startCard(SPADE, SEVEN);
	for(int i=0; i<kNumbeOfPlayers; i++) {
		for(int j=0; j<SUIT_COUNT*RANK_COUNT/kNumbeOfPlayers; j++) {
			Card card = deck.deal();
			if(card == startCard)
				firstPlayer = i;
			player_[i].addCard(card);
		}
	}
}

