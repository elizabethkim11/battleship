//
//  Game.h
//  cs32proj3
//
//  Created by Elizabeth Kim on 5/4/22.
//

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <iostream>

using namespace std;

class Player;
class Point;

class Game
{
public:
    Game(int nRows, int nCols);
    ~Game();
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const;
    Player* play(Player* p1, Player* p2, bool shouldPause = true);
private:
    GameImpl* m_impl;
};

#endif /* GAME_INCLUDED */
