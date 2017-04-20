#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "MovableObjects.h"

class Player : MovableObjects
{
private:

	// Constructor
	Player(vector3 ip, bool ir, vector3 is, MeshManagerSingleton* IMeshManager) : MovableObjects(ip, ir, is, IMeshManager) {
		m_iBullets = 5;

		// Creates the body for drawing - Not used yet
		m_pBody = new PrimitiveClass();
		m_pBody->GenerateSphere(1.0f, 5, RERED);
	};

	// Destructor
	~Player() {
		delete m_pBody;
		ReleaseInstance();
	};

	bool m_bGoLeft;						// Getter / Setter -> Set in AppClassControls, used to determine which direction across the Z AXIS the player travels
	bool m_bGoUp;						// Getter / Setter -> Set in AppClassControls, used to determine which direction across the X AXIS the player travels
	int m_iLives;						// Getter / Setter -> Used by UILayer / GameManager to get and change how many lives the player has left
	int m_iBullets;						// Getter / Setter -> Used by UILayer / GameManager to get and change number of bullets player starts with
	const static int m_iMove = 1;		// Used to determine how much the player moves

	PrimitiveClass* m_pBody;

	static Player* instance;

public:

	/*// Equals / assignment operator - DON'T EVER USE THIS (because of the GetInstance)
	  Player& operator=(Player other) {
		m_bGoLeft = other.GetLeft();
		m_bGoUp = other.GetUp();
		instance = other.GetInstance(meshManager);
	};*/

	// Since there will only ever be one player, make it a singleton / instance
	  static Player* GetInstance(MeshManagerSingleton* IMeshManager) {
		if (instance == nullptr) {
			instance = new Player(vector3(0.0f, 0.0f, 0.0f), true, vector3(1.0f, 1.0f, 1.0f), IMeshManager);
		}
		return instance;
	};

	  void ReleaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}
	
	// Draws the Object based on m_pBody and inherited class's variables
	  void Draw() {
		  meshManager->AddSphereToRenderList(modelMatrix, RERED, SOLID);
	  };

	// Moves the player based on m_fMove
	  void Move() {

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
	  };

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

#endif // __PLAYER_H_
