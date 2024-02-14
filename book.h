#ifndef BOOK_H
#define BOOK_H

#include "product.h"
//book inherits from Product
class Book : public Product {
public:
  Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author);
  ~Book();
  //three functions
  std::string displayString() const;
  void dump(std::ostream& os) const;
  std::set<std::string> keywords() const;

  

  
private:
  std::string author_;
  std::string isbn_;
};
#endif