#include "movie.h"
#include "util.h"

// inherit product constructor and set our own vars
Movie::Movie(const std::string& category, const std::string& name, double price, int qty, const std::string& genre, const std::string& rating): Product(category, name, price, qty){
    // set movie specific vars
    genre_ = genre;
    rating_ = rating;
}

std::set<std::string> Movie::keywords() const {
    // keywords are name and genre per assignment instructions
    std::set<std::string> keys = parseStringToWords(name_);

    // parse genre here to make it easier to read for myself
    std::set<std::string> genreKeys = parseStringToWords(genre_);

    // slap on the genre now since name is in already
    keys.insert(genreKeys.begin(), genreKeys.end());
    return keys;
}


// format display string as per assignment instructions
std::string Movie::displayString() const {
    return name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}


// dump movie info in the correct format
void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}