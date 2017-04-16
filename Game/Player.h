#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "MovableObjects.h"

class Player : MovableObjects
{
private:
	bool m_bGoLeft;				// Setter -> Used to determine which direction across the X AXIS the player travels
	static int m_iBullets;		// Getter / Setter -> Used by UILayer / GameManager to get and change number of bullets player starts with
	const static float m_fMove;	// Used to determine how much the player moves

public:
	Player();
	Player(vector3 ip, vector3 ir, vector3 is);
	~Player();

	// Getter / Setter for m_iBullets
	int GetBullets();
	void SetBullets(int b);

	// Setter for m_bGoLeft
	void SetLeft(bool l);

	// Moves the player based on m_fMove
	virtual void Move();
};

#endif // __PLAYER_H_