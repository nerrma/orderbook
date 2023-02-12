#ifndef ORDERBOOK_H_
#define ORDERBOOK_H_

#include "order/order.hpp"
#include "pricebucket/pricebucket.hpp"
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

template<typename BucketAlgo = pricebucket::pricebucketmanager, order::side side = order::side::ask>
class book {
public:
	auto add_bucket(double const& level) -> bool {
		if (not algo_.find_bucket(level)) {
			algo_.add_level(level);
			return true;
		}

		return false;
	}

	auto begin() -> typename BucketAlgo::iterator {
		return algo_.begin();
	}

	auto end() -> typename BucketAlgo::iterator {
		return algo_.end();
	}

	auto get_bucket(double const& level) -> typename BucketAlgo::value_type& {
		return algo_.find_bucket(level);
	}

	auto add_order(order::order const& order) -> bool {
		return algo_.add_order(order.get_price(), order);
	}

	auto cancel_order(order::order const& order) -> bool {
		return algo_.cancel_order(order.get_price(), order);
	}

	[[nodiscard]] auto get_closest(double const& level) const -> double {
		return algo_.get_closest(level);
	}

	[[nodiscard]] auto get_volume(double const& price) const -> uint64_t {
		return algo_.get_volume(price);
	}

	[[nodiscard]] auto best_price() const -> double {
		if constexpr (side == order::side::ask) {
			return algo_.get_min();
		}
		else {
			return algo_.get_max();
		}
	}

	[[nodiscard]] auto get_data() const -> std::vector<typename BucketAlgo::data_type> {
		auto res = std::vector<typename BucketAlgo::data_type>();

		for (auto const& elem : algo_) {
			res.push_back(elem.get_data());
		}
		return res;
	}

private:
	BucketAlgo algo_;
};

template<typename BucketAlgo = pricebucket::pricebucketmanager>
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

	[[nodiscard]] auto get_data() const -> data_type {
		return std::make_pair(buy_book_.get_data(), sell_book_.get_data());
	}

	[[nodiscard]] auto get_volume(order::side const& side, double const& price) const -> uint64_t {
		if (side == order::side::ask) {
			return buy_book_.get_volume(price);
		}
		return sell_book_.get_volume(price);
	}

	auto match() -> void {
		for (auto& bucket : buy_book_) {
			auto cur_order = bucket.top();
			auto rem_units = cur_order.get_amt();

			auto& sell_bucket = sell_book_.get_bucket(bucket.get_level());
			while (rem_units > 0 && !sell_bucket.empty()) {
				auto sell_order = sell_bucket.top();
				if (sell_order.get_amt() > rem_units) {
					auto partial_order =
					   order::order(sell_order, sell_order.get_amt() - rem_units, std::time(nullptr));
					sell_bucket.add_order(partial_order);
				}

				rem_units -= std::min(rem_units, sell_order.get_amt());
				sell_bucket.pop();
			}

			bucket.pop();

			if (rem_units) {
				auto partial_order = order::order(cur_order, rem_units, std::time(nullptr));
				bucket.add_order(partial_order);
			}
		}
	}

private:
	book<BucketAlgo, order::side::bid> buy_book_;
	book<BucketAlgo, order::side::ask> sell_book_;
};

#endif // ORDERBOOK_H_
