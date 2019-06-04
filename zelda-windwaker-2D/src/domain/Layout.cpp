#include "Layout.h"
#include <string.h>
#include "Adventure.h"

using namespace std;
using namespace adventure::domain;

Island& Layout::findIsland(string island) {
	string islandNotFoundMessage = "Invalid Island : " + island;
	if (island.empty()) {
		throw AdventureException(islandNotFoundMessage);
	}

	for (Island& validIsland : islands) {
		if (Utils::caseInsensitiveStringCompare(island, validIsland.getName())) {
			return validIsland;
		}
	}
	throw AdventureException(islandNotFoundMessage);
}