//
//  Board.cpp
//  cs32proj3
//
//  Created by Elizabeth Kim on 5/4/22.
//

#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <vector>

using namespace std;

class BoardImpl
{
  public:
    BoardImpl(const Game& g);
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;
private:
    const Game& m_game;
    char m_board[MAXROWS][MAXCOLS];
    struct Ship {
        int shipId;
        char shipSymbol;
        int shipHealth;
        Point topOrLeft;
        Direction dir;
    };
    vector<Ship> m_ship;
};

/* Initialize a board. The parameter g refers to the game the board is being used in. Board
 member functions that need to know the number of rows or columns or the characteristics
 of ships will presumably ask the game object the board was constructed with. */
BoardImpl::BoardImpl(const Game& g)
: m_game(g) {
    for (int r = 0; r < g.rows(); r++) {
        for (int c = 0; c < g.cols(); c++) {
            m_board[r][c] = '.';
        }
    }
}

/* This function clears the board so it is empty, ready to be populated with ships. */
void BoardImpl::clear() {
    for (int r = 0; r < m_game.rows(); r++) {
        for (int c = 0; c < m_game.cols(); c++) {
            m_board[r][c] = '.';
        }
    }
}

void BoardImpl::block() {
    Point p;
    int boardArea = m_game.rows()*m_game.cols();
    int halfBoard = (boardArea/2);
    int count = 0;
    while (halfBoard != count) {
        p = m_game.randomPoint();
        if (m_board[p.r][p.c] == '.') {
            m_board[p.r][p.c] = '#';
            count++;
        }
    }
}

/* This function clears the board so it is empty, ready to be populated with ships. */
void BoardImpl::unblock() {
    for (int r = 0; r < m_game.rows(); r++) {
        for (int c = 0; c < m_game.cols(); c++) {
            if (m_board[r][c] == '#') {
                m_board[r][c] = '.';
            }
        }
    }
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir) {
    for (int i = 0; i < m_ship.size(); i++) {
        if (shipId < 0) {
            return false;
        } else if (m_ship[i].shipSymbol == shipId) {
            return false;
        }
    }
    if (topOrLeft.r >= 0 && topOrLeft.r < m_game.rows() && topOrLeft.c >= 0 && topOrLeft.c < m_game.cols()) {
        if (dir == HORIZONTAL) {
            Point leftmost = topOrLeft;
            if (leftmost.c + m_game.shipLength(shipId) <= m_game.cols()) {
                for (int i = 0; i < m_game.shipLength(shipId); i++) {
                    if (m_board[leftmost.r][leftmost.c+i] != '.') {
                        return false;
                    }
                }
                for (int i = 0; i < m_game.shipLength(shipId); i++) {
                    if (m_board[leftmost.r][leftmost.c+i] == '.') {
                        m_board[leftmost.r][leftmost.c+i] = m_game.shipSymbol(shipId);
                    }
                }
                Ship placedShip{shipId, m_game.shipSymbol(shipId), m_game.shipLength(shipId), topOrLeft, dir};
                m_ship.push_back(placedShip);
                return true;
            }
        } if (dir == VERTICAL){
            Point topmost = topOrLeft;
            if (topmost.r + m_game.shipLength(shipId) <= m_game.rows()) {
                for (int i = 0; i < m_game.shipLength(shipId); i++) {
                    if (m_board[topmost.r+i][topmost.c] != '.') {
                        return false;
                    }
                }
                for (int i = 0; i < m_game.shipLength(shipId); i++) {
                    if (m_board[topmost.r+i][topmost.c] == '.') {
                        m_board[topmost.r+i][topmost.c] = m_game.shipSymbol(shipId);
                    }
                }
                Ship placedShip{shipId, m_game.shipSymbol(shipId), m_game.shipLength(shipId), topOrLeft, dir};
                m_ship.push_back(placedShip);
                return true;
            }
        }
    }
    return false;
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    if(m_ship[shipId].dir != dir || (m_ship[shipId].topOrLeft.r != topOrLeft.r && m_ship[shipId].topOrLeft.c != topOrLeft.c))
        return false;

    vector <Ship>:: iterator it = m_ship.begin();

    if (shipId > 0 && shipId < m_game.nShips()) {
        if (dir == HORIZONTAL) {
            Point leftmost = topOrLeft;
            for (int i = 0; i < m_game.shipLength(shipId); i++) {
                if (m_game.isValid(Point(leftmost.r, leftmost.c + i)) &&  m_board[leftmost.r][leftmost.c + i] == m_game.shipSymbol(shipId)) {
                    m_board[leftmost.r][leftmost.c + i] = '.';
                    return true;
                }
            }
            m_ship.erase(it);
        }
        if (dir == VERTICAL) {
            Point topmost = topOrLeft;
            for (int i = 0; i < m_game.shipLength(shipId); i++) {
                if (m_game.isValid(Point(topmost.r + i, topmost.c)) && m_board[topmost.r + i][topmost.c] == m_game.shipSymbol(shipId))
                {
                    m_board[topmost.r + i][topmost.c] = '.';
                    return true;
                }
            }
            m_ship.erase(it);
        }
    }
    return false;
}

void BoardImpl::display(bool shotsOnly) const {
    cout << "  ";
    for (int c = 0; c < m_game.cols(); c++) {
        cout << c;
    }
    cout << endl;
    for (int r = 0; r < m_game.rows(); r++) {
        cout << r << " ";
        for (int c = 0; c < m_game.cols(); c++) {
            if (shotsOnly) {
                if (m_board[r][c] != '.' && m_board[r][c] != 'X' && m_board[r][c] != 'o') {
                    cout << '.';
                }
                else {
                    cout << m_board[r][c];
                }
            }
            if (!shotsOnly) {
                cout << m_board[r][c];
            }
        }
        cout << endl;
    }
}


bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    if (!m_game.isValid(p)) {
        return false;
    }

    if (m_board[p.r][p.c] == 'o' || m_board[p.r][p.c] == 'X') {
        return false;
    }

    else if (m_board[p.r][p.c] == '.') {
        shotHit = false;
        shipDestroyed = false;
        m_board[p.r][p.c] = 'o';
        return true;
    }

    else
    {
        shotHit = true;
        for (int i = 0; i < m_game.nShips(); i++)
        {
            if (m_game.shipSymbol(i) == m_board[p.r][p.c])
            {
                shipId = i;
                m_ship[i].shipHealth--;
                if (m_ship[i].shipHealth == 0)
                    shipDestroyed = true;
                else
                    shipDestroyed = false;
            }
        }
        m_board[p.r][p.c] = 'X';
        return true;
    }

    return false;
}

bool BoardImpl::allShipsDestroyed() const
{
    for (int r = 0; r < m_game.rows(); r++)
    {
        for (int c = 0; c < m_game.cols(); c++)
        {
            if (m_board[r][c] != '.' && m_board[r][c] !='o' && m_board[r][c] !='X')
                return false;
        }
    }
    return true;
}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}

