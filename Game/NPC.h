#pragma once
//Jordan Mato 4/15/17

#include "MovableObjects.h"
class NPC :
	public MovableObjects
{
public:
	virtual void Draw();
	virtual void Move(float fTImer);
	NPC(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager);
	~NPC();
protected:
	vector3 v3_Start;
	vector3 v3_End;
};

