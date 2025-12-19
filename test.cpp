// Copyright (C) 2025 Gabriel Domingues <gmd01bit@gmail.com>
// Linear-parse

#include "linear.hpp"

int main(void) {
	{ // balanced parentheses
		auto tape = linear::parse("{{(()[])}{}}");
		auto expect = linear::tape_t{
			{{'{', 6}, {'{', 5}, {'(', 5}, {'(', 4}, {'[', 5}, {'{', 6}},
			{},
		};
		assert(tape == expect);
	}

	{ // strings
		auto tape = linear::parse("[\"0\\\"1\\\\2\"]");
		auto expect = linear::tape_t{
			{
				{'[', 2},
				{'"', 0},
			},
			{"0\"1\\2\0", 6},
		};
		assert(tape == expect);
	}

	{ // lispy
		auto tape = linear::parse("{\"a\" 4 \"b\" [1 2]}");
		auto expect = linear::tape_t{
			{
				{'{', 7},
				{'"', 0},
				{'0', 4},
				{'"', 2},
				{'[', 7},
				{'0', 1},
				{'0', 2},
			},
			{"a\0b\0", 4},
		};
		assert(tape == expect);
	}

	return 0;
}
