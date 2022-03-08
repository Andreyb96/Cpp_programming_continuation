Base const * D1BaseToD2Base(Base const * base)
{
	D1* d1_ptr = (D1*)base;
	D3* d3_ptr = static_cast<D3*>(d1_ptr);

	D2* d2_ptr = (D2*)d3_ptr;
	Base* base_ret = (Base*)d2_ptr;

	return base_ret;
}