// Copyright (C) 2025 Gabriel Domingues <gmd01bit@gmail.com>
// Linear-parse

#ifndef LINEAR_H_
#define LINEAR_H_

#include <array>
#include <cassert>
#include <cstdint>
#include <vector>

namespace linear {

struct item_t {
	uint8_t category;
	int64_t index;

	bool operator<=>(const item_t&) const noexcept = default;
};

using tape_t = std::vector<item_t>;

template <uint8_t A, uint8_t... Args>
struct index;

template <uint8_t A, uint8_t B, uint8_t... Args>
struct index<A, B, Args...> {
	static constexpr int64_t value =
		(A == B) ? 0 : 1 + index<A, Args...>::value;
};

template <uint8_t A>
struct index<A> {
	static constexpr int64_t value = -1;
};

template <uint8_t A, uint8_t... Args>
static constexpr int64_t index_v = index<A, Args...>::value;

template <uint8_t... Args>
struct delim_t {
	using array_t = std::array<int64_t, sizeof...(Args) + 1>;
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
	void open(tape_t& tape) {
		tape.push_back({A, get<A>()});
		get<A>() = tape.size() - 1;
	}

	template <uint8_t A>
	void close(tape_t& tape) {
		assert(balanced<A>());
		auto mark = tape[get<A>()].index;
		tape[get<A>()].index = tape.size();
		get<A>() = mark;
	}
};

tape_t parse(const char* text);

}; // namespace linear

#endif
