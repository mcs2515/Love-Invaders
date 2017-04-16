#include "MovableObjects.h"

void MovableObjects::Move()
{
}

MovableObjects::MovableObjects(vector3 ip, boolean ir, vector3 is)
{
	position = ip;
	rotation = ir;
	size = is;
	modelMatrix = IDENTITY_M4;
	modelMatrix *= glm::translate(position);
	if (!rotation)
	{
		modelMatrix *= glm::rotate(180.0f, REAXISY);
	}
	modelMatrix *= glm::scale(size);
}


MovableObjects::~MovableObjects()
{
}