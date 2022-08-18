#ifndef ORDER_H_
#define ORDER_H_

#include <cstdint>
#include <string>
#include <sys/types.h>
#include <utility>

namespace order {
	enum side { bid, ask };

	struct order_data {
		uint32_t id;
		side order_side;
		uint64_t amt;
		double price;

		[[nodiscard]] auto operator==(order_data const& o) const {
			return order_side == o.order_side && amt == o.amt && price == o.price;
		};
	};

	class order {
	public:
		explicit order(u_int32_t const& id, side const& side, uint64_t const& amt, double const& price)
		: id_{id}
		, side_{side}
		, amt_{amt}
		, price_{price} {}

		order(order&& other) noexcept
		: id_{std::exchange(other.id_, {})}
		, side_{std::exchange(other.side_, {})}
		, amt_{std::exchange(other.amt_, {})}
		, price_{std::exchange(other.price_, {})} {}

		order(order const& other) = default;

		[[nodiscard]] auto get_data() const -> order_data {
			return order_data{id_, side_, amt_, price_};
		}

		[[nodiscard]] auto get_side() const -> side {
			return side_;
		}

		[[nodiscard]] auto get_price() const -> double {
			return price_;
		}

		auto operator<=>(const order& oth) const = default;

	private:
		uint32_t id_;
		side side_;
		uint64_t amt_;
		double price_;
	};
} // namespace order

#endif // ORDER_H_
