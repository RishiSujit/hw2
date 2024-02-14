#include "book.h"
#include "product.h"
#include "util.h"
#include <sstream>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) :
Product(category, name, price, qty)
{
  //initializing private variables that are unique to book
  isbn_ = isbn;
  author_ = author;
}
Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
  //create set to store keywrods
  std::set<std::string> words;
  //parse product names into wordsa and add to set
  std::set<std::string> nameWords = parseStringToWords(name_);
  words.insert(nameWords.begin(), nameWords.end());
  //parse author into words and add to set
  std::set<std::string> authorWords = parseStringToWords(author_);
  words.insert(authorWords.begin(), authorWords.end());

  return words;
  
}

std::string Book::displayString() const
{
  //displaying the string
  string s;
  string price = to_string(price_);
  string rPrice = price.substr(0, price.find(".")+3);
  s+=name_;
  s+= "\nAuthor: ";
  s+= author_;
  s+= " ISBN: ";
  s+= isbn_;
  s+= "\n";
  s+= rPrice;
  s+= " ";
  s+= to_string(qty_);
  s+= " left.";
  return s;
}

void Book::dump(std::ostream& os) const
{
  //outputting
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}