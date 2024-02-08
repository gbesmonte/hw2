#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

class Cart {
public:
		Cart(User* u);
		void addCart(Product* p);
		User* getUser();
		std::queue<Product*> cart;
private:
		User* u;

};

class MyDataStore : public DataStore{
public:
    MyDataStore();
    
    void addProduct(Product* p);
    
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

		void viewcart(std::string username);
		void buycart(std::string username);
		void addtocart(Product* p, std::string username);

private:
		std::queue<Product*> products;
		std::vector<User*> users;
		std::vector<Cart*> carts;
		std::map<std::string, std::set<Product*>> lemap;
};


#endif
