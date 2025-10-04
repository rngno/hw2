#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <string>
#include <set>

// has to inherit from Product (is-a)
class Book : public Product {
public:
    Book(const std::string& category, const std::string& name, double price, int qty, const std::string& isbn, const std::string& author);


    // we can override these functions since they are pure virtual in Product
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

// DONT RENAME THESE!! NEEDED FOR PARSER
private:
    std::string isbn_;
    std::string author_;
};

#endif