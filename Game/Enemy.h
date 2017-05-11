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
	Enemy(vector3 initialPosition, boolean initialRotation, vector3 initialSize, vector3 initialStart, vector3 initialEnd, MeshManagerSingleton* IMeshManager, std::vector<vector3> bunkersList, ObjectType it, float startPercent, int inum);
	~Enemy();
	void Kill();
	int num;


private:
	std::vector<vector3> MakeEnemyCollisionBox(vector3 size);
	std::vector<vector3> bunkerLocs;
};
#endif
