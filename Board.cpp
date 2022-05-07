//
//  Board.cpp
//  cs32proj3
//
//  Created by Elizabeth Kim on 5/4/22.
//

#include "Board.h"
#include "Game.h"
#include "Player.h"
#include <vector>

class BoardImpl
{
public:
    BoardImpl(const Game& g);
    ~BoardImpl();
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
    int nRows;
    int nCols;
    char m_board[][10];
};

/* Initialize a board. The parameter g refers to the game the board is being used in. Board
 member functions that need to know the number of rows or columns or the characteristics
 of ships will presumably ask the game object the board was constructed with. */
BoardImpl::BoardImpl(const Game& g)
: m_game(g) {
    nRows = g.rows();
    nCols = g.cols();
    
    for (int r = 0; r < nRows; r++) {
        for (int c = 0; c < nCols; c++) {
            m_board[r][c] = '.';
        }
    }
}

// destructor
BoardImpl::~BoardImpl() {
    
}

/* This function clears the board so it is empty, ready to be populated with ships. */
void BoardImpl::clear() {
    for (int r = 0; r < m_game.rows(); r++) {
        for (int c = 0; c < m_game.cols(); c++) {
            m_board[r][c] = '.';
        }
    }
}

/* For a board has R rows and C columns, this function blocks exactly ⌊RC/2⌋ randomly
 chosen positions on the board (i.e, half the positions). This function will be used only by
 the MediocrePlayer when placing ships on the board at the start of play. If a position is
 blocked, then that player may not place a ship in a way that occupies that location. */
void BoardImpl::block() {
    for (int r = 0; r < m_game.rows(); r++) {
        for (int c = 0; c < m_game.cols(); c++) {
            if (randInt(2) == 0) {
                m_board[r][c] = 'X';
            }
        }
    }
}

/* This function clears the board so it is empty, ready to be populated with ships. */
void BoardImpl::unblock() {
    for (int r = 0; r < m_game.rows(); r++) {
        for (int c = 0; c < m_game.cols(); c++) {
            if (m_board[r][c] == 'X') {
                m_board[r][c] = '.';
            }
        }
    }
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir) {
    
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir) {
    
}

void BoardImpl::display(bool shotsOnly) const {
    
}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId) {
    
}

bool BoardImpl::allShipsDestroyed() const {
    
}

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
