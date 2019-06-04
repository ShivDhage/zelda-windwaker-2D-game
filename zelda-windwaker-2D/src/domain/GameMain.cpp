#include "GameEngine.h"
#include "Player.h"

using namespace adventure::domain;

int main1() {
	
	GameEngine gm("WindWaker.json");
	Player player(gm.getLayout());
	gm.play(player);
	
	return 0;
}