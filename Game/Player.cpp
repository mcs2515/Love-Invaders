#include "Player.h"
// PRIVATE - CONSTRUCTOR
Player::Player(vector3 ip, bool ir, vector3 is, MeshManagerSingleton* IMeshManager) : MovableObjects(ip, ir, is, IMeshManager)
{
	m_iBullets = 5;

	// Creates the body for drawing - Not used yet
	m_pBody = new PrimitiveClass();
	m_pBody->GenerateSphere(1.0f, 5, RERED);
}
// PRIVATE - DESTRUCTOR


// Draws the body - Not used yet, just adds a sphere to the render list
void Player::Draw()
{
	meshManager->AddSphereToRenderList(modelMatrix, RERED, SOLID);
}

void Player::Move() {
	// X AXIS movement
	if (m_bGoLeft)
		position.x -= static_cast<float>(m_iMove);
	else
		position.x += static_cast<float>(m_iMove);

	// Z AXIS movement
	if (m_bGoUp)
		position.z -= static_cast<float>(m_iMove);
	else
		position.z += static_cast<float>(m_iMove);

	// Updates the model matrix after moving
	modelMatrix = glm::translate(position);
	/*if (!rotation)
	{
		modelMatrix *= glm::rotate(180.0f, REAXISY);
	}*/
	modelMatrix *= glm::scale(size);

}