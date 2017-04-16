#include "Bullet.h"



Bullet::Bullet()
{
}

void Bullet::Draw()
{
	meshManager->LoadModel("Lego\\Unikitty.bto", "Bullet");
}

Bullet::Bullet(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager)
	: NPC(initialPosition, initialRotation, initialSize, initialStart, initialEnd, IMeshManager)
{
}


Bullet::~Bullet()
{
}
