// mazequeue.cpp

#include <iostream>
#include <queue>
#include <string>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{

    queue<Coord> cQueue; //declaring a Queue of Coords

    //Push the starting coordinate (sr,sc) onto the coordinate queue and
    //update maze[sr][sc] to indicate that the algorithm has encountered
    //it(i.e., set maze[sr][sc] to have a value other than '.').

    cQueue.push(Coord(sr, sc));
    maze[sr][sc] = 'O';

    while (!cQueue.empty()) //While the stack is not empty
    {
        //Pop the front coordinate off the queue.This gives you the current
        //(r, c) location that your algorithm is exploring.

        int r = cQueue.front().r(); //getting r
        int c = cQueue.front().c(); //getting c

        //cout << "(" << r << "," << c << ") "; //This is for problem 4

        cQueue.pop(); //popping the front coordinate off the queue

        if ((r == er) && (c == ec))
            //If the current(r, c) coordinate is equal to the ending
            //coordinate, then we've solved the maze so return true!
        {
            return true;
        }

        //Check each place you can move from the current cell as follows :

        if (maze[r][c - 1] == '.')
            //If you can move WEST and haven't encountered that cell yet,
            //then push the coordinate(r, c - 1) onto the queue and update
            //maze[r][c - 1] to indicate the algorithm has encountered it.
        {
            cQueue.push(Coord(r, c - 1));
            maze[r][c - 1] = 'O';
        }

        if (maze[r + 1][c] == '.')
            //If you can move SOUTH and haven't encountered that cell yet,
            //then push the coordinate(r + 1, c) onto the queue and update
            //maze[r + 1][c] to indicate the algorithm has encountered it.
        {
            cQueue.push(Coord(r + 1, c));
            maze[r + 1][c] = 'O';
        }

        if (maze[r][c + 1] == '.')
            //If you can move EAST and haven't encountered that cell yet,
            //then push the coordinate(r, c + 1) onto the queue and update
            //maze[r][c + 1] to indicate the algorithm has encountered it.
        {
            cQueue.push(Coord(r, c + 1));
            maze[r][c + 1] = 'O';
        }

        if (maze[r - 1][c] == '.')
            //If you can move NORTH and haven't encountered that cell yet,
            //then push the coordinate(r - 1, c) onto the queue and update
            //maze[r - 1][c] to indicate the algorithm has encountered it.
        {
            cQueue.push(Coord(r - 1, c));
            maze[r - 1][c] = 'O';
        }

    }

    return false; //There was no solution, so return false

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