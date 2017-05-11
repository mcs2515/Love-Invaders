#include "Bullet.h"

void Bullet::Move(float fPercent)
{
	//lerp from start to end
	position = glm::lerp(v3_Start, v3_End, (fPercent * 3));

	if (fPercent >= 0.33f && !returning) //reached destination
	{
		//swap start and end
		vector3 temp = v3_Start;
		v3_Start = v3_End;
		v3_End = temp;
		timer = 0.0f;
		returning = true;
	}
	modelMatrix = IDENTITY_M4;
	modelMatrix *= glm::translate(position);
	if (!rotation)
	{
		modelMatrix *= glm::rotate(180.0f, REAXISY);
	}
	modelMatrix *= glm::scale(size);
}

std::vector<vector3> Bullet::MakeBulletCollisionBox(vector3 size)
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

void Bullet::Draw()
{
	//only need draw for now
	
	meshManager->SetModelMatrix(modelMatrix, std::to_string(num));
	//meshManager->AddSphereToRenderList(modelMatrix, REBLACK, SOLID);
	SetModelMatrix(modelMatrix);
	//RenderBox();
	//RenderSphere();
	if (!active)
	{

		modelMatrix *= glm::translate(vector3(-100, -100, -100));
		meshManager->SetModelMatrix(modelMatrix, std::to_string(num));
	}
}

Bullet::Bullet(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager, int inum)
	: NPC(initialPosition, initialRotation, initialSize, initialStart, initialEnd, IMeshManager, MakeBulletCollisionBox(initialSize), 0.0f)
{
	num = inum;
	returning = false;
	meshManager->LoadModel("Love\\Heart.obj", std::to_string(num));
	meshManager->SetModelMatrix(modelMatrix * glm::translate(vector3(-100, -100, -100)), std::to_string(num));
}


Bullet::~Bullet()
{
}

void Bullet::Reset()
{
	timer = 0;
	returning = false;
	active = false;
}

bool Bullet::GetReturn(void) { return returning; }
void Bullet::SetIsActive(bool value) { active = value; }
bool Bullet::GetIsActive(void) { return active; }
