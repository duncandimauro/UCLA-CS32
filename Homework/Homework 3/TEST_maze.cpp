// TESTp3.cpp

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{

    if ((sr == er) && (sc == ec))
        //If the current(r, c) coordinate is equal to the ending
        //coordinate, then we've solved the maze so return true!
    {
        return true;
    }

    maze[sr][sc] = 'O'; //starting location marked as visited

    if (maze[sr][sc - 1] == '.')
        //If you can move WEST and haven't encountered that cell yet
    {
        if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
            return true;
    }

    if (maze[sr + 1][sc] == '.')
        //If you can move SOUTH and haven't encountered that cell yet
    {
        if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
            return true;
    }

    if (maze[sr][sc + 1] == '.')
        //If you can move EAST and haven't encountered that cell yet
    {
        if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
            return true;
    }

    if (maze[sr - 1][sc] == '.')
        //If you can move NORTH and haven't encountered that cell yet
    {
        if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
            return true;
    }

    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X.X..X...X",
        "X....XXX.X",
        "X.XXXX.X.X",
        "X......XXX",
        "X.XX.X...X",
        "X.X..X.X.X",
        "X.X.XXXX.X",
        "X.X...X..X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10, 10, 4, 6, 1, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}