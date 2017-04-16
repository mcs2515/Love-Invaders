#include "Bullet.h"



Bullet::Bullet()
{
}

void Bullet::Draw(MeshManagerSingleton* meshManager)
{
}

Bullet::Bullet(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd)
	: NPC(initialPosition, initialRotation, initialSize, initialStart, initialEnd)
{
}


Bullet::~Bullet()
{
}
