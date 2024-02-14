#include "mydatastore.h"
#include "util.h"
#include "product.h"
#include "user.h"
#include <queue>
#include <iostream>
#include <iterator>

using namespace std;

MyDataStore::MyDataStore(){

}
MyDataStore::~MyDataStore()
{
  //deallocating memory in destructor
  for(Product* p :products)
  {
    delete p;
  }
  for(User* u:users)
  {
    delete u;
  }
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  std::vector<Product*> result;
  //checking an intersection search
  if(type == 0)
  {
    std::set<Product*> resultSet;
    bool firstT = true;
    for(std::string& term:terms)
    {
      //find products associated with term
      auto it = keywordIndex.find(term);
      if (it != keywordIndex.end())
      {
        //if it is the firsttime initalize the result
        if (firstT)
        {
          resultSet = it->second;
          firstT = false;
        }
        else
        {
          //otherwise perform set intersection
          resultSet = setIntersection(resultSet, it->second);
        }
      }
      else
      {
        //if an item is not found give an empty result
        return std::vector<Product*>();
      } 
    }
    result = std::vector<Product*>(resultSet.begin(), resultSet.end());

  }
  //union search
  else if(type ==1)
  {
    std::set<Product*> resultSet;
    std::set<Product*> tempSet;
    for (const std::string& term : terms)
    {
      //find products associated with terms
      auto it = keywordIndex.find(term);
      if(it!=keywordIndex.end())
      {
        //insert product into result set
        resultSet.insert(it->second.begin(), it->second.end());

      }
      //conver rthe result set to vector
      result = std::vector<Product*>(resultSet.begin(), resultSet.end());
    }
  }
  return result;
  
}
void MyDataStore::addProduct(Product* p)
{
  //adding product to vector
  products.push_back(p);
  std::set<std::string> productKeywords = p->keywords();
  for (std::set<std::string>::iterator it = productKeywords.begin(); it != productKeywords.end(); ++it)
  {
    //insert product
    keywordIndex[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u)
{
  //adding user
  u.push_back(u);
  carts[u->getName()];
}



void MyDataStore::addToCart(std::string u, Product* p)
{
  if(carts.find(u) == carts.end())
  {
    cout << "Invalid Request" << endl;
    return;
  }
  carts[u].push_back(p);
}

void MyDataStore::viewCart(std::string u)
{
  //finding the cart and displaying it
  std::vector<Product*>& temp = carts[u];
  for(size_t i = 0; i < temp.size(); i++)
  {
    cout << "Item " << i+1 << endl;
    cout << temp[i] -> displayString() <<endl;
    cout << endl;
  }
}

void MyDataStore::buyCart(std::string u)
{

  //find the users object
  User* uObj = nullptr;

  for(User* u_ : users)
  {
    if(convToLower(u_->getName()) == convToLower(u))
    {
      uObj = u_;
      break;
    }
  }
  //making sure user exists

  if(uObj == nullptr)
  {
    cout << "Username is not valid" << endl;
    return;
  }
  //finding the users cart
  auto cartIt = carts.find(u);
  if(cartIt == carts.end())
  {
    cout << "cart isnt found" << endl;
    return;
  }
  //retrieving the cart
  std::vector<Product*>& userCart = cartIt->second;

  for(auto it = userCart.begin(); it != userCart.end();)
  {
    //check if product is available and has enough balance
    Product* product = *it;
    if(product->getQty() > 0 && uObj->getBalance() >= product->getPrice())
    {
      //purchasing product and ubdating inventory
      product->subtractQty(1);
      uObj->deductAmount(product->getPrice());

      cout << "Product bought: " << product->displayString() << endl;
      //removing from cart
      it = userCart.erase(it);
    }
    else{
      //skip to next product if cantbuy previous
      cout << "Unable to buy: " << product->displayString() << endl;
      it++;
    }

  }

}

void MyDataStore::dump(std::ostream& ofile)
{
  //dump products
  ofile << "<products>" << endl;
  for (Product* p : products)
  {
    if (p != nullptr) {
      p->dump(ofile);
    }
  }
  ofile << "</products>" << endl;

  //dump users
  ofile << "<users>" << endl;
  for (User* u : users) {
    if (u != nullptr)
    {
      u->dump(ofile);
    }
  }
  ofile << "</users>" << endl;
  
}