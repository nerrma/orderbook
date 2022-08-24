#include "order/order.hpp"
#include "orderbook/orderbook.hpp"

#include <catch2/catch.hpp>

TEST_CASE("basic volume test") {
	auto or1 = order::order(1, order::side::ask, 140, 10);

	auto obook = orderbook();

	obook.add_order(or1);

	CHECK(obook.get_volume(order::side::ask, 10) == 140);
}

TEST_CASE("basic cancel test") {
	auto or1 = order::order(1, order::side::ask, 140, 10);

	auto obook = orderbook();
	obook.add_order(or1);
	CHECK(obook.get_volume(order::side::ask, 10) == 140);

	obook.cancel_order(or1);
	CHECK(obook.get_volume(order::side::ask, 10) == 0);
}
