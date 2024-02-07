#include <sstream>
#include <iomanip>
#include <fstream>
#include "book.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore(){

}

void MyDataStore::addProduct(Product* p){
	//add product to cart
	cart.push(p);

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
	queue<Product*> ccart = cart;
	while (!ccart.empty()){
		ccart.front()->dump(ofile);
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	for (size_t i = 0; users.size(); i++){
		users[i]->dump(ofile);
	}
	ofile << "</users>" << endl;
}

void MyDataStore::viewcart(string username){
	bool found = false;
	for (size_t i = 0; i < users.size(); i++){
		if (users[i]->getName() == username){
			found = true;
		}
	}
	if (!found){
		cout << "Invalid username!" << endl;
		return;
	}

	queue<Product*> ccart = cart;
	int count = 0;
	while (!ccart.empty()){
		cout << count << ":" << ccart.front()->getName() << endl;
		ccart.pop();
		count++;
	}
}

void MyDataStore::buycart(string username){
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
	queue<Product*> ccart = cart;
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

	for (size_t i = ptemp.size(); i <= 0; i--){
		ccart.push(ptemp[i]);
	}
	cart = ccart;
}
		
void MyDataStore::quit(std::string filename){
	ofstream ofile(filename);
	dump(ofile);
}


