//Jordan Mato 4/15/17
#include "Enemy.h"


Enemy::Enemy(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager)
	: NPC(initialPosition, initialRotation, initialSize, initialStart, initialEnd, IMeshManager)
{
	n_EnemyCount++;
}

void Enemy::Draw()
{
<<<<<<< HEAD
=======

	meshManager->AddSphereToRenderList(modelMatrix, REGREEN, SOLID);

	modelMatrix = IDENTITY_M4;
>>>>>>> d88efdb201fdf11afa1241fadad446632cc26072
	//only need draw for now
	meshManager->SetModelMatrix(modelMatrix);
<<<<<<< HEAD
	meshManager->AddSphereToRenderList(modelMatrix, REGREEN, SOLID);
=======

>>>>>>> d88efdb201fdf11afa1241fadad446632cc26072
}

void Enemy::Move(float fPercent)
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
	modelMatrix = IDENTITY_M4;
	modelMatrix *= glm::translate(position);
	if (!rotation)
	{
		modelMatrix *= glm::rotate(180.0f, REAXISY);
	}
	modelMatrix *= glm::scale(size);
}

<<<<<<< HEAD

Enemy::Enemy(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager)
	: NPC(initialPosition, initialRotation, initialSize, initialStart, initialEnd, IMeshManager)
{
	n_EnemyCount++;
}

=======
>>>>>>> d88efdb201fdf11afa1241fadad446632cc26072

Enemy::~Enemy()
{
}
