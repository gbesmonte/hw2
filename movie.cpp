#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, string genre, string rating) : Product(category,name,price,qty){
	this->genre = genre;
	this->rating = rating; 
}
  
Movie::~Movie(){

}	

set<string> Movie::keywords() const{
	set<string> s;
	s.insert(genre);
	return s;
}

string Movie::displayString() const{
	string s;
	s = getName() + "\n" + "Genre: " + genre + "Rating: " + rating + "\n" + to_string(getPrice()) + " " + to_string(getQty()) + " left.";
	return s;
}

void Movie::dump(std::ostream& os) const{
	os << "movie" << endl;
	os << getName() << endl;
	os << to_string(getPrice()) << endl;
	os << to_string(getQty()) << endl;
	os << genre << endl;
	os << rating << endl;
}


