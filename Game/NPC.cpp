#include "NPC.h"



NPC::NPC()
	: MovableObjects(vector3(0, 0, 0), true, vector3(1, 1, 1))
{
	//set dummy starter values
	v3_Start = vector3(0, 0, 0);
	v3_End = vector3(1, 1, 1);
}

void NPC::Draw()
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
