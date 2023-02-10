#include "order/order.hpp"
#include "orderbook/orderbook.hpp"

#include <catch2/catch.hpp>

TEST_CASE("basic volume test") {
	auto or1 = order::order(1, order::side::ask, 140, 10, std::time(nullptr));

	auto obook = orderbook();

	obook.add_order(or1);

	CHECK(obook.get_volume(order::side::ask, 10) == 140);
}

TEST_CASE("basic cancel test") {
	auto or1 = order::order(1, order::side::ask, 140, 10, std::time(nullptr));

	auto obook = orderbook();
	obook.add_order(or1);
	CHECK(obook.get_volume(order::side::ask, 10) == 140);

	obook.cancel_order(or1);
	CHECK(obook.get_volume(order::side::ask, 10) == 0);
}

TEST_CASE("single full matching test") {
	auto ask = order::order(1, order::side::ask, 140, 10, std::time(nullptr));

	auto obook = orderbook();
	obook.add_order(ask);

	auto bid = order::order(2, order::side::bid, 140, 10, std::time(nullptr));
	obook.add_order(bid);

	CHECK(obook.get_volume(order::side::ask, 10) == 140);
	obook.match();
	CHECK(obook.get_volume(order::side::ask, 10) == 0);
}

TEST_CASE("single partial matching test") {
	auto ask = order::order(1, order::side::ask, 140, 10, std::time(nullptr));

	auto obook = orderbook();
	obook.add_order(ask);

	auto bid = order::order(2, order::side::bid, 70, 10, std::time(nullptr));
	obook.add_order(bid);

	CHECK(obook.get_volume(order::side::ask, 10) == 140);
	obook.match();
	CHECK(obook.get_volume(order::side::ask, 10) == 70);
}

TEST_CASE("two asks, one bid fifo matching test") {
	auto ask = order::order(1, order::side::ask, 140, 10, std::time(nullptr));
	auto ask2 = order::order(2, order::side::ask, 140, 10, std::time(nullptr));

	auto obook = orderbook();
	obook.add_order(ask);
	obook.add_order(ask2);

	auto bid = order::order(3, order::side::bid, 140, 10, std::time(nullptr));
	obook.add_order(bid);

	CHECK(obook.get_volume(order::side::ask, 10) == 280);
	obook.match();
	CHECK(obook.get_volume(order::side::ask, 10) == 140);

	auto [buy_book, sell_book] = obook.get_data();
	CHECK(buy_book.size() == 1);
	CHECK(buy_book[0].size() == 1);
	CHECK(buy_book[0][0] == ask2.get_data());
}

TEST_CASE("two asks, one bid partial matching test") {
	auto ask = order::order(1, order::side::ask, 100, 10, std::time(nullptr));
	auto ask2 = order::order(2, order::side::ask, 30, 10, std::time(nullptr));

	auto obook = orderbook();
	obook.add_order(ask);
	obook.add_order(ask2);

	auto bid = order::order(3, order::side::bid, 140, 10, std::time(nullptr));
	obook.add_order(bid);

	CHECK(obook.get_volume(order::side::ask, 10) == 130);
	obook.match();
	CHECK(obook.get_volume(order::side::ask, 10) == 30);
	CHECK(obook.get_volume(order::side::bid, 10) == 40);
	obook.match();
	CHECK(obook.get_volume(order::side::ask, 10) == 0);
	CHECK(obook.get_volume(order::side::bid, 10) == 10);
}
