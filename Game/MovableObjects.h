#pragma once
#include "RE\ReEngAppClass.h"

class MovableObjects
{
public:
	matrix4 modelMatrix;
	vector3 position;
	//true = left/false = right
	boolean rotation;
	vector3 size;

	virtual void Move();
	MovableObjects(vector3 ip, boolean ir, vector3 is);
	~MovableObjects();
};
