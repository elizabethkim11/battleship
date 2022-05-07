//
//  Board.h
//  cs32proj3
//
//  Created by Elizabeth Kim on 5/4/22.
//

#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include "globals.h"

class Game;
class BoardImpl;

class Board
{
public:
    Board(const Game& g);
    ~Board();
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;
private:
    BoardImpl* m_impl;
};

#endif /* BOARD_INCLUDED */
