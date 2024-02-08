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
	s = parseStringToWords(getName());

	string g = convToLower(genre);
	s.insert(g);

	return s;
}

string Movie::displayString() const{
	string s;
	//s = getName() + "\n" + "Genre: " + genre + " Rating: " + rating + "\n" + to_string(getPrice()) + " " + to_string(getQty()) + " left.";
	stringstream ss;
	ss << getName() + "\n" + "Genre: " + genre + " Rating: " + rating  + "\n" << fixed << setprecision(2) << getPrice() << " " << getQty() << " left.";
	s = ss.str();
	return s;
}

void Movie::dump(std::ostream& os) const{
	os << "movie" << endl;
	os << getName() << endl;
	os << fixed << setprecision(2) << getPrice() << endl;
	os << to_string(getQty()) << endl;
	os << genre << endl;
	os << rating << endl;
}


