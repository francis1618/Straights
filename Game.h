#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include <vector>


class Game {
public:
	Game();
	~Game();
	
	void initGame();
	void playGame();

private:
	void initRound();
	void playRound();
	bool gameOver();
	
private:
	static const int kNumbeOfPlayers = 4;
	Player* player_[kNumbeOfPlayers];
	std::vector<Card> table;
	Deck& deck_;

	int firstPlayer_;
};
#endif