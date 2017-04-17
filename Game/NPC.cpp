#include "NPC.h"



void NPC::Draw()
{
}

void Move(float fTImer)
{
}

NPC::NPC(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager)
	: MovableObjects(initialPosition, initialRotation, initialSize, IMeshManager)
{
	v3_Start = initialStart;
	v3_End = initialEnd;
}


NPC::~NPC()
{
}
