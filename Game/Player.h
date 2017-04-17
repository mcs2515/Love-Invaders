#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "MovableObjects.h"

class Player : MovableObjects
{
private:
	bool m_bGoLeft;						// Getter / Setter -> Set in AppClassControls, used to determine which direction across the Z AXIS the player travels
	bool m_bGoUp;						// Getter / Setter -> Set in AppClassControls, used to determine which direction across the X AXIS the player travels
	int m_iLives;						// Getter / Setter -> Used by UILayer / GameManager to get and change how many lives the player has left
	static int m_iBullets;				// Getter / Setter -> Used by UILayer / GameManager to get and change number of bullets player starts with
	const static int m_iMove = 5;		// Used to determine how much the player moves

	PrimitiveClass* m_pBody;
	
	// Constructor
	Player(vector3 ip, bool ir, vector3 is, MeshManagerSingleton* IMeshManager);
	// Equals / assignment operator - DON'T EVER USE THIS (becaues of the GetInstance)
	Player& operator=(Player other) {
		m_bGoLeft = other.GetLeft();
		m_bGoUp = other.GetUp();
		instance = other.GetInstance(meshManager);
	};
	// Destructor
	~Player();
public:
	static Player* instance;

	// Since there will only ever be one player, make it a singleton / instance
	static Player* GetInstance(MeshManagerSingleton* IMeshManager) {
		if (instance == nullptr) {
			instance = new Player(vector3(0.0f, 0.0f, 0.0f), true, vector3(1.0f, 1.0f, 1.0f), IMeshManager);
		}
		return instance;
	};

	static void ReleaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}

	// Draws the Object based on m_pBody and inherited class's variables
	void Draw();

	// Moves the player based on m_fMove
	virtual void Move();

	// Getter / Setter for m_bGoLeft
	bool GetLeft() { return m_bGoLeft; };
	void SetLeft(bool l) { m_bGoLeft = l; };
	// Getter / Setter for m_bGoUp
	bool GetUp() { return m_bGoUp; };
	void SetUp(bool u) { m_bGoUp = u; };
	// Getter / Setter for m_iLives
	int GetLives() { return m_iLives; };
	void SetLives(int l) { m_iLives = l; };
	// Getter / Setter for m_iBullets
	int GetBullets() { return m_iBullets; };
	void SetBullets(int b) { m_iBullets = b; };

};

Player* Player::instance = nullptr;

#endif // __PLAYER_H_