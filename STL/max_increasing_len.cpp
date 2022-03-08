template<class It>
size_t max_increasing_len(It p, It q)
{
	if (p == q)
	{
		return 0;
	}

	size_t result = 1;
	size_t maxResult = 1;
	It p_prev = p;

	for (p++; p != q; p++)
	{
		if (*p_prev < *p)
		{
			result++;
		}
		else
		{
			if (maxResult < result)
			{
				maxResult = result;
			}
			result = 1;
		}
		p_prev++;
	}

	if (maxResult < result)
	{
		maxResult = result;
	}

	return maxResult;
}