#include "NPC.h"


void NPC::Draw()
{
}

void NPC::Move(float fTimer)
{
}

NPC::NPC(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager, std::vector<vector3> vertexList)
	: MovableObjects(initialPosition, initialRotation, initialSize, IMeshManager, vertexList)
{
	v3_Start = initialStart;
	v3_End = initialEnd;
}


NPC::~NPC()
{
}
