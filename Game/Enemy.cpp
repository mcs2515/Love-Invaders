//Jordan Mato 4/15/17
#include "Enemy.h"


Enemy::Enemy(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager)
	: NPC(initialPosition, initialRotation, initialSize, initialStart, initialEnd, IMeshManager)
{
}

void Enemy::Draw()
{

	modelMatrix = IDENTITY_M4;
	//only need draw for now
	meshManager->SetModelMatrix(modelMatrix);
	meshManager->AddSphereToRenderList(modelMatrix, REGREEN, SOLID);
}

void Enemy::Move(float fTimer)
{
	//lerp from start to end
	position = glm::lerp(v3_Start, v3_End, fTimer);

	if (fTimer>= 1.0f) //reached destination
	{
		//swap start and end
		vector3 temp = v3_Start;
		v3_Start = v3_End;
		v3_End = temp;
	}
	modelMatrix = IDENTITY_M4;
	modelMatrix *= glm::translate(position);
	if (!rotation)
	{
		modelMatrix *= glm::rotate(180.0f, REAXISY);
	}
	modelMatrix *= glm::scale(size);
}

Enemy::~Enemy()
{
}
