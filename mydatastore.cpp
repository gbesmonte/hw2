#include <sstream>
#include <iomanip>
#include <fstream>
#include "book.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
	for (size_t i = 0; i < carts.size(); i++){
		delete carts[i];
	}

	for (size_t i = 0; i < users.size(); i++){
		delete users[i];
	}

	while (!products.empty()){
		delete products.front();
		products.pop();
	}
}

void MyDataStore::addProduct(Product* p){
	//add product to products
	products.push(p);

	//access all keywords in product
	set<string> s = p->keywords();
	set<string>::iterator it;
	//for all keywords in product
	for (it = s.begin(); it != s.end(); ++it){
		//if keyword is already in map, add it to set
		map<string, set<Product*>>::iterator it2 = lemap.find(*it);
		if (it2 != lemap.end()){
			it2->second.insert(p);
		}
		//if keyword is not already in map, add it to set
		else{
			set<Product*> newSet;
			newSet.insert(p);
			lemap.insert(make_pair(*it, newSet));
		}
	}
}

void MyDataStore::addUser(User* u){
	users.push_back(u);
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
	vector<Product*> v;
	if (type == 0){ //AND search
		set<Product*> s;
		bool first = true;
		//for all searchwords in terms
		for (size_t i = 0; i < terms.size(); i++){
			//find if term is in the map
			map<string, set<Product*>>::iterator it = lemap.find(terms[i]);
			//if it is, set s to it
			if (it != lemap.end() && first){
				s = it->second;
				first = false;
			}
			//if it is and s is already set, check it against s
			else if (it != lemap.end() && !first){
				set<Product*> s2 = it->second;
				s = setIntersection(s, s2);
			}
		}
		for (set<Product*>::iterator it = s.begin(); it != s.end(); ++it){
			v.push_back(*it);
		}
		return v;
	}
	else if (type == 1){ //OR search
		set<Product*> s;
		bool first = true;
		//for all searchwords in terms
		for (size_t i = 0; i < terms.size(); i++){
			//find if term is in the map
			map<string, set<Product*>>::iterator it = lemap.find(terms[i]);
			//if it is, set s to it
			if (it != lemap.end() && first){
				s = it->second;
				first = false;
			}
			//if it is and s is already set, check it against s
			else if (it != lemap.end() && !first){
				set<Product*> s2 = it->second;
				s = setUnion(s, s2);
			}
		}
		for (set<Product*>::iterator it = s.begin(); it != s.end(); ++it){
			v.push_back(*it);
		}
		return v;
	}
	return v;
}

void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" << endl;
	queue<Product*> p = products;
	while (!p.empty()){
		p.front()->dump(ofile);
		p.pop();
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	for (size_t i = 0; i < users.size(); i++){
		users[i]->dump(ofile);
	}
	ofile << "</users>" << endl;
}

//EVERYTHING BELOW THIS LINE NEEDS CART FIXING

void MyDataStore::viewcart(string username){
	
	bool found = false;
	User* myU;
	for (size_t i = 0; i < users.size(); i++){
		if (users[i]->getName() == username){
			found = true;
			myU = users[i];
		}
	}
	if (!found){
		cout << "Invalid username!" << endl;
		return;
	}

	queue<Product*> ccart;
	for (size_t i = 0; i < carts.size(); i++){
		if (carts[i]->getUser() == myU){
				ccart = carts[i]->cart;
		}
	}

	int count = 1;
	while (!ccart.empty()){
		cout << "Product\t" << count << endl;
		cout << ccart.front()->displayString() << endl;
		ccart.pop();
		count++;
	}
}

void MyDataStore::buycart(string username){
	//find User* corresponding to username
	bool found = false;
	User* myU;
	for (size_t i = 0; i < users.size(); i++){
		if (users[i]->getName() == username){
			found = true;
			myU = users[i];
		}
	}
	if (!found){
		cout << "Invalid username!" << endl;
		return;
	}
	double balance = myU->getBalance();
	double initialbal = myU->getBalance();

	//find cart that user has
	int j = 0;
	queue<Product*> ccart;
	for (size_t i = 0; i < carts.size(); i++){
		if (carts[i]->getUser() == myU){
				ccart = carts[i]->cart;
				j = i;
		}
	}

	//buy the stuff
	vector<Product*> ptemp; 
	while (!ccart.empty()){
		Product* curr = ccart.front();
		if (curr->getPrice() <= balance && curr->getQty() >= 1){
			curr->subtractQty(1);
			balance -= curr->getPrice();
			ccart.pop();
		}
		else{
			ptemp.push_back(curr);
			ccart.pop();
		}
	}
	

	for (size_t i = ptemp.size() -1; i <= 0; i--){
		ccart.push(ptemp[i]);
	}

	carts[j]->cart = ccart;
	myU->deductAmount(initialbal - balance);
}

void MyDataStore::addtocart(Product* p, string username){
	bool found = false;
	User* myU;
	for (size_t i = 0; i < users.size(); i++){
		if (users[i]->getName() == username){
			found = true;
			myU = users[i];
		}
	}
	if (!found){
		cout << "Invalid request" << endl;
		return;
	}
	
	bool found2 = false;
	Cart* myC = nullptr;
	for (size_t i = 0; i < carts.size(); i++){
		if (carts[i]->getUser() == myU){
				carts[i]->addCart(p);
				found2=true;
				//cout << "Added to existing cart" << endl;
		}
	}

	if (!found2){
		//cout << "Made new cart" << endl;
		myC = new Cart(myU);
		myC->addCart(p);
		carts.push_back(myC);
	}
}
		

Cart::Cart(User* u){
	this->u = u;
}

void Cart::addCart(Product* p){
	cart.push(p);
}

User* Cart::getUser(){
	return u;
}