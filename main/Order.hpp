#ifndef ORDER_HPP
#define ORDER_HPP
#include <string>

enum Side {
	Bid,
	Ask
};

class Order {
	Order(std::string id, std::string t, int q, float p, Side s) : ticker{t}, quantity{q}, price{p}, side{s} {}

	public:
		std::string getID() { return id; }
		std::string getTicker() { return ticker; }
		int getQuantity() { return quantity; }
		float getPrice() { return price; }
		Side getSide() { return side; }

	private:
		std::string id;
		std::string ticker;
		int quantity; 
		float price; 
		Side side; 
};

#endif
