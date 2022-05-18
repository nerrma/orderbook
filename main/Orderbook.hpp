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

		/* Add an order to the book */
		int addOrder(Order* order);

		/* Cancel an order */
		int cancelOrder(Order* order);

		/* Get the depth for a price as a depth object */
		depth * getDepth(float price);

		/* Get the depths of all prices */
		std::vector<depth *> getAllDepths();
};

class Orderbook {
	private:
		std::map<std::string, Book> books;
	public:
		/* Add an order to the correspoding book */
		int addOrder(Order* order);

		/* Add a stock to the overall orderbook */
		void addStock(std::string ticker);
};

#endif
