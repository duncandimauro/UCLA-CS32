//StudentWorld.cpp
//Duncan Di Mauro
//SID 805163177

#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath), m_peach(nullptr), m_isGameWon(false), m_levelComplete(false) {}

int StudentWorld::init()
{
    int lvl_number = getLevel();

    //the only levels are 1, 2, and 3 with file names "level01.txt", "level02.txt", and "level03.txt"
    string lvl_name = "level0" + to_string(lvl_number) + ".txt";

    Level lvl(assetPath());

    Level::LoadResult(lvl.loadLevel(lvl_name));

    for (int x = 0; x < GRID_WIDTH; x++)
    {
        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            switch (lvl.getContentsOf(x, y))
            {
            case Level::GridEntry::empty:
                break;
            case Level::GridEntry::block:
                m_actorList.push_back(new Block(x, y, Block::none, this));
                break;
            case Level::GridEntry::flower_goodie_block:
                m_actorList.push_back(new Block(x, y, Block::flower, this));
                break;
            case Level::GridEntry::mushroom_goodie_block:
                m_actorList.push_back(new Block(x, y, Block::mushroom, this));
                break;
            case Level::GridEntry::star_goodie_block:
                m_actorList.push_back(new Block(x, y, Block::star, this));
                break;
            case Level::GridEntry::flag:
                m_actorList.push_back(new LevelEnder(this, IID_FLAG, x, y, false));
                break;
            case Level::GridEntry::goomba:
                m_actorList.push_back(new Goomba(x, y, this));
                break;
            case Level::GridEntry::koopa:
                m_actorList.push_back(new Koopa(x, y, this));
                break;
            case Level::GridEntry::mario:
                m_actorList.push_back(new LevelEnder(this, IID_MARIO, x, y, true));
                break;
            case Level::GridEntry::peach:
                m_peach = new Peach(x, y, this);
                m_actorList.push_back(m_peach);
                break;
            case Level::GridEntry::pipe:
                m_actorList.push_back(new Pipe(x, y, this));
                break;
            case Level::GridEntry::piranha:
                m_actorList.push_back(new Piranha(x, y, this));
                break;
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //Loop to give all actors a chance to do something
    for (list<Actor*>::iterator it = m_actorList.begin(); it != m_actorList.end(); it++) //loop through the list
    {
        (*it)->doSomethingIfAlive();
    }

    //Checks if the level has been completed or if game has been won
    if (m_levelComplete)
    {
        m_levelComplete = false;
        return endLevel(m_isGameWon);
    }

    //Loop to remove any dead actors after all have had a chance to doSomething
    for (list<Actor*>::iterator it = m_actorList.begin(); it != m_actorList.end();) //loop through the list
    {
        if (!(*it)->isAlive ()) //if actor is dead
        {
            if (*it == m_peach)
            {
                decLives();
                playSound(SOUND_PLAYER_DIE);
                return GWSTATUS_PLAYER_DIED;
            }
            else
            {
                delete* it; //removing the actor
                it = m_actorList.erase(it); //delete the pointer in the list & move "it" to next item
            }
        }
        else
        {
            it++;
        }
    }

    ostringstream oss;
    
    string StarPower = "";
    string ShootPower = "";
    string JumpPower = "";
    
    oss << "Lives: " << setw(1) << getLives();
    oss.fill('0');
    oss << "  Level: " << setw(2) << getLevel();
    oss << "  Points: " << setw(6) << getScore();
    if (m_peach->hasStarPower())
        StarPower = " StarPower!";
    if (m_peach->hasShootPower())
        ShootPower = " ShootPower!";
    if (m_peach->hasJumpPower())
        JumpPower = " JumpPower!";
    
    oss << StarPower + ShootPower + JumpPower;

    string text = oss.str();

    setGameStatText(text);

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::LevelCompleted()
{
    m_levelComplete = true;
}

void StudentWorld::GameIsWon()
{
    m_isGameWon = true;
}

int StudentWorld::endLevel(bool isGameWon)
{
    if (isGameWon)
    {
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    }
    else
    {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
}

void StudentWorld::FacePeach(Actor* self)
{
    if (dXfromPeach(self) > 0)
    {
        self->setDirection(180);
    }
    else if (dXfromPeach(self) < 0)
    {
        self->setDirection(0);
    }
}

double StudentWorld::dXfromPeach(Actor* self)
{
    return (self->getX() - peachX());
}

double StudentWorld::dYfromPeach(Actor* self)
{
    return (self->getY() - peachY());
}

//checks if an object at x, y, will overlap with an Actor "self"
bool StudentWorld::overlap(double x, double y, Actor* self)
{
    //(min x of self <= max x of obj) && (min x of obj <= max x of self)
    if ((self->getX() <= x + SPRITE_WIDTH - 1) && (x <= self->getX() + SPRITE_WIDTH - 1))
    {
        //(min y of self <= max y of object) && (min y of obj <= max y of self)
        if ((self->getY() <= y + SPRITE_HEIGHT - 1) && (y <= self->getY() + SPRITE_HEIGHT - 1))
        {
            return true;
        }
    }
    return false;
}

bool StudentWorld::overlapsWithPeach(Actor* self)
{
    if (self != m_peach)
    {
        if (overlap(peachX(), peachY(), self))
        {
            return true;
        }
    }
    return false;
}

bool StudentWorld::bonkOverlappingPeach(Actor* bonker)
{
    if (overlapsWithPeach(bonker))
    {
        m_peach->BonkMe(false);
        return true;
    }
    return false;
}

void StudentWorld::BonkOverlappingActors(Actor* bonker)
{
    for (list<Actor*>::iterator it = m_actorList.begin(); it != m_actorList.end(); it++) //loop through the list
    {
        if (*it != bonker)
        {
            if (overlap(bonker->getX(), bonker->getY(), *it)) //if they overlap
            {
                if (bonker == m_peach && m_peach->hasStarPower())
                    (*it)->BonkMe(true);
                else
                    (*it)->BonkMe(false);
            }
        }
    }
}

bool StudentWorld::DamageOverlappingActor(Actor* damager, bool damagedByPeach)
{
    for (list<Actor*>::iterator it = m_actorList.begin(); it != m_actorList.end(); it++) //loop through the list
    {
        if (*it != damager)
        {
            if (overlap(damager->getX(), damager->getY(), *it) && (*it)->isDamagable()) //if they overlap and the object is damageable
            {
                if (damagedByPeach)
                {
                    if (*it != m_peach) //Peach can't damage herself
                    {
                        (*it)->damageMe();
                        return true;
                    }
                }
                else //it is a hostile projectile so can only damage peach
                {
                    if (*it == m_peach)
                    {
                        (*it)->damageMe();
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//Checks if it is allowed for an object to move to coord x, y, or if it would be blocked
bool StudentWorld::spaceBlocked(double x, double y, Actor* self)
{
    for (list<Actor*>::iterator it = m_actorList.begin(); it != m_actorList.end(); it++) //loop through the list
    {
        if (*it != self && !(*it)->isCollidable()) //if the object we're checking is not collidable
        {
            if (overlap(x, y, *it)) //if they would collide
                return true;
        }
    }
    return false;
}

void StudentWorld::bonkOtherObjectHere(double x, double y, Actor* self)
{
    for (list<Actor*>::iterator it = m_actorList.begin(); it != m_actorList.end(); it++) //loop through all actors
    {
        if ((*it) != self)
        {
            if (overlap(x, y, *it)) //if the object is at this space
                (*it)->BonkMe(false); //false in case an enemy is near that space
        }
    }
    return;
}

bool StudentWorld::moveOrBonk(int x, int y, Actor* self)
{
    if (!spaceBlocked(x, y, self)) //if the space isn't blocked
    {
        self->moveTo(x, y);
        return true;
    }
    else
    {
        bonkOtherObjectHere(x, y, self);
        return false;
    }
}

void StudentWorld::addActor(Actor* a)
{
    m_actorList.push_front(a); //Actors do something the tick AFTER created
}

void StudentWorld::cleanUp()
{
    m_peach = nullptr;

    for (list<Actor*>::iterator it = m_actorList.begin(); it != m_actorList.end();)
    {
        delete* it; //removing the actor
        it = m_actorList.erase(it); //delete the pointer in the list & move "it" to next item
    }
}

double StudentWorld::peachX()
{
    return m_peach->getX();
}
double StudentWorld::peachY()
{
    return m_peach->getY();
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

void StudentWorld::setPeachHP(int hp) const
{
    m_peach->setHP(hp);
}
void StudentWorld::grantStarPower() const
{
    m_peach->gainStarPower(150);
}
void StudentWorld::grantShootPower() const
{
    m_peach->gainShootPower();
}
void StudentWorld::grantJumpPower() const
{
    m_peach->gainJumpPower();
}