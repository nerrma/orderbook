#ifndef PRICEBUCKET_H_
#define PRICEBUCKET_H_

#include "order/order.hpp"
#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <utility>
namespace pricebucket {
	class pricebucket {
	public:
		auto add_order(order::order const& order) -> void {
			if (auto val = std::find(orders_.begin(), orders_.end(), order); val == orders_.end()) {
				orders_.push_back(order);
			}
		}

		auto remove_order(order::order const& order) -> void {
			if (auto val = std::find(orders_.begin(), orders_.end(), order); val != orders_.end()) {
				orders_.erase(val);
			}
		}

		[[nodiscard]] auto volume() const -> uint64_t {
			auto res = uint64_t{};
			for (auto e : orders_) {
				res += e.get_amt();
			}

			return res;
		}

	private:
		std::deque<order::order> orders_;
	};
	class pricebucketmanager {
	public:
		using value_type = pricebucket;

		struct data_type {};

		using data_type = data_type;

		auto find_bucket(double const& level) const -> pricebucket {
			if (auto bck = buckets_.find(level); bck != buckets_.end()) {
				return bck->second;
			}

			return {};
		}

		auto add_level(double const& level) -> bool {
			if (buckets_.contains(level)) {
				return false;
			}
			buckets_[level] = pricebucket();
			return true;
		}

		auto add_order(double const& level, order::order const& order) -> bool {
			if (not buckets_.contains(level)) {
				add_level(level);
			}

			buckets_[level].add_order(order);
			return true;
		}

		auto cancel_order(double const& level, order::order const& order) -> bool {
			if (buckets_.contains(level)) {
				return false;
			}

			buckets_[level].remove_order(order);
			return true;
		}

		auto get_volume(double const& level) const -> uint64_t {
			if (not buckets_.contains(level)) {
				return 0;
			}
			return buckets_.at(level).volume();
		}

		auto get_min() const -> double {
			return std::min(buckets_.begin(),
			                buckets_.end(),
			                [](auto const& e1, auto const& e2) { return e1->first < e2->first; })
			   ->first;
		}

		auto get_max() const -> double {
			return std::min(buckets_.begin(),
			                buckets_.end(),
			                [](auto const& e1, auto const& e2) { return e1->first > e2->first; })
			   ->first;
		}

	private:
		std::unordered_map<double, pricebucket> buckets_;
	};
} // namespace pricebucket

#endif // PRICEBUCKET_H_
