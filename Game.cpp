//
//  Game.cpp
//  cs32proj3
//
//  Created by Elizabeth Kim on 5/4/22.
//

#include <iostream>
#include "globals.h"
#include "Game.h"

using namespace std;

class GameImpl
{
public:
    GameImpl(int nRows, int nCols);
    ~GameImpl();
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
    int m_rows;
    int m_cols;
    struct Ship {
        
    }
};

//Construct a game with the indicated number of rows and columns, which must not
//exceed MAXROWS and MAXCOLS (defined in globals.h), respectively.
GameImpl::GameImpl(int nRows, int nCols)
: m_rows(nRows), m_cols(nCols) {
}

// Return the number of rows in the game board.
int GameImpl::rows() const {
    return m_rows;
}

// Return the number of columns in the game board.
int GameImpl::cols() const {
    return m_cols;
}

// Return true if and only if the point denotes a position on the game board
bool GameImpl::isValid(Point p) const {
    
}

// Return a random point on the game board.
Point GameImpl::randomPoint() const {
    return Point(randInt(rows()), randInt(cols()));
}

// Add a new type of ship to the game. (Later, when play() is called, each player will place
//one of each type of ship on their board.) The ship has the indicated length, which must
//be positive and must allow the ship to fit on the board. When the board is displayed, the
//indicated symbol will be displayed in the positions occupied by that ship; that symbol
//must be a printable character other than X, o, and . (which are used for other purposes in
//the display), and must not be the same as for any other ship. (A printable character is one
//for which the <cctype> function isprint returns a non-zero value.) The indicated
//name is what will be used to denote the ship when writing messages. If g is a Game, the
//function might be called like this:
//g.addShip(5, 'A', "aircraft carrier")
//If the arguments in a call to addShip satisfy the constraints, the call results in a new ship
//type being added to the game, and the call returns true. Otherwise, a new ship type is not
//added, and the call returns false.
bool GameImpl::addShip(int length, char symbol, string name) {
    
}

/* Return the number of ship types in the game, which will be the number of times addShip
 was called returning true. The integers from 0 to nShips()−1 will be the ship IDs of the
 ships in the game, each one corresponding to the ship type added by one of the successful
 calls to addShip. Although each ship type's ship ID will be a distinct integer in the range
 0 to nShips()-1, it is not required that the first ship added have ship ID 0, the next 1, the
 next 2, etc. (although that may be what naturally happens with your implementation). */
int GameImpl::nShips() const {

}

//Return the number of positions occupied by the ship whose ID is shipId.
int GameImpl::shipLength(int shipId) const {

}

// Return the character that, when displaying a board, will be used to represent the ship
//whose ID is shipId.
char GameImpl::shipSymbol(int shipID) const {
    
}

// Return the string that, when writing messages, will be used to denote the ship whose ID is
//shipId.
string GameImpl::shipName(int shipID) const {
    
}

// check spec
Player* GameImpl::play(Player* p1, Player* p2, bool shouldPause) {
    
}
