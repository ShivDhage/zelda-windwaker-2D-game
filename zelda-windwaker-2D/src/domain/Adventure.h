#pragma once
#include<string>

/* User defined exception ,which can be used to indicate error condition in various situations. It allows 
	to capture an error message,which can be used to inform why and how the exception occurred.
*/
namespace adventure {
	namespace domain {

		using namespace std;

		struct AdventureException : public exception {
			string message;
			AdventureException(string message_) : message(message_) {}
			~AdventureException() throw () {} // Updated
			const char* what() const throw() { return message.c_str(); }
		};
	}
}