#pragma once
#include "Player.h"
#include "UILabels.h"
#include "Bullet.h"
#include "Enemy.h"

#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H


//Singleton class
class GameManager
{
	static GameManager* instance;

	//instance of other singleton classes
	Player* player;
	SystemSingleton* m_pSystem;
	MeshManagerSingleton* meshManager;

public:
	// Returns the instance of GameManager singleton and 
	static GameManager* GetInstance(MeshManagerSingleton* meshManager);

	// Deletes the instance of GameManager singleton if not already destroyed
	static void ReleaseInstance(void);

	void Update();

	//objects
	UILabels* ui;
	std::vector<Bullet> bulletList; // List of bullet objects the singleton creates and has control over
	std::vector<Enemy> enemyList; // List of enemy objects the singleton creates and has control over

#pragma region Game_Loop_Functions
	// called when player fails to reach round goal
	void ResetRound();

	void NewGame(void);

	void NextRound(void);

	void GameOver();
#pragma endregion

#pragma region Functions Called_By_NextRound()
	// decrements how many ammo the player starts with in current round
	// increments the goal the player needs to reach in current round
	void IncreaseChallenge();

	// increments the current score when player hits something
	void IncrementCurrentScore(int value);
#pragma endregion

	void MovePlayer(bool left, bool dir);

	// Used to detect a collision between enemies & bullets
	void DetectCollision();

#pragma region Other_Helper_Functions
	void UpdateTimer(void);

	// at the end of the timer, checks to see if player reached their goal
	void CheckGoal(void);

	void DisplayData();

	//returns a percentage based on time that is used for LERPING
	float Percentage(float scaleOriginalMin, float scaleOriginalMax, float mappedMin, float mappedMax);
#pragma endregion

#pragma region Destorying_Objects
	void DestroyEnemy(int enemy);

	void DestroyBullet(int bullet);
#pragma endregion

#pragma region Rendering_Objects
	void RenderEnemy(int enemy);

	void RenderBullet(int bullet);
#pragma endregion


#pragma region Properties
	//GOAL properties
	int GetGoal();
	void SetGoal(int value);

	// CURRENT SCORE properties
	int GetCurrentScore();
	void SetCurrentScore(int value);


	// TOTAL SCORE properties
	int GetTotalScore(void);
	void SetTotalScore(int value);

	//LIVES properties
	int GetLives(void);
	void SetLives(int value);


	// AMMO COUNT properties
	int GetAmmo(void);
	void SetAmmo(int value);

	// CURRENT TIMER properties
	void GameManager::SetCurrentTimer(float value);
#pragma endregion
	
private: 

	// Basic constructor
	GameManager(MeshManagerSingleton* mesh) {
		bulletList = std::vector<Bullet>();
		enemyList = std::vector<Enemy>();
		meshManager = mesh;
		//meshManager = MeshManagerSingleton::GetInstance();
		m_pSystem = SystemSingleton::GetInstance();
		player = Player::GetInstance(meshManager);
	};

	//// Copy constructor
	//GameManager(GameManager const& other) {
	//	instance = other.GetInstance();
	//};

	//// Copy assignment
	//GameManager& operator=(GameManager const& other) {
	//	instance = other.GetInstance();
	//};

	// Basic destructor
	~GameManager() {
		SafeDelete(ui);
		player->ReleaseInstance();
		ReleaseInstance();
	};

#pragma region variables
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
#pragma endregion

};
#endif
