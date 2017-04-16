//Jordan Mato 4/15/17
#include "Enemy.h"



void Enemy::Draw(MeshManagerSingleton* meshManager)
{
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
}

Enemy::Enemy()
{
}

Enemy::Enemy(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd) 
	: NPC(initialPosition, initialRotation, initialSize, initialStart, initialEnd)
{
	n_EnemyCount++;
}


Enemy::~Enemy()
{
}
