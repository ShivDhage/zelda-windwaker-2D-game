#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Layout.h"
#include "Player.h"
#include "GameEngine.h"

using namespace adventure::domain;

GameEngine game;
Layout& layout = game.getLayout();
Player player(layout);

//layout tests
TEST_CASE("Verify Starting Island") {
	REQUIRE("OutsetIsland" == layout.getStartingIsland());
}

TEST_CASE("Verify Destination Island") {
	REQUIRE("HyruleCastle" == layout.getEndingIsland());
}

TEST_CASE("Verify Number of Islands") {
	REQUIRE(8 == layout.getIslands().size());
}

TEST_CASE("No island with empty string") {
	CHECK_THROWS(layout.getIsland(""));
}

TEST_CASE("Invalid Island Test") {
	CHECK_THROWS(layout.getIsland("Cony"));
}

TEST_CASE("Validate all setup in a given island") {
	string island = "OutsetIsland";
	REQUIRE(3 == layout.getIsland(island).getDirections().size());
	REQUIRE("Northwest" == layout.getIsland(island).findDirection("Northwest").getDirectionName());
	REQUIRE("Northeast" == layout.getIsland(island).findDirection("Northeast").getDirectionName());
	REQUIRE("East" == layout.getIsland(island).findDirection("East").getDirectionName());
	CHECK_THROWS(layout.getIsland(island).findDirection("North"));
	CHECK_THROWS(layout.getIsland(island).findDirection("South"));

	Direction northewest = layout.getIsland(island).findDirection("Northwest");

	REQUIRE("ForsakenFortress" == northewest.getIslandName());
	REQUIRE(!northewest.isEnabled());
	REQUIRE(1 == northewest.getValidKeyNames().size());
	REQUIRE("HeroSword" == northewest.getValidKeyNames()[0]);

	REQUIRE(1 == layout.getIsland(island).getItems().size());
	REQUIRE("HeroSword" == layout.getIsland(island).getItems()[0].getName());

	REQUIRE(0 == layout.getIsland(island).getMonsters().size());

}

//game tests
TEST_CASE("Empty command test") {
	REQUIRE(false == game.isValidCommand("goto foo"));
}

TEST_CASE("Valid command test") {
	REQUIRE(true == game.isValidCommand("go west"));
}

TEST_CASE("Invalid command test") {
	REQUIRE(true == game.isValidCommand("go sideways"));
}

TEST_CASE("Check allpossible directions")
{
	REQUIRE("Northwest[ForsakenFortress], Northeast[DragonRoostIsland], or East[ForestHaven]" == player.printPossibleDirections());
}

TEST_CASE(" Test if player can reach TowerOfTheGods")
{
	vector<string> directions = { "Northwest", "Southeast", "East", "South", "Northwest" };

	for (int i = 0; i < directions.size(); i++) {
		player.moveInADirection(directions[i]);
	}

	REQUIRE("TowerOfTheGods" == player.getCurrentIsland().getName());

	
}

TEST_CASE(" Test if player can reach Destination")
{
	vector<string> directions = { "Northwest", "Southeast", "East", "South", "Northwest","Down","Down"};

	for (int i = 0; i < directions.size(); i++) {
		player.moveInADirection(directions[i]);
	}

	REQUIRE("HyruleCastle" == player.getCurrentIsland().getName());


}