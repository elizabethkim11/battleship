//
//  Player.h
//  cs32proj3
//
//  Created by Elizabeth Kim on 5/4/22.
//

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <iostream>

class Board;
class Game;
class Point;

using namespace std;

class Player
{
public:
    Player(string nm, const Game& g);
    virtual ~Player();
    string name() const;
    const Game& game() const;
    virtual bool isHuman() const;
    virtual bool placeShips(Board& b) = 0;
    virtual Point recommendAttack() = 0;
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId) = 0;
    virtual void recordAttackByOpponent(Point p) = 0;
};

Player* createPlayer(string type, string nm, const Game& g);

#endif /* PLAYER_INCLUDED */
