#include <algorithm>

template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
    return std::remove_if(p, q, [&n](decltype(*p) val) { return n-- == 0; });
}