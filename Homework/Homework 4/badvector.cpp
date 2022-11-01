void removeBad(vector<Movie*>& v)
{
	for (vector<Movie*>::iterator it = v.begin(); it != v.end();) //loop through the vector
	{
		if ((*it)->rating() < 50)
		{
			delete* it;
			it = v.erase(it); //delete the pointer in the vector & move "it" to next item
		}
		else
		{
			it++;
		}
	}
}