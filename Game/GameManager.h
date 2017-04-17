#pragma once
#include "Player.h"
#include "UILabels.h"
#include "Bullet.h"
#include "Enemy.h"

class GameManager
{
public:
	GameManager(MeshManagerSingleton* meshManager);

	void Update();

	void NextRound(void);
	void ResetRound(void);
	void NewGame(void);
	void GameOver(void);

	void CheckGoal(void);

	void IncreaseChallenge(void);

	void IncrementCurrentScore(int value);

	float Percentage(float scaleOrginalMin, float scaleOriginalMax, float mappedMin, float mappedMax);

	void DisplayData();

	void UpdateTimer(void);

	void DetectCollision(void);

	void DestroyEnemy(void);
	void DestroyBullets(void);

	int GetGoal(void);
	void SetGoal(int value);

	void SetCurrentTimer(float value);

	int GetAmmo(void);
	void SetAmmo(int value);

	int GetCurrentScore(void);
	void SetCurrentScore(int value);

	int GetTotalScore(void);
	void SetTotalScore(int value);

	void SetLives(int value);
	int GetLives(void);

	UILabels* ui;
	Player* player;
	Bullet* bullet;
	Enemy* enemy;
	
	SystemSingleton* m_pSystem;

	MeshManagerSingleton* meshManager;

	~GameManager();
	
private: 
	//goal
	int goal;

	//timer
	float roundTimer;
	float currentTimer;

	//score
	int totalScore;
	int currentScore;

	//keeps track of the ammo player starts off with at beginning of current round
	int roundAmmo;

	double fTimeSpan;
	static double fRunTime;
};

