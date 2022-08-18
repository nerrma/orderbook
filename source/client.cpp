#include "orderbook/orderbook.hpp"
#include <iostream>
#include <order/order.hpp>

auto main() -> int {
	auto o = order::order(1, order::side::ask, 140, 1180);

	auto ob = orderbook();
	ob.add_order(o);
	std::cout << ob.get_volume(order::side::ask, 1180) << std::endl;

	return 0;
}
