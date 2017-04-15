#pragma once
#include "RE\ReEngAppClass.h"

class MovableObjects
{
public:
	matrix4 modelMatrix;
	vector3 position;
	vector3 rotation;
	vector3 size;

	virtual void Move();
	MovableObjects(vector3 ip, vector3 ir, vector3 is);
	~MovableObjects();
};
