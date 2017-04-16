#include "MovableObjects.h"

void MovableObjects::Move()
{
}

MovableObjects::MovableObjects() {
	position = vector3(0.0f, 0.0f, 0.0f);
	rotation = vector3(0.0f, 0.0f, 0.0f);
	size = vector3(1.0f, 1.0f, 1.0f);
	modelMatrix = IDENTITY_M4;
}

MovableObjects::MovableObjects(vector3 ip, vector3 ir, vector3 is)
{
	position = ip;
	rotation = ir;
	size = is;
	modelMatrix = IDENTITY_M4;
	modelMatrix *= glm::translate(position);
	//modelMatrix *= glm::rotate(position);
	modelMatrix *= glm::scale(size);
}


MovableObjects::~MovableObjects()
{
}