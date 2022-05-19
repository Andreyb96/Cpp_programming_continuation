template<typename IL>
struct Length
{
	static int const value = 1 + Length<typename IL::Tail>::value;
};

template<>
struct Length<IntList<>>
{
	static int const value = 0;
};