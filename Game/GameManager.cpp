#include "GameManager.h"
Player* Player::instance = nullptr;

GameManager* GameManager::GetInstance(MeshManagerSingleton* mesh) {
	if (instance == nullptr) {
		instance = new GameManager(mesh);

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
		//DetectCollision();

		DisplayData(); //display UI

		//for loop for bullet rendering
		for (int i = 0; i < bulletList.size(); i++)
		{
			if (bulletList[i].GetRenderVisibily())
			{
				bulletList[i].TimeTick((float)fTimeSpan);
				float bulletLerp = MapValue(bulletList[i].GetTime(), 0.0f, 2.0f, 0.0f, 1.0f);
				bulletList[i].Move(bulletLerp);
				std::cout << bulletLerp << std::endl;
				bulletList[i].Draw();
			}
		}

		player->Draw();	// display Player; temporary
		RenderEnemy();

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
	bulletSize = vector3(0.2f, 0.2f, 0.2f);
	humanSize = vector3(1.0f,1.0f,1.0f);
	//bulletInitialPos = vector3();

	SetLives(3); //reset lives

	SetTotalScore(0); //reset total score

	SetCurrentScore(0); //reset current score

	SetCurrentTimer(roundTimer); //reset current timer-seconds

	//reset ammo count
	SetAmmo(20);
	roundAmmo = 20;

	//create bullet objects
	for (int i = 0; i < player->GetBullets(); i++) {
		bulletList.push_back(Bullet(vector3(0, 0, 0), false, bulletSize, vector3(0, 0, 0), vector3(0, 0, 0), meshManager));
	}

	//create bullet objects
	for (int i = 0; i < enemyLSize; i++) {
		enemyList.push_back(Enemy(vector3(0, 0, 0), false, humanSize, vector3(0, 0, 0), vector3(0, 0, 0), meshManager));
	}

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

void GameManager::MovePlayer(int left, int up) {
	// X AXIS movement
	if (left == -1)
		player->position.x -= static_cast<float>(player->GetMoveSpeed());
	else if (left == 1)
		player->position.x += static_cast<float>(player->GetMoveSpeed());

	// Z AXIS movement
	if (up == -1)
		player->position.z -= static_cast<float>(player->GetMoveSpeed());
	else if (up == 1)
		player->position.z += static_cast<float>(player->GetMoveSpeed());

	player->Move();
}

void GameManager::DetectCollision()
{
	for (int i = 0; i < bulletList.size(); i++)
	{
		for (int j = 0; j < enemyList.size(); j++)
		{
			if (bulletList[i].IsColliding(&enemyList[i]))
			{
				enemyList.erase(enemyList.begin()+i);
			}

			if (bulletList[i].IsColliding(player))
			{
				bulletList.erase(bulletList.begin() + i);
			}
		}
	}
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

	meshManager->PrintLine(ui->DisplayLives(GetLives()));	//display player lives
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
void GameManager::RenderEnemy() {
	// render the enemy
	for (int i = 0; i < enemyLSize; i++) {
		enemyList[i].Draw();
		enemyList[i].Move(Percentage(0, 25, 0, 5));
	}
}

void GameManager::RenderBullet(int bullet) {

	if (player->GetBullets() > 0) {
		if (bulletList[bullet].GetRenderVisibily()) {
			// render the bullet that we want
			bulletList[bullet].Draw();
		}
	}
}

#pragma endregion

#pragma region Properties
// GOAL properties
int GameManager::GetGoal() {return goal;}
void GameManager::SetGoal(int value) {goal = value;}

// CURRENT SCORE properties
int GameManager::GetCurrentScore() {return currentScore;}
void GameManager::SetCurrentScore(int value) {currentScore = value;}

// TOTAL SCORE properties
int GameManager::GetTotalScore() {return totalScore;}
void GameManager::SetTotalScore(int value) {totalScore = value;}

// LIVES properties
int GameManager::GetLives() {return player->GetLives();}
void GameManager::SetLives(int value) {player->SetLives(value);}

// AMMO COUNT properties
int GameManager::GetAmmo(void) {return player->GetBullets();}
void GameManager::SetAmmo(int value) {player->SetBullets(value);}

// CURRENT TIMER properties
void GameManager::SetCurrentTimer(float value) {currentTimer = value;}
#pragma endregion