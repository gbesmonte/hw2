#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const string category, const string name, double price, int qty, string ISBN, string author) : Product(category,name,price,qty){
	this->ISBN = ISBN;
	this->author = author; 
}
  
Book::~Book(){

}	

set<string> Book::keywords() const{
	set<string> s;
	s = parseStringToWords(author);
	s.insert(ISBN);
	return s;
}

string Book::displayString() const{
	string s;
	s = getName() + "\n" + "Author: " + author + " ISBN: " + ISBN + "\n" + to_string(getPrice()) + " " + to_string(getQty()) + " left.";
	return s;
}

void Book::dump(std::ostream& os) const{
	os << "book" << endl;
	os << getName() << endl;
	os << to_string(getPrice()) << endl;
	os << to_string(getQty()) << endl;
	os << ISBN << endl;
	os << author << endl;
}


