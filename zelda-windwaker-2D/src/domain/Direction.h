#pragma once
#include <vector>
#include <string>
#include "Utils.h"

/*
	Encapsulates the direction and associated data and behavior. It holds the name of the island present in this direction.
	Direction may be disabled. If it's disabled then it can be enabled by any item present in it's container of valid key names
*/
namespace adventure {
	namespace domain {

		using namespace std;

		class Direction {
		private:
			string directionName;
			string islandName;
			bool enabled;
			vector<string> validKeyNames;
		public:
			void setDirectionName(string directionName_) {
				directionName = directionName_;
			}

			void setIslandName(string islandName_) {
				islandName = islandName_;
			}

			void setEnabled(bool enabled_) {
				enabled = enabled_;
			}

			vector<string>& getValidKeyNames() {
				return validKeyNames;
			}

			void setValidKeyNames(vector<string> validKeyNames_) {
				validKeyNames = validKeyNames_;
			}

			string& getDirectionName() {
				return directionName;
			}

			string& getIslandName() {
				return islandName;
			}

			bool& isEnabled() {
				return enabled;
			}

			void enable();
			bool canBeEnabled(string itemName);

			/*
			const string& toString() {
				return "[islandName=" + islandName + ",directionName="+ directionName +", enabled="+ (enabled ? "true" : "false") +",validKeyNames=[" + Utils::stringifyVector(validKeyNames) + "]]";
			}
			*/
		};
	}
}
