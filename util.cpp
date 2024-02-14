#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include <string_view>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}
bool isLetter(string s)
{
  if (s >= "a" && s <= "z")
  {
    return true;
  }
  else
  {
    return false;
  }
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    //converting to lower case
    rawWords = convToLower(rawWords);
    std::set<std::string> wordSet;
    string str = "";
    for(size_t i =0; i < rawWords.length(); i++)
    {
        //identifying and adding the words
        std::string part = rawWords.substr(i,1);
        if(isLetter(part))
        {
            str+= part;
        }
        else if (str.length()>=2)
        {
            wordSet.insert(str);
            str = "";
        }
        else{
            str = "";
        }
    }
    //making sure word is not empty
    if(!str.empty()) wordSet.insert(str);

    //return set
    return wordSet;

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
