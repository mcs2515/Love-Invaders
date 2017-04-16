#include "Player.h"

Player::Player()
{
	m_iBullets = 5;
}

Player::Player(vector3 ip, vector3 ir, vector3 is) : MovableObjects(ip, ir, is)
{
	m_iBullets = 5;
}


Player::~Player()
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