#pragma once
#include "Player.h"
#include "UILabels.h"

class GameManager
{
public:
	GameManager();

	void ResetRound(void);
	void ResetGame(void);
	
	
	//bool CheckGoal();

	void ChangeAmmoAmount(void);

	void ChangeGoalAmount(void);

	void IncrementCurrentScore(int value);

	void DisplayData(MeshManagerSingleton* meshManager);

	int GetGoal(void);
	void SetGoal(int value);

	void SetCurrentTimer(int value);

	int GetAmmo(void);
	void SetAmmo(int value);

	int GetCurrentScore(void);
	void SetCurrentScore(int value);


	int GetTotalScore(void);
	void SetTotalScore(int value);

	UILabels* ui;
	Player* player;

	~GameManager();

private: 
	//bullets
	int ammo;
	//goal
	int goal;
	//timer
	int currentTimer;
	//win/lose
	bool roundCleared;
	//score
	int totalScore;
	int currentScore;
};

