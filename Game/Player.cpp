#include "Player.h"

Player::Player()
{
	m_iBullets = 5;
	m_fMove = 5.0f;
}

Player::Player(vector3 ip, vector3 ir, vector3 is, MeshManagerSingleton* IMeshManager) : MovableObjects(ip, ir, is, IMeshManager)
{
	m_iBullets = 5;
	m_fMove = 5.0f;
}


Player::~Player()
{
}

void Player::Draw()
{
}

int Player::GetBullets()
{
	return m_iBullets;
}

void Player::SetBullets(int b)
{
	m_iBullets = b;
}

void Player::SetLeft(bool l)
{
	m_bGoLeft = l;
}

void Player::Move() {
	if (m_bGoLeft)
		position.x -= m_fMove;
	else
		position.x += m_fMove;

}