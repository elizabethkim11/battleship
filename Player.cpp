//
//  Player.cpp
//  cs32proj3
//
//  Created by Elizabeth Kim on 5/4/22.
//

#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <stack>

using namespace std;

//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
  public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
  private:
    Point m_lastCellAttacked;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
 : Player(nm, g), m_lastCellAttacked(0, 0) {
}

bool AwfulPlayer::placeShips(Board& b)
{
      // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if ( ! b.placeShip(Point(k,0), k, HORIZONTAL))
            return false;
    return true;
}

Point AwfulPlayer::recommendAttack()
{
    if (m_lastCellAttacked.c > 0)
        m_lastCellAttacked.c--;
    else
    {
        m_lastCellAttacked.c = game().cols() - 1;
        if (m_lastCellAttacked.r > 0)
            m_lastCellAttacked.r--;
        else
            m_lastCellAttacked.r = game().rows() - 1;
    }
    return m_lastCellAttacked;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                     bool /* shotHit */, bool /* shipDestroyed */,
                                     int /* shipId */)
{
      // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
      // AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result(cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}

class HumanPlayer : public Player {
  public:
    HumanPlayer(string nm, const Game& g);
    virtual ~HumanPlayer() {}
    virtual bool isHuman() const {return true;}
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId) {}
    virtual void recordAttackByOpponent(Point p) {}
};

HumanPlayer::HumanPlayer(string nm, const Game& g)
: Player(nm, g) {
}

bool HumanPlayer::placeShips(Board& b) {
    int r = 0, c = 0;
    Direction dir;
    char chooseDir;
    bool shipsPlaced = false;
    cout << name() << " the Human must place " << game().nShips() << " ships." << endl;
        b.display(true);
    for (int i = 0; i < game().nShips(); i++){
        while (!shipsPlaced) {
            cout << "Enter h or v for direction of "<< game().shipName(i) << " (length " << game().shipLength(i) << "): ";
            cin >> chooseDir;
            cin.ignore(10000, '\n');
            if (chooseDir == 'h') {
                dir = HORIZONTAL;
                cout << "Enter row and column of the leftmost cell (e.g. 3 5): ";
                while (!getLineWithTwoIntegers(r, c)){
                    cout << "You must enter two integers." << endl;
                    break;
                }
                if (b.placeShip(Point(r, c), i, dir)) {
                    shipsPlaced = true;
                    b.display(false);
                }
                else if (!b.placeShip(Point(r,c), i, dir))
                {
                    cout << "The ship cannot be placed there." << endl;
                }
            }
            else if (chooseDir == 'v') {
                dir = VERTICAL;
                cout << "Enter row and column of the leftmost cell (e.g. 3 5): ";
                while (!getLineWithTwoIntegers(r, c)){
                    cout << "You must enter two integers." << endl;
                    break;
                }
                if (b.placeShip(Point(r, c), i, dir)) {
                    shipsPlaced = true;
                    b.display(false);
                }
                else if (!b.placeShip(Point(r,c), i, dir))
                {
                    cout << "The ship cannot be placed there." << endl;
                }
            }
            else {
                cout << "Direction must be h or v." << endl;
            }
        }
        shipsPlaced = false;
    }
    return true;
}

Point HumanPlayer::recommendAttack() {
    int r = 0, c = 0;
    cout << "Enter the row and column to attack (e.g., 3 5):" << endl;
    while (!getLineWithTwoIntegers(r, c)) {
        cout << "You must enter two integers." << endl;
        cout << "Enter the row and column to attack (e.g., 3 5):" << endl;
    }
    return Point(r, c);
}

//*********************************************************************
//  MediocrePlayer
//*********************************************************************

class MediocrePlayer : public Player
{
public:
    MediocrePlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p) {}
private:
    Point m_lastCellAttacked;
    bool placeShipsAux(Board& b, int shipId);
    int points[MAXROWS*MAXCOLS];
    int state = 1;
    int numAvailPts = 0;
    int otherBoard[MAXROWS][MAXCOLS]; // represent with 0 and 1 instead of . and X
};

MediocrePlayer::MediocrePlayer(string nm, const Game& g)
: Player(nm, g) {
    for (int r = 0; r < g.rows(); r++) {
        for (int c = 0; c < g.rows(); c++) {
            otherBoard[r][c] = 0; // all unhit 0
        }
    }
}

bool MediocrePlayer::placeShipsAux(Board& b, int shipId) {
    if (shipId == game().nShips()) { // base case, stops recursion
        return true;
    }
    for (int r = 0; r < game().rows(); r++) {
        for (int c = 0; c < game().cols(); c++) {
            if (b.placeShip(Point(r,c), points[shipId], HORIZONTAL)) { // try horizontal
                if (placeShipsAux(b, shipId + 1)) { // check next spot
                    return true;
                }
                else {
                    b.unplaceShip(Point(r,c), points[shipId], HORIZONTAL); // backtrack
                }
            }
            if (b.placeShip(Point(r,c), points[shipId], VERTICAL)) { // try vertical
                if (placeShipsAux(b, shipId + 1)) { // check next spot
                    return true;
                }
                else {
                    b.unplaceShip(Point(r,c), points[shipId], VERTICAL); // backtrack
                }
            }
        }
    }
    return false; // no points work, cannot place
}

bool MediocrePlayer::placeShips(Board& b) {
    int index = 0;
    // reorder ships in list from greatest to least
    for (int i = MAXROWS; i > 0; i--) {
        for (int j = 0; j < game().nShips(); j++) {
            if (game().shipLength(j) == i) {
                points[index] = j;
                index++;
            }
        }
    }
    for (int i = 0; i < 50; i++) { // mediocreplayer gets 50 tries
        b.block();
        if (placeShipsAux(b, 0)) // call auxillary function
        {
            b.unblock();
            return true;
        }
        b.unblock();
    }
    return false; // cant place in 50 tries
}

Point MediocrePlayer::recommendAttack() {
    int tryRows = 0;
    int tryCols = 0;
    if (state == 1) {
        while (1) { // keeps going
            tryRows = randInt(game().rows()); // randomly choose row
            tryCols = randInt(game().cols()); // randomly choose column
            if (otherBoard[tryRows][tryCols] == 0) // find random point that hasn't been attacked yet
                break;
        }
    }
    else if (state == 2) { // 4 points in each direction
        while (1) {
            if (randInt(2) != 0) { // randomly looks for point in row
                tryRows = m_lastCellAttacked.r;
                tryCols = m_lastCellAttacked.c + randInt(9) - 4;
            }
            if (randInt(2) == 0) // randomly looks for point in col
            {
                tryRows = m_lastCellAttacked.r + randInt(9) - 4;
                tryCols = m_lastCellAttacked.c;
            }
            if (tryRows < 0 || tryRows >= game().rows() || tryCols < 0 || tryCols >= game().cols()) { // in bounds
                continue;
            }
            if (otherBoard[tryRows][tryCols] == 0) // point available to attack
            {
                numAvailPts--; // one less point available to attack later
                break;
            }
        }
    }
    otherBoard[tryRows][tryCols] = 1; // mark point as attacked
    return Point(tryRows, tryCols);
}

void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId) {
    if (shotHit) {
        if (shotHit && shipDestroyed) { // was last shot in a ship aka ship sank
            state = 1; // go back to looking for random points, no more state 2 reference point
            return;
        }
        if (shotHit && state == 1) {
            m_lastCellAttacked = p; // reference point for state 2 points (4 in each direction)
            numAvailPts = 0;
            for (int i = 0; i < 9; i++) { // which points in this range work for attacking
                if (game().isValid(Point(m_lastCellAttacked.r-4+i, m_lastCellAttacked.c))) {
                    if (otherBoard[m_lastCellAttacked.r-4+i][m_lastCellAttacked.c] == 0) {
                        numAvailPts++;
                    }
                }
            }
            for (int i = 0; i < 9; i++) { // which points in this range work for attacking
                if (game().isValid(Point(m_lastCellAttacked.r, m_lastCellAttacked.c-4+i))) {
                    if (otherBoard[m_lastCellAttacked.r][m_lastCellAttacked.c-4+i] == 0) {
                        numAvailPts++;
                    }
                }
            }
            state = 2; // switch to 2 bc hit
        }
        if (shotHit && numAvailPts == 0) { // already tried all possible state 2 points
            state = 1;
        }
    }
}

//*********************************************************************
//  GoodPlayer
//*********************************************************************

class GoodPlayer : public Player
{
public:
    GoodPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p) {}
private:
    bool placeShipsAux(Board& b, int shipId);
    int numAvailPts = 0;
    Point m_lastCellAttacked;
    Point shipFront, shipBack;
    Direction dir;
    int otherBoard[MAXROWS][MAXCOLS];
    int points[MAXROWS*MAXCOLS];
    int state = 1;
};

GoodPlayer::GoodPlayer(string nm, const Game& g)
: Player(nm, g) {
    for (int r = 0; r < g.rows(); r++) {
        for (int c = 0; c < g.cols(); c++) {
            otherBoard[r][c] = 0; // all unhit, 0
        }
    }
}

bool GoodPlayer::placeShipsAux(Board& b, int shipId)
{
    if (shipId == game().nShips()) { // base case
        return true;
    }
    for (int r = 0; r < game().rows(); r++) {
        for (int c = 0; c < game().cols(); c++) {
            if (b.placeShip(Point(r,c), points[shipId], HORIZONTAL)) { // try horiz
                if (placeShipsAux(b, shipId + 1)) { // check next spot
                    return true;
                }
                else {
                    b.unplaceShip(Point(r,c), points[shipId], HORIZONTAL); // backtrack
                }
            }
            if (b.placeShip(Point(r,c), points[shipId], VERTICAL)) { // try vert
                if (placeShipsAux(b, shipId + 1)) { // check next spot
                    return true;
                }
                else {
                    b.unplaceShip(Point(r,c), points[shipId], VERTICAL); // backtrack
                }
            }
        }
    }
    return false; // if all points don't work, return false
}

bool GoodPlayer::placeShips(Board& b) { // same as mediocre
    int index = 0;
    for (int i = MAXROWS; i > 0; i--) { // reorder ships from greatest to least
        for (int j = 0; j < game().nShips(); j++) {
            if (i == game().shipLength(j)) {
                points[index] = j;
                index++;
            }
        }
    }
    for (int e = 0; e < 50; e++) { // mediocreplayer has 50 tries to place ships
        b.block();
        if (placeShipsAux(b, 0)) { // call auxiliary func
            b.unblock();
            return true;
        }
        b.unblock();
    }
    return false; // can't place after 50 tries
}

Point GoodPlayer::recommendAttack() {
    int tryRows = 0;
    int tryCols = 0;
    if (state == 1) {
        Point p;
        p = Point(tryRows, tryCols);
        for (int tryRows = 0; tryRows < game().rows(); tryRows++) {
            if (tryRows % 2 == 0) {
                for (int tryCols = 0; tryCols < game().cols(); tryCols += 2) {
                    if (otherBoard[tryRows][tryCols] == 0) {
                        otherBoard[tryRows][tryCols] = 1; // mark point as attacked
                        return Point(tryRows,tryCols);
                    }
                }
            }
            if (tryRows % 2 != 0) {
                for (int tryCols = 1; tryCols < game().cols(); tryCols += 2) {
                    if (otherBoard[tryRows][tryCols] == 0) {
                        otherBoard[tryRows][tryCols] = 1; // mark point as attacked
                        return Point(tryRows,tryCols);
                    }
                }
            }
        }
        // from original algorithm
        while (1) { // keeps going
            tryRows = randInt(game().rows()); // randomly choose row
            tryCols = randInt(game().cols()); // randomly choose column
            if (otherBoard[tryRows][tryCols] == 0) // find random point that hasn't been attacked yet
                break;
        }
    }
    else if (state == 2) { // 1 point in each direction
        while (1) {
            if (randInt(2) != 0) { // randomly looks for point in row
                tryRows = m_lastCellAttacked.r;
                tryCols = m_lastCellAttacked.c + randInt(9) - 4;
            }
            if (randInt(2) == 0) // randomly looks for point in col
            {
                tryRows = m_lastCellAttacked.r + randInt(9) - 4;
                tryCols = m_lastCellAttacked.c;
            }
            if (tryRows < 0 || tryRows >= game().rows() || tryCols < 0 || tryCols >= game().cols()) { // in bounds
                continue;
            }
            if (otherBoard[tryRows][tryCols] == 0) // point available to attack
            {
                numAvailPts--; // one less point available to attack later
                break;
            }
        }
    }
    otherBoard[tryRows][tryCols] = 1; // mark point as attacked
    return Point(tryRows, tryCols);
}

void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId) {
    if (shotHit) {
        if (shotHit && shipDestroyed) { // was last point shot in a ship aka ship sank
            state = 1; // go back to looking for random points, no more state 2 reference point
            return;
        }
        if (shotHit && state == 1) {
            m_lastCellAttacked = p; // reference point for state 2 points (1 in each direction)
            numAvailPts = 0;
            for (int i = 0; i < 9; i++) { // which points in this range work for attacking
                if (game().isValid(Point(m_lastCellAttacked.r-4+i, m_lastCellAttacked.c))) {
                    if (otherBoard[m_lastCellAttacked.r-4+i][m_lastCellAttacked.c] == 0) {
                        numAvailPts++;
                    }
                }
            }
            for (int i = 0; i < 9; i++) { // which points in this range work for attacking
                if (game().isValid(Point(m_lastCellAttacked.r, m_lastCellAttacked.c-4+i))) {
                    if (otherBoard[m_lastCellAttacked.r][m_lastCellAttacked.c-4+i] == 0) {
                        numAvailPts++;
                    }
                }
            }
            state = 2; // switch to 2 bc hit
        }
        if (shotHit && numAvailPts == 0) { // already tried all possible state 2 points
            state = 1;
        }
    }
}

//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };
    
    int pos;
    for (pos = 0; pos != sizeof(types)/sizeof(types[0])  && type != types[pos]; pos++);
    switch (pos)
    {
      case 0:  return new HumanPlayer(nm, g);
      case 1:  return new AwfulPlayer(nm, g);
      case 2:  return new MediocrePlayer(nm, g);
      case 3:  return new GoodPlayer(nm, g);
      default: return nullptr;
    }
}
