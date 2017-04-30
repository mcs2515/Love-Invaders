#include "Player.h"
//Player* Player::instance = nullptr;
// PRIVATE - CONSTRUCTOR
Player::Player(vector3 ip, bool ir, vector3 is, MeshManagerSingleton* IMeshManager) : MovableObjects(ip, ir, is, IMeshManager, MakePlayerCollisionBox(is))
{
	m_iBullets = 5;

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
		instance = new Player(vector3(0.0f, 3.0f, 0.0f), true, vector3(1.0f, 1.0f, 1.0f), IMeshManager);
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
	SetModelMatrix(modelMatrix);
	RenderBox();
	RenderSphere();
}

void Player::Move() {
	// Checks to see if the player is beyond certain margins
	/*bool passedPos = false;
	if (position.x > 10)
	{
		position.x = 10;
		passedPos = true;
	}
	else if (position.x < -10)
	{
		position.x = -10;
		passedPos = true;
	}
	if (position.z > 10)
	{
		position.z = 10;
		passedPos = true;
	}
	else if (position.z < -10)
	{
		position.z = -10;
		passedPos = true;
	}
	if (passedPos)
		return;*/
	// Updates the model matrix after moving
	modelMatrix = glm::translate(position);
	/*if (!rotation)
	{
	modelMatrix *= glm::rotate(180.0f, REAXISY);
	}*/
	modelMatrix *= glm::scale(size);
}

Bullet Player::FireBullet() {
	Bullet b = Bullet(position, false, vector3(0.3f), position, vector3(position.x, 0, position.z), meshManager);
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

