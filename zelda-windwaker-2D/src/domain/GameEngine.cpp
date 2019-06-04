#include "GameEngine.h"
#include "Layout.h"
#include <string.h>
#include "Utils.h"
#include "json.hpp"
#include "Adventure.h"
#include "GameResult.h"

using namespace std;
using namespace adventure::domain;


GameEngine::GameEngine(string layoutFileName)
{
	loadLayoutFromFile(defaultFileName);
}

GameEngine::GameEngine()
{
	loadLayoutFromFile(defaultFileName);


}
GameEngine::GameEngine(Layout& layout_) :  layout(layout_) {}



GameResult GameEngine::processPlayerInput(Player & player, string& playerCmd)
{
	//cout << "processPlayerInput() called with cmd=" << playerCmd << endl;
	string gameResultMessage = "";
	GameResult gameResult;

	if (player.getCurrentIsland().getName().compare((layout.getEndingIsland())) == 0) {
		gameResult.gameStatus = GameResult::GAME_OVER;
		gameResult.gameMessage = SUCCESS_MSG;
		gameOver = true;
		return gameResult;
	}

		// Checks if the player wants to leave the game
		if ((playerCmd.compare("quit") == 0) || (playerCmd.compare("exit") == 0)) {
			gameResult.gameStatus = GameResult::GAME_EXIT;
			gameResult.gameMessage = "Exiting the game!!";
			return gameResult;
		}

		// Checks if the player command is a valid command
		else if (!isValidCommand(playerCmd)) {
			gameResult.gameStatus = GameResult::GAME_INVALID_COMMAND;
			gameResult.gameMessage = (CMD_NOT_GOOD + "'" + playerCmd + "'");
			return gameResult;
		}

		// Splits the string into a string array for easier traversal
		vector<string> cmdStrings = Utils::split(playerCmd, " ");

		if (cmdStrings[0].compare(CMD_PICK_ITEM) == 0) {
			//totalMoves++;
			try {
				vector<Item>& pickedUpItems = player.getItems();
				vector<Item>& item = player.getCurrentIsland().pickupItems(cmdStrings[1], pickedUpItems);
				gameResult.gameStatus = GameResult::GAME_CONTINUE;
				gameResult.gameMessage = (cmdStrings[1] + " was picked up");
			}
			catch (AdventureException& ae) {
				gameResult.gameStatus = GameResult::GAME_ERROR;
				gameResult.gameMessage = "Error during picking up items: " + string(ae.what());

			}
		}
		else if (cmdStrings[0].compare(CMD_FIGHT_MONSTER) == 0) {

			try {
				Monster monster = player.getCurrentIsland().findMonster(cmdStrings[1]);

				vector<Item> items = player.getItems();
				bool incorrectItem = true;
				for (Item item : items) {
					if (player.getCurrentIsland().fightMonster(monster, item)) {
						incorrectItem = false;
						break;
					}
				}

				if (incorrectItem) {
					gameResult.gameMessage = " YOU LOST...GAME OVER...JK...RESPAWNED";
				}
				else {
					gameResult.gameMessage = "You have beaten " + cmdStrings[1] + " successfully";
				}
			}
			catch (AdventureException& ae) {
				gameResult.gameMessage = "Error during fighting with monster: " + string(ae.what());
			}

			gameResult.gameStatus = GameResult::GAME_CONTINUE;
		}
		else if (cmdStrings[0].compare(CMD_ENABLE_DIRECTION) == 0) {
			//totalMoves++;
			string itemName = cmdStrings[1];
			string directionName = cmdStrings[3];

			std::transform(directionName.begin(), directionName.end(), directionName.begin(), ::tolower);

			//check if player has the item
			if (!player.hasItem(itemName)) {
				gameResult.gameMessage = itemName + " is not present with player, please pickup then proceed";
				
			}
			// Checks if the given direction is a valid direction
			if (std::find(directions.begin(), directions.end(), directionName) == directions.end()) {
				gameResult.gameMessage = CMD_NOT_GOOD + directionName;
				
			}

			try {
				Direction& direction = player.getCurrentIsland().findDirection(directionName);
				if (direction.isEnabled()) {
					gameResult.gameMessage = cmdStrings[3] + " is already enabled";
					
				}
				else if (!direction.canBeEnabled(itemName)) {
					gameResult.gameMessage = cmdStrings[3] + " could not be enabled by " + itemName;
					
				}
				else {
					direction.enable();
					//player.removeItem(itemName);
					gameResult.gameMessage = cmdStrings[3] + " direction was enabled successfully";
					
				}
			}
			catch (AdventureException& ae) {
				gameResult.gameMessage = "Error during enabling direction " +string(ae.what());
				
			}
			gameResult.gameStatus = GameResult::GAME_CONTINUE;
		}
		// Checks if the first word of the command is go and starts to move the player
		if (cmdStrings[0].compare(CMD_GO) == 0) {

			if (player.getCurrentIsland().containsMonster()) {
				string monsterName = player.getCurrentIsland().getMonsters()[0].getMonsterName();
				gameResult.gameMessage = "This island contains the ferocious monster " + monsterName + ", " +
					"you must defeat him if you wish to leave";
				
			}
			string playerDirection = cmdStrings[1];

			vector<Direction> directions = player.getCurrentIsland().getDirections();
			bool allowMoving = false;

			for (Direction& direction : directions) {
				if (Utils::caseInsensitiveStringCompare(direction.getDirectionName(), playerDirection)) {
					if (direction.isEnabled()) {
						allowMoving = true;
					}
					else {
						gameResult.gameMessage = playerDirection + " is disabled, " +
							"please obtain/use " + direction.getValidKeyNames()[0] + " to enable this direction";
					}
					break;
				}
			}

			if (allowMoving) {
				//cout << " player moving in direction : " << playerDirection << endl;
				player.moveInADirection(playerDirection);
				gameResult.gameMessage = "You have moved in direction "+ playerDirection +" successfully!";
				
			}
			else if (!allowMoving) {
				gameResult.gameMessage = "You cannot go " + playerDirection + "!";
				
			}
			gameResult.gameStatus = GameResult::GAME_CONTINUE;
		}

		//finally check if player reached final destination
		if (player.getCurrentIsland().getName().compare((layout.getEndingIsland())) == 0) {
			gameResult.gameStatus = GameResult::GAME_OVER;
			gameResult.gameMessage = SUCCESS_MSG;
			gameOver = true;
		}

		return gameResult;

}
void GameEngine::play(Player& player) {

	string playerCmd = "";

	while (!gameOver) {
		try {
			totalMoves++;
			printEnvironmentMessages(player);
			if (gameOver)
			{
				continue;
			}
			// Takes in a player command and makes it lowercase
			getline(cin, playerCmd);
			transform(playerCmd.begin(), playerCmd.end(), playerCmd.begin(), ::tolower);
			GameResult gameResult = processPlayerInput(player, playerCmd);
			cout << gameResult.gameMessage<<endl;
			if (gameResult.gameStatus == GameResult::GAME_EXIT || 
				gameResult.gameStatus == GameResult::GAME_OVER )
			{
				break;
			}
			else
			{
				continue;
			}
			// Catches a bad command exception
		} catch (exception& badCommandException) {
			std::cout << (CMD_NOT_GOOD + "'" + playerCmd + "'") << endl;
			std::cout << (badCommandException.what()) << endl;
		}
	} // end of outer loop
}

string GameEngine::getGameEngineResponse(Player& player) {


	string gameEngineResponse;

	gameEngineResponse += player.getCurrentIsland().getDescription() + "\n";



	if (!gameStart)
	{
		gameEngineResponse += STARTING_MSG + "\n";
		totalMoves = 0;
		gameStart = true;
		gameOver = false;
	}
	gameEngineResponse += ("Your Items: " + player.printItemsInPossession()) + "\n";
	gameEngineResponse += ("Items to pickup: " + player.printPossibleIslandItems()) + "\n";
	gameEngineResponse += ("Monsters to fight: " + player.printMonstersOnIsland()) + "\n";
	gameEngineResponse += ("From here, you can go: " + player.printPossibleDirections());
	
	return gameEngineResponse;
}
void GameEngine::printEnvironmentMessages(Player& player) {
	cout << getGameEngineResponse(player) << endl;
}

bool GameEngine::isValidCommand(string cmdString) {
	// Checks if the player command is null or empty
	if (cmdString.empty()) {
		return false;
	}

	// Splits the string into a string array for easier traversal
	vector<string> cmdStringArray = Utils::split(cmdString, " ");
	string command = cmdStringArray[0];
	if (std::find(VALID_CMDS.begin(), VALID_CMDS.end(), cmdStringArray[0]) == VALID_CMDS.end()) {
		return false;
	}
	if (Utils::caseInsensitiveStringCompare(command, CMD_ENABLE_DIRECTION)) {
		if (cmdStringArray.size() == 4) {
			return true;
		} else {
			return false;
		}
	} else {
		if (cmdStringArray.size() == 2) {
			return true;
		} else {
			return false;
		}
	}
}


