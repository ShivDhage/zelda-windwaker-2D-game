#include "Direction.h"
#include <string.h>
#include "Adventure.h"

using namespace std;
using namespace adventure::domain;

bool Direction::canBeEnabled(string itemName) {
	if (itemName.empty()) {
		throw AdventureException("empty item name supplied");
	}

	if (validKeyNames.empty()) {
		return true;
	}

	if (!enabled && !validKeyNames.empty()) {
		for (string currKeyName : validKeyNames) {
			if (Utils::caseInsensitiveStringCompare(currKeyName, itemName)) {
				return true;
			}
		}
	}
	return false;
}

void Direction::enable() {
	enabled = true;
}