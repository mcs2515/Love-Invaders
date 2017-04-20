#include "GameManager.h"
GameManager* GameManager::GetInstance() {
	if (instance == nullptr) {
		instance = new GameManager();

	}
	return instance;
}

void GameManager::ReleaseInstance(void) {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

void GameManager::Update() {
	//Lets us know how much time has passed since the last call
	fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

									   //cumulative time
	fRunTime += fTimeSpan; //How much time has passed since the program started

	if (currentTimer > 0) {
		//draw E,P,B and background
		//move E,B
		//detect collision
		DetectCollision();

		DisplayData(); //display UI

		player->Draw();	// display Player; temporary

		UpdateTimer(); //update timer
	}
	else {
		CheckGoal();
	}
}

#pragma region Game_Loop_Functions
void GameManager::ResetRound() {
	//as long as player's hp is >0
	if (player->GetLives() > 0) {

		player->SetLives(GetLives() - 1); //player lose 1 health

		SetTotalScore(GetTotalScore() - GetCurrentScore()); //return to original score

		SetCurrentScore(0); //reset current score

		SetCurrentTimer(roundTimer); //seconds //reset current timer

		player->SetBullets(roundAmmo); //Ammo and Goal are the same for the current round
	}
	else {
		GameOver(); //if player health = 0, call GameOver
	}
}

void GameManager::NewGame(void) {

	fRunTime = 0.0f; //reset run time
	roundTimer = 60; //seconds

	SetLives(3); //reset lives

	SetTotalScore(0); //reset total score

	SetCurrentScore(0); //reset current score

	SetCurrentTimer(roundTimer); //reset current timer-seconds

								 //reset ammo count
	SetAmmo(20);
	roundAmmo = 20;

	SetGoal(5); //reset goal
}

void GameManager::NextRound(void) {
	SetTotalScore(GetTotalScore() + GetCurrentScore()); //increment total score

	SetCurrentScore(0); //reset current score

	SetCurrentTimer(roundTimer); //reset current timer-seconds

	IncreaseChallenge(); //increase game challenge
}

void GameManager::GameOver(){
	//destroy enemies
	for (int i = 0; i < enemyList.size(); i++) {
		DestroyEnemy(i);
	}

	//destroy bullets
	for (int i = 0; i < bulletList.size(); i++) {
		DestroyBullet(i);
	}

	//call new game if player wishes to continue
}
#pragma endregion

#pragma region Functions Called_By_NextRound()
void GameManager::IncreaseChallenge() {
	if (player->GetBullets() > 3) {

		int ranNum = rand() % 3; //get a new rando value

		roundAmmo = GetAmmo() + ranNum; //used for reseting round. 
		SetAmmo(GetAmmo() - ranNum); //decrement ammo

		ranNum = rand() % 3; //get a new rando value

		SetGoal(GetGoal() + ranNum); //increment goal
	}
}

void GameManager::IncrementCurrentScore(int value) {
	currentScore += value;
}
#pragma endregion

void GameManager::MovePlayer(bool left, bool dir) {
	if (left) {
		player->SetLeft(dir);
	}
	else {
		player->SetUp(dir);
	}
	player->Move();
}

void GameManager::DetectCollision(void)
{
}


#pragma region Other_Helper_Functions
void GameManager::UpdateTimer(void) {
	currentTimer -= fTimeSpan;
}

void GameManager::CheckGoal(void) {
	if (currentScore >= goal) {

		NextRound(); //player goes to a next round
	}
	else {

		ResetRound(); //player has to replay round
	}
}

void GameManager::DisplayData() {
	meshManager->PrintLine(ui->DisplayTotalScore(GetTotalScore())); //display total score

	meshManager->PrintLine(ui->DisplayGoal(GetGoal())); //display current round goal

	meshManager->PrintLine(ui->DisplayCurrentScore(GetCurrentScore())); //display current score

	meshManager->PrintLine(ui->DisplayAmmoCount(GetAmmo())); //display current bullet count

	meshManager->PrintLine(ui->DisplayCurrentTime(fRunTime));	// CHANGE FROM SYSTEM TIME TO CURRENT TIME LATER

																//display player lives
	meshManager->PrintLine(ui->DisplayLives(GetLives()));
}

float GameManager::Percentage(float scaleOriginalMin, float scaleOriginalMax, float mappedMin, float mappedMax) {
	float percentage = MapValue(static_cast<float>(fRunTime), scaleOriginalMin, scaleOriginalMax, mappedMin, mappedMax);

	return percentage;
}
#pragma endregion

#pragma region Destroying_Objects
void GameManager::DestroyEnemy(int enemy) {
	// destroy the enemy that we want
}

void GameManager::DestroyBullet(int bullet) {
	// destroy the bullet that we want
}
#pragma endregion

#pragma region Rendering_Objects
void GameManager::RenderEnemy(int enemy) {
	// render the enemy that we want
}

void GameManager::RenderBullet(int bullet) {
	// render the bullet that we want
}
#pragma endregion

#pragma region Properties
// GOAL properties
int GameManager::GetGoal() {
	return goal;
}
void GameManager::SetGoal(int value) {
	goal = value;
}

// CURRENT SCORE properties
int GameManager::GetCurrentScore() {
	return currentScore;
}
void GameManager::SetCurrentScore(int value) {
	currentScore = value;
}

// TOTAL SCORE properties
int GameManager::GetTotalScore() {
	return totalScore;
}
void GameManager::SetTotalScore(int value) {
	totalScore = value;
}

// LIVES properties
int GameManager::GetLives() {
	return player->GetLives();
}
void GameManager::SetLives(int value) {
	player->SetLives(value);
}

// AMMO COUNT properties
int GameManager::GetAmmo(void) {
	return player->GetBullets();
}
void GameManager::SetAmmo(int value) {
	player->SetBullets(value);
}

// CURRENT TIMER properties
void GameManager::SetCurrentTimer(float value) {
	currentTimer = value;
}
#pragma endregion
/*
GameManager::GameManager(void) {
	bulletList = std::vector<Bullet>();
	enemyList = std::vector<Enemy>();

	//meshManager = MeshManagerSingleton::GetInstance();
	m_pSystem = SystemSingleton::GetInstance();
	player = Player::GetInstance(meshManager);
	//player = new Player(vector3(0.0f), false, vector3(1.0f), meshManager);//Player::GetInstance(meshManager);
}

GameManager::GameManager(GameManager const& other) {
	instance = other.GetInstance();
}

GameManager & GameManager::operator=(GameManager const & other) {
	instance = other.GetInstance();
}

GameManager::~GameManager() {
	SafeDelete(ui);
	player->ReleaseInstance();
	ReleaseInstance();
}*/