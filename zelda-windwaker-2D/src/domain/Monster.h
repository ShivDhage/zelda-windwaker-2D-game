#pragma once
#include <vector>
#include <string>
#include "Utils.h"

/*
One or more Monsters canbe present ona given island,which canbe fought with the item which is present in  
as monster's weakness which is modelled as a string container
*/
namespace adventure {
	namespace domain {

		using namespace std;

		class Monster {
		private:
			string monsterName;
			vector<string> weakness;
		public:
			void setMonsterName(string monsterName_) {
				monsterName = monsterName_;
			}

			void setWeakness(vector<string> weakness_) {
				weakness = weakness_;
			}

			string& getMonsterName() {
				return monsterName;
			}

			vector<string>& getWeakness() {
				return weakness;
			}

			/*
			const string& toString() {
				return "[monsterName=" + monsterName + ",weakness=[" + Utils::stringifyVector(weakness) + "]]";
			}
			*/
		};
	}
}
