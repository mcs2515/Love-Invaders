#include "Player.h"
// PRIVATE - CONSTRUCTOR
Player::Player(vector3 ip, vector3 is) : MovableObjects(ip, true, is)
{
	m_iBullets = 5;

<<<<<<< HEAD
	// Creates the body for drawing
	m_pBody = new PrimitiveClass();
	m_pBody->GenerateSphere(1.0f, 5, RERED);
=======
Player::Player(vector3 ip, vector3 ir, vector3 is, MeshManagerSingleton* IMeshManager) : MovableObjects(ip, ir, is, IMeshManager)
{
	m_iBullets = 5;
	m_fMove = 5.0f;
>>>>>>> dc2a3e68b1e1c4b55e6cb92de74ecdd52c4f59e5
}
// PRIVATE - DESTRUCTOR
Player::~Player()
{
	SafeDelete(m_pBody);
	ReleaseInstance();
}

// Draws the 
void Player::Draw()
{
}

void Player::Move() {
	// X AXIS movement
	if (m_bGoUp)
		position.x -= static_cast<float>(m_iMove);
	else
		position.x += static_cast<float>(m_iMove);

	// Z AXIS movement
	if (m_bGoLeft)
		position.z -= static_cast<float>(m_iMove);
	else
		position.z += static_cast<float>(m_iMove);

}