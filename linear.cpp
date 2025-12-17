// Copyright (C) 2025 Gabriel Domingues <gmd01bit@gmail.com>
// Linear-parse

#include "linear.hpp"

namespace linear {

tape_t parse(const char* text) {
	tape_t tape{};
	delim_t<'(', '[', '{'> delim{};

	for (;; ++text)
		switch (*text) {
		case '(': delim.open<'('>(tape); break;
		case '[': delim.open<'['>(tape); break;
		case '{': delim.open<'{'>(tape); break;
		case ')': delim.close<'('>(tape); break;
		case ']': delim.close<'['>(tape); break;
		case '}': delim.close<'{'>(tape); break;
		default: break;
		case '\0': goto exit;
		}
exit:
	return tape;
}

}; // namespace linear
