#include "Island.h"
#include <string.h>
#include "Adventure.h"

using namespace std;
using namespace adventure::domain;

bool Island::containsMonster() {
	return (monsters.size() > 0);
}

vector<Item>& Island::pickupItems(string itemName,vector<Item>& pickedUpItems) {
	if (itemName.empty()) { 
		throw AdventureException("empty item name supplied");
	}

	//vector<Item> pickedupItems;
	if (items.size() == 0) {
		throw AdventureException("No items on island");
	}

	if (Utils::caseInsensitiveStringCompare(itemName,"all")) {
		for (Item curItem : items) {
			pickedUpItems.push_back(move(curItem));
		}
		items.clear();
		return pickedUpItems;
	} else {
		int removedIndex = -1;
		for (int i = 0; i < items.size(); i++) {
			if (Utils::caseInsensitiveStringCompare(itemName, items[i].getName())) {
				pickedUpItems.push_back(items[i]);
				removedIndex = i;
				break;
			}
		}

		if (removedIndex > -1) {
			items.erase(items.begin() + removedIndex);
			return pickedUpItems;
		}
	}
	throw AdventureException(itemName + " not found");
}

bool Island::fightMonster(Monster& monster, Item& item) {
	/*
	for (int i = 0; i < monster.getWeakness().size(); i++) {
		string currWeakness = monster.getWeakness()[i];
	//for (string currWeakness : monster.getWeakness()) {
		if (Utils::caseInsensitiveStringCompare(currWeakness, item.getName())) {
			for (int j = 0; j < monsters.size(); j++) {
				if (Utils::caseInsensitiveStringCompare(monsters[j].getMonsterName(), monster.getMonsterName())) {
					monsters.erase(monsters.begin() + j);
					return true;
				}
			}
		}
	}
	*/
	vector<string> weaknesses = monster.getWeakness();
	for (auto i = 0; i < weaknesses.size(); i++) {
		if (Utils::caseInsensitiveStringCompare(weaknesses[i], item.getName())) {
			monsters.erase(monsters.begin());
			return true;
		}
	}
	return false;
}

Monster& Island::findMonster(string monster) {
	if (getMonsters().empty()) {
		throw AdventureException(this->getName() + " does not have a monster currently");
	}
	if (monster.empty()) {
		throw AdventureException("empty monster name supplied");
	}

	for (Monster& currMonster : monsters) {
		if (Utils::caseInsensitiveStringCompare(monster, currMonster.getMonsterName())) {
			return currMonster;
		}
	}
	throw AdventureException(monster + " not found on "+ this->getName());
}

Direction& Island::findDirection(string directionName) {
	if (directions.empty()) {
		throw AdventureException(this->getName() + " island is not surrounded by any other islands");
	}

	for (Direction& currDirection : directions) {
		if (Utils::caseInsensitiveStringCompare(directionName, currDirection.getDirectionName())) {
			return currDirection;
		}
	}
	throw AdventureException("There is no island in the direction "+ directionName +" from " + this->getName());
}