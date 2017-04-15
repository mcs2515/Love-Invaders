#include "MovableObjects.h"

void MovableObjects::Move()
{
}

MovableObjects::MovableObjects(vector3 ip, vector3 ir, vector3 is)
{
	position = ip;
	rotation = ir;
	size = is;
	modelMatrix = IDENTITY_M4;
	modelMatrix *= position;
	modelMatrix *= rotation;
	modelMatrix *= size;
}


MovableObjects::~MovableObjects()
{
}