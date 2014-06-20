#include "ComputerStrategy.h"
#include "Player.h"
#include <vector>
using namespace std;

void ComputerStrategy::executeStrategy(Player& player,  vector<Card>& table) {
	vector<Card> choices = validStraightPlays(player, table);
	if(!choices.empty()) {
		player.playCard(choices.front());
		table.push_back(choices.front());
	} else {
		player.discard(player.getHand().front());
	}
}