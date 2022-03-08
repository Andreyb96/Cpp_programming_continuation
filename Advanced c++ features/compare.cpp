template<typename A, typename B>
bool compare(A const& a1, A const& a2, B(A::*Meth)() const)
{
	return (a1.*Meth)() < (a2.*Meth)();
}