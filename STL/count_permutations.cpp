#include <algorithm>
#include <vector>

template <typename Iterator>
std::size_t count_permutations(Iterator p, Iterator q)
{
    using ItType = typename std::iterator_traits<Iterator>::value_type;

    if (p == q) {
        return 1;
    }

    std::vector<ItType> v(p, q);
    std::sort(v.begin(), v.end());
    std::size_t perm_count = (std::adjacent_find(v.cbegin(), v.cend()) == v.cend());

    while (std::next_permutation(v.begin(), v.end())) {
        if (std::adjacent_find(v.cbegin(), v.cend()) == v.cend()) {
            ++perm_count;
        }
    }

    return perm_count;
}