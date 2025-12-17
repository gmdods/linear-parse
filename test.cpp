// Copyright (C) 2025 Gabriel Domingues <gmd01bit@gmail.com>
// Linear-parse

#include "linear.hpp"
#include <algorithm>

int main(void) {

	auto tape = linear::parse("{{(()[])}{}}");

	auto expect = linear::tape_t{
		{'{', 6}, {'{', 5}, {'(', 5}, {'(', 4}, {'[', 5}, {'{', 6},
	};
	assert(
		std::equal(tape.cbegin(), tape.cend(), expect.cbegin(), expect.cend()));

	return 0;
}
