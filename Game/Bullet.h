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

	bool GetRenderVisibily(void);
	void SetRenderVisibility(bool value);
private:
	std::vector<vector3> MakeBulletCollisionBox(vector3 size);
	bool visible = false;

	bool returning; //used to check if it has bounced off the ground
};
#endif
