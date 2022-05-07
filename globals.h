//
//  globals.h
//  cs32proj3
//
//  Created by Elizabeth Kim on 5/4/22.
//

#ifndef GLOBALS_INCLUDED
#define GLOBALS_INCLUDED

#include <random>

const int MAXROWS = 10;
const int MAXCOLS = 10;

enum Direction {
 HORIZONTAL, VERTICAL
};

class Point
{
 public:
 Point() : r(0), c(0) {}
 Point(int rr, int cc) : r(rr), c(cc) {}
 int r;
 int c;
};

inline int randInt(int limit)
{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<> distro(0, limit-1);
    return distro(generator);
}


#endif /* GLOBALS_INCLUDED */
