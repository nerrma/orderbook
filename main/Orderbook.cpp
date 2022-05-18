#include "Orderbook.hpp"

int Book::addOrder(Order* order){
	Pricebucket * pb = priceBucketManager.findPrice(order->getPrice());

	if(pb)
		pb = priceBucketManager.addPrice(order->getPrice());

	pb->addOrder(order);

	return 0;
}

int Book::cancelOrder(Order* order){
	Pricebucket * pb = priceBucketManager.findPrice(order->getPrice());

	if(!pb)
		return -1;
	

	return pb->removeOrder(order);
}

depth * Book::getDepth(float price){
	Pricebucket * pb = priceBucketManager.findPrice(price);

	if(!pb)
		return NULL;

	return new depth{price, pb->sizeBid(), pb->sizeAsk()};
}

std::vector<depth *> Book::getAllDepths(){
	auto buckets = priceBucketManager.getBuckets();

	std::vector<depth *> res;

	for(auto b : buckets){
		res.push_back(new depth{b.first, b.second.sizeBid(), b.second.sizeAsk()});
	}

	return res;
}
