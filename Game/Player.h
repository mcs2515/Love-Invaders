#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "MovableObjects.h"

class Player : MovableObjects
{
private:

	// Constructor
	Player(vector3 ip, bool ir, vector3 is, MeshManagerSingleton* IMeshManager);

	// Destructor
	~Player();

	bool m_bGoLeft;						// Getter / Setter -> Set in AppClassControls, used to determine which direction across the Z AXIS the player travels
	bool m_bGoUp;						// Getter / Setter -> Set in AppClassControls, used to determine which direction across the X AXIS the player travels
	int m_iLives;						// Getter / Setter -> Used by UILayer / GameManager to get and change how many lives the player has left
	int m_iBullets;						// Getter / Setter -> Used by UILayer / GameManager to get and change number of bullets player starts with
	const static int m_iMove = 1;		// Used to determine how much the player moves

	PrimitiveClass* m_pBody;

	static Player* instance;

public:

	// Equals / assignment operator - DON'T EVER USE THIS (because of the GetInstance)
	inline Player& operator=(Player other) {
		m_bGoLeft = other.GetLeft();
		m_bGoUp = other.GetUp();
		instance = other.GetInstance(meshManager);
	};

	// Since there will only ever be one player, make it a singleton / instance
	inline static Player* GetInstance(MeshManagerSingleton* IMeshManager) {
		if (instance == nullptr) {
			instance = new Player(vector3(0.0f, 0.0f, 0.0f), true, vector3(1.0f, 1.0f, 1.0f), IMeshManager);
		}
		return instance;
	};

	inline void ReleaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}
	
	// Draws the Object based on m_pBody and inherited class's variables
	void Draw();

	// Moves the player based on m_fMove
	void Move();

	// Getter / Setter for m_bGoLeft
	inline bool GetLeft() { return m_bGoLeft; };
	inline void SetLeft(bool l) { m_bGoLeft = l; };
	// Getter / Setter for m_bGoUp
	inline bool GetUp() { return m_bGoUp; };
	inline void SetUp(bool u) { m_bGoUp = u; };
	// Getter / Setter for m_iLives
	inline int GetLives() { return m_iLives; };
	inline void SetLives(int l) { m_iLives = l; };
	// Getter / Setter for m_iBullets
	inline int GetBullets() { return m_iBullets; };
	inline void SetBullets(int b) { m_iBullets = b; };

};

#endif // __PLAYER_H_
