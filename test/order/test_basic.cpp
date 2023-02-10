#include "order/order.hpp"

#include <catch2/catch.hpp>

TEST_CASE("basic operator test") {
	auto o1 = order::order(1, order::side::ask, 140, 10, std::time(nullptr));
	auto o2 = order::order(2, order::side::ask, 180, 10, std::time(nullptr));
	auto o3 = order::order(3, order::side::ask, 180, 20, std::time(nullptr));

	CHECK(o1 == o1);

	CHECK(o1 < o2);
	CHECK(o2 < o3);
}

TEST_CASE("struct test") {
	auto start_time = std::time(nullptr);
	auto o1 = order::order(1, order::side::ask, 140, 10, start_time);

	CHECK(o1.get_data() == order::order_data{1, order::side::ask, 140, 10, start_time});
}
