//Jordan Mato 4/15/17
#include "Enemy.h"


Enemy::Enemy(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager)
	: NPC(initialPosition, initialRotation, initialSize, initialStart, initialEnd, IMeshManager, MakeEnemyCollisionBox(initialSize))
{
	
}

void Enemy::Draw()
{
	//only need draw for now
	meshManager->SetModelMatrix(modelMatrix);
	meshManager->AddCubeToRenderList(modelMatrix, REGREEN, SOLID);
	SetModelMatrix(modelMatrix);
	RenderBox();
	RenderSphere();
}

void Enemy::Move(float percentage)
{
	//lerp from start to end
	position = glm::lerp(v3_Start, v3_End, percentage);

	if (percentage >= 1.0f) //reached destination
	{
		std::swap(v3_Start, v3_End);
		timer = 0;
	}

	modelMatrix = IDENTITY_M4;
	modelMatrix *= glm::translate(position);
	if (!rotation)
	{
		//modelMatrix *= glm::rotate(180.0f, REAXISY);
	}
	modelMatrix *= glm::scale(size);
}


std::vector<vector3> Enemy::MakeEnemyCollisionBox(vector3 size)
{
	std::vector<vector3> data;

	data.push_back(vector3(size.x, size.y, size.z));
	data.push_back(vector3(-size.x, size.y, size.z));
	data.push_back(vector3(size.x, -size.y, size.z));
	data.push_back(vector3(size.x, size.y, -size.z));
	data.push_back(vector3(-size.x, -size.y, size.z));
	data.push_back(vector3(size.x, -size.y, -size.z));
	data.push_back(vector3(-size.x, size.y, -size.z));
	data.push_back(vector3(-size.x, -size.y, -size.z));

	return data;
}


Enemy::~Enemy()
{
}
