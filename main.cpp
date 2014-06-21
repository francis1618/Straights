#include "Game.h"

int main(int argc, char* argv[]) {
	
	//seed given param, default to 0
	if(2<=argc)
		srand48(atoi(argv[1]));
	else
		srand48(0);

	//create and play new game
	Game game;
	game.playGame();
}
