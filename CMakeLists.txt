cmake_minimum_required(VERSION 3.23.1)

project(orderbook)

set(SOURCE_FILES main/Orderbook.cpp main/Orderbook.hpp main/Order.hpp main/Pricebucket.hpp)

add_executable(${PROJECT_NAME} SOURCE_FILES)
