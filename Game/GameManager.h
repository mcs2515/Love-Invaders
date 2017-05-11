#pragma once
#include "Player.h"
#include "UILabels.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Octree.h"

#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H


//Singleton class
class GameManager
{
	static GameManager* instance;

public:
	//instance of other singleton classes
	Player* player;
	SystemSingleton* m_pSystem;
	MeshManagerSingleton* meshManager;

	// Returns the instance of GameManager singleton and 
	static GameManager* GetInstance(MeshManagerSingleton* meshManager);

	// Deletes the instance of GameManager singleton if not already destroyed
	static void ReleaseInstance(void);

	void DisplayGameStates();

	void Update();

	//objects
	UILabels ui;
	std::vector<Bullet> bulletList; // List of bullet objects the singleton creates and has control over
	std::vector<Enemy> enemyList; // List of enemy objects the singleton creates and has control over
	std::vector<vector3> bunkerVecs;
	enum GameState { TITLE, CREDITS, PAUSE, GAME_PLAY, NEXT_ROUND, RESTART_ROUND, GAME_OVER };

	Octree octree = Octree(-20.0f, 20.0f, -20.0f, 20.0f, -20.0f, 20.0f, 5); // The octree

#pragma region Game_Loop_Functions
	// called when player fails to reach round goal
	void ResetRound();

	void NewGame(void);

	void NextRound(void);

	void GameOver();
	// Method used to reset all objects
	// PARAMS: number of player bullets, number of enemies, whether objects should be added or everything is just deleted
	void ResetObjects(int playerBullets, int numEnemies, bool addObjs);
#pragma endregion

#pragma region Functions Called_By_NextRound()
	// decrements how many ammo the player starts with in current round
	// increments the goal the player needs to reach in current round
	void IncreaseChallenge();

	// increments the current score when player hits something
	void IncrementCurrentScore(int value);

	// Resets the position of the player - also called in AppClassControls by key 'R'
	void ResetPlayer();
#pragma endregion

	void MovePlayer(int left, int up);

	// Used to detect a collision between enemies & bullets
	void DetectCollision();

	void FireBullet();

	void ResetOctree();

#pragma region Other_Helper_Functions
	void UpdateTimer(void);

	void DrawPlanes(void);

	void DrawBunkers(void);

	void SpawnEnemies(int numEnemies);

	// at the end of the timer, checks to see if player reached their goal
	void CheckGoal(void);

	void DisplayData();

	//returns a percentage based on time that is used for LERPING
	float Percentage(float scaleOriginalMin, float scaleOriginalMax, float mappedMin, float mappedMax);
#pragma endregion

#pragma region Destroying_Objects
	void DestroyEnemy(int enemy);

	void DestroyBullet(Bullet bullet);
#pragma endregion

#pragma region Rendering_Objects
	void RenderEnemy();

	void RenderBullets();
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
	int GetPlayerAmmo(void);
	void SetPlayerAmmo(int value);

	int GetGameState(void);
	void SetGameState(GameState value);

	// CURRENT TIMER properties
	void GameManager::SetCurrentTimer(float value);
#pragma endregion
	
private: 

	// Basic constructor
	GameManager(MeshManagerSingleton* mesh) {
		//gameState = TITLE;
		gameState = GAME_PLAY;
		bulletList = std::vector<Bullet>();
		enemyList = std::vector<Enemy>();
		ui =  UILabels();
		meshManager = mesh;

		//meshManager = MeshManagerSingleton::GetInstance();
		m_pSystem = SystemSingleton::GetInstance();
		player = Player::GetInstance(meshManager);
		bunkerVecs = std::vector<vector3>();
		bunkerVecs.push_back(vector3(-15.0f, 0.2f, -9.0f));
		bunkerVecs.push_back(vector3(-15.0f, 0.2f, 9.0f));
		bunkerVecs.push_back(vector3(15.0f, 0.2f, 9.0f));
		bunkerVecs.push_back(vector3(15.0f, 0.2f, -9.0f));
	}

	// Copy constructor
	GameManager(GameManager const& other) {
		instance = other.GetInstance(meshManager);
	}

	// Copy assignment
	GameManager& operator=(GameManager const& other) {
		instance = other.GetInstance(meshManager);
	}

	// Basic destructor
	~GameManager() {
		//SafeDelete(ui);
		player->ReleaseInstance();
		ReleaseInstance();
	}

#pragma region variables
	//goal
	int goal;

	vector3 humanSize;
	vector3 bulletSize;
	int enemyLSize = 6;

	//timer
	float roundTimer;
	float currentTimer;

	//score
	int totalScore;
	int currentScore;

	//keeps track of the ammo player starts off with at beginning of current round
	int roundAmmo;

	float fTimeSpan;
	float fRunTime;

    GameState gameState;

	matrix4 floorPlane;
	matrix4 floorBox; //optional
	matrix4 wall1Plane;
	matrix4 wall2Plane;

	matrix4 bunker;
	matrix4 bunker2;
	matrix4 bunker3;
	matrix4 bunker4;
#pragma endregion

};
#endif
