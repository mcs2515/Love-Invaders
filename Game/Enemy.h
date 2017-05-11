#ifndef ENEMY_H
#define ENEMY_H
//Jordan Mato 4/15/17
#include "NPC.h"
class Enemy :
	public NPC
{
public:
	void Draw();
	void Move(float fTimer);
<<<<<<< HEAD
	Enemy(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager, std::vector<vector3> bunkersList, ObjectType it, float startPercent);
=======
	Enemy(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager, std::vector<vector3> bunkersList, float startPercent, int inum);
>>>>>>> d9fa5c7f9c00c524d2916469fad88fa10d677615
	~Enemy();
	void Kill();
	int num;


private:
	std::vector<vector3> MakeEnemyCollisionBox(vector3 size);
	std::vector<vector3> bunkerLocs;
};
#endif
