#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> result; // need something to store our output

    // now instead of an O(nlogn) solution, we can do this in O(n) time, but im feeling too lazy to actually implement that tonight (my bad)

    // go through each element in s1, and check if it's in s2
    for(const auto& elt : s1) {
        // if it's in s2, add it to the result set
        if(s2.find(elt) != s2.end()) {
            result.insert(elt);
        }
    }

    return result;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> result = s1; // start with LHS 

    // s1 starts off result, so we can just copy the rest of s2 into result
    result.insert(s2.begin(), s2.end());

    // return the combined sets (union)
    return result;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
