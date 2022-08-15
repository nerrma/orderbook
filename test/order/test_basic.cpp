#include "order/order.hpp"

#include <catch2/catch.hpp>

TEST_CASE("basic operator test") {
	auto o1 = order::order(order::side::ask, 140, 10);
	auto o2 = order::order(order::side::ask, 180, 10);
	auto o3 = order::order(order::side::ask, 180, 20);

	CHECK(o1 == o1);

	CHECK(o1 < o2);
	CHECK(o2 < o3);
}

TEST_CASE("struct test") {
	auto o1 = order::order(order::side::ask, 140, 10);

	CHECK(o1.get_data() == order::order_data{order::side::ask, 140, 10});
}
