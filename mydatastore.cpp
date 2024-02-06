#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore(){

}

void myDataStore::addProduct(Product* p){
	cart.push_back(p);
	
}

void myDataStore::addUser(User* u){
	users.push_back(u);
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
	vector<Product*> v;
	
	if (type == 0){ //AND search
		//for all products in cart
		//s= setintersection(product keywords(), terms)
		//if is not empty
		//add product to v

		return v;
	}
	else if (type == 1){ //OR search

		return v;
	}
}

void MyDataStore::dump(std::ostream& ofile){

}

void MyDataStore::viewcart(User* u){

}

void MyDataStore::buycart(User* u){
	double balance = u->getBalance();

}
		
void MyDataStore::quit(std::string filename){

}


