#pragma once
#include <vector>
#include <string>
#include "Island.h"
#include "Utils.h"
#include <map>
#include "Adventure.h"

/*
This class models the whole machinery used in the game. It holds starting and ending island names.It has knowledge of
all the islands.
*/
namespace adventure {
	namespace domain {

		using namespace std;

		class Layout {

		private :
			string startingIsland;
			string endingIsland;
			vector<Island> islands;
			map<string, Island> islandMap;
		public :
			void setStartingIsland(string startingIsland_) {

				startingIsland = startingIsland_;
			}

			void setEndingIsland(string endingIsland_) {
				endingIsland = endingIsland_;
			}

			void setIslands(vector<Island> islands_) {
				islands = islands_;

				for (Island curIsland : islands_) {
					islandMap[curIsland.getName()] = curIsland;
				}
			}

			Island& getIsland(string islandName) {
				if (islandName.empty()) {
					throw AdventureException("empty islandName passed, can't locate the Island");
				}

				if (islandMap.find(islandName) == islandMap.end()) {
					throw AdventureException(islandName+" is not a valid Island");
				}

				return islandMap[islandName];
			}

			string& getStartingIsland() {
				return startingIsland;
			}

			string& getEndingIsland() {
				return endingIsland;
			}

			vector<Island>& getIslands() {
				return islands;
			}

			Island& findIsland(string island);

			/*
			const string& toString() {

				return "[startingIsland=" + startingIsland + ",endingIsland=" + endingIsland + ",islands=[" + Utils::stringifyVector(islands) + "]]";
			}
			*/
		};
	}
}
