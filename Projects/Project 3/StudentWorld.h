//StudentWorld.h
//Duncan Di Mauro
//SID 805163177

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetPath);
	~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();

	void LevelCompleted();
	void GameIsWon();
	void FacePeach(Actor* self);
	double dXfromPeach(Actor* self);
	double dYfromPeach(Actor* self);
	bool overlap(double x, double y, Actor* self);
	bool overlapsWithPeach(Actor* self);
	bool bonkOverlappingPeach(Actor* bonker);
	void BonkOverlappingActors(Actor* bonker); //only used by Peach to bonk overlapping actors
	bool DamageOverlappingActor(Actor* damager, bool damagedByPeach); //true if damaged, false otherwise
	bool spaceBlocked(double x, double y, Actor* self);
	bool moveOrBonk(int x, int y, Actor* self);
	void addActor(Actor* a);
	void setPeachHP(int hp) const;
	void grantStarPower() const;
	void grantShootPower() const;
	void grantJumpPower() const;

private:
	std::list<Actor*> m_actorList;
	Peach* m_peach;
	bool m_isGameWon;
	bool m_levelComplete;
	
	double peachX();
	double peachY();
	int endLevel(bool isGameWon);
	void bonkOtherObjectHere(double x, double y, Actor* self);

};

#endif // STUDENTWORLD_H_