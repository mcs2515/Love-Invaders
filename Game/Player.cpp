#include "Player.h"
// PRIVATE - CONSTRUCTOR
Player::Player(vector3 ip, vector3 is) : MovableObjects(ip, true, is)
{
	m_iBullets = 5;

	// Creates the body for drawing
	m_pBody = new PrimitiveClass();
	m_pBody->GenerateSphere(1.0f, 5, RERED);
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