#include "Bullet.h"



Bullet::Bullet()
{
}

void Bullet::Draw()
{
	meshManager->SetModelMatrix(modelMatrix, 4);
}

Bullet::Bullet(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager)
	: NPC(initialPosition, initialRotation, initialSize, initialStart, initialEnd, IMeshManager)
{
	meshManager->LoadModel("Lego\\Unikitty.bto", "Bullet");
}


Bullet::~Bullet()
{
}
