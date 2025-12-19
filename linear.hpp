// Copyright (C) 2025 Gabriel Domingues <gmd01bit@gmail.com>
// Linear-parse

#ifndef LINEAR_H_
#define LINEAR_H_

#include <array>
#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

namespace linear {

struct item_t {
	uint8_t category;
	int64_t index;

	bool operator<=>(const item_t&) const noexcept = default;
};

using tree_t = std::vector<item_t>;

struct tape_t {
	tree_t tree;
	std::string text;

	bool operator==(const tape_t&) const noexcept = default;
	bool operator!=(const tape_t&) const noexcept = default;
};

template <uint8_t A, uint8_t... Args>
struct index;

template <uint8_t A, uint8_t... Args>
struct index<A, A, Args...> {
	static constexpr int64_t value = 0;
};

template <uint8_t A, uint8_t B, uint8_t... Args>
struct index<A, B, Args...> {
	static constexpr int64_t value = 1 + index<A, Args...>::value;
};

template <uint8_t A>
struct index<A>;

template <uint8_t A, uint8_t... Args>
static constexpr int64_t index_v = index<A, Args...>::value;

template <uint8_t... Args>
struct delim_t {
	using array_t = std::array<int64_t, sizeof...(Args)>;
	array_t array_ = {0};

	delim_t() : array_{init()} {}

	static constexpr array_t init() {
		array_t a = {};
		for (auto& el : a)
			el = -1;
		return a;
	}

	template <uint8_t A>
	int64_t& get() {
		return array_[index_v<A, Args...>];
	}

	template <uint8_t A>
	const int64_t& get() const {
		return array_[index_v<A, Args...>];
	}

	template <uint8_t A>
	bool balanced() {
		int64_t v = get<A>();
		for (auto el : array_) {
			if (el > v) return false;
		}
		return true;
	}

	template <uint8_t A>
	void open(tree_t& tree) {
		tree.push_back({A, get<A>()});
		get<A>() = tree.size() - 1;
	}

	template <uint8_t A>
	void close(tree_t& tree) {
		assert(balanced<A>());
		auto mark = tree[get<A>()].index;
		tree[get<A>()].index = tree.size();
		get<A>() = mark;
	}
};

tape_t parse(const char* text);

}; // namespace linear

#endif
