#include <array>
#include <iostream>

template <typename IL1, typename IL2, template <int, int> class Fun> struct Zip;

template <int... Vals1, int... Vals2, template <int, int> class Fun>
struct Zip<IntList<Vals1...>, IntList<Vals2...>, Fun> {
    using type = IntList<Fun<Vals1, Vals2>::value...>;
};

template <int a, int b> struct Plus {
    static constexpr int value = a + b;
};

template <int a, int b> struct Minus {
    static constexpr int value = a - b;
};

template <template <int...> class TL, int... Vals>
void print_int_list(TL<Vals...>&& tl)
{
    std::array<int, sizeof...(Vals)> a{ {Vals...} };

    std::cout << "IntList<";
    for (auto it = a.cbegin(); it != a.cend(); ++it) {
        std::cout << *it;

        if (std::next(it) != a.cend()) {
            std::cout << ", ";
        }
    }
    std::cout << ">" << std::endl;
}

template <int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0,
    int cd = 0>
using Dimension = IntList<m, kg, s, A, K, mol, cd>;

template <typename Dim> struct Quantity {
    Quantity() : value_{ 0 } {}
    explicit Quantity(double value) : value_{ value } {}

    ~Quantity() = default;

    Quantity(const Quantity& q) = default;
    Quantity& operator=(const Quantity& q) = default;

    double value() const noexcept { return value_; }

    Quantity& operator+=(const Quantity& rhs) noexcept
    {
        value_ += rhs.value_;

        return *this;
    }

    Quantity& operator-=(const Quantity& rhs) noexcept
    {
        value_ -= rhs.value_;

        return *this;
    }

    Quantity& operator+=(double rhs) noexcept
    {
        value_ += rhs;

        return *this;
    }

    Quantity& operator-=(double rhs) noexcept
    {
        value_ -= rhs;

        return *this;
    }

    Quantity& operator*=(double rhs) noexcept
    {
        value_ *= rhs;

        return *this;
    }

    Quantity& operator/=(double rhs)
    {
        value_ /= rhs;

        return *this;
    }

    template <typename T>
    friend Quantity operator+(Quantity lhs, const T& rhs) noexcept
    {
        lhs += rhs;
        return lhs;
    }

    friend Quantity operator+(double lhs, const Quantity& rhs) noexcept
    {
        Quantity tmp{ rhs };

        tmp += lhs;

        return tmp;
    }

    template <typename T>
    friend Quantity operator-(Quantity lhs, const T& rhs) noexcept
    {
        lhs -= rhs;
        return lhs;
    }

    friend Quantity operator-(double lhs, const Quantity& rhs) noexcept
    {
        Quantity tmp{ rhs };

        tmp -= lhs;

        return tmp;
    }

    friend Quantity operator*(Quantity lhs, double rhs) noexcept
    {
        lhs *= rhs;
        return lhs;
    }

    friend Quantity operator*(double lhs, const Quantity& rhs) noexcept
    {
        Quantity tmp{ rhs };
        tmp *= lhs;
        return tmp;
    }

    friend Quantity operator/(Quantity lhs, double rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    template <typename Dim2>
    using Product = typename Zip<Dim2, Dim, Plus>::type;

    template <typename Dim2>
    using Quotient = typename Zip<Dim2, Dim, Minus>::type;

    template <typename Dim2>
    friend Quantity<Product<Dim2>> operator*(const Quantity& q1,
        const Quantity<Dim2>& q2) noexcept
    {
        return Quantity<Product<Dim2>>{q1.value()* q2.value()};
    }

    friend Quantity<Quotient<Dimension<>>> operator/(double lhs,
        const Quantity& rhs)
    {
        Quantity<Quotient<Dimension<>>> tmp{ rhs.value() };
        tmp /= lhs;
        return tmp;
    }

    template <typename Dim2>
    friend Quantity<Quotient<Dim2>> operator/(const Quantity<Dim2>& q1,
        const Quantity& q2)
    {
        return Quantity<Quotient<Dim2>>{q1.value() / q2.value()};
    }

    void print_dim() const noexcept { print_int_list(Dim{}); }

private:
    double value_;
};