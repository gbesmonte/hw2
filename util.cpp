#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	set<string> s;

	if (rawWords.size() <= 1){
		return s;
	}

	int i = 0;
	while (rawWords.length() > 0){
		if (i == rawWords.length()){
			if (rawWords.length() > 1){
				rawWords = convToLower(rawWords);
				s.insert(rawWords);
			}
			break;
		}
		if (ispunct(rawWords[i]) || isspace(rawWords[i])){
			string kw = rawWords.substr(0,i);
			rawWords = rawWords.substr(i+1);
			i = 0;
			if (kw.size() > 1){
				kw = convToLower(kw);
				s.insert(kw);
			}
		}
		else{
			i++;
		}
	}

	return s;
}





/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
