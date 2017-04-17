#include "NPC.h"


<<<<<<< HEAD

void NPC::Draw()
{
}

void Move(float fTImer)
=======
void NPC::Draw()
>>>>>>> b2796f5a91a0aeea8976c76f2e6c1360e46d858f
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
