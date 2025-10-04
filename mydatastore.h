#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <vector>
#include <set>
#include <map>
#include <string>

class MyDataStore : public DataStore {
public:
    MyDataStore(); // DataStore uses virtual constructor so we need to define our own
    ~MyDataStore(); // we're gonna need this to free memory (VERY IMPORTANT DO NOT FORGET)

    // implement pure virtual functions from DataStore
    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;
    std::vector<User*> getUsers() const { return users_; }// need this for amazon.cpp to get users for ADD command
    void addToCart(User* u, Product* p); // also need this for amazon.cpp to add products to user's cart
    std::vector<Product*> getCart(User* u); // view cart for a given username
    void buyCart(User* u); // buy cart for a given username

private:
    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::map<std::string, std::vector<Product*>> carts_; // wow i just learned about this one
};

#endif