#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, string size, string brand) : Product(category,name,price,qty){
	this->size = size;
	this->brand = brand; 
}
  
Clothing::~Clothing(){

}	

set<string> Clothing::keywords() const{
	set<string> s;
	s = parseStringToWords(brand);
	/*for (set<string>::iterator it = s.begin(); it != s.end(); ++it){
		cout << *it << endl;
	}*/

	set<string> s2;
	s = parseStringToWords(getName());

	s = setUnion(s,s2);
	return s;
}

string Clothing::displayString() const{
	string s;
	s = getName() + "\n" + "Size: " + size + " Brand: " + brand + "\n" + to_string(getPrice()) + " " + to_string(getQty()) + " left.";
	return s;
}

void Clothing::dump(std::ostream& os) const{
	os << "clothing" << endl;
	os << getName() << endl;
	os << to_string(getPrice()) << endl;
	os << to_string(getQty()) << endl;
	os << size << endl;
	os << brand << endl;
}



