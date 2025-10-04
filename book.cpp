#include "book.h"
#include "util.h"

// only need to inherit the product constructor and set our own vars
Book::Book(const std::string& category, const std::string& name, double price, int qty, const std::string& isbn, const std::string& author): Product(category, name, price, qty){
    // set book specific vars
    isbn_ = isbn;
    author_ = author;
}

// set keywords from parsed data
std::set<std::string> Book::keywords() const {
    // keywords are name, author, and isbn per assignment instructions
    std::set<std::string> keys = parseStringToWords(name_);

    // parse author here to make it easier to read for myself
    std::set<std::string> authorKeys = parseStringToWords(author_);

    // we can slap on the author and isbn now since name is in already
    keys.insert(authorKeys.begin(), authorKeys.end());
    keys.insert(isbn_);
    return keys;
}

// format display string as per assignment instructions
std::string Book::displayString() const {
    return name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

// dump book info in the correct format
void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}