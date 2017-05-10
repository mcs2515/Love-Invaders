#include "Player.h"
//Player* Player::instance = nullptr;
// PRIVATE - CONSTRUCTOR
Player::Player(vector3 ip, bool ir, vector3 is, MeshManagerSingleton* IMeshManager) : MovableObjects(ip, ir, is, IMeshManager, MakePlayerCollisionBox(is))
{
	m_iBullets = 5;
	m_iMove = 0.5f;

	// Creates the body for drawing - Not used yet
	m_pBody = new PrimitiveClass();
	m_pBody->GenerateSphere(1.0f, 5, RERED);
}
// PRIVATE - DESTRUCTOR

Player::~Player()
{
	delete m_pBody;
	ReleaseInstance();
}

Player* Player::GetInstance(MeshManagerSingleton* IMeshManager) {
	if (instance == nullptr) {
		instance = new Player(vector3(0.0f, 3.0f, 0.0f), true, vector3(1.0f), IMeshManager);
	}
	return instance;
}

void Player::ReleaseInstance() {

	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

// Draws the body - Not used yet, just adds a sphere to the render list
void Player::Draw()
{
	meshManager->AddSphereToRenderList(modelMatrix, RERED, SOLID);
	//meshManager->LoadModel("Love-Invaders\\ufo.obj", "UFO");
	SetModelMatrix(modelMatrix);

	//shadow
	shadowMatrix = glm::translate(position.x, 0.5f, position.z);
	shadowMatrix *= glm::scale(1.0f, 0.1f, 1.0f);
	meshManager->AddCylinderToRenderList(shadowMatrix, REBLACK, SOLID);

}

void Player::Move() {
	// Checks to see if the player is beyond certain margins - make sure they stay within certain areas
	bool passedPos = false;
	if (position.x > 16)
	{
		position.x = 16;
		passedPos = true;
	}
	else if (position.x < -17)
	{
		position.x = -17;
		passedPos = true;
	}
	if (position.z > 11)
	{
		position.z = 11;
		passedPos = true;
	}
	else if (position.z < -9)
	{
		position.z = -9;
		passedPos = true;
	}
	if (passedPos)
		return;
	// Updates the model matrix after moving
	modelMatrix = glm::translate(position);
	/*if (!rotation)
	{
	modelMatrix *= glm::rotate(180.0f, REAXISY);
	}*/
	modelMatrix *= glm::scale(size);
}

Bullet Player::FireBullet() {
	Bullet b = Bullet(position, false, vector3(0.1f), position, vector3(position.x, 0, position.z), meshManager);
	b.SetIsActive(true);
	return b;
}

std::vector<vector3> Player::MakePlayerCollisionBox(vector3 size)
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

