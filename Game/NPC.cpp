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
	timer = 0;
}


NPC::~NPC()
{
}

vector3 NPC::GetStart()
{
	return v3_Start;
}

void NPC::SetStart(vector3 start)
{
	v3_Start = start;
}

vector3 NPC::GetEnd()
{
	return v3_End;
}

void NPC::SetEnd(vector3 end)
{
	v3_End = end;
}

float NPC::GetTime()
{
	return timer;
}

void NPC::TimeTick(float deltaTime)
{
	timer += deltaTime;
}
