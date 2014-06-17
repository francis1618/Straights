#include "Player.h"
#include "Command.h"
void HumanStrategy::HumanStrategy(Command &command) 
	: command_(command) {}

void HumanStrategy::executeStrategy(Player& player,  const vector<Card>& validPlays) {

}