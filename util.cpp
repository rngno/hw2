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
    std::set<std::string> keywords;
    std::string word;

    // keep going char by char until end of rawWords
    for (char c : rawWords) {
        // make sure to put the char in lowercase
        if (isalnum(c)) {
            word += tolower(c);

            // put this here so i can nest a little less :)
            continue; // go to next char
        } 
        // hit a non-alphanumeric char, check to make sure word is long enough
        if (word.length() >= 2) {
            keywords.insert(word);
        }
        // clear out word so we can keep parsing
        word.clear();
    }

    // last word needs to be checked separately to make sure that there's not an issue with it being too short
    if (word.length() >= 2) {
        keywords.insert(word);
    }

    return keywords;
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
