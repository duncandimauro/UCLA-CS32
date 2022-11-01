void removeOdd(vector<int>& v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end();) //loop through the vector
	{
		int temp = *it;
		if (temp % 2 != 0) //it will be odd
		{
			it = v.erase(it);
		}
		else
		{
			it++;
		}
	}
}