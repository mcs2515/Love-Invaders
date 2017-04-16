#pragma once
#include "RE\ReEngAppClass.h"
#include "NPC.h"

class Bullet : public NPC
{
public:
	Bullet();
	void Draw(MeshManagerSingleton* meshManager);
	Bullet(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd);
	~Bullet();
};

