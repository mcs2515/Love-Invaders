//Jordan Mato 4/15/17
#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(vector3 initialPosition, vector3 initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd) 
	: NPC(initialPosition, initialRotation, initialSize, initialStart, initialEnd)
{
}


Enemy::~Enemy()
{
}
