#ifndef BULLET_H
#define BULLET_H

#include "RE\ReEngAppClass.h"
#include "NPC.h"

class Bullet : public NPC
{
public:
	void Draw();
	void Move(float fTImer);
	Bullet(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager);
	~Bullet();

	void Reset();
private:
	std::vector<vector3> MakeBulletCollisionBox(vector3 size);
<<<<<<< HEAD
=======
	bool visible = true;
>>>>>>> f5967d345c29ebe251c0669f52f20725fc811b2c

	bool returning; //used to check if it has bounced off the ground
};
#endif
