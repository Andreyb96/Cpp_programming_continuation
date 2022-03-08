template<class T>
bool isSameObject(T const * p, T const * q)
{
	return dynamic_cast<void const *>(p) == dynamic_cast<void const *>(q);
}