//
//  Player.cpp
//  cs32proj3
//
//  Created by Elizabeth Kim on 5/4/22.
//

#include <iostream>
#include "Player.h"

using namespace std;

class AwfulPlayer : public Player
{
public:
    AwfulPlayer(string nm, const Game& g);
    virtual ~AwfulPlayer();
    string name() const;
    const Game& game() const;
    virtual bool isHuman() const;
    virtual bool placeShips(Board& b) = 0;
    virtual Point recommendAttack() = 0;
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId) = 0;
    virtual void recordAttackByOpponent(Point p) = 0;
};

// Initialize a player whose name is nm. The parameter g refers to the game the player is being used in.
AwfulPlayer::AwfulPlayer(string nm, const Game& g)
: Player(nm, g) {
}

AwfulPlayer::~AwfulPlayer() {
    
}

// Return the name of the player.
string AwfulPlayer::name() const {
}

/* Return a constant reference to the game the player is being used in. (Derived classes can
 use this to find out the number of ships in the game, for example.) */
const Game& AwfulPlayer::game() const {
    
}

/* Return true if the player is a human, false otherwise. (This affects how an opponent's
 board will be displayed.) */
bool AwfulPlayer::isHuman() const {
    
}

/* This function must be implemented in concrete derived player classes. It must implement
 the logic required to place the ships on the board before game play begins. It returns true
 if all ships could be placed, and false otherwise (e.g., because the game parameters are
 such that there is no configuration of ships that will fit, or because a MediocrePlayer is
 unable to place all of the ships after 50 tries). */
bool AwfulPlayer::placeShips(Board& b) {
    
}

/* This function must be implemented in concrete derived player classes. It must return a
 point that indicates the position on the opponent's board that the player would like to
 attack next. */
Point AwfulPlayer::recommendAttack() {
    
}

void AwfulPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId) {
    
}

void AwfulPlayer::recordAttackByOpponent(Point p) {
    
}


class HumanPlayer : public Player
{
public:
    HumanPlayer(string nm, const Game& g);
    virtual ~HumanPlayer();
    string name() const;
    const Game& game() const;
    virtual bool isHuman() const;
    virtual bool placeShips(Board& b) = 0;
    virtual Point recommendAttack() = 0;
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId) = 0;
    virtual void recordAttackByOpponent(Point p) = 0;
};

// Initialize a player whose name is nm. The parameter g refers to the game the player is being used in.
HumanPlayer::HumanPlayer(string nm, const Game& g) {
}

HumanPlayer::~HumanPlayer() {
    
}

// Return the name of the player.
string HumanPlayer::name() const {
}

/* Return a constant reference to the game the player is being used in. (Derived classes can
 use this to find out the number of ships in the game, for example.) */
const Game& HumanPlayer::game() const {
    
}

/* Return true if the player is a human, false otherwise. (This affects how an opponent's
 board will be displayed.) */
bool HumanPlayer::isHuman() const {
    
}

/* This function must be implemented in concrete derived player classes. It must implement
 the logic required to place the ships on the board before game play begins. It returns true
 if all ships could be placed, and false otherwise (e.g., because the game parameters are
 such that there is no configuration of ships that will fit, or because a MediocrePlayer is
 unable to place all of the ships after 50 tries). */
bool HumanPlayer::placeShips(Board& b) {
    
}

/* This function must be implemented in concrete derived player classes. It must return a
 point that indicates the position on the opponent's board that the player would like to
 attack next. */
Point HumanPlayer::recommendAttack() {
    
}

void HumanPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId) {
    
}

void HumanPlayer::recordAttackByOpponent(Point p) {
    
}
