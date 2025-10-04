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
    users_.push_back(u); // Add user to vector
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

// HELPER FUNCTIONS FOR AMAZON.CPP COMMANDS
void MyDataStore::addToCart(User* u, Product* product) {
    // error handling for invalid user
    if (u == nullptr) {
        return;
    }

    // error handling for duplicate products in cart
    // walk through all products in cart and see if product is already there
    for(Product* p : carts_[u->getName()]) {
        if (p == product) {
            return; // product already in cart, do nothing
        }
    }

    // add product to user's cart (handles diff than usual bc it's a map)
    carts_[u->getName()].push_back(product);
}

// view cart for a given username
std::vector<Product*> MyDataStore::getCart(User* u) {
    // error handling for invalid user
    if(u == nullptr){
        return std::vector<Product*>(); // return empty vector
    }

    // only get here if we find the cart for the specific user
    return carts_[u->getName()];
}

// buy cart for a given username
void MyDataStore::buyCart(User* u) {
    // in retrospect i couldve added a getUser function but the due date is coming soon

    // error handling for invalid user
    if(u == nullptr){
        return;
    }

    std::map<std::string, std::vector<Product*> >::iterator cartIt = carts_.find(u->getName());

    // error handling for empty cart
    if (cartIt == carts_.end()) {
        return;
    }

    // set up iterator and reference for easier reading/formatting
    std::vector<Product*>& cart = cartIt->second;
    std::vector<Product*>::iterator it = cart.begin();

    // iterate through the cart and attempt to buy each item
    while (it != cart.end()) {
        Product* product = *it; // readability purposes

        // check if product is purchasable and if user can afford it
        if (product->getQty() > 0 && u->getBalance() >= product->getPrice()) {
            product->subtractQty(1);
            u->deductAmount(product->getPrice());
            it = cart.erase(it); // only able to purchase one of an item
        }

        // move on if not purchasable or not enough balance 
        else {
            ++it;
        }
    }
}