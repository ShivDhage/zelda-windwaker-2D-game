#pragma once
//#include <Printable.h>

#include <vector>
#include <string>
#include "Utils.h"
#include <stdio.h> 
#include <sstream>
/*
Item is used in two scenarios : enabling adirection, fighting with a monster.
As Player goes from island to island, he/she picks up the items from island to be used during the journey
*/
namespace adventure {
	namespace domain {

		using namespace std;
		
		class Item {
		private:
			string name;
		public:
			void setName(string name_) {
				name = name_;
			}

			string& getName() {
				return name;
			}
			
			/*
			const string& toString() {
				return "[name=" + name + "]";
			}
			*/
		};
	}
}
