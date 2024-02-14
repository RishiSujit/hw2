#include "clothing.h"
#include "product.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
Product(category, name, price, qty)
{
  size_ = size;
  brand_ = brand;
}
Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const
{
  //create set to store keywords
  std::set<std::string> words;
  //parsing product name into keywords and adding to set
  std::set<std::string> nameWords = parseStringToWords(name_);
  words.insert(nameWords.begin(), nameWords.end());
  //parsing brand into keywords and adding to set
  std::set<std::string> brandWords = parseStringToWords(brand_);
  words.insert(brandWords.begin(), brandWords.end());

  return words;

}

std::string Clothing::displayString() const
{
  //displaying
  string price = to_string(price_);
  string roundPrice = price.substr(0, price.find(".") + 3);
  string s; 
  s += name_;
  s += "\nSize: ";
  s += size_;
  //s+= "\n"
  s += " Brand: ";
  s += brand_; 
  s += "\n";
  s += roundPrice;
  s += " ";
  s += to_string(qty_);
  s += " left.";
  return s;
}

void Clothing::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}