#include <iostream>
#include <order/order.hpp>

auto main() -> int {
	auto o = order::order(order::side::ask, 140, 1180);
	auto i = order::order(std::move(o));

	auto d = o.get_data();

	std::cout << d.amt << std::endl;
	std::cout << d.price << std::endl;
	std::cout << d.order_side << std::endl;

	return 0;
}
