#ifndef ORDER_H_
#define ORDER_H_

#include <string>
#include <utility>

namespace order {
	enum side { bid, ask };

	struct order_data {
		side order_side;
		long long amt;
		double price;

		[[nodiscard]] auto operator==(order_data const& o) const {
			return order_side == o.order_side && amt == o.amt && price == o.price;
		};
	};

	class order {
	public:
		explicit order(side const& side, long long const& amt, double const& price)
		: side_{side}
		, amt_{amt}
		, price_{price} {}

		order(order&& other) noexcept
		: side_{std::exchange(other.side_, {})}
		, amt_{std::exchange(other.amt_, {})}
		, price_{std::exchange(other.price_, {})} {}

		order(order const& other) = default;

		[[nodiscard]] auto get_data() const -> order_data {
			return order_data{side_, amt_, price_};
		}

		auto operator<=>(const order& o) const = default;

	private:
		side side_;
		long long amt_;
		double price_;
	};
} // namespace order

#endif // ORDER_H_
