#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP
#include "Order.hpp"
#include "Pricebucket.hpp"
#include <string>
#include <map>

class Book {
	private:
		PricebucketManager priceBucketManager;
		std::string stock;
	public:
		Book(std::string s) : stock{s} {}

		void addPrice();
};

class Orderbook {
	private:
		std::map<std::string, Book> books;
	public:
		Orderbook() {}

		void addOrder(Order);
		void addStock();
};

#endif
