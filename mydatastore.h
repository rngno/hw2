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

private:
    std::vector<Product*> products_;
    std::vector<User*> users_;
};

#endif