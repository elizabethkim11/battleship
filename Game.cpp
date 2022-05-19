//
//  Game.cpp
//  cs32proj3
//
//  Created by Elizabeth Kim on 5/4/22.
//

#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>

using namespace std;

class GameImpl
{
  public:
    GameImpl(int nRows, int nCols);
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const;
    Player* play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);
private:
    int m_rows;
    int m_cols;
    struct Ship {
        int m_length;
        char m_symbol;
        string m_name;
        Ship(int length, char symbol, string name)
        : m_length(length), m_symbol(symbol), m_name(name) {
        }
    };
    vector<Ship> m_ship;
};

void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

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
    return p.r >= 0  &&  p.r < rows()  &&  p.c >= 0  &&  p.c < cols();
}

// Return a random point on the game board.
Point GameImpl::randomPoint() const {
    return Point(randInt(rows()), randInt(cols()));
}

bool GameImpl::addShip(int length, char symbol, string name) {
    Ship newShip{length, symbol, name};
    m_ship.push_back(newShip);
    return true;
}

int GameImpl::nShips() const {
    return m_ship.size();
}

//Return the number of positions occupied by the ship whose ID is shipId.
int GameImpl::shipLength(int shipId) const {
    return m_ship[shipId].m_length;
}

// Return the character that, when displaying a board, will be used to represent the ship
//whose ID is shipId.
char GameImpl::shipSymbol(int shipId) const {
    return m_ship[shipId].m_symbol;
}

// Return the string that, when writing messages, will be used to denote the ship whose ID is
//shipId.
string GameImpl::shipName(int shipId) const {
    return m_ship[shipId].m_name;
}

Player* GameImpl::play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause) {
    if (!p1->placeShips(b1) || !p2->placeShips(b2)) {
        return nullptr;
    }
    bool player1turn = true;
    Player *firstTurn, *opponent;
    Board* boardToAttack;
    while (!b1.allShipsDestroyed() && !b2.allShipsDestroyed()) {
        bool hit = false;
        bool destroyed = false;
        bool validShot = false;
        int shipId = 0;
        if (player1turn) {
            firstTurn = p1;
            opponent = p2;
            boardToAttack = &b2;
        }
        else {
            firstTurn = p2;
            opponent = p1;
            boardToAttack = &b1;
        }
        cout << firstTurn->name() << "'s turn. Board for " << opponent->name() << ":" << endl;
        boardToAttack->display(firstTurn->isHuman());
        Point attemptedAttack = firstTurn->recommendAttack();
        firstTurn->recordAttackResult(attemptedAttack, validShot, hit, destroyed, shipId);
        validShot = boardToAttack->attack(attemptedAttack, hit, destroyed, shipId);
            if (!validShot) {
                cout << firstTurn->name() << " wasted a shot at (" << attemptedAttack.r << "," << attemptedAttack.c << ")." << endl;
                firstTurn->recordAttackResult(attemptedAttack, false, false, false, shipId);
                opponent->recordAttackByOpponent(attemptedAttack);
            }
            else
            {
                cout << firstTurn->name() << " attacked (" << attemptedAttack.r << "," << attemptedAttack.c << ") and ";
                if (hit && !destroyed)
                    cout << "hit something";
                else if (hit && destroyed)
                    cout << "destroyed the " << this->shipName(shipId);
                else
                    cout << "missed";
                cout <<", resulting in:" << endl;
                boardToAttack->display(firstTurn->isHuman());
                firstTurn->recordAttackResult(attemptedAttack, true, hit, destroyed, shipId);
                firstTurn->recordAttackByOpponent(attemptedAttack);
            }
        player1turn = !player1turn;
        if (b1.allShipsDestroyed() || b2.allShipsDestroyed()) {
            break;
        }
        if (shouldPause) {
            waitForEnter();
        }
    }
    if (b2.allShipsDestroyed())
        firstTurn = p1;
    else if (b1.allShipsDestroyed())
        firstTurn = p2;
    cout << firstTurn->name() << " wins!" << endl;
    if (b2.allShipsDestroyed() && p1->isHuman()) {
        cout << "Here's where " << p2->name() << "'s ships were:" << endl;
        b2.display(false);
    }
    if (b1.allShipsDestroyed() && p2->isHuman()) {
        cout << "Here's where " << p1->name() << "'s ships were:" << endl;
        b1.display(false);
    }
    return firstTurn;
}

//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1  ||  nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1  ||  nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols);
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows()  &&  length > cols())
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
             << endl;
        return false;
    }
    if (!isascii(symbol)  ||  !isprint(symbol))
    {
        cout << "Unprintable character with decimal value " << symbol
             << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X'  ||  symbol == '.'  ||  symbol == 'o')
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
             << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
                 << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipName(shipId);
}

Player* Game::play(Player* p1, Player* p2, bool shouldPause)
{
    if (p1 == nullptr  ||  p2 == nullptr  ||  nShips() == 0)
        return nullptr;
    Board b1(*this);
    Board b2(*this);
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}
