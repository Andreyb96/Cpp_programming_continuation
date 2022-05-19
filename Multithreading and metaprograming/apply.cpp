#include <iostream>
#include <tuple>

template <typename F, typename T, int... Is>
auto apply(F f, T&& t, IntList<Is...>) -> decltype(f(std::get<Is>(t)...))
{
    return f(std::get<Is>(t)...);
}

template <typename F, typename... T,
    typename Index = typename Generate<sizeof...(T)>::type>
auto apply(F f, const std::tuple<T...>& t) -> decltype(apply(f, t, Index()))
{
    return apply(f, t, Index());
}