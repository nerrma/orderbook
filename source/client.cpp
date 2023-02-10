#include "orderbook/orderbook.hpp"
#include <iostream>
#include <order/order.hpp>

auto main() -> int {
	auto ask = order::order(1, order::side::ask, 140, 10, std::time(nullptr));

	auto obook = orderbook();
	obook.add_order(ask);

	auto bid = order::order(2, order::side::bid, 140, 10, std::time(nullptr));
	obook.add_order(bid);

	obook.match();
}
