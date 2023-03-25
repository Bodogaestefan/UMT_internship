#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#pragma warning (disable : 4996)

using namespace std;

ifstream inputFile;

int nrRect;//this variable holds the final answer
int nrP; // number of points
bool flag=true; // This flag is used to parse the input string correctly into x and y coordinates

//structure used to store the points from the input string 
struct point {
    float x;
    float y;
}points[100];

//check if the line ab is parallel with the Ox axis (used to make sure that the rectangle is parallel with the origin axis)
bool checkSlope(point a, point b) { 
    if ((b.y - a.y) / (b.x - a.x) == 0)
        return true;
    return false;
}

//calculates the distance between two points
float calcDist(point a, point b) {
    return sqrt((b.y - a.y) * (b.y - a.y) + (b.x - a.x) * (b.x - a.x));
}

bool checkRect(point a, point b, point c, point d) {
    int slopes = 0;
    if (calcDist(a, b) == calcDist(c, d) && calcDist(a, c) == calcDist(b, d) && calcDist(a, d) == calcDist(b, c)) { // if the distances between all non adjacent lines are equal (including the diagonals) then we are sure the points form a rectangle
        if (checkSlope(a, b))
            slopes++;
        if (checkSlope(a, c))  //we check that exactly 2 lines are parallel to the OX axis, this way we make sure the rectangle is parallel to the two axis
            slopes++;
        if (checkSlope(a, d))
            slopes++;
        if (checkSlope(b, c))
            slopes++;
        if (checkSlope(b, d))
            slopes++;
        if (checkSlope(c, d))
            slopes++;
        if (slopes == 2)
            return true;
    }
    return false;
}


//We parse the input string and fill the array of points with the coordinates of every point in our input
void parseInput(char s[]) { 
    char* p;
    p = strtok(s, ",() ");
    while (p)
    {
        if (flag==true)
        {
            points[nrP].x = atof(p);
            flag = false;
        }
        else
        {
            points[nrP].y = atof(p);
            nrP++;
            flag = true;
        }
        p = strtok(NULL, ",() ");
    }
}

int main()
{
    inputFile.open("input.txt");
    char line[100];
    inputFile.getline(line, 100);
    parseInput(line);
    for (int i = 0; i < nrP - 3; i++) { // We take every combination of 4 points and check if it is a rectangle, then we increment the nrRect counter.
        for (int j = i+1; j < nrP - 2; j++) {
            for (int k=j+1; k < nrP - 1; k++) {
                for (int l = k+1; l < nrP; l++) {
                    if (checkRect(points[i], points[j], points[k], points[l])) {
                        nrRect++;
                    }
                }
            }
        }
            
    }
    cout << nrRect;
    
}