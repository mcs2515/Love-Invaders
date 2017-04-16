#pragma once
#include "Player.h"
#include "UILabels.h"
#include "Bullet.h"
#include "Enemy.h"

class GameManager
{
public:
	GameManager();

	void NextRound(void);
	void ResetRound(void);
	void ResetGame(void);
	
	
	bool CheckGoal(void);

	void ChangeAmmoAmount(void);

	void ChangeGoalAmount(void);

	void IncrementCurrentScore(int value);

	float Percentage(float valueToMap, float scaleOrginalMin, float scaleOriginalMax, float mappedMin, float mappedMax);

	void DisplayData(MeshManagerSingleton* meshManager);

	void GameOver(void);

	int GetGoal(void);
	void SetGoal(int value);

	void SetCurrentTimer(int value);

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

	~GameManager();
	
private: 
	//goal
	int goal;

	//timer
	int currentTimer;

	//score
	int totalScore;
	int currentScore;
};

