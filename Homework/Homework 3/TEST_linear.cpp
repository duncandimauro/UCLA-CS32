//TESTp2.cpp

#include <iostream>
#include <string>
using namespace std;

bool somePredicate(double test)
{
	if (test > 10)
	{
		return true;
	}
	return false;

}

// Return true if the somePredicate function returns false for at
// least one of the array elements, false otherwise.
bool anyFalse(const double a[], int n)
{
	if (n <= 0)
	{
		return false;
	}
	if (!somePredicate(*a))
	{
		return true;
	}

	return anyFalse(a + 1, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
	if (n <= 0)
	{
		return 0;
	}

	if (!somePredicate(*a))
	{
		return 1 + countFalse(a + 1, n - 1);
	}
	else
	{
		return countFalse(a + 1, n - 1);
	}

}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}
	if (somePredicate(*a))
	{
		return 0;
	}
	else if (firstTrue(a + 1, n - 1) == -1)
	{
		return -1;
	}
	else
	{
		return 1 + firstTrue(a + 1, n - 1);
	}
}

// Return the subscript of the largest element in the array (i.e.,
// return the smallest subscript m such that a[m] >= a[k] for all
// k such that k >= 0 and k < n).  If there is no such subscript,
// return -1.
int locateMax(const double a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}

	if (a[0] >= a[n-1]) //if the 1st element is greater or equal to the last
	{
		if (locateMax(a, n - 1) == -1)
		{
			return 0; //if we've gone through the array, return subscript of the final element left
		}
		else
		{
			return 0 + locateMax(a, n-1); //otherwise delete the last element and loop
		}
	}
	else //if 1st element is not greater or equal to last, remove first element
	{
		if (locateMax(a, n - 1) == -1) //check if we are now on our final element
		{
			return 1; //return the subscript of the final element
		}
		else 
		{
			return 1 + locateMax(a + 1, n-1);
		}	
	}
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not contain
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool contains(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0) //if all elements of a2 have been deleted
	{
		return true;
	}
	else if (n1 <= 0) //if all elements of a1 have been deleted but not all elements of a2
	{
		return false;
	}

	if (a2[0] != a1[0]) //if first element of a2 does not equal first of a1
	{
		return contains(a1 + 1, n1 - 1, a2, n2); //remove first element of a1 and loop
	}
	else //if first element of a1 does indeed equal the first of a2
	{
		return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	}
}

int main()
{
	double yee[] = { 20, 1, 29, 1, 20, 21 };

	bool test = anyFalse(yee, 6);

	cout << test;

	int meme = countFalse(yee, 6);

	cout << endl << meme << endl;

	cout << firstTrue(yee, 6) << endl;

	int legend = locateMax(yee, 6);

	cout << "locate Max: " << legend << endl;

	double a1[] = { 10, 50, 40, 20, 50, 40, 30 };

	double a2[] = { 50, 40, 20 };

	cout << contains(a1, 7, a2, 3);
}