#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "mydatastore.cpp"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            /* Add support for other commands here */

            // ohhhhh my god this nesting is so ugly and hard to read
            else if ( cmd == "ADD") {
                string username;
                int hitNum;

                // get username and hit number, only proceed if they're given
                if (ss >> username >> hitNum) {
                    // check that hit number is valid
                    if (hitNum < 1 || hitNum > (int)hits.size()) {
                        cout << "Invalid request" << endl;
                        continue;
                    }

                    User* user = nullptr;

                    // find user with given username
                    for (User* u : ds.getUsers()) {
                        if (u->getName() == username) {
                            user = u;
                            break;
                        }
                    }
                    // error handling for username that doesn't exist
                    if (user == nullptr) {
                        cout << "Invalid request" << endl;
                        continue;
                    }
                    ds.addToCart(user, hits[hitNum - 1]);
                    cout << "Added to cart" << endl;
                }
                else {
                    cout << "Invalid request" << endl;
                }
            }
            else if ( cmd == "VIEWCART") {
                string username;
                if (ss >> username) {
                    User* user = nullptr;

                    // only populate user if we find a matching username
                    for (User* u : ds.getUsers()) {
                        if (u->getName() == username) {
                            user = u;
                            break;
                        }
                    }

                    // error handling for invalid username
                    if (user == nullptr) {
                        cout << "Invalid username" << endl;
                        continue;
                    }

                    // get the actual cart vector for the user
                    const vector<Product*>& cart = ds.getCart(user);
                    if (cart.empty()) {
                        cout << "Empty cart" << endl;
                        continue;
                    }

                    // display cart contents
                    int itemNo = 1;
                    for (Product* p : cart) {
                        cout << "Item " << itemNo << endl;
                        cout << p->displayString() << endl;
                        cout << endl;
                        itemNo++;
                    }
                }
                else {
                    cout << "Invalid request" << endl;
                }
            }
            else if ( cmd == "BUYCART") {
                string username;
                if (ss >> username) {
                    User* user = nullptr;

                    // only populate user if we find a matching username
                    for (User* u : ds.getUsers()) {
                        if (u->getName() == username) {
                            user = u;
                            break;
                        }
                    }

                    // error handling for invalid username
                    if (user == nullptr) {
                        cout << "Invalid username" << endl;
                        continue;
                    }

                    // get the actual cart vector for the user
                    vector<Product*>& cart = ds.getCart(user);
                    if (cart.empty()) {
                        cout << "Empty cart" << endl;
                        continue;
                    }

                    // iterate through cart and buy what we can
                    int i = 0;
                    while (i < (int)cart.size()) {
                        Product* p = cart[i];
                        if (p->getQty() > 0 && user->getBalance() >= p->getPrice()) {
                            user->deductAmount(p->getPrice());
                            p->subtractQty(1);
                            cart.erase(cart.begin() + i);
                        } 
                        // move on if not purchasable or not enough balance
                        else {
                            i++;
                        }
                    }
                } 
                else {
                    //cout << "Invalid request" << endl;
                    done = true;
                }
            }
            else {
                cout << "Unknown command" << endl;
            }
        }
    }
    return 0;
}

void displayProducts(vector<Product*>& hits){
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
