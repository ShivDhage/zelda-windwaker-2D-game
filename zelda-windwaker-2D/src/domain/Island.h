#pragma once
#include <vector>
#include <string>
#include "Direction.h"
#include "Monster.h"
#include "Item.h"
#include "Utils.h"
/*
This class models the Island. At any point player is standing on a given island. This island has a name and description.
It has a items which can be picked up by the player. It has monsters which need tobe fought before exiting this island.
It's connection with other islands isrepresented by Direction object
*/
namespace adventure {
	namespace domain {

		using namespace std;

		class Island {
		private:
			string islandName;
			string islandDescription;
			vector<Direction> directions;
			vector<Item> items;
			vector<Monster> monsters;
		public:

			void setIslandName(string islandName_) {
				islandName = islandName_;
			}

			void setIslandDescription(string islandDescription_) {
				islandDescription = islandDescription_;
			}

			void setDirections(vector<Direction> directions_) {
				directions = directions_;
			}

			void setItems(vector<Item> items_) {
				items = items_;
			}

			void setMonsters(vector<Monster> monsters_) {
				monsters = monsters_;
			}

			vector<Direction>& getDirections() {
				return directions;
			}

			string& getName() {
				return islandName;
			}

			string& getDescription() {
				return  islandDescription;
			}

			vector<Item>& getItems() {
				return items;
			}

			vector<Monster>& getMonsters() {
				return monsters;
			}

			bool containsMonster();
			vector<Item>& pickupItems(string itemName, vector<Item>& items);
			bool fightMonster(Monster& monster, Item& item);
			Monster& findMonster(string monster);
			Direction& findDirection(string directionName);

			/*
			const string& toString() {
				return "[islandName=" + islandName + ",islandDescription=" + islandDescription +  ",directions=[" + Utils::stringifyVector(directions) + "]"+
					islandDescription + ",items=[" + Utils::stringifyVector(items) + "]"+ ",items=[" + Utils::stringifyVector(items) + "]" +"]";
			}
			*/
		};
	}
}
