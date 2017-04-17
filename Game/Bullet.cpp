#include "Bullet.h"

void Bullet::Move(float fPercent)
{
	//lerp from start to end
	position = glm::lerp(v3_Start, v3_End, fPercent);

	if (fPercent >= 1.0f) //reached destination
	{
		//swap start and end
		vector3 temp = v3_Start;
		v3_Start = v3_End;
		v3_End = temp;
	}
}

void Bullet::Draw()
{
	meshManager->AddSphereToRenderList(modelMatrix, REBLUE, SOLID);
}
Bullet::Bullet(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager)
	: NPC(initialPosition, initialRotation, initialSize, initialStart, initialEnd, IMeshManager)
{

}


Bullet::~Bullet()
{
}
