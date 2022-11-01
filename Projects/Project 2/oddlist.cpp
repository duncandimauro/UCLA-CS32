void removeOdd(list<int>& li)
{
	for (list<int>::iterator it = li.begin(); it != li.end();) //loop through the list
	{
		int temp = *it;
		if (temp % 2 != 0) //it will be odd
		{
			it = li.erase(it);
		}
		else
		{
			it++;
		}
	}
}