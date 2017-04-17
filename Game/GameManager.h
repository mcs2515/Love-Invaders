#pragma once
#include "Player.h"
#include "UILabels.h"
#include "Bullet.h"
#include "Enemy.h"

#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H

class GameManager
{
public:
	GameManager(MeshManagerSingleton* meshManager);

	// Update method
	void Update();

	// Resets the game or round based on function
	void NextRound(void);
	void ResetRound(void);
	void NewGame(void);
	void GameOver(void);

	// Called when timer is down to 0; checks to see if the goal was met
	void CheckGoal(void);

	// Called to increase the challenge when moving onto the next round
	void IncreaseChallenge(void);

	// Called to increment the score
	void IncrementCurrentScore(int value);

	// Calculates lerp values for enemies / bullets
	float Percentage(float scaleOrginalMin, float scaleOriginalMax, float mappedMin, float mappedMax);

	// Displays UILabel data
	void DisplayData();

	// Called every update, updates the timer
	void UpdateTimer(void);

	// Used to detect a collision between enemies & bullets
	void DetectCollision(void);

	// Called whenever collision is detected; destroys enemy / bullet
	void DestroyEnemy(void);
	void DestroyBullets(void);

	// Is called by AppClassControls; used to set direction boolean
	void MovePlayer(bool left, bool dir);

	// PROPERTIES---------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Gets / sets the current goal for the round
	int GetGoal(void);
	void SetGoal(int value);

	// Sets the timer for the next round
	void SetCurrentTimer(float value);

	// Gets / sets the player's ammo for the next round
	int GetAmmo(void);
	void SetAmmo(int value);

	// Gets / sets the score for the round
	int GetCurrentScore(void);
	void SetCurrentScore(int value);

	// Gets / sets the overall score
	int GetTotalScore(void);
	void SetTotalScore(int value);

	// Gets / sets the number of remaining lives player has
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
	double fRunTime;
};
#endif
