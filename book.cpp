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

	set<string> s2;
	s2 = parseStringToWords(getName());

	s = setUnion(s,s2);
	
	/*for (set<string>::iterator it = s.begin(); it != s.end(); ++it){
		cout << *it << endl;
	}*/
	
	s.insert(ISBN);
	return s;
}

string Book::displayString() const{
	string s;
	stringstream ss;
	ss << getName() + "\n" + "Author: " + author + " ISBN: " + ISBN + "\n" << fixed << setprecision(2) << getPrice() << " " << getQty() << " left.";
	//s = getName() + "\n" + "Author: " + author + " ISBN: " + ISBN + "\n" + to_string(getPrice()) + " " + to_string(getQty()) + " left.";
	s = ss.str();
	return s;
}

void Book::dump(std::ostream& os) const{
	os << "book" << endl;
	os << getName() << endl;
	os << fixed << setprecision(2) << getPrice() << endl;
	os << to_string(getQty()) << endl;
	os << ISBN << endl;
	os << author << endl;
}


