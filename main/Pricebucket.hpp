#ifndef PRICEBUCKET_HPP
#define PRICEBUCKET_HPP
#include <map>
#include <deque>
#include "Order.hpp"

/* Data class to standardise depth format */
struct depth { float price; int numBids; int numAsks; };

class Pricebucket {
	private:
		float price;
		std::deque<Order> bids;
		std::deque<Order> asks;

	public:
		Pricebucket(float p) : price{p} {}

		/* Add an order to the price bucket */
		void addOrder(Order*);

		/* Remove an order from the price bucket */
		int removeOrder(Order*);

		/* Find an order in the bid or ask list
		 The side (bid or ask) of the order is specified within the class
		 */
		Order* findOrder(Order*);

		/* Get the number of bids for this price bucket*/
		int sizeBid();

		/* Get the number of asks for this price bucket */
		int sizeAsk();
};

class PricebucketManager {
	private:
		std::map<float, Pricebucket> buckets;
	
	public:
		/* Add a price to the price buckets */
		Pricebucket * addPrice(float price);

		/* Find a price in the price buckets, returned as copy to prevent tampering */
		Pricebucket findPrice(float price);

		/* Return all buckets as a copy */
		std::map<float, Pricebucket> getBuckets();
};

#endif
