#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include <vector>

// Straight GAme
class Game {
public:
	//consturctor, destructor
	Game();
	~Game();
	
	//setup new game, play new game
	void initGame();
	void playGame();


private:
	//internal helper function
	void initRound();	//new round setup
	void playRound();	//play round
	void endRound();	//round cleanup
	bool gameOver();	//check if game has ended
	
private:
	static const int kNumbeOfPlayers = 4;	//number of players
	Player* player_[kNumbeOfPlayers];		//players
	std::vector<Card> table_;				//cards on the table
	Deck& deck_;							//deck to distribute from

	int firstPlayer_;						//first player of the round
};
#endif