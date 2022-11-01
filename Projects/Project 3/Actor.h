//Actor.h
//Duncan Di Mauro
//SID 805163177

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

////////////////////////////////////////////////////////////////////////////////////////
//BASE CLASS - ACTOR

class StudentWorld;
class Actor : public GraphObject
{
public:
	Actor(StudentWorld* sw, int imageID, int startX, int startY, int dir, int depth, double size, bool collidable, bool damageable)
		: GraphObject(imageID, startX, startY, dir, depth, size), m_world(sw), m_alive(true),
		m_collidable(collidable), m_direction(dir), m_damageable(damageable) {}

	bool isAlive() const;
	void setDead();
	bool isCollidable() const;
	bool isDamagable() const;
	void reverseDir();
	StudentWorld* getWorld();
	void doSomethingIfAlive();
	virtual void BonkMe(bool bonkerIsStarPowerPeach);
	virtual void damageMe();
	bool fall(double checkBelow, double moveDown);
	bool AutoMoveOrTurn(double spacesPerTick); //Moves the actor the correct amount if the space isn't blocked, else turns the actor

private:
	virtual void doSomething() = 0;
	StudentWorld* m_world;
	bool m_collidable;
	bool m_alive;
	int m_direction;
	bool m_damageable;
};

////////////////////////////////////////////////////////////////////////////////////////
//PEACH CLASS

class Peach : public Actor
{
public:
	Peach(int pos_x, int pos_y, StudentWorld* sw)
		: Actor(sw, IID_PEACH, pos_x* SPRITE_WIDTH, pos_y* SPRITE_HEIGHT, 0, 0, 1, true, true), 
		m_hp(1), m_remaining_jump_distance(0), m_firePower(false), m_jumpPower(false), m_starPower(false), 
		m_tempInvincible(false), m_starPowerTicks(0), m_tempInvincibilityTicks(0), m_recharge_time(0) {}

	
	void BonkMe(bool bonkerIsStarPowerPeach);
	void setHP(int hp);
	void gainStarPower(int ticks);
	void gainShootPower();
	void gainJumpPower();
	bool hasStarPower() const;
	bool hasShootPower() const;
	bool hasJumpPower() const;
	

private:
	void damageMe();
	bool isInvincible() const;
	void TempInvincibility(int ticks);
	void doSomething();
	int m_hp;
	int m_remaining_jump_distance;
	bool m_firePower;
	bool m_jumpPower;
	bool m_starPower;
	bool m_tempInvincible;
	int m_starPowerTicks;
	int m_tempInvincibilityTicks;
	int m_recharge_time;
	
};

////////////////////////////////////////////////////////////////////////////////////////
//BLOCK CLASS

class Block : public Actor
{
public:
	enum BlockType { none, flower, mushroom, star };

	Block(int pos_x, int pos_y, BlockType goodie, StudentWorld* sw)
		: Actor(sw, IID_BLOCK, pos_x* SPRITE_WIDTH, pos_y* SPRITE_HEIGHT, 0, 2, 1, false, false),
		m_goodie(goodie), m_released(false) {}

private:
	void BonkMe(bool bonkerIsStarPowerPeach);
	void doSomething();
	BlockType m_goodie;
	bool m_released;
};

////////////////////////////////////////////////////////////////////////////////////////
//PIPE CLASS

class Pipe : public Actor
{
public:
	Pipe(int pos_x, int pos_y, StudentWorld* sw)
		: Actor(sw, IID_PIPE, pos_x* SPRITE_WIDTH, pos_y* SPRITE_HEIGHT, 0, 2, 1, false, false) {}

private:
	void doSomething();
};

////////////////////////////////////////////////////////////////////////////////////////
//LEVEL_ENDER CLASS

class LevelEnder : public Actor
{
public:
	LevelEnder(StudentWorld* sw, int imageID, int pos_x, int pos_y, bool isMario)
		: Actor(sw, imageID, pos_x* SPRITE_WIDTH, pos_y* SPRITE_HEIGHT, 0, 1, 1, true, false), 
		m_isMario(isMario) {}

private:
	void doSomething();
	bool m_isMario;
};

////////////////////////////////////////////////////////////////////////////////////////
//ENEMY CLASS + DERIVED CLASSES

class Enemy : public Actor
{
public:
	Enemy(StudentWorld* sw, int imageID, int pos_x, int pos_y)
		: Actor(sw, imageID, pos_x* SPRITE_WIDTH, pos_y* SPRITE_HEIGHT, 180 * (rand() % 2), 0, 1, true, true) {}

private:
	virtual void doSomething();
	void BonkMe(bool bonkerIsStarPowerPeach);
	void damageMe();
};

class Koopa : public Enemy
{
public:
	Koopa(int pos_x, int pos_y, StudentWorld* sw)
		: Enemy(sw, IID_KOOPA, pos_x, pos_y) {}

private:
	void damageMe();
};

class Goomba : public Enemy
{
public:
	Goomba(int pos_x, int pos_y, StudentWorld* sw)
		: Enemy(sw, IID_GOOMBA, pos_x, pos_y) {}
};

class Piranha : public Enemy
{
public:
	Piranha(int pos_x, int pos_y, StudentWorld* sw)
		: Enemy(sw, IID_PIRANHA, pos_x, pos_y), m_fire_delay(0) {}

private:
	void doSomething();
	int m_fire_delay;
};

////////////////////////////////////////////////////////////////////////////////////////
//GOODIE CLASS + DERIVED CLASSES
class Goodie : public Actor
{
public:
	Goodie(StudentWorld* sw, int imageID, int pos_x, int pos_y)
		: Actor(sw, imageID, pos_x, pos_y, 0, 1, 1, true, false) {}

private:
	virtual void givePower() = 0;
	void doSomething();
};

class Flower : public Goodie
{
public:
	Flower(int pos_x, int pos_y, StudentWorld* sw)
		: Goodie(sw, IID_FLOWER, pos_x, pos_y) {}

private:
	void givePower();
};

class Mushroom : public Goodie
{
public:
	Mushroom(int pos_x, int pos_y, StudentWorld* sw)
		: Goodie(sw, IID_MUSHROOM, pos_x, pos_y) {}

private:
	void givePower();
};

class Star : public Goodie
{
public:
	Star(int pos_x, int pos_y, StudentWorld* sw)
		: Goodie(sw, IID_STAR, pos_x, pos_y) {}

private:
	void givePower();
};

////////////////////////////////////////////////////////////////////////////////////////
//PROJECTILE CLASS + DERIVED CLASSES

class Projectile : public Actor
{
public:
	Projectile(StudentWorld* sw, int imageID, int pos_x, int pos_y, int dir, bool fromPeach)
		: Actor(sw, imageID, pos_x, pos_y, dir, 1, 1, true, false), m_isFromPeach(fromPeach) {}
	
private:
	virtual void doSomething();
	bool fromPeach();
	bool m_isFromPeach;
};

class PiranhaFireball : public Projectile
{
public:
	PiranhaFireball(int pos_x, int pos_y, int dir, StudentWorld* sw)
		: Projectile(sw, IID_PIRANHA_FIRE, pos_x, pos_y, dir, false) {}
};

class PeachFireball : public Projectile
{
public:
	PeachFireball(int pos_x, int pos_y, int dir, StudentWorld* sw)
		: Projectile(sw, IID_PEACH_FIRE, pos_x, pos_y, dir, true) {}
};

class Shell : public Projectile
{
public:
	Shell(int pos_x, int pos_y, int dir, StudentWorld* sw)
		: Projectile(sw, IID_SHELL, pos_x, pos_y, dir, true) {}
};

#endif // ACTOR_H_