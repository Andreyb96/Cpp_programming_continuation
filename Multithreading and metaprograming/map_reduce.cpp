#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>

template <typename It, typename UnOp, typename BinOp>
auto process(It begin, It end, UnOp f1, BinOp f2)
-> decltype(f2(f1(*begin), f1(*begin)))
{
    auto res = f1(*begin);

    while (++begin != end) {
        res = f2(res, f1(*begin));
    }

    return res;
}

template <typename It, typename UnOp, typename BinOp>
auto map_reduce(It begin, It end, UnOp f1, BinOp f2, std::size_t threads)
-> decltype(f2(f1(*begin), f1(*begin)))
{
    using Type = decltype(process(begin, end, f1, f2));
    auto it_offset = std::distance(begin, end) / threads;
    std::vector<std::future<Type>> v;
    It cur_begin = begin;
    It cur_end = (threads > 1) ? std::next(cur_begin, it_offset) : end;

    for (auto i = 0; i < threads; ++i) {
        v.emplace_back(std::async(std::launch::async, process<It, UnOp, BinOp>,
            cur_begin, cur_end, f1, f2));
        cur_begin = cur_end;
        cur_end = (i + 2 != threads) ? std::next(cur_begin, it_offset) : end;
    }

    Type res = process(v.begin(), v.end(),
        [](decltype(*v.begin()) f) { return f.get(); }, f2);

    return res;
}