#include "Player.h"
#include <string.h>
#include "Adventure.h"

using namespace std;
using namespace adventure::domain;

//Player::Player() {}
Player::Player(Layout& layout_) : layout(layout_), currentIsland(layout_.findIsland(layout_.getStartingIsland())) {}
void Player::setInitialIsland() {
	currentIsland = layout.findIsland(layout.getStartingIsland());

}

bool Player::moveInADirection(string directionName) {

	//cout << "in Player::moveInADirection() for " << directionName << endl;
	if (directionName.empty()) {
		throw AdventureException("empty direction name supplied");
	}

	vector<Direction> possibleDirections = currentIsland.getDirections();
	for (Direction& direction : possibleDirections) {
		if (Utils::caseInsensitiveStringCompare(directionName, direction.getDirectionName())) {
			currentIsland = layout.findIsland(direction.getIslandName());
			return true;
		}
	}
	return false;
}

string Player::printPossibleDirections() {
	string directions = "";
	for (int i = 0; i < currentIsland.getDirections().size(); i++) {
		string prefix = "";

		if (i == 0) {
			prefix = "";
		} else if (i == currentIsland.getDirections().size() - 1) {
			prefix = ", or ";
		} else {
			prefix = ", ";
		}

		directions += prefix + (currentIsland.getDirections()[i].getDirectionName() +
			"[" + currentIsland.getDirections()[i].getIslandName() + "]");
	}
	return directions;
}

string Player::printPossibleIslandItems() {
	string items = "";
	for (int i = 0; i < currentIsland.getItems().size(); i++) {
		string prefix = "";

		if (i == 0) {
			prefix = "";
		} else {
			prefix = ", ";
		}

		items += prefix + currentIsland.getItems()[i].getName();
	}
	return items;
}

string Player::printItemsInPossession() {
	string itemsList = "";
	for (int i = 0; i < items.size(); i++) {
		string prefix = "";

		if (i == 0) {
			prefix = "";
		} else {
			prefix = ", ";
		}

		itemsList += prefix + items[i].getName();
	}
	return itemsList;
}

string Player::printMonstersOnIsland() {
	string monsterList = "";
	for (int i = 0; i < currentIsland.getMonsters().size(); i++) {
		string prefix = "";

		if (i == 0) {
			prefix = "";
		} else {
			prefix = ", ";
		}

		monsterList += prefix + currentIsland.getMonsters()[i].getMonsterName();
	}
	return monsterList;
}

vector<Item>& Player::getItems() {
	return items;
}

bool Player::hasItem(string itemName) {
	for (Item item : items) {
		if (Utils::caseInsensitiveStringCompare(itemName, item.getName())) {
			return true;
		}
	}
	return false;
}

