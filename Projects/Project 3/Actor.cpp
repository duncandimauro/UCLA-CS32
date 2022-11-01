//Actor.cpp
//Duncan Di Mauro
//SID 805163177

#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


////////////////////////////////////////////////////////////////////////////////////////
//BASE CLASS - ACTOR IMPLEMENTATIONS

bool Actor::isAlive() const
{
	return m_alive;
}

void Actor::setDead()
{
	m_alive = false;
}

bool Actor::isCollidable() const
{
	return m_collidable;
}

bool Actor::isDamagable() const
{
	return m_damageable;
}

void Actor::reverseDir()
{
	if (getDirection() == left)
	{
		setDirection(right);
	}
	else
	{
		setDirection(left);
	}
}

void Actor::BonkMe(bool bonkerIsStarPowerPeach)
{
	return;
}

void Actor::damageMe()
{
	return;
}

bool Actor::AutoMoveOrTurn(double spacesPerTick)
{
	StudentWorld* world = getWorld();

	double pixelsToMove;
	if (getDirection() == right)
	{	
		pixelsToMove = 1;
	}
	else
	{
		pixelsToMove = -1;
	}

	pixelsToMove = spacesPerTick * pixelsToMove;

	if (!world->spaceBlocked(getX() + pixelsToMove, getY(), this)) //if the space isn't blocked
	{
		moveTo(getX() + pixelsToMove, getY()); //move the correct amt the correct direction
		return true;
	}
	else
	{
		reverseDir(); //otherwise automatically turn around
		return false;
	}
}

bool Actor::fall(double checkBelow, double moveDown)
{
	if (!m_world->spaceBlocked(getX(), getY() - checkBelow, this))
	{
		moveTo(getX(), getY() - moveDown); //fall moveDown pixels down
		return true;
	}
	return false;
}

StudentWorld* Actor::getWorld()
{
	return m_world;
}

void Actor::doSomethingIfAlive()
{
	if (m_alive)
	{
		doSomething();
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//PEACH IMPLEMENTATIONS

void Peach::setHP(int hp)
{
	m_hp = hp;
}

void Peach::TempInvincibility(int ticks)
{
	m_tempInvincibilityTicks = ticks;
	if (ticks > 0)
	{
		m_tempInvincible = true;
	}
	else
	{
		m_tempInvincible = false;
	}
}

void Peach::gainStarPower(int ticks)
{
	m_starPowerTicks = ticks;
	if (ticks > 0)
	{
		m_starPower = true;
	}
	else
	{
		m_starPower = false;
	}
}

void Peach::gainShootPower()
{
	m_firePower = true;
}

void Peach::gainJumpPower()
{
	m_jumpPower = true;
}

bool Peach::isInvincible() const
{
	if (m_starPower || m_tempInvincible)
		return true;
	else
		return false;
}

bool Peach::hasStarPower() const
{
	if (m_starPower)
		return true;
	else
		return false;
}


bool Peach::hasShootPower() const
{
	if (m_firePower)
		return true;
	else
		return false;
}

bool Peach::hasJumpPower() const
{
	if (m_jumpPower)
		return true;
	else
		return false;
}

void Peach::BonkMe(bool bonkerIsStarPowerPeach)
{
	if (!isInvincible())
	{
		m_hp--;
		TempInvincibility(10);
		m_firePower = false;
		m_jumpPower = false;
		
		if (m_hp > 0)
		{
			getWorld()->playSound(SOUND_PLAYER_HURT);
		}
		else
		{
			setDead();
		}
	}
}

void Peach::damageMe()
{
	BonkMe(false); //getting damaged does the same thing as being bonked
}

void Peach::doSomething()
{
	StudentWorld* world = getWorld();

	//CHECKING IF PEACH SHOULD BE INVINCIBLE
	if (m_starPower)
	{
		gainStarPower(m_starPowerTicks - 1); //Making her invincible for 1 less tick
	}
	if (m_tempInvincible)
	{
		TempInvincibility(m_tempInvincibilityTicks - 1);
	}

	if (m_recharge_time > 0)
	{
		m_recharge_time--;
	}

	world->BonkOverlappingActors(this); //bonks anything currently in contact with peach

	//CHECK IF FALLING//
	bool falling = false;
	if (m_remaining_jump_distance == 0)
	{
		falling = fall(4, 4); //checks if anything 4 pixels below blocking, then moves 4 pixels down
	}

	int key;
	//CHECK IF USER PRESS KEY//
	if (world->getKey(key))
	{
		switch (key)
		{
		case KEY_PRESS_UP:
			if (m_remaining_jump_distance == 0)
			{
				//if Peach is not falling and there is a block one space under her
				if (!falling && world->spaceBlocked(getX(), getY() - 1, this))
				{
					world->playSound(SOUND_PLAYER_JUMP);

					if (m_jumpPower)
					{
						m_remaining_jump_distance = 12;
					}
					else
					{
						m_remaining_jump_distance = 8;
					}
				}
			}
			break;
		case KEY_PRESS_LEFT:
			if (getDirection() != left)
			{
				reverseDir();
			}
			world->moveOrBonk(getX() - 4, getY(), this);
			break;
		case KEY_PRESS_RIGHT:
			if (getDirection() != right)
			{
				reverseDir();
			}
			world->moveOrBonk(getX() + 4, getY(), this);
			break;
		case KEY_PRESS_SPACE:
			if (hasShootPower())
			{
				if (m_recharge_time <= 0)
				{
					world->playSound(SOUND_PLAYER_FIRE);
					m_recharge_time = 8;

					double fourInFront;
					if (getDirection() == left)
						fourInFront = -4;
					else
					{
						fourInFront = 4;
					}
					world->addActor(new PeachFireball(this->getX() + fourInFront, this->getY(), getDirection(), world));
				}
			}
			break;
		}
	}

	//PEACH IS TRYING TO JUMP
	if (m_remaining_jump_distance > 0)
	{
		bool moved = world->moveOrBonk(getX(), getY() + 4, this);
		if (moved == true)
			m_remaining_jump_distance--;
		else
			m_remaining_jump_distance = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//BLOCK IMPLEMENTATIONS

void Block::doSomething()
{
	return;
}

void Block::BonkMe(bool bonkerIsStarPowerPeach)
{
	StudentWorld* world = getWorld();
	switch (m_goodie)
	{
	case none:
		world->playSound(SOUND_PLAYER_BONK);
		break;
	case flower:
		if (!m_released)
		{
			world->addActor(new Flower(this->getX(), this->getY() + 8, world));
			world->playSound(SOUND_POWERUP_APPEARS);
			m_released = true;
		}
		else
			world->playSound(SOUND_PLAYER_BONK);
		break;
	case mushroom:
		if (!m_released)
		{
			world->addActor(new Mushroom(this->getX(), this->getY() + 8, world));
			world->playSound(SOUND_POWERUP_APPEARS);
			m_released = true;
		}
		else
			world->playSound(SOUND_PLAYER_BONK);
		break;
	case star:
		if (!m_released)
		{
			world->addActor(new Star(this->getX(), this->getY() + 8, world));
			world->playSound(SOUND_POWERUP_APPEARS);
			m_released = true;
		}
		else
			world->playSound(SOUND_PLAYER_BONK);
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//PIPE IMPLEMENTATIONS

void Pipe::doSomething()
{
	return;
}

////////////////////////////////////////////////////////////////////////////////////////
//LEVEL_ENDER IMPLEMENTATIONS

void LevelEnder::doSomething()
{
	if (getWorld()->overlapsWithPeach(this))
	{
		getWorld()->increaseScore(1000);
		setDead();
		getWorld()->LevelCompleted();

		if (m_isMario)
			getWorld()->GameIsWon();
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//ENEMY IMPLEMENTATIONS

void Enemy::doSomething()
{
	if (getWorld()->bonkOverlappingPeach(this))
	{
		return;
	}

	StudentWorld* world = getWorld();

	double onePixel;
	if (getDirection() == right)
	{
		onePixel = 1;
	}
	else
	{
		onePixel = -1;
	}

	if ((!world->spaceBlocked(getX() + onePixel, getY(), this)) && (world->spaceBlocked(getX() + onePixel*(SPRITE_WIDTH), getY()-1, this)))
	{
		moveTo(getX() + onePixel, getY()); //move 1 pixel
	}
	else
	{
		reverseDir();
	}
}
void Enemy::BonkMe(bool bonkerIsStarPowerPeach)
{
	if (bonkerIsStarPowerPeach == true)
	{
		getWorld()->playSound(SOUND_PLAYER_KICK);
		getWorld()->increaseScore(100);
		setDead();
	}
}

void Enemy::damageMe()
{
	getWorld()->increaseScore(100);
	setDead();
}

////////////////////////////////////////////////////////////////////////////////////////
//KOOPA IMPLEMENTATIONS

void Koopa::damageMe()
{
	getWorld()->increaseScore(100);
	setDead();

	StudentWorld* world = getWorld();
	world->addActor(new Shell(this->getX(), this->getY(), this->getDirection(), world));
}

////////////////////////////////////////////////////////////////////////////////////////
//GOOMBA IMPLEMENTATIONS

//all implementations covered by enemy class

////////////////////////////////////////////////////////////////////////////////////////
//PIRANHA IMPLEMENTATIONS

void Piranha::doSomething()
{
	StudentWorld* world = getWorld();

	increaseAnimationNumber();
	
	//Checking if Bonk
	if (world->bonkOverlappingPeach(this))
	{
		return;
	}

	if (world->dYfromPeach(this) <= (1.5 * SPRITE_HEIGHT) && world->dYfromPeach(this) >= 0)
	{

		world->FacePeach(this);

		//Check Firing Delay
		if (m_fire_delay > 0)
		{
			m_fire_delay--;
			return;
		}
		double width = SPRITE_WIDTH;
		if (abs(world->dXfromPeach(this)) < (8 * width))
		{
			world->addActor(new PiranhaFireball(this->getX(), this->getY() + 1, getDirection(), world));
			world->playSound(SOUND_PIRANHA_FIRE);
			m_fire_delay = 40;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//GOODIE IMPLEMENTATIONS

void Goodie::doSomething()
{
	StudentWorld* world = getWorld();

	AutoMoveOrTurn(2);

	fall(2, 2);
	
	if (world->overlapsWithPeach(this))
	{
		givePower();
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//FLOWER IMPLEMENTATIONS

void Flower::givePower()
{
	getWorld()->increaseScore(50);
	getWorld()->grantShootPower();
	getWorld()->setPeachHP(2);
	setDead();
	getWorld()->playSound(SOUND_PLAYER_POWERUP);
}

////////////////////////////////////////////////////////////////////////////////////////
//MUSHROOM IMPLEMENTATIONS

void Mushroom::givePower()
{
	getWorld()->increaseScore(75);
	getWorld()->grantJumpPower();
	getWorld()->setPeachHP(2);
	setDead();
	getWorld()->playSound(SOUND_PLAYER_POWERUP);
}

////////////////////////////////////////////////////////////////////////////////////////
//STAR IMPLEMENTATIONS

void Star::givePower()
{
	getWorld()->increaseScore(100);
	getWorld()->grantStarPower();
	getWorld()->playSound(SOUND_PLAYER_POWERUP);
	setDead();
}

////////////////////////////////////////////////////////////////////////////////////////
//PROJECTILE IMPLEMENTATIONS

void Projectile::doSomething()
{

	StudentWorld* world = getWorld();
	
	fall(2, 2); 
	
	if (AutoMoveOrTurn(2) == false)
	{
		setDead(); //if the projectile needed to turn, ie it was blocked, setDead
		return;
	}

	//Projectiles are destroyed if they damage an actor
	if (m_isFromPeach)
	{
		if (world->DamageOverlappingActor(this, true))
			setDead();
	}
	else
	{
		if (world->DamageOverlappingActor(this, false))
			setDead();
	}
}

bool Projectile::fromPeach()
{
	return m_isFromPeach;
}