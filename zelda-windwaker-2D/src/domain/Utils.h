#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include <fstream>
#include <iostream> 
#include <iterator>
#include <sstream>


/*
This class have all static utility methods.
*/



		using namespace std;
//		using namespace adventure::domain;

		class Utils {
		public:
			/* get absolute path of the file */
			static string getFullPath(const string& fileName) {
				string fullPath = __FILE__;
				fullPath = fullPath.substr(0, 1 + fullPath.find_last_of('\\'));
				fullPath = fullPath + fileName;

				return fullPath;
			}

			/* convert given string to lower case*/
			static void convert_tolower(const std::string& string1, std::string& string2) {
				for (short i = 0; i < string1.size(); ++i) {
					string2 += tolower(string1[i]);
				}
			}

			/* split the supplied string into vector<string> using the given delimiter*/
			static vector<string> split(string s, string delimiter) {
				size_t pos_start = 0, pos_end, delim_len = delimiter.length();
				string token;
				vector<string> res;

				while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
					token = s.substr(pos_start, pos_end - pos_start);
					pos_start = pos_end + delim_len;
					res.push_back(token);
				}

				res.push_back(s.substr(pos_start));
				return res;
			}

			/* compare two string in case insensitive manner */
			static bool caseInsensitiveStringCompare(const string& str1, const string& str2) {
				string str1Cpy;
				string str2Cpy;

				convert_tolower(str1, str1Cpy);
				convert_tolower(str2, str2Cpy);

				return (str1Cpy == str2Cpy);
			}

			/* Using nlohmann's json parser to convert given json file into various application objects*/
			static nlohmann::json get_json(const string& json_file_path) {
				ifstream json_file(getFullPath(json_file_path));

				//error when loading Window data.
				if (!json_file.is_open()) {
					return nullptr;
				}

				nlohmann::json json_data = nlohmann::json::parse(json_file);
				json_file.close();
				return json_data;
			}
		};
