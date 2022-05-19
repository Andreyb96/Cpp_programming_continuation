#include <array>
#include <iostream>

template <int a, int b> struct Plus {
    static constexpr int value = a + b;
};

template <typename IL1, typename IL2, template <int, int> class Fun> struct Zip;

template <int... Vals1, int... Vals2, template <int, int> class Fun>
struct Zip<IntList<Vals1...>, IntList<Vals2...>, Fun> {
    using type = IntList<Fun<Vals1, Vals2>::value...>;
};

template <template <int...> class TL, int... Vals>
void print_int_list(TL<Vals...>&& tl)
{
    std::array<int, sizeof...(Vals)> a{ Vals... };

    std::cout << "IntList<";
    for (auto it = a.cbegin(); it != a.cend(); ++it) {
        std::cout << *it;

        if (std::next(it) != a.cend()) {
            std::cout << ", ";
        }
    }
    std::cout << ">" << std::endl;
}