#include "clothing.h"
#include "util.h"


// inherit product constructor and set our own vars
Clothing::Clothing(const std::string& category, const std::string& name, double price, int qty, const std::string& size, const std::string& brand): Product(category, name, price, qty){
    // set clothing specific vars
    size_ = size;
    brand_ = brand;
}

// set keywords from parsed data
// im honestly just copy-pasting from the other inherited classes at this point
std::set<std::string> Clothing::keywords() const {
    // keywords are name and brand per assignment instructions
    std::set<std::string> keys = parseStringToWords(name_);

    // parse brand here to make it easier to read for myself
    std::set<std::string> brandKeys = parseStringToWords(brand_);

    // we can slap on the brand now since name is in already
    keys.insert(brandKeys.begin(), brandKeys.end());
    return keys;
}

// format display string as per assignment instructions
std::string Clothing::displayString() const {
    return name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}


// dump clothing info in the correct format
void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}