#pragma once
#include <string>

namespace adventure {
	namespace domain {
		using namespace std;
		class GameResult {
		private:
		public:
			static enum  GAME_STATUS { GAME_NOT_STARTED, GAME_CONTINUE, GAME_EXIT, GAME_INVALID_COMMAND, GAME_ERROR,GAME_OVER };
			/*
			GameResult() {
				gameStatus = GAME_NOT_STARTED;
				gameMessage = "Please start the game";
			};
			*/
			GAME_STATUS gameStatus = GAME_NOT_STARTED;
			string gameMessage = "Please start the game";
		};
	}
}