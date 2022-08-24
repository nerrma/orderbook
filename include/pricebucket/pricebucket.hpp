#ifndef PRICEBUCKET_H_
#define PRICEBUCKET_H_

#include "order/order.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <iterator>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>
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

		[[nodiscard]] auto get_data() const -> std::vector<order::order_data> {
			auto res = std::vector<order::order_data>();

			for (auto const& e : orders_) {
				res.push_back(e.get_data());
			}

			return res;
		}

		[[nodiscard]] auto volume() const -> uint64_t {
			auto res = uint64_t{};
			for (auto const& e : orders_) {
				res += e.get_amt();
			}

			return res;
		}

	private:
		std::deque<order::order> orders_;
	};

	class pricebucketmanager {
	public:
		using data_type = std::vector<order::order_data>;
		using value_type = pricebucket;

		class iterator_impl {
			using map_it = std::unordered_map<double, pricebucket>::iterator;

			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = pricebucket;
			using reference = value_type&;
			using pointer = value_type*;

		public:
			explicit iterator_impl(map_it it)
			: curr_{it} {}

			auto operator*() const -> reference {
				return curr_->second;
			}

			auto operator->() const -> pointer {
				return &(curr_->second);
			}

			auto operator++() -> iterator_impl& {
				curr_++;
				return *this;
			}

			auto operator==(iterator_impl const& other) -> bool {
				return curr_ == other.curr_;
			}

		private:
			map_it curr_;
		};

		class const_iterator_impl {
			using map_it = std::unordered_map<double, pricebucket>::const_iterator;

			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = pricebucket;
			using reference = value_type;

		public:
			explicit const_iterator_impl(map_it it)
			: curr_{it} {}

			auto operator*() const -> reference {
				return curr_->second;
			}

			auto operator++() -> const_iterator_impl& {
				curr_++;
				return *this;
			}

			auto operator==(const_iterator_impl const& other) -> bool {
				return curr_ == other.curr_;
			}

		private:
			map_it curr_;
		};

		using iterator = iterator_impl;
		using const_iterator = const_iterator_impl;

		auto begin() -> iterator {
			return iterator(buckets_.begin());
		}

		auto end() -> iterator {
			return iterator(buckets_.end());
		}

		auto begin() const -> const_iterator {
			return const_iterator(buckets_.begin());
		}

		auto end() const -> const_iterator {
			return const_iterator(buckets_.end());
		}

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
			if (not buckets_.contains(level)) {
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
			return std::max(buckets_.begin(),
			                buckets_.end(),
			                [](auto const& e1, auto const& e2) { return e1->first > e2->first; })
			   ->first;
		}

	private:
		std::unordered_map<double, pricebucket> buckets_;
	};
} // namespace pricebucket

#endif // PRICEBUCKET_H_
