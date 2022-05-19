template <int value, class IL>
struct IntCons {};

template <int value, int... primes>
struct IntCons<value, IntList<primes...>>
{
	using type = IntList<value, primes...>;
};

template <typename IL1, typename IL2>
struct Concat;

template <int... IL1, int... IL2>
struct Concat<IntList<IL1...>, IntList<IL2...>>
{
	using type = IntList<IL1..., IL2...>;
};

template <int N, class Collection = IntList<>>
struct Generate
{
	static const int Length = N;
	using type = typename Concat<typename Generate<N - 1>::type, IntList<Generate<N - 1>::Length>>::type;
};

template<>
struct Generate<0>
{
	static const int Length = 0;
	using type = IntList<>;
};