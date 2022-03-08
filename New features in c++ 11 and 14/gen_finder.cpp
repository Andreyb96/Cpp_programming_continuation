#include <algorithm>

auto gen_finder = [](int *inner, int *innerBorder) {
	return [inner, innerBorder](int innerValue) -> bool {
		return std::find(inner, innerBorder, innerValue) != innerBorder;
	};
};