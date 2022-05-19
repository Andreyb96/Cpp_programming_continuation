template <int ... T>
struct IntList;

template<int H, int ... T>
struct IntList<H, T...>
{
	static const int Head = H;
	using Tail = IntList<T...>;
};

template<>
struct IntList<>
{};