// History.cpp

#include <iostream>

#include "History.h"
#include "globals.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  History implementations
///////////////////////////////////////////////////////////////////////////

History::History(int nRows, int nCols)
	: m_rows(nRows), m_cols(nCols)
{
    for (int r = 1; r <= nRows; r++)
    {
        for (int c = 1; c <= nCols; c++)
        {
            map[r-1][c-1] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if (r > m_rows || r < 1 || c > m_cols || c < 1)
        return false;
    else
    {
        map[r - 1][c - 1] += 1;
        return true;
    }
}

void History::display() const
{

    // Draw the grid
    clearScreen();
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            if (map[r][c] == 0)
            {
                cout << '.';
            }
            else if (map[r][c] >= 26)
            {
                cout << 'Z';
            }
            else
            {
                char amtAttacked = map[r][c] + 64;
                cout << amtAttacked;
            }
        }
        cout << endl;
    }
    cout << endl;
}