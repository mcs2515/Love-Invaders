#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "MovableObjects.h"

class Player : public MovableObjects
{
protected:

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


	std::vector<vector3> MakePlayerCollisionBox(vector3 size);

public:

	/*// Equals / assignment operator - DON'T EVER USE THIS (because of the GetInstance)
	  Player& operator=(Player other) {
		m_bGoLeft = other.GetLeft();
		m_bGoUp = other.GetUp();
		instance = other.GetInstance(meshManager);
	};*/

	// Since there will only ever be one player, make it a singleton / instance
	  static Player* GetInstance(MeshManagerSingleton* IMeshManager);
	  void ReleaseInstance();
	
	// Draws the Object based on m_pBody and inherited class's variables
	  void Draw();

	// Moves the player based on m_fMove
	  void Move();


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
	  int GetMoveSpeed() { return m_iMove; };

	  vector3 SetPosition(vector3 p) { position = p; }
	  vector3 GetPosition() { return position; }
};

#endif // __PLAYER_H_
