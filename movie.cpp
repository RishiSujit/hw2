#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
Product(category,name, price, qty)
{
  //initializing private members
  genre_ = genre;
  rating_ = rating;
}
Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
  //create a set to store keyword
  std::set<std::string> words;
  //parsing names into keywords and adding to set
  std::set<std::string> nameWords = parseStringToWords(name_);
  words.insert(nameWords.begin(), nameWords.end());
//parsing genre into keyword and adding to set
  std::set<std::string> genreWords = parseStringToWords(genre_);
  words.insert(genreWords.begin(), genreWords.end());

  return words;
}

std::string Movie::displayString() const
{
  //displayng
  string s;
  string price = to_string(price_);
  string roundPrice = price.substr(0, price.find(".")+3);
  s+=name_;
  s+= "\nGenre: ";
  s+= genre_;
  s+= " Rating: ";
  s+= rating_;
  s+= "\n";
  s+= roundPrice;
  s+= " ";
  s+= to_string(qty_);
  s+= " left.";
  return s;
}

void Movie::dump(std::ostream& os) const
{
   os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}