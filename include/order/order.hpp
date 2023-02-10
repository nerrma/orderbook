#ifndef ORDER_H_
#define ORDER_H_

#include <cstdint>
#include <ctime>
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
		time_t time;

		[[nodiscard]] auto operator==(order_data const& o) const {
			return order_side == o.order_side && amt == o.amt && price == o.price && time == o.time;
		};
	};

	class order {
	public:
		explicit order(u_int32_t const& id,
		               side const& side,
		               uint64_t const& amt,
		               double const& price,
		               time_t const& time)
		: id_{id}
		, side_{side}
		, amt_{amt}
		, price_{price}
		, time_{time} {}

		order(order const& other) = default;

		order(order const& other, uint64_t const& amt, time_t const& time)
		: amt_{amt}
		, time_{time} {}

		[[nodiscard]] auto get_data() const -> order_data {
			return order_data{id_, side_, amt_, price_, time_};
		}

		[[nodiscard]] auto get_side() const -> side {
			return side_;
		}

		[[nodiscard]] auto get_price() const -> double {
			return price_;
		}

		[[nodiscard]] auto get_amt() const -> uint64_t {
			return amt_;
		}

		[[nodiscard]] auto get_time() const -> uint64_t {
			return time_;
		}

		auto operator<=>(const order& oth) const = default;

	private:
		uint32_t id_;
		side side_;
		uint64_t amt_;
		double price_;
		time_t time_;
	};
} // namespace order

#endif // ORDER_H_
