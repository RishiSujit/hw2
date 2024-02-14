#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <set>
#include <vector>

class Movie : public Product {
public:
  Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
  ~Movie();
  //three member functions
  void dump(std::ostream& os) const;
  std::string displayString() const;
  std::set<std::string> keywords() const;

  

  
private:
  std::string genre_;
  std::string rating_;
};
#endif