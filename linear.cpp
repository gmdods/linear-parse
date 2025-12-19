// Copyright (C) 2025 Gabriel Domingues <gmd01bit@gmail.com>
// Linear-parse

#include "linear.hpp"
#include <cctype>
#include <cstdlib>
#include <unordered_map>

namespace linear {

int64_t unquote(const char* text, char** endptr, std::string& out) {
	static std::unordered_map<char, char> escapes = {
		{'"', '"'}, {'\\', '\\'}, {'n', '\n'}, {'t', '\t'}, {'r', '\r'},
	};
	int64_t index = out.size();
	assert(*text++ == '"');
	for (bool esc = false; (*text != '"' || esc) && *text != '\0';
		 esc = (*text++ == '\\') && !esc) {
		if (esc)
			out.back() = escapes.at(*text);
		else
			out.push_back(*text);
	}
	out.push_back('\0');
	if (endptr) *endptr = (char*) text;
	return index;
}

tape_t parse(const char* text) {
	tape_t tape{};
	delim_t<'(', '[', '{'> delim{};

	for (;; ++text)
		switch (*text) {
		case '(': delim.open<'('>(tape.tree); break;
		case '[': delim.open<'['>(tape.tree); break;
		case '{': delim.open<'{'>(tape.tree); break;
		case ')': delim.close<'('>(tape.tree); break;
		case ']': delim.close<'['>(tape.tree); break;
		case '}': delim.close<'{'>(tape.tree); break;
		case ' ':
		case '\t':
		case '\r':
		case '\n': break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': {
			char* end = nullptr;
			tape.tree.push_back({'0', std::strtol(text, &end, 10)});
			text = --end;
			break;
		}
		case '"': {
			char* end = nullptr;
			tape.tree.push_back({'"', unquote(text, &end, tape.text)});
			text = end;
			break;
		}
		default: break;
		case '\0': goto exit;
		}
exit:
	return tape;
}

}; // namespace linear
