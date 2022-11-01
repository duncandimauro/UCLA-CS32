void removeBad(list<Movie*>& li)
{
	for (list<Movie*>::iterator it = li.begin(); it != li.end();) //loop through the list
	{
		if ((*it)->rating() < 50)
		{
			delete* it;
			it = li.erase(it); //delete the pointer in the list & move "it" to next item
		}
		else
		{
			it++;
		}
	}
}