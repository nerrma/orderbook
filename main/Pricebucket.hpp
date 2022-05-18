#ifndef PRICEBUCKET_HPP
#define PRICEBUCKET_HPP
#include <map>
#include <deque>
#include "Order.hpp"

struct depth {
	float price;
	int numBids;
	int numAsks;
};

class Pricebucket {
	private:
		float price;
		std::deque<Order> bids;
		std::deque<Order> asks;

	public:
		Pricebucket(float p) : price{p} {}
		void addOrder(Order*);
		int removeOrder(Order*);
		void findBid(Order*);
		void findAsk(Order*);
		int sizeBid();
		int sizeAsk();
};

class PricebucketManager {
	private:
		std::map<float, Pricebucket> buckets;
	
	public:
		Pricebucket * addPrice(float price);
		Pricebucket * findPrice(float price);
		std::map<float, Pricebucket> getBuckets();
};

#endif
