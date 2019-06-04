#pragma once
#include <vector>
#include <string>
#include "Layout.h"
#include "Player.h"
#include "GameResult.h"
/*
This is a game driver class and defines data and methods needed to play the game
*/
namespace adventure {
	namespace domain {

		using namespace std;

		static const string CMD_GO = "go";
		static const string CMD_NOT_GOOD = "I don't understand ";
		static const string STARTING_MSG = "Your journey begins here";
		static const string SUCCESS_MSG = "Hurray! You made it. Your are on destination Island!!";
		static const vector<string> directions = {"north", "south", "east", "west", "up", "down",
				"northeast", "northwest", "southeast", "southwest" };

		static const string defaultFileName = "WindWaker.json";
		
		static const string CMD_FIGHT_MONSTER = "fight";
		static const string CMD_PICK_ITEM = "pickup";
		static const string CMD_ENABLE_DIRECTION = "use";
		static const vector<string> VALID_CMDS = {CMD_GO, CMD_FIGHT_MONSTER, 
			CMD_PICK_ITEM, CMD_ENABLE_DIRECTION};

		class GameEngine {
		private:
			Layout layout = Layout();
			
			bool gameOver = false;
			bool gameStart = false;
			int totalMoves = 0;
		public:
			GameEngine();
			GameEngine(string layoutFile);
			GameEngine(Layout& layout);
			void play(Player& player);
			void printEnvironmentMessages(Player& player);
			string getGameEngineResponse(Player& player);
			bool isValidCommand(string cmdString);
			Layout& getLayout() {
				return layout;
			}
			bool isGameOver()
			{
				return gameOver;
			}

			GameResult processPlayerInput(Player & player, string& playerCmd);
			void loadLayoutFromFile(string layoutFile)
			{
				
				try {
					auto json_data = Utils::get_json(layoutFile);
					vector<Island> islands;

					layout.setStartingIsland(json_data["startingIsland"]);
					layout.setEndingIsland(json_data["endingIsland"]);
					for (const auto& island : json_data["islands"]) {
						Island newIsland;
						newIsland.setIslandName(island["name"]);
						newIsland.setIslandDescription(island["description"]);
						vector<Direction> directions;
						// check if item["batters"]["batter"] exists
						if (island.find("directions") != island.end()) {
							for (const auto& directionElement : island["directions"]) {
								Direction direction;
								direction.setDirectionName(directionElement["directionName"]);
								direction.setIslandName(directionElement["island"]);
								direction.setEnabled(directionElement["enabled"]);
								direction.setValidKeyNames(directionElement["validKeyNames"]);
								directions.push_back(direction);
							}
						}

						vector<Item> items;
						vector<Monster> monsters;
						if (island.find("items") != island.end()) {
							for (const auto& itemElement : island["items"]) {
								Item item;
								item.setName(itemElement["name"]);
								items.push_back(item);
							}
						}

						if (island.find("monsters") != island.end()) {
							for (const auto& monsterElement : island["monsters"]) {
								Monster monster;
								monster.setMonsterName(monsterElement["name"]);
								monster.setWeakness(monsterElement["weakness"]);
								monsters.push_back(monster);
							}
						}

						newIsland.setDirections(directions);
						newIsland.setItems(items);
						newIsland.setMonsters(monsters);
						islands.push_back(newIsland);
					}
					layout.setIslands(islands);

				}
				catch (exception& parsingException) {
					cout << "Json parsing failed " << parsingException.what() << endl;
				}
				//return layout;

			}
		};
	}
}

