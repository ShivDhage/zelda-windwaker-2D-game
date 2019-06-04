#pragma once
#include <vector>
#include <string>
#include "Island.h"
#include "Item.h"
#include "Player.h"
#include "Layout.h"
/*
At any point in time, Player is present on a given island. Possiblity of Player's movement in a gievn direction 
is modelled in this class. Also collection of items arealso maintained here
*/
namespace adventure {
	namespace domain {

		using namespace std;

		class Player {
		private:
			Island& currentIsland;
			Layout& layout;
			vector<Item> items;
		public: 
			//Player();
			Player(Layout& layout_);

			Island& getCurrentIsland() {
				return currentIsland;
			}

			void setCurrentIsland(Island& islandInput) {
				currentIsland = islandInput;
			}

			void setInitialIsland();
			bool moveInADirection(string directionName);
			string printPossibleDirections();
			string printPossibleIslandItems();
			string printItemsInPossession();
			string printMonstersOnIsland();
			void addItems(vector<Item> items);
			vector<Item>& getItems();
			bool hasItem(string itemName);
			string toString();

			void setItems(vector<Item> items_) {
				items = items_;
			}

			void setLayout(Layout& layout_) {
				layout = layout_;
				setCurrentIsland(layout.findIsland(layout.getStartingIsland()));

			}

			//void removeItem(string itemName);
		};
	}
}
