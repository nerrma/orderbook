# Orderbook

A limit orderbook implementation in C++.

## What is a orderbook?

An orderbook should store orders to purchase a stock and match them with orders to sell a stock in terms of quantity and price. A limit orderbook allows market participants to place orders with a certain *limit* price, in which this is the highest price they will buy a stock and lowest they will sell it. We can therefore approximately match these orders to allow for more favourable outcomes for the market participants.

## How does it work?

Disregarding networking for now, we want to store the orders for a certain price and match incoming orders accordingly. This can be done by using a red-black tree (for fast searching) to store the price levels, keeping the actual prices as a float for accurate matching. We can simply use the C++ `std::map`, which models uses a red-black tree to manage O(logn) lookups.

We also want to match orders accordingly. This can be done naively by storing a FIFO, queue at each price level and matching the oldest orders first.

### Project structure

#### order.hpp
Essentially just a dataclass to store order details, includes:
- id - as an order id
- side - bid/ask
- amount - number of securities
- price - price level of order

#### pricebucket.hpp
A price-bucket/level storing orders at that level.

Includes a generic manager as an abstraction of adding and removing from a set of pricebuckets. The manager has custom iterators to go over the buckets and retrieve their contents.

#### orderbook.hpp
Putting everything together, stores a pricebucket manager and an abstract interface to add and remove from the orderbook itself.
