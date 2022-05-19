#include <typeinfo>
#include <typeindex>
#include <map>
#include <functional>

template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    std::map<std::pair<size_t, size_t>, std::function<Result(Base*, Base*)>> functions;

    void addImpl(std::type_info const& t1, std::type_info const& t2, std::function<Result(Base*, Base*)> f)
    {
        functions.insert(std::make_pair(std::make_pair(t1.hash_code(), t2.hash_code()), f));
    }

    bool hasImpl(Base* a, Base* b) const
    {
        auto res = functions.find(std::make_pair(typeid(*a).hash_code(), typeid(*b).hash_code()));

        if (Commutative && res == functions.end())
        {
            auto sRes = functions.find(std::make_pair(typeid(*b).hash_code(), typeid(*a).hash_code()));

            if (sRes != functions.end())
                return true;
            else
                return false;
        }
        return res != functions.end();
    }

    Result call(Base* a, Base* b) const
    {
        auto res = functions.find(std::make_pair(typeid(*a).hash_code(), typeid(*b).hash_code()));

        if (res == functions.end() && Commutative)
        {
            auto sRes = functions.find(std::make_pair(typeid(*b).hash_code(), typeid(*a).hash_code()));

            return sRes->second(b, a);
        }
        return res->second(a, b);
    }
};