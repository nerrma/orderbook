#ifndef PRICEBUCKET_HPP
#define PRICEBUCKET_HPP
#include <map>
#include "Order.hpp"

class Pricebucket {
};

class PricebucketManager {
	private:
		std::map<float, Pricebucket> orders;
	
	public:
		void addPrice();
		void findPrice();
};

#endif
