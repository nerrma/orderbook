#ifndef ORDERBOOK_H_
#define ORDERBOOK_H_

#include "order/order.hpp"
#include <cstdint>
#include <utility>
#include <vector>

template<typename BucketAlgo, order::side side>
class book {
public:
	auto add_bucket(uint64_t const& level) -> bool {
		if (not algo_.find_level(level)) {
			algo_.add_level(level);
		}
	}

	auto get_bucket(uint64_t const& level) -> typename BucketAlgo::value_type {
		return algo_.find_bucket(level);
	}

	auto add_order(order::order const& order) -> bool {
		return algo_.add_order(order.get_price(), order);
	}

	auto cancel_order(order::order const& order) -> bool {
		return algo_.cancel_order(order.get_price(), order);
	}

	auto get_volume(uint64_t const& price) -> uint64_t {
		auto level = algo_.find_bucket(price);
		return level.get_volume();
	}

	[[nodiscard]] auto best_price() const -> uint64_t {
		if constexpr (side == order::side::ask) {
			return algo_.get_min();
		}
		else {
			return algo_.get_max();
		}
	}

	[[nodiscard]] auto get_book_data() const -> std::vector<typename BucketAlgo::data_type> {
		auto res = std::vector<typename BucketAlgo::data_type>();

		for (auto elem : algo_) {
			res.push_back(elem.get_data());
		}

		return res;
	}

private:
	BucketAlgo algo_;
};

template<typename BucketAlgo>
class orderbook {
	using data_type =
	   std::pair<std::vector<typename BucketAlgo::data_type>, std::vector<typename BucketAlgo::data_type>>;

public:
	auto add_order(order::order const& order) -> bool {
		if (order.get_side() == order::side::ask) {
			return buy_book_.add_order(order);
		}
		return sell_book_.add_order(order);
	}

	auto cancel_order(order::order const& order) -> bool {
		if (order.get_side() == order::side::ask) {
			return buy_book_.cancel_order(order);
		}
		return sell_book_.cancel_order(order);
	}

	auto get_data() const -> data_type {
		return std::make_pair(buy_book_.get_data(), sell_book_.get_data());
	}

private:
	book<BucketAlgo, order::side::bid> buy_book_;
	book<BucketAlgo, order::side::ask> sell_book_;
};

#endif // ORDERBOOK_H_
