//utility.cpp

#include "utility.h"
#include "provided.h"

bool operator < (const AttValPair& lhs, const AttValPair& rhs)
{
	if (lhs.value < rhs.value)
	{
		return true;
	}
	return false;
}

bool operator > (const AttValPair& lhs, const AttValPair& rhs)
{
	if (lhs.value > rhs.value)
	{
		return true;
	}
	return false;
}

bool operator > (const EmailCount& lhs, const EmailCount& rhs)
{
	if (lhs.count > rhs.count)
	{
		return true;
	}
	else if (lhs.count == rhs.count)
	{
		if (lhs.email < rhs.email)
			return true;
	}
	return false;
}

bool operator < (const EmailCount& lhs, const EmailCount& rhs)
{
	if (lhs.count < rhs.count)
	{
		return true;
	}

	else if (lhs.count == rhs.count)
	{
		if (lhs.email > rhs.email)
			return true;
	}
	return false;
}

bool operator == (const EmailCount& lhs, const EmailCount& rhs)
{
	if ((lhs.count == rhs.count) && (lhs.email == rhs.email))
		return true;

	return false;
}