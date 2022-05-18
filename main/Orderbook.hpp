#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP
#include "Order.hpp"
#include "Pricebucket.hpp"
#include <string>
#include <vector>
#include <map>

class Book {
	private:
		PricebucketManager priceBucketManager;
		std::string stock;
	public:
		Book(std::string s) : stock{s} {}

		int addOrder(Order* order);
		int cancelOrder(Order* order);
		depth * getDepth(float price);
		std::vector<depth *> getAllDepths();
};

class Orderbook {
	private:
		std::map<std::string, Book> books;
	public:
		void addOrder(Order* order);
		void addStock(std::string ticker);
};

#endif
