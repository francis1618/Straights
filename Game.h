#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"
#include "Card.h"

class Game {
public:
	Game();
	~Game();
	void initRound();
	//void playRound();
	//void endGame();
	//void finished();
	
private:
	static const int kNumbeOfPlayers = 4;
	Player* player_[kNumbeOfPlayers];
	Deck deck_;

	int firstPlayer;
};
#endif