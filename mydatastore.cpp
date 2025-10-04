#include "mydatastore.h"
#include "util.h"


// don't really need to construct anything
MyDataStore::MyDataStore() {}

// since products and users are dynamically allocated, need to free them here
MyDataStore::~MyDataStore() {
    for (Product* p : products_) {
        delete p;
    }
    for (User* u : users_) {
        delete u;
    }
}

// just push back the product into our vector, nothing fancy
void MyDataStore::addProduct(Product* p) {
    products_.push_back(p);
}

// just push back the user into our vector, nothing fancy
void MyDataStore::addUser(User* u) {
    users_.push_back(u);
}

// and/or search implementation using set operations from util.h per assignment instructions
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    // need one vector for results and one set for easier intersection/union ops
    std::vector<Product*> results;
    std::set<Product*> resultSet;

    // error handling for empty search terms
    if (terms.empty()) {
        return results;
    }

    // for each term, get the products that match it
    for (const std::string& term : terms) {
        std::set<Product*> tempSet;
        for (Product* p : products_) {
            if (p->keywords().count(term) > 0) {
                tempSet.insert(p);
            }
        }
        // if resultSet is empty, just set it to tempSet
        if (resultSet.empty()) {
            resultSet = tempSet;

            // to remove nesting
            continue; // go to next term 
        }

        // what type of search are we doing?
        if (type == 0) {
            // AND search (intersection)
            resultSet = setIntersection(resultSet, tempSet);
        } 
        else{
            // OR search (union)
            resultSet = setUnion(resultSet, tempSet);
        }
    }

    // convert set back to vector for return (DONT FORGET THIS STEP)
    results.assign(resultSet.begin(), resultSet.end());
    return results;
}

// dump products and users in the correct format per assignment instructions
void MyDataStore::dump(std::ostream& ofile) {
    // head off sections for parsing later
    ofile << "<products>\n";
    for (Product* p : products_) {
        p->dump(ofile);
    }

    // close products section and open users section
    ofile << "</products>\n<users>\n";
    for (User* u : users_) {
        u->dump(ofile);
    }

    // close users section
    ofile << "</users>\n";
}